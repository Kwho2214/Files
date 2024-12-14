/*
 * File:   Protocol2.c
 * Author: kwho
 *
 * Created on February 5, 2024, 1:10 PM
 */


#include "xc.h"
#include <BOARD.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Protocol2.h"
#include "MessageIDs.h"
#include "circularbuffer.h"
#include <sys/attribs.h>
#include "uart.h"

#define HEAD 0xCC
#define TAIL 0xB9
#define END1 0x0D
#define END2 0x0A

pktbuff RXpacketbuff;
rxpT RXpacket;

extern cbuffer TXbuffer;
extern cbuffer RXbuffer;

int Protocol_Init(unsigned long baudrate){
    Uart_Init(baudrate);
    packetinit(&RXpacket);
    newPacketBuffer(&RXpacketbuff);
    return 0;
}

uint8_t Protocol_QueuePacket(rxpT *packet){
    if(packetbuff_isfull(&RXpacketbuff)){
        return 0;
    }
    packet_enqueue(&RXpacketbuff, packet);
    return 1;
}

/**
 * @Function int Protocol_GetInPacket(uint8_t *type, uint8_t *len, uchar *msg)
 * @param *type, *len, *msg
 * @return SUCCESS (true) or WAITING (false)
 * @brief Reads the next packet from the packet Buffer 
 * @author instructor W2022 */
int Protocol_GetInPacket(uint8_t *type, uint8_t *len, unsigned char *msg){
    if(packetbuff_isempty(&RXpacketbuff)){
        return 1;
    }
    rxpT packet;
    packetinit(&packet);
    packet = packet_dequeue(&RXpacketbuff);
    *type = packet.payLoad[0];
    *len = packet.len;
    for(int i = 0; i < packet.len; i++){
        msg[i] = packet.payLoad[i];
    }
    return 0;
}


/**
 * @Function int Protocol_SendDebugMessage(char *Message)
 * @param Message, Proper C string to send out
 * @return SUCCESS (true) or ERROR (false)
 * @brief Takes in a proper C-formatted string and sends it out using ID_DEBUG
 * @warning this takes an array, do <b>NOT</b> call sprintf as an argument.
 * @author mdunne */
int Protocol_SendDebugMessage(char *Message){
    unsigned char len = strlen(Message);
    len++; // increase len by b/c of ID in payload
    static unsigned char checksum = 0;
    for(int i = 0; i < len; i++){
        if(i == 0){
            checksum = Protocol_CalcIterativeChecksum(ID_DEBUG, checksum);
        }else {
            checksum = Protocol_CalcIterativeChecksum(Message[i - 1], checksum);
        }
    }
    PutChar(HEAD);
    PutChar(len);
    PutChar(ID_DEBUG);
    for(int i = 0; i < len - 1; i++){
        PutChar(Message[i]);
    }
    PutChar(TAIL);
    PutChar(checksum);
    PutChar(END1);
    PutChar(END2);
    
    checksum = 0;
    return 0;
}

/**
 * @Function int Protocol_SendPacket(unsigned char len, void *Payload)
 * @param len, length of full <b>Payload</b> variable
 * @param Payload, pointer to data
 * @return SUCCESS (true) or ERROR (false)
 * @brief composes and sends a full packet
 * @author instructor W2022 */
int Protocol_SendPacket(unsigned char len, unsigned char ID, void *Payload){
    static unsigned char checksum = 0;
    unsigned char *msg = (unsigned char *)Payload;
    unsigned char *x = (unsigned char *)Payload;
    if(ID == ID_LEDS_STATE){
        msg[0] = ID_LEDS_STATE;
    }
    for(int i = 0; i < len; i++){
        checksum = Protocol_CalcIterativeChecksum(msg[i], checksum);
    }
    PutChar(HEAD);
    PutChar(len);
    //ID inside payload
    for(int i = 0; i < len; i++){
        PutChar(x[i]);
    }
    PutChar(TAIL);
    PutChar(checksum);
    PutChar(END1);
    PutChar(END2);
    
    checksum = 0;
    return 0;
}

void __ISR(_UART1_VECTOR) IntUart1Handler(void){
    if(IFS0bits.U1RXIF){
        IFS0bits.U1RXIF = 0;
        unsigned char receivedChar = U1RXREG;
        enqueue(&RXbuffer, receivedChar);
        //PutChar(receivedChar); //to echo to the terminal
    }
    if(IFS0bits.U1TXIF && U1STAbits.TRMT){
        IFS0bits.U1TXIF = 0;
        while(!isempty(&TXbuffer)){
            char from_TXbuff = dequeue(&TXbuffer);
            U1TXREG = from_TXbuff;
        }
    }
}

/**
 @Function unsigned char Protocol_ReadNextID(void)
 * @param None
 * @return Reads the ID of the next available Packet
 * @brief Returns ID or 0 if no packets are available
 * @author instructor W2022 */
unsigned char Protocol_ReadNextPacketID(void){
    RXpacket = packet_dequeue(&RXpacketbuff);
    return RXpacket.ID;
}

unsigned int convertEndian(unsigned int *input_num){
    unsigned int num = *input_num;
    unsigned int num1 = ((num & 0xFF) << 24);
    unsigned int num2 = ((num & 0xFF0000) >> 8);
    unsigned int num3 = ((num & 0xFF00) << 8);
    unsigned int num4 = ((num & 0xFF000000) >> 24);
    num = num1 | num2 | num3 | num4;
    return num;
}

void Protocol_ParsePacket(rxpT *packet){
    TRISE = 0x00;
    
    if(packet->payLoad[0] == ID_LEDS_SET) {
        LEDS_SET(packet->payLoad[1]);
    }
    
    if(packet->payLoad[0] == ID_LEDS_GET){
        char LED_GET = LEDS_GET();
        Protocol_SendPacket(packet->len + 1, ID_LEDS_STATE, packet->payLoad);
    }
    
    static unsigned char payload_value[MAXPAYLOADLENGTH] = {0};
    static unsigned int converted_payload_value = 0;
    if(packet->ID == ID_PING){
        unsigned char *payload_ptr = packet->payLoad;
        for (int i = 1; i < packet->len; i++) {
            payload_value[i - 1] = payload_ptr[i];          
        }

        // Extract bytes from payload and reconstruct unsigned int
        converted_payload_value = 0;
        for (int i = 1; i < packet->len && i - 1 < sizeof(unsigned int) && i <= MAXPAYLOADLENGTH - 1; i++) {
            converted_payload_value |= ((unsigned int)payload_ptr[i]) << ((i - 1) * 8);
        }
        // Convert endianness
        converted_payload_value = convertEndian(&converted_payload_value);

        // Perform bit manipulation operations
        unsigned int val = converted_payload_value >> 1;
        
        //convert again
        converted_payload_value = convertEndian(&val);
        
        //Put ID back in to the payload_value that will be sent out
        payload_value[0] = ID_PONG;
        
        // Copy the bytes back to payload_value
        // start at 1 b/c ID is at 0
        for (int i = 1; i <= sizeof(unsigned int) && i <= MAXPAYLOADLENGTH - 1; i++) {
            payload_value[i] = (converted_payload_value >> ((i - 1) * 8)) & 0xFF;
        }
        Protocol_SendPacket(packet->len, ID_PONG, payload_value);
    }
}

void flushPacketBuffer(){
    RXpacketbuff.head = 0;
    RXpacketbuff.tail = 0;
    RXpacketbuff.overflow_count = 0;
}

void packetinit(rxpT *packet){
    packet->ID = 0;
    packet->checkSum = 0;
    packet->len = 0;
}

uint8_t BuildRxPacket (rxpT *rxPacket, unsigned char receivebyte){ // changed RXpacket param!
    static uint8_t state = 0;
    static int byte_count = 0;
    static unsigned char currChecksum = 0;
    
    //unsigned char receivebyte;
    
    //receivebyte = GetChar();
    
    switch(state){
        //at if we got the head
        case 0:
            if(receivebyte == HEAD){
                state = 1;
            }else if(receivebyte == 0xfe){
                receivebyte = HEAD;
                state = 1;
            }else{
                break;
            }
            break;
        //at length of packet
        case 1:
            rxPacket->len = receivebyte;
            state = 2;
            break;
        //at payload
        case 2:
            rxPacket->payLoad[byte_count] = receivebyte;
            byte_count++;
            currChecksum = Protocol_CalcIterativeChecksum(receivebyte, currChecksum);
            if(byte_count >= rxPacket->len){
                //set ID to the first byte of the payload
                rxPacket->ID = rxPacket->payLoad[0];
                state = 4;
            }
            break;
        //at tail;
        case 3:
            if(receivebyte == TAIL){
                state = 4;
            }
            break;
        //checksum
        case 4:
            //if the checksum ive been calculating is equal to what I got from getchar
            if(currChecksum == receivebyte){
                rxPacket->checkSum = currChecksum;
                state = 5;
            }
            break;
        //got "\r"
        case 5:
            if(receivebyte == END1){
                state = 6;
            }
            break;
        //got "\n"
        case 6:
            if(receivebyte == END2){
                currChecksum = 0;
                byte_count = 0;
                state = 0;
                return SUCCESS;
            }
            break;
    }
    return 0;
}

unsigned char Protocol_CalcIterativeChecksum(unsigned char charIn, unsigned char curChecksum){
    curChecksum = (curChecksum >> 1) | (curChecksum << 7);
    curChecksum += charIn;
    return curChecksum;
}

int main(void) {
    unsigned char get_byte;
    uint8_t *type = malloc(sizeof(uint8_t));
    uint8_t *len = malloc(sizeof(uint8_t));
    unsigned char msg[MAXPAYLOADLENGTH] = {0};// Define a buffer for the payload
    BOARD_Init();
    LEDS_INIT();
    
    // Initialize UART
    unsigned long baudRate = 115200;
    Protocol_Init(baudRate);

    
    // Get compilation date and time
//    const char *compile_date = __DATE__;
//    const char *compile_time = __TIME__;
//    char debug_message[1024];
//    sprintf(debug_message, "This is my debug message. Made on %s at %s", compile_date, compile_time);
//    Protocol_SendDebugMessage(debug_message);
    
    while(true){
        if(isempty(&RXbuffer)){
            continue;
        }
        get_byte = GetChar();
        if(BuildRxPacket(&RXpacket, get_byte) == SUCCESS){
            
            Protocol_QueuePacket(&RXpacket);
            Protocol_GetInPacket(type, len, msg);
            
            Protocol_ParsePacket(&RXpacket);
        }
    }
    return 0;
}
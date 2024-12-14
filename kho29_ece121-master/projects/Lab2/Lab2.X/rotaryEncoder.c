#include "xc.h"
#include "BOARD.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/attribs.h>
#include "Protocol2.h"
#include "MessageIDs.h"
#include "FreeRunningTimer.h"
#include "RotaryEncoder.h"

#define SYSTEM_CLOCK 80000000L
#define PB_CLOCK SYSTEM_CLOCK/2

int RotaryEncoder_Init(char interfaceMode){
    //SPI init
    //disable all interrupts
    IEC1bits.SPI2RXIE = 0;
    IEC1bits.SPI2TXIE = 0;
    
    //Enable master mode
    SPI2CONbits.MSTEN = 1;
    //Disable slave
    SPI2CONbits.SSEN = 0;
    
    //Setting SPI to mode 1 which samples at falling edge
    SPI2CONbits.CKE = 0;
    SPI2CONbits.CKP = 0;
    SPI2BRG = (PB_CLOCK / (2 * 10000000)) - 1;
    
    SPI2CONbits.MODE16 = 1;
    SPI2CONbits.MODE32 = 0;
    
    // Enable SPI module
    SPI2CONbits.ON = 1; 
    
    //Removed IO shield and using the uno32 board pins
    //Look at uC32 reference manual 
    // Configure SS, MOSI, and SCK pins as outputs
    TRISGbits.TRISG9 = 0; // SS pin as output
    TRISGbits.TRISG7 = 1; // MISO pin as input
    PORTGbits.RG9 = 1;
    TRISGbits.TRISG6 = 0; // SCK2 pin as output
    TRISGbits.TRISG8 = 0; // MOSI pin as output
    
    return 1;
}

unsigned short RotaryEncoder_ReadRawAngle(void){
    //doing spi stuff
    //chip select low
    //writing to buffer
    //wait and read data
    //chip select back to high
    
    PORTGbits.RG9 = 0; //SS pin    
    SPI2BUF = 0xFFFF;   //command to read
    while(!SPI2STATbits.SPIRBF); // Wait for receive buffer to fill up
    unsigned short g = SPI2BUF;    
    PORTGbits.RG9 = 1;
    
    PORTGbits.RG9 = 0;
    SPI2BUF = 0xFFFF;
    while(!SPI2STATbits.SPIRBF);
    unsigned short angle = SPI2BUF;
    PORTGbits.RG9 = 1;
   
    return (angle & 0x3FFF);
}

int main(void){
    BOARD_Init();
    unsigned long baudRate = 115200;
    Protocol_Init(baudRate);    
    RotaryEncoder_Init(ENCODER_BLOCKING_MODE);
    char str[16];
    unsigned char arr[2];
    
    unsigned int mi = FreeRunningTimer_GetMilliSeconds();
    
    while(true){
        if(mi % 10 == 0){
            unsigned short angle = RotaryEncoder_ReadRawAngle();
            unsigned char x = angle >> 8;
            unsigned char y = angle & 0xFF;
            arr[1] = x;
            arr[0] = y;
    //        sprintf(str, "%d", angle);
    //        Protocol_SendDebugMessage(str);

            Protocol_SendPacket(0x3, ID_ROTARY_ANGLE, arr);
        }
    }
    return 0;
}
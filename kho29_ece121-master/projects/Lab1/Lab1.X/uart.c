/*
 * File:   uart.c
 * Author: kwho
 *
 * Created on January 22, 2024, 2:17 PM
 */


#include "xc.h"
#include <BOARD.h>
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "circularbuffer.h"
#include <sys/attribs.h>
#include "Protocol2.h"

cbuffer TXbuffer;
cbuffer RXbuffer;

void Uart_Init(unsigned long baudRate){
    cbuffer TXbuffer;
    cbuffer RXbuffer;
    //clearing control registers
    U1MODE = 0;
    U1STA = 0;
    U1BRG = 0;
    U1TXREG = 0;
    U1RXREG = 0;
    
    //setting U1BRG to 115200
    U1BRG = (Fpb / (16 * baudRate)) - 1;
    
    //8 N 1 uart
    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;
    
    U1MODEbits.SIDL = 0;    // 0 = continue operation in idle mode
    U1MODEbits.IREN = 0;    // 0 = IrDA disable
    U1MODEbits.RTSMD = 0;   // 0 = Flow control mode
    U1MODEbits.UEN = 0;     // 0 = enable UxTX and UxRX
    U1MODEbits.LPBACK = 0;  // 0 = disable loopback mode
    U1MODEbits.BRGH = 0;    // 1 = enable high baud rate
    U1MODEbits.RXINV = 0;   // 0 = does not invert RX
    U1MODEbits.ABAUD = 0;   // 0 = baude rade measurment is disable or complete
    U1MODEbits.ON = 1;      //enable uart1
    U1MODEbits.WAKE = 1;    //enable wake up on start;
    
    IPC6bits.U1IP = 6;      //set interrupt priority 
    IPC6bits.U1IS = 0;      //sets interrupt sub priority
    
    U1STAbits.UTXEN = 1;    //enable UART1 transmit
    U1STAbits.URXEN = 1;    //enable UART1 receive
    
    IEC0bits.U1RXIE = 1;    //enable interrupts for receiver reg
    IEC0bits.U1TXIE = 1;    //enable interrupts for transmitter reg

    U1STAbits.URXISEL = 0;  //00 = Interrupt flag bit is asserted while receive buffer is not empty
    U1STAbits.UTXISEL = 0;  //00 = Interrupt is generated and asserted while the transmit buffer contains at least one empty space
    
    newbuffer(&TXbuffer);
    newbuffer(&RXbuffer);
}

int PutChar(char ch){
    int x = enqueue(&TXbuffer, ch);
    IFS0bits.U1TXIF = 1;
    return x;
}

unsigned char GetChar(void){
    unsigned char val;
    val = dequeue(&RXbuffer);
    return val;
}

void _mon_putc(char c){
    PutChar(c);
}


//part2
//int main(void)
//{   
//    BOARD_Init();
//    //setting U1BRG to 115200
//    unsigned long baudeRate = 115200;
//    Uart_Init(baudeRate);
//
//    setbuf(stdout, NULL);
//    printf("HELLO WORLD!\r\n");
//    fflush(stdout);
//    printf("My name is Jason Ho\r\n");
//    fflush(stdout);
//    return 0;
//}

//part1
//int main(void){
//       //testing buffer
//    newbuffer(&TXbuffer);
//    enqueue(&TXbuffer, 'c');
//    for(int i = 1; i < 15; i++){
//        enqueue(&TXbuffer, 'd');
//    }
////    int y;
//    char check = dequeue(&TXbuffer);
//    char x;
//    for(int i = 1; i < 15; i++){
//        x = dequeue(&TXbuffer);
//    }
////    setbuf(stdout, NULL);
////    fflush(stdout);
//    
//    BOARD_Init();
//    //clearing control registers
//    U1MODE = 0;
//    U1STA = 0;
//    U1BRG = 0;
//    U1TXREG = 0;
//    U1RXREG = 0;
//    
//    //setting U1BRG to 115200
//    //unsigned long baudeRate = 115200;
//    U1BRG = (Fpb / (16 * 115200)) - 1;
//    
//    //8 N 1 uart
//    U1MODEbits.PDSEL = 0;
//    U1MODEbits.STSEL = 0;
//    
//    U1MODEbits.SIDL = 0;    // 0 = continue operation in idle mode
//    U1MODEbits.IREN = 0;    // 0 = IrDA disable
//    U1MODEbits.RTSMD = 0;   // 0 = Flow control mode
//    U1MODEbits.UEN = 0;     // 0 = enable UxTX and UxRX
//    U1MODEbits.LPBACK = 0;  // 0 = disable loopback mode
//    U1MODEbits.BRGH = 0;    // 1 = enable high baud rate
//    U1MODEbits.RXINV = 0;   // 0 = does not invert
//    U1MODEbits.ABAUD = 0;   // 0 = baude rade measurment is disable or complete
//    U1MODEbits.ON = 1;      //enable uart1
//    U1MODEbits.WAKE = 1;    //enable wake up on start
//    
//    U1STAbits.UTXEN = 1;    //enable UART1 transmit
//    U1STAbits.URXEN = 1;    //enable UART1 receive
//    
//    U1STAbits.URXISEL = 1;  //enable interrupts for receiver reg
//    U1STAbits.UTXISEL = 1;  //enable interrupts for transmitter reg
//    setbuf(stdout, NULL);
//    printf("HELLO WORLD!\r\n");
//    
//    while(1){
//        //char x = dequeue(&TXbuffer);
//        if(U1STAbits.URXDA == 1){ //1 = Receive buffer has data
//            U1TXREG = U1RXREG;
//        }
//    }
//    
//    return 0;
//}
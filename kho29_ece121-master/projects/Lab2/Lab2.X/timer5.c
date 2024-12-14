#include "xc.h"
#include "BOARD.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uart.h"
#include "Protocol2.h"
#include <sys/attribs.h>
#include "FreeRunningTimer.h"

static unsigned int milli = 0;

#define BLINK_FREQUENCY 0.5 //hz
#define BLINK_PERIOD_MS (1000 / BLINK_FREQUENCY)

static unsigned int lastms = 0;
static bool led = false; 

/**
 * @Function FreeRunningTimer_Init(void)
 * @param none
 * @return None.
 * @brief  Initializes the timer module */
void FreeRunningTimer_Init(void){
    // Clearing registers
    T5CON = 0;
    TMR5 = 0;
    PR5 = 1000;
    T5CONbits.TCKPS = 0b100; // Set prescaler to 4
    IEC0bits.T5IE = 1;       // Enable Timer5 interrupt
    IPC5bits.T5IP = 3;       // Set Timer5 interrupt priority to 3
    T5CONbits.ON = 1;
}

/**
 * Function: FreeRunningTimer_GetMilliSeconds
 * @param None
 * @return the current MilliSecond Count
 */
unsigned int FreeRunningTimer_GetMilliSeconds(void){
    return milli;
}

/**
 * Function: FreeRunningTimer_GetMicroSeconds
 * @param None
 * @return the current MicroSecond Count
 */
unsigned int FreeRunningTimer_GetMicroSeconds(void){
    return (milli * 1000);
}


void __ISR(_TIMER_5_VECTOR, ipl3auto) Timer5IntHandler(void){
    milli++;
    IFS0bits.T5IF = 0;
}

//int main(void){
//    BOARD_Init();
//    unsigned long baudRate = 115200;
//    Protocol_Init(baudRate);    
//    FreeRunningTimer_Init();
//    LEDS_INIT();
//    
//    char msg[1024];
//    unsigned int ms = FreeRunningTimer_GetMilliSeconds();
//    unsigned int mc = FreeRunningTimer_GetMicroSeconds();
//
//    // Convert millisecond and microsecond counts to strings
//    char ms_str[16];
//    char mc_str[16];
//    snprintf(ms_str, 16, "%u", ms);
//    snprintf(mc_str, 16, "%u", mc);
//    snprintf(msg, 1024, "Milli: %s, Micro: %s", ms_str, mc_str);   
//    
//    TRISE = 0x00;
//    LATE = 0x00;
//    
//    unsigned int lastDebugSend = ms; // Keep track of the last time a debug message was sent
//    
//    while(true) {
//        unsigned int currentms = FreeRunningTimer_GetMilliSeconds();
//        unsigned int currentus = FreeRunningTimer_GetMicroSeconds();
//
//        // Check if it's time to send a debug message (every 2000 ms)
//        if (currentms - lastDebugSend >= 2000) {
//            snprintf(msg, 1024, "Milli: %u, Micro: %u", currentms, currentus);
//            Protocol_SendDebugMessage(msg);
//            lastDebugSend = currentms;
//        }
//
//        // Check if it's time to toggle the LED
//        if (currentms - lastms >= BLINK_PERIOD_MS) {
//            led = !led;
//            LATEbits.LATE0 = led; 
//
//            lastms = currentms;
//        }
//    }
//    return 0;
//}


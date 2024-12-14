/*
 * File:   Lab0.c
 * Author: kwho
 *
 * Created on January 16, 2024, 1:07 PM
 */

#include "xc.h"
#include <BOARD.h>
#include <stdio.h>

int main(void)
{
    BOARD_Init(); 
    // 0 is output but 1 is input
    TRISD = 0xFF; //buttons 2 3 4
    TRISF = 0xFF; //button 1
    TRISE = 0x00; //LED
    LATE = 0x00; //LED patterns to follow
   
    while(TRUE){
        //1st button 
        if(PORTFbits.RF1){
            LATE = 0B00000011;
        }
        //2nd button
        if(PORTDbits.RD5){
            LATE = 0B00001100;
        }
        //3d button
        if(PORTDbits.RD6){
            LATE = 0B00110000;
        }
        //4th button
        if(PORTDbits.RD7){
            LATE = 0B11000000;
        }
    }

    //part 2
    int LED = 0x00;
    
    while(TRUE){
        LATE = LED;
        
        LED++;
        
        //if button is pressed: reset
        if(PORTFbits.RF1){
            LED = 0;
        }
        
        //if the led is 
        if(LED >= 0xFF){
            LED = 0;
        }
        
        //delay
        int i;
        for(i = 0; i < 50000; i++){
            asm("NOP");
        }
        
    }
}

/***
 * File:    uart.h
 * Author:  Instructor
 * Created: ECE121 W2022 rev 1
 * This library implements a true UART device driver that enforces 
 * I/O stream abstraction between the physical and application layers.
 * All stream accesses are on a per-character or byte basis. 
 */
#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdbool.h>
#include <sys/attribs.h>
#define SYSTEM_CLOCK 80000000L
#define PB_CLOCK SYSTEM_CLOCK/2
#define Fpb PB_CLOCK

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/
/**
 * @Function Uart_Init(unsigned long baudrate)
 * @param baudrate
 * @return none
 * @brief  Initializes UART1 to baudrate N81 and creates circ buffers
 * @author instructor ece121 W2022 */
void Uart_Init(unsigned long baudRate);

/**
 * @Function int PutChar(char ch)
 * @param ch - the character to be sent out the serial port
 * @return True if successful, else False if the buffer is full or busy.
 * @brief  adds char to the end of the TX circular buffer
 * @author instrutor ECE121 W2022 */
int PutChar(char ch);

/**
 * @Function unsigned char GetChar(void)
 * @param None.
 * @return NULL for error or a Char in the argument.
 * @brief  dequeues a character from the RX buffer,
 * @author instructor, ECE121 W2022 */
unsigned char GetChar(void);

/**
* Refer to ...\docs\MPLAB C32 Libraries.pdf: 32-Bit Language Tools Library.
* In sec. 2.13.2 helper function _mon_putc() is noted as normally using
* UART2 for STDOUT character data flow. Adding a custom version of your own
* can redirect this to UART1 by calling your putchar() function.
*/
void _mon_putc(char c);


/****************************************************************************
* Function: IntUart1Handler
* Parameters: None.
* Returns: None.
* The PIC32 architecture calls a single interrupt vector for both the
* TX and RX state machines. Each IRQ is persistent and can only be cleared
* after "removing the condition that caused it". This function is declared in
* sys/attribs.h.
****************************************************************************/
//void __ISR(_UART1_VECTOR) IntUart1Handler(void);

#endif // UART_H
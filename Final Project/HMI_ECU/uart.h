/*-------------------------------------------------------------------------------
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART driver
 *
 * Author: Mahmoud Ahmed
 *
 -------------------------------------------------------------------------------*/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/* UART Driver Baud Rate */
#define USART_BAUDRATE 38400

/*-----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPES
 -----------------------------------------------------------------------------*/
void UART_init();
void UART_sendByte(const uint8 data);
uint8 UART_receiveByte(void);
void UART_sendString(const uint8 *Str, uint8 Str_size);
void UART_receiveString(uint8 *Str);

#endif /* UART_H_ */

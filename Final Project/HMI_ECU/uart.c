/**********************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART driver
 *
 * Author: Mahmoud Ahmed
 *
 *********************************************************************************/
#include "uart.h"

/* Baud Prescale Calculation */
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

void UART_init(void) {

	/* Double Transmission Speed is Enabled */
	UCSRA = (1 << U2X);

	/*---------UCSRB--------------------------------------------
	 * (RXCIE = 0) (TXCIE = 0) (UDRIE = 0) Interrupt Disable
	 * RXEN = 1 Receiver Enable
	 * TXEN = 1 Transmitter Enable
	 * UCSZ2 = 0 (8-bit data mode)
	 * --------------------------------------------------------*/
	UCSRB = (1 << RXEN) | (1 << TXEN);

	/*---------UCSRC---------------------------------------------
	 * URSEL = 1 To Read UCSRC
	 * (UCSZ0 = 1) (UCSZ1 = 1) 8-bit data mode
	 * --------------------------------------------------------*/
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);

	/* Set BAUD_PRESCALE first 8-bits in UBRRL and last 4-bits in UBRRH */
	UBRRH = BAUD_PRESCALE >> 8;
	UBRRL = BAUD_PRESCALE;
}

void UART_sendByte(const uint8 data) {
	/* UDRE Flag to indicate that the TX buffer (UDR) is empty and ready to
	 * transmit a new byte*/
	while (BIT_IS_CLEAR(UCSRA, UDRE)) {
		/* Wait until UDRE = 1 */
	}
	/* UDR: I/O Data Register */
	UDR = data;
	/* UDRE Flag is automatically cleared now as UDR is not empty anymore */
}

uint8 UART_receiveByte(void) {
	/* RXC Flag is set when there are unread data in the Receive buffer (Not empty) */
	while (BIT_IS_CLEAR(UCSRA, RXC)) {
		/* Wait until RXC = 1 */
	}
	/* Read data from UDR */
	return UDR;
	/* RXC Flag is automatically cleared by the CPU now  */
}

void UART_sendString(const uint8 *Str, uint8 Str_size) {
	/* Send string length */
	UART_sendByte(Str_size);
	while (*Str != '\0') {
		UART_sendByte(*Str);
		Str++;
	}
}

void UART_receiveString(uint8 *Str) {
	uint8 i = 0, length;
	/* Receive string length from other Micro-Controllers */
	length = UART_receiveByte();
	while (i <= length) {
		*Str = UART_receiveByte();
		Str++;
		i++;
	}
	*Str = '\0';

}

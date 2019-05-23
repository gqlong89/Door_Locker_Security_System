/*
 * HMI_main.c
 *
 *  Created on: May 14, 2019
 *      Author: Mahmoud 10
 */

#include "hmi_main.h"

uint8 status = 0;

int main(void) {
	uint8 i = 0;

	UART_init();
	LCD_init();

	/* Receive the initialized status from CTRL_uC */
	status = UART_receiveByte();

	while (1) {

		/* 1.Check the current status
		 * 2.Send it to CTRL_uC
		 * 3.Do Status Functionality
		 */
		switch (status) {

		case NOT_INITIALIZED:
			/* Send Current Status to CTRL_uC */
			UART_sendByte(status);
			Keypad_setPassword();
			break;

		case INITIALIZED:
			UART_sendByte(status);
			Keypad_enterPassword();
			break;

		case MAIN:
			UART_sendByte(status);
			LCD_mainOptions();
			break;

		case WARNING:
			UART_sendByte(status);
			LCD_clearScreen();
			LCD_displayString("ERROR");
			/* Wait for 10 sec */
			for (i = 0; i < 10; i++) {
				_delay_ms(1000);
			}
			/* Change The Current Status */
			status = INITIALIZED;
			break;

		case OPEN:
			UART_sendByte(status);
			LCD_clearScreen();
			LCD_displayString("Door Opens");
			/* Wait for 3 sec */
			_delay_ms(3000);
			LCD_clearScreen();
			LCD_displayString("HODOR");
			/* Wait for 1 sec */
			_delay_ms(1000);
			/* Change The Current Status */
			status = INITIALIZED;
			break;
		}
	}
	return 0;
}


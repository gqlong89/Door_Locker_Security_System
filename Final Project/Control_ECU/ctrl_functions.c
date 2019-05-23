/*
 * ctrl_functions.c
 *
 *  Created on: May 19, 2019
 *      Author: Mahmoud 10
 */

#include "ctrl.h"

void EEPROM_passwordSet(void) {

	uint8 i = 0;
	uint8 pw[5];
	uint8 pw_check[5];

	/* Receive the Entered Password and store it in pw[5] */
	for (i = 0; i < 5; i++) {
		pw[i] = UART_receiveByte();
	}

	/* Receive the Re-Entered Password and store it in pw_check[5] */
	for (i = 0; i < 5; i++) {
		pw_check[i] = UART_receiveByte();
		/* Check Condition */
		if (pw_check[i] != pw[i]) {
			UART_sendByte(ERROR);
			return; /* Return ERROR */
		}
	}

	/* Save Password in EEPROM */
	for (i = 0; i < 5; i++) {
		EEPROM_writeByte(0x01F4 + i, pw[i]);
		_delay_ms(10);
	}

	/* Change Status and save it in EEPROM */
	status = INITIALIZED;
	EEPROM_writeByte(0x00C8, status);
	_delay_ms(10);

	UART_sendByte(SUCCESS);
}

void EEPROM_passwordCheck(uint8 *saved_pw) {

	uint8 i = 0;
	uint8 pw[5];
	static uint8 wrong_counts;

	/* Receive the entered PW from HMI_uC */
	for (i = 0; i < 5; i++) {
		pw[i] = UART_receiveByte();
	}

	/* Compare values */
	for (i = 0; i < 5; i++) {

		/* Check if the entered PW matches the saved one in the EEPROM */
		if (pw[i] != saved_pw[i]) {
			wrong_counts++;
			UART_sendByte(ERROR); /* Send ERROR value to HMI_uC */
			if (wrong_counts < 3) {
				return;
			} else {
				wrong_counts = 0;
				return;
			}
		}
	}

	UART_sendByte(SUCCESS); /* Send SUCCESS to the second uC */
}

void Time0_PWM_Clk(unsigned short _duty_cycle) {
	/* Timer1 Fast PWM (non-inverting mode) */
	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	/* Fast PWM mode with the TOP in ICR1 */
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11);
	TCNT1 = 0;
	ICR1 = 2499; /* Set TOP count in Timer1 */
	OCR1A = _duty_cycle;
}

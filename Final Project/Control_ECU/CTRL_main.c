/*
 * HMI_main.c
 *
 *  Created on: May 14, 2019
 *      Author: Mahmoud 10
 */

#include "ctrl.h"

uint8 status;
uint8 read_pw[5];

int main(void) {

	uint8 i = 0;
	PORTB = 0;

	UART_init();
	EEPROM_init();

	/* Read the saved status from EEPROM and send it to HMI_uC */
	EEPROM_readByte(0x00C8, &status);
	UART_sendByte(status);

	while (1) {

		/* Receive the current status from the other uC */
		status = UART_receiveByte();

		switch (status) {

		/* PW Set/Change Case */
		case NOT_INITIALIZED:
			EEPROM_passwordSet();
			break;

		case INITIALIZED:
			/* Read the saved PW from EEPROM */
			for (i = 0; i < 5; i++) {
				EEPROM_readByte(0x01F4 + i, &read_pw[i]);
			}
			EEPROM_passwordCheck(read_pw);
			break;

		case MAIN:
			break;

		case WARNING:
			/* Buzzer ON */
			SET_BIT(PORTB, PB0);

			/* Wait for 10 Sec */
			for (i = 0; i < 10; i++) {
				_delay_ms(1000);
			}

			/* Buzzer OFF */
			CLEAR_BIT(PORTB, PB0);
			break;

			/* Rotate Motor To Open The Door For 3 Sec Then Close it*/
		case OPEN:
			SET_BIT(DDRD, PD5); /* Configure OC1A pin as O/P */
			Time0_PWM_Clk(250); /* Rotate Servo +90° (CW) */
			_delay_ms(3000); /* Wait 3 Sec */
			Time0_PWM_Clk(187); /* Rotate Servo +0° (Anti CW) */
			break;
		}
	}
	return 0;
}

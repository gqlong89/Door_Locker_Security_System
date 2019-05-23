/*
 * hmi_functions.c
 *
 *  Created on: May 17, 2019
 *      Author: Mahmoud 10
 */

#include "hmi_main.h"

void Keypad_setPassword(void) {
	uint8 key;
	uint8 i = 0;
	uint8 received_data;

	/*----------------------------------- Enter PW Step*/
	LCD_clearScreen();
	LCD_displayString("New Password");
	LCD_goToRowColumn(1, 0);

	/* Get NEW password form the user and send it */
	for (i = 0; i < 5; i++) {
		key = KeyPad_getPressedKey();
		if ((key >= 0) && (key <= 9)) {
			UART_sendByte(key); /* UART send */
			LCD_displayCharacter('*');
			_delay_ms(500);
		}
	}

	/*--------------------------------- Confirm PW Step*/
	LCD_clearScreen();
	LCD_displayString("ReEnter PW");
	LCD_goToRowColumn(1, 0);

	/* Re-Enter NEW password form the user and send it */
	for (i = 0; i < 5; i++) {
		key = KeyPad_getPressedKey();
		if ((key >= 0) && (key <= 9)) {
			UART_sendByte(key); /* UART send */
			LCD_displayCharacter('*');
			_delay_ms(500);
		}
	}

	/*------------------Receive Checking Status (ERROR/SUCCESS) */
	received_data = UART_receiveByte();

	if (received_data == ERROR) {
		LCD_clearScreen();
		LCD_displayString("Doesn't match");
		_delay_ms(500);
		return; /* Exit The Function */
	}

	if (received_data == SUCCESS) {
		LCD_clearScreen();
		LCD_displayString("Change Success!");
		/* Change Status to INITIALIZED */
		status = INITIALIZED;
		/* Send current status to the 2nd uC */
		_delay_ms(500);
	}
}

void Keypad_enterPassword(void) {
	uint8 key;
	uint8 i = 0;
	uint8 received_data;
	/* This variable is static to keep it's value when the function recalled */
	static uint8 wrong_counts;

	LCD_clearScreen();
	LCD_displayString("Enter Password");
	LCD_goToRowColumn(1, 0);

	for (i = 0; i < 5; i++) {
		key = KeyPad_getPressedKey();
		UART_sendByte(key); /* Send the pressed key to the CTRL_uC */
		LCD_displayCharacter('*'); /* Display '*' on the LCD */
		_delay_ms(500);
	}

	/* Receive PW matching result */
	received_data = UART_receiveByte();

	if (received_data == ERROR) {
		wrong_counts++;

		LCD_clearScreen();
		LCD_displayString("Wrong Password!");
		_delay_ms(500);

		/* Check if the entered password was wrong for 3 times then go to the WARNING status */
		if (wrong_counts > 2) {
			status = WARNING;
			wrong_counts = 0;
			return; /* Exit the function */
		}

		/* Exit The Function */
		return;
	}

	if (received_data == SUCCESS) {
		wrong_counts = 0;
		status = MAIN; /* Go to MAIN status */
	}
}

void LCD_mainOptions(void) {
	uint8 key;
	LCD_clearScreen();
	LCD_displayString("(+)Change PW");
	LCD_goToRowColumn(1, 0);
	LCD_displayString("(-)Open");

	key = KeyPad_getPressedKey();
	_delay_ms(500);

	switch (key) {

	case '-':
		/* Change Status to OPEN */
		status = OPEN;
		break;

	case '+':
		/* Change Status to NOT_INITIALIZED */
		status = NOT_INITIALIZED;
		break;

	default:
		LCD_clearScreen();
		LCD_displayString("Wrong Command!");
		LCD_goToRowColumn(1, 0);
		LCD_displayString("Enter (+) or (-)");
		_delay_ms(500);
		LCD_clearScreen();
		LCD_mainOptions(); /* Recall The Function */
		break;
	}

}

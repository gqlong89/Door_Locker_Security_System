/*
 * LCD.c
 *
 *  Created on: May 2, 2019
 *      Author: Mahmoud 10
 */

#include "LCD.h"

void LCD_init(void) {

	LCD_CTRL_PORT_DIR |= (1 << RS) | (1 << RW) | (1 << E); /* Configuring RS,RW,E as o/p pins */
#if (DATA_BITS_MODE==4)
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_DIR = 0xF0;
#else
	LCD_DATA_PORT_DIR = 0x0F;
#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE);
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT_DIR = 0xFF; /* Configuring the data port as o/p */
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* 2-line LCD + 8-bit Data Mode + 5*7 dot display Mode */
#endif
	LCD_sendCommand(CURSOR_ON); /* Cursor ON */
	LCD_sendCommand(CLEAR_COMMAND); /* Clearing LCD at the beginning */
}

void LCD_sendCommand(uint8 command) {
	CLEAR_BIT(LCD_CTRL_PORT, RS); /* Instructions mode RS=0 */
	CLEAR_BIT(LCD_CTRL_PORT, RW); /* Write data to LCD RW=0 */
	_delay_ms(1); /* tas= 50ns */
	SET_BIT(LCD_CTRL_PORT, E); /* Enabling the LCD E=1 */
	_delay_ms(1); /* tpw-tdws= 190ns */
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0)>>4);
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = command; /* The required Command */
	_delay_ms(1); /* tdws = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT, E); /* Disabling the LCD E=0 */
	_delay_ms(1); /* th=13ns */
#endif
}

void LCD_displayCharacter(uint8 data) {
	SET_BIT(LCD_CTRL_PORT, RS); /* Data Mode RS=1 */
	CLEAR_BIT(LCD_CTRL_PORT, RW); /* Write data to LCD RW=0 */
	_delay_ms(1); /* tas= 50ns */
	SET_BIT(LCD_CTRL_PORT, E); /* Enabling the LCD E=1 */
	_delay_ms(1); /* tpw-tdws= 190ns */
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0)>>4);
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = data; /* The required Command */
	_delay_ms(1); /* tdws = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT, E); /* Disabling the LCD E=0 */
	_delay_ms(1); /* th=13ns */
#endif
}

void LCD_displayString(const char *Str) {
	while (*Str != '\0') {
		LCD_displayCharacter(*Str);
		Str++;
	}
}

void LCD_goToRowColumn(uint8 row, uint8 column) {
	uint8 address;
	switch (row) {
	case 0:
		address = column;
		break;
	case 1:
		address = column + 0x40;
		break;
	case 2:
		address = column + 0x10;
		break;
	case 3:
		address = column + 0x50;
		break;
	}
	LCD_sendCommand(address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row, uint8 column, const char *Str) {
	LCD_goToRowColumn(row, column);
	LCD_displayString(Str);
}

void LCD_clearScreen() {
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_intgerToString(int intger) {
	char buff[16];
	itoa(intger, buff, 10);
	LCD_displayString(buff);
}

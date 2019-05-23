/**********************************************************************************
 *
 ****************************EDIT THIS CODE****************************************
 *
 *********************************************************************************/

/**********************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM driver
 *
 * Author: Mahmoud Ahmed
 *
 *********************************************************************************/

#include "external_eeprom.h"
#include "i2c.h"

void EEPROM_init(void) {
	/* Initializing I2C */
	TWI_init();
}

uint8 EEPROM_writeByte(uint16 u16address, uint8 u8data) {

	/* Send Start Bit */
	TWI_start();
	if (TWI_getStatus() != TW_S)
		return ERROR;

	/* Send the device address with Write bit 0b(1010)(A8,A9,A10)(W=0) */
	TWI_write((uint8) (0xA0 | ((u16address & 0x700) >> 7)));
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
		return ERROR;

	/* Send the required memory location address (A7,A6,A5,A4,A3,A2,A1,A0) */
	TWI_write((uint8) u16address);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
		return ERROR;

	/* Write data to EEPROM */
	TWI_write(u8data);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
		return ERROR;

	/* Send Stop Bit */
	TWI_stop();

	return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data) {

	/* Send Start Bit */
	TWI_start();
	if (TWI_getStatus() != TW_S)
		return ERROR;

	/* Send the device address with Write bit 0b(1010)(A10,A9,A8)(W=0) */
	TWI_write((uint8) ((0xA0) | ((u16addr & 0x700) >> 7)));
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
		return ERROR;

	/* Send the required memory location address (A7,A6,A5,A4,A3,A2,A1,A0) */
	TWI_write((uint8) u16addr);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
		return ERROR;

	/* Send the Repeated Start Bit */
	TWI_start();
	if (TWI_getStatus() != TW_RS)
		return ERROR;

	/* Send the device address with Write bit 0b(1010)(A8,A9,A10)(R=1) */
	TWI_write((uint8) ((0xA0) | ((u16addr & 0x700) >> 7) | 1));
	if (TWI_getStatus() != TW_MT_SLA_R_ACK)
		return ERROR;

	/* Read Data From Memory With Nack (Without ACK) */
	*u8data = TWI_readWithNACK();
	if (TWI_getStatus() != TW_MR_DATA_NACK)
		return ERROR;

	/* Send Stop Bit */
	TWI_stop();

	return SUCCESS;
}

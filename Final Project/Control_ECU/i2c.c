/**********************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.c
 *
 * Description: Source file for the I2C driver
 *
 * Author: Mahmoud Ahmed
 *
 *********************************************************************************/

#include "i2c.h"

void TWI_init(void) {

	/* TWPS1:0 = 00 (Prescaler value = 1) TWBR = 02 so F_SCL = 400 kHz */
	TWBR = 0x02;
	TWSR = 0x00;

	/* TWI ENABLE */
	TWCR = (1 << TWEN);

	/* My address if to call this MC by any master */
	TWAR = 0b00000010;
}
void TWI_start(void) {

	/*---------TWCR--------------------------------------------
	 * TWINT = 1 CLEAR INTERRUPT FLAG
	 * TWSTA = 1 SEND START BIT
	 * TWEN = 1 TWI ENABLE
	 * --------------------------------------------------------*/
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	while (BIT_IS_CLEAR(TWCR, TWINT)) {
		/* Wait till TWINT = 1 (Bit is sent successfully) */
	}
}
void TWI_stop(void) {

	/*---------TWCR--------------------------------------------
	 * TWINT = 1 CLEAR INTERRUPT FLAG
	 * TWSTO = 1 SEND STOP BIT
	 * TWEN = 1 TWI ENABLE
	 * --------------------------------------------------------*/
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8 data) {

	/* Put data in TWDR register */
	TWDR = data;

	/*---------TWCR--------------------------------------------
	 * TWINT = 1 CLEAR INTERRUPT FLAG
	 * TWEN = 1 TWI ENABLE
	 * --------------------------------------------------------*/
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (BIT_IS_CLEAR(TWCR, TWINT)) {
		/* Wait till TWINT = 1 (Bit is sent successfully) */
	}
}

uint8 TWI_readWithACK(void) {

	/*---------TWCR--------------------------------------------
	 * TWINT = 1 CLEAR INTERRUPT FLAG
	 * TWEA = 1 ENABLE ACKNOWLEDGE BIT
	 * TWEN = 1 TWI ENABLE
	 * --------------------------------------------------------*/
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	while (BIT_IS_CLEAR(TWCR, TWINT)) {
		/* Wait till TWINT = 1 (Bit is sent successfully) */
	}
	/* READ DATA */
	return TWDR;
}
uint8 TWI_readWithNACK(void) {

	/*---------TWCR--------------------------------------------
	 * TWINT = 1 CLEAR INTERRUPT FLAG
	 * TWEN = 1 TWI ENABLE
	 * --------------------------------------------------------*/
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (BIT_IS_CLEAR(TWCR, TWINT)) {
		/* Wait till TWINT = 1 (Bit is sent successfully) */
	}

	/* READ DATA */
	return TWDR;
}

uint8 TWI_getStatus(void) {
	uint8 status;

	/* Masking to read the last 5-bits in TWSR register */
	status = TWSR & 0xF8;

	/* Return status */
	return status;
}

/**********************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.h
 *
 * Description: Header file for the I2C driver
 *
 * Author: Mahmoud Ahmed
 *
 *********************************************************************************/

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*-----------------------------------------------------------------------------
 *                   Status Codes for I2C in the TWSR register
 -----------------------------------------------------------------------------*/
#define TW_S 0x08
#define TW_RS 0x10
#define TW_MT_SLA_W_ACK  0x18
#define TW_MT_SLA_R_ACK  0x40
#define TW_MT_DATA_ACK   0x28
#define TW_MR_DATA_ACK   0x50
#define TW_MR_DATA_NACK  0x58

/*-----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPES
 -----------------------------------------------------------------------------*/
void TWI_init(void);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_readWithACK(void);
uint8 TWI_readWithNACK(void);
uint8 TWI_getStatus(void);

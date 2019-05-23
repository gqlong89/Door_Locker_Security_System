/*
 * ctrl_functions.h
 *
 *  Created on: May 19, 2019
 *      Author: Mahmoud 10
 */

#ifndef CTRL_H_
#define CTRL_H_

#include "i2c.h"
#include "external_eeprom.h"
#include "uart.h"

/*-----------------------------------------------------------------------------
 *                          PREPROCESSOR MACROS
 -----------------------------------------------------------------------------*/
#define INITIALIZED 3
#define WARNING 4
#define MAIN 5
#define NOT_INITIALIZED 6
#define OPEN 7

/*-----------------------------------------------------------------------------
 *                          GLOBAL VARIABLES
 -----------------------------------------------------------------------------*/
extern uint8 status;
/* Global Array contains the saves PW in the EEPROM */
extern uint8 read_pw[5];

/*-----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPES
 -----------------------------------------------------------------------------*/
void EEPROM_passwordSet(void);
void EEPROM_passwordCheck(uint8 *saved_pw);
void Time0_PWM_Clk(unsigned short _duty_cycle);

#endif /* CTRL_H_ */

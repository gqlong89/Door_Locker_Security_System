/*
 * hmi_main.h
 *
 *  Created on: May 14, 2019
 *      Author: Mahmoud 10
 */

#ifndef HMI_MAIN_H_
#define HMI_MAIN_H_

#include "lcd.h"
#include "keypad.h"
#include "uart.h"

/*-----------------------------------------------------------------------------
 *                          PREPROCESSOR MACROS
 -----------------------------------------------------------------------------*/
#define SUCCESS 21
#define ERROR 20
#define NOT_INITIALIZED 6
#define INITIALIZED 3
#define WARNING 4
#define MAIN 5
#define OPEN 7

/*-----------------------------------------------------------------------------
 *                           GLOBAL VARIABLES
 -----------------------------------------------------------------------------*/
extern uint8 status;

/*-----------------------------------------------------------------------------
 *                         FUNCTIONS PROTOTYPES
 -----------------------------------------------------------------------------*/
void Keypad_setPassword(void);
void Keypad_passwordConfirm(void);
void Keypad_enterPassword(void);
void Keypad_reEnterPassword(void);
void LCD_mainOptions(void);

#endif /* HMI_MAIN_H_ */

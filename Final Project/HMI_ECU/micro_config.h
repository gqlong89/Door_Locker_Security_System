/*************************************************************************
 *
 * Module: Micro -Configuration
 *
 * File Name: micro_config.h
 *
 * Description: File includes all Microcontroller libraries
 *
 * Author: Mahmoud Ahmed
 *
 **************************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 1000000UL /* 1MHz Clock Frequency */
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif /* MICRO_CONFIG_H_ */

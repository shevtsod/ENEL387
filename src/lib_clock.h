/*
* FILENAME: lib_clock.h
*
*	DESCRIPTION:
*		Function prototypes for handling
*		system clock setup and timing functions
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Jan. 24, 2017
*/

#include "stm32f10x.h"

/* FUNCTION PROTOTYPES */
void initializeClock(void);
void delay(uint32_t t);
void delayMS(uint32_t t);

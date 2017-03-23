/*
* FILENAME: lib_interrupt.h
*
*	DESCRIPTION:
*		Function prototypes to initialize and use 
*		interrupt routines
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Feb. 14, 2017
*/

#include "stm32f10x.h"

/* FUNCTION PROTOTYPES */
void initializeSysTick(void);
void initializeEXTI0(void);

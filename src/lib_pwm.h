/*
* FILENAME: lib_pwm.h
*
*	DESCRIPTION:
*		Function prototypes to initialize and use 
*		systems to run Pulse Width Modulation
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Mar. 7, 2017
*/

#include "stm32f10x.h"

/* FUNCTION PROTOTYPES */
void initializePWM(void);
void setDutyCycle(int value);
void setPWMEnabled(int value);

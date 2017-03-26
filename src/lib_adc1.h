/*
* FILENAME: lib_adc1.h
*
*	DESCRIPTION:
*		Function prototypes to initialize and use 
*		ADC1 on the STM32F100.
*
*		The ADC used is a SAR with a 12-bit resolution,
*		16 external inputs, and 2 internal inputs.
*		It is located on pins:
*		PA0 to PA7,
*		PB0,
*		PB1,
*		PC0 to PC5
*	
*   Inputs to the ADC are a 10K potentiometer on pin PA1
		and an LM35 temperature sensor on pin PA0
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Feb. 7, 2017
*/

#include "stm32f10x.h"

/* FUNCTION PROTOTYPES */
void initializeADC1(void);
uint32_t getValueFromChannel(uint8_t channel);

//Driver for thumbstick
uint8_t getPosX(void);
uint8_t getNegX(void);

uint8_t getPosY(void);
uint8_t getNegY(void);

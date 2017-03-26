/*
* FILENAME: lib_adc1.c
*
*	DESCRIPTION:
*		Functions to initialize and use ADC1
*		on the STM32F100, based on definitions
*		in lib_adc1.h
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Feb. 7, 2017
*/

#include "lib_adc1.h"

/*
* Helper function. Initializes the clock of ports required for this library
*/
void initializeADC1Clock(void) {
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN 
							 | RCC_APB2ENR_IOPBEN 
							 | RCC_APB2ENR_IOPCEN
							| RCC_APB2ENR_ADC1EN ;
	;
}

/*
* Initialize ADC1 according to the instructions in lab 4
*/
void initializeADC1(void) {
	initializeADC1Clock();
	
	//Configure port A as analog input
	GPIOA->CRL = 0x00000000;
	
	//Turn on ADC
	ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CAL;
	
	//Set maximum sample time
	ADC1->SMPR2 = 0xFFFFFFFF;
	
	//Set the conversion sequence
	ADC1->SQR3 = 0x0;
	
}

/*
* Takes an integer channel (0 or 1) and returns the data
*	from the ADC as a 32 bit hex value
*/
uint32_t getValueFromChannel(uint8_t channel) {
	
	//Select channel to convert
	switch(channel) {
		case 0:
			ADC1->SQR3 = 0x0;
			break;
		case 1:
			ADC1->SQR3 = 0x1;
			break;
	}
	
	//Start the conversion sequence
	ADC1->CR2 |= ADC_CR2_ADON;
	
	//Wait for sequence to complete
	while((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC) {
			//Loop until completed
	}
	
	//return data from the ADC
	return ADC1->DR;
}

//Functions for Thumbstick driver

/*
* Return true if X is in the positive region above the deadzone
*/
uint8_t getPosX(void) {
	return getValueFromChannel(1) > 0xE00;
}

/*
* Return true if X is in the negative region below the deadzone
*/
uint8_t getNegX(void) {
	return getValueFromChannel(1) < 0x200;
}

/*
* Return true if Y is in the positive region above the deadzone
*	X direction has priority over Y
*/
uint8_t getPosY(void) {
	return (!getPosX() && !getNegX()) && getValueFromChannel(0) > 0xE00;
}

/*
* Return true if Y is in the negative region below the deadzone
* X direction has priority over Y
*/
uint8_t getNegY(void) {
	return (!getPosX() && !getNegX()) && getValueFromChannel(0) < 0x200;
}

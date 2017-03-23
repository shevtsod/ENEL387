/*
* FILENAME: lib_clock.c
*
*	DESCRIPTION:
*		Functions to handle system clock setup
*		and timing functions, based on definitions
*		in lib_clock.h
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Jan. 24, 2017
*/


#include "lib_clock.h"

/*
*	Initialize the clock of the device to 24MHz using PLL
*/
void initializeClock(void) {
	
	uint32_t verify = 0x0;
	
	//Clock configuration register
	//Bits 0-1 		- 	10 		PLL selected as system clock
	//Bit 16			-		1			
	//Bit 17			-		1			
	//Bits 18-21 	- 	0001 	PLL input clock x3
	RCC->CFGR = 0x00050002;
	
	//Clock Control Register
	//Bit 19			-		1			CSS ON
	//Bit 24			-		1			PLL ON
	RCC->CR |= RCC_CR_CSSON | RCC_CR_PLLON;
	
	//Wait for Bit 25 = 1 = PLL ready flag
	while(verify != 0x02000000) {
		verify = RCC->CR & 0x02000000;
	}
	
}

/*
* Delay for t clock cycles (t = 6000 = 1ms)
*/
void delay(uint32_t t) {
	int i = 0;
	for(i = 0; i < t; i++);
}

/*
* Delay for t milliseconds
*/
void delayMS(uint32_t t) {
	int i = 0;
	t *= 6000;
	for(i = 0; i < t; i++); 
}

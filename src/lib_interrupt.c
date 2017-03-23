/*
* FILENAME: lib_interrupt.c
*
*	DESCRIPTION:
*		Functions to initialize and use 
*		interrupt routines
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Feb. 14, 2017
*/

#include "lib_interrupt.h"

/*
* Initialize SysTick and EXTI
*/

/*
* Initializes SysTick system - A counter that calls
* an interrupt handler when it completes
*/
void initializeSysTick(void) {
	//Enable interrupt clock
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	//Disable SysTick
	SysTick->CTRL = 0;
	//Clear SysTick value
	SysTick->VAL = 0;
	//Set interrupt interval
	//SysTick->LOAD = 0xF42400;
	SysTick->LOAD = 0xFFFFFF;
	//Select clock source, enable interrupt, enable counter
	SysTick->CTRL = 7;
}

/*
* Initializes EXTI0 to call an interrupt handler whenever
* USER switch is pressed
*/
void initializeEXTI0(void) {
	uint32_t mask = ~0xF;
	
	//Enable interrupt clock
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	//Select port A pins as the source for EXTI0
	AFIO->EXTICR[0] &= mask;
	//Unmask PA0 as interrupt source
	EXTI->IMR = 1;
	//Select falling edge of PA0 as trigger for interrupt
	EXTI->FTSR = 1;
	//Unmask EXTI0 as interrupt source in NVIC
	NVIC->ISER[0] |= NVIC_ISER_SETENA_6;
}

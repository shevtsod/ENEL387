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
* Initializes EXTI to call an interrupt handler when PD2 is ON
*/
void initializeEXTI(void) {   
  //Enable interrupt clock 
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 
  //Select port D pins as the source for EXTI2
  AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PD; 
  //Unmask PD2 as interrupt source 
  EXTI->IMR = EXTI_IMR_MR2;
  //Select falling edge of PD2 as trigger for interrupt 
  EXTI->RTSR = EXTI_RTSR_TR2;
  //Unmask EXTI2 as interrupt source in NVIC 
  NVIC->ISER[0] |= NVIC_ISER_SETENA_8; 
}

/*
* FILENAME: lib_pwm.c
*
*	DESCRIPTION:
*		Functions to initialize and use 
*		systems to run Pulse Width Modulation
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Mar. 7, 2017
*/

#include "lib_pwm.h"

/*
 Initialize the PWM system registers
*/
void initializePWM(void) {
	//Initialize clocks for required components
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN 
								| RCC_APB2ENR_IOPAEN 
								| RCC_APB2ENR_AFIOEN;
	
	//Set PA8 as AFIO Push-Pull output
	GPIOA->CRH |= GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1;
	GPIOA->CRH |= GPIO_CRH_CNF8_1;
	GPIOA->CRH &= ~GPIO_CRH_CNF8_0;
	
	//Initialize TIM1 flags for PWM
	TIM1->CR1 |= TIM_CR1_CEN;
	TIM1->CR2 |= TIM_CR2_OIS1;
	TIM1->EGR |= TIM_EGR_UG;
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 
							| TIM_CCMR1_OC1M_1
							| TIM_CCMR1_OC1PE
							| TIM_CCMR1_OC1FE;
	TIM1->CCER &= ~TIM_CCER_CC1E;
	//Divide 24MHz clock to 40KHz
	TIM1->PSC = 59;
	//Initial PERIOD - frequency = 4KHz
	TIM1->ARR = 100;
	//Initial PULSE WIDTH
	TIM1->CCR1 = 50;
	TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI;
	TIM1->CR1 |= TIM_CR1_CEN;
}

/*
 Changes the duty cycle. 
 Valid values: 1 to 99
*/
void setDutyCycle(int value) {
	//Set new duty cycle value
	TIM1->CCR1 = value;
	
	//Transfer new value to register
	TIM1->EGR |= TIM_EGR_UG;
}

/*
 Turns of PWM system if value = 0, turns on otherwise
*/
void setPWMEnabled(int value) {
	if(value == 0)
		TIM1->CR1 &= ~TIM_CR1_CEN;
	else
		TIM1->CR1 |= TIM_CR1_CEN;
}

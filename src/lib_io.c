/*
* FILENAME: lib_io.c
*
*	DESCRIPTION:
*		Functions to initialize and use switches and LEDs
*		on the ENEL 387 board, based on definitions
*		in lib_io.h
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Jan. 24, 2017
*/

#include "lib_io.h"

	//SW1 - PA6, PA7, PC10, PC11 (4x Dipswitch)
	//SW2 - PB8
	//SW3 -	PB9 
	//SW4 - PC12
	//SW5 - PA5
	
	//LEDs
	//PA9, PA10, PA11, PA12

/*
*	Helper function. Initializes clock for APB2 for GPIO
*	Initializes ports A, B, and C
*/
void initializeIOClock(void) {
	//APB2 peripheral clock enable register
	//Enable clocks for port A, B, C
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN 
								| RCC_APB2ENR_IOPBEN 
								| RCC_APB2ENR_IOPCEN;
}

/*
* Set mode and configuration of IO pins
*/
void initializeIO(void) {
	initializeIOClock();
	
	/* INPUTS */
	//Switches are reset to their correct configuration,
	//no configuration needed.
	GPIOA->CRH &= ~GPIO_CRH_MODE13 & ~GPIO_CRH_MODE14 & ~GPIO_CRH_MODE15;
	GPIOA->CRH |= GPIO_CRH_CNF13_0 | GPIO_CRH_CNF14_0 | GPIO_CRH_CNF15_0;
	GPIOA->CRH &= ~GPIO_CRH_CNF13_1 & ~GPIO_CRH_CNF14_1 & ~GPIO_CRH_CNF15_1;
	
	/* OUTPUTS */
	//GPIOA_CRH
	//Bits 4-5, 8-9, 12-13, 16-17		-		11		Max speed 50MHz
	//Bits 2-3, 6-7, 10-11, 14-15		-		00		GP Push Pull
	//GPIOA->CRH |= 0x00033330;
	GPIOA->CRH |= GPIO_CRH_MODE9 
							| GPIO_CRH_MODE10 
							| GPIO_CRH_MODE11 
							| GPIO_CRH_MODE12;
	GPIOA->CRH &= ~GPIO_CRH_CNF9
							& ~GPIO_CRH_CNF10
							& ~GPIO_CRH_CNF11
							& ~GPIO_CRH_CNF12;
	
	//GPIOA_CRH
	//On-board LEDs on ports PC8, PC9
	GPIOC->CRH |= GPIO_CRH_MODE8
							| GPIO_CRH_MODE9;
	GPIOC->CRH &= ~GPIO_CRH_CNF8
							& ~GPIO_CRH_CNF9;
	
	
	//Set the LEDs to their OFF state
	setLED1(0);
	setLED2(0);
	setLED3(0);
	setLED4(0);
}


//*********************************************************/

//Get input values

/*
* Return value of on-board USER switch
*/
uint16_t getSWUser(void) {
	//USER - PA0
	return (GPIOA->IDR & GPIO_IDR_IDR0);
}

/*
* Return value of SW1.1 (Dipswitch 1)
*/
uint16_t getSW1_1(void) {
	//SW1.1 - PA6
	return !(GPIOA->IDR & GPIO_IDR_IDR6);
}

/*
* Return value of SW1.2 (Dipswitch 2)
*/
uint16_t getSW1_2(void) {
	//SW1.2 - PA7
	return !(GPIOA->IDR & GPIO_IDR_IDR7);
}

/*
* Return value of SW1.3 (Dipswitch 3)
*/
uint16_t getSW1_3(void) {
	//SW1.3 - PC10
	return !(GPIOC->IDR & GPIO_IDR_IDR10);
}

/*
* Return value of SW1.4 (Dipswitch 4)
*/
uint16_t getSW1_4(void) {
	//SW1.4 - PC11
	return !(GPIOC->IDR & GPIO_IDR_IDR11);
}

/*
* Return value of SW2 (Red Button)
*/
uint16_t getSW2(void) {
	//SW2 - PB8
	return !(GPIOB->IDR & GPIO_IDR_IDR8);
}

/*
* Return value of SW3 (Green Button)
*/
uint16_t getSW3(void) {
	//SW3 -	PB9
	return !(GPIOB->IDR & GPIO_IDR_IDR9);
}

/*
* Return value of SW4 (Blue Button)
*/
uint16_t getSW4(void) {
	//SW4 - PC12
	return !(GPIOC->IDR & GPIO_IDR_IDR12);
}

/*
*	Return value of SW5 (Black Button)
*/
uint16_t getSW5(void) {
	//SW5 - PA5
	return !(GPIOA->IDR & GPIO_IDR_IDR5);
}

/*
* Return value of Button A (PA14)
*/
uint16_t getA(void) {
	return !(GPIOA->IDR & GPIO_IDR_IDR14);
}

/*
* Return value of Button B (PA15)
*/
uint16_t getB(void) {
	return !(GPIOA->IDR & GPIO_IDR_IDR15);
}

/*
* Return value of Menu Button (PA13)
*/
uint16_t getMenu(void) {
	return !(GPIOA->IDR & GPIO_IDR_IDR13);
}


//*********************************************************/
//Set output values

/*
* set LED 1 to ON if state is true, OFF if state is false
*/
void setLED1(uint16_t state) {
	//PA9
	if(state) {
		GPIOA->ODR &= ~GPIO_ODR_ODR9;
	} else {
		GPIOA->ODR |= GPIO_ODR_ODR9;
	}
}
/*
* set LED 2 to ON if state is true, OFF if state is false
*/
void setLED2(uint16_t state) {
	//PA10
	if(state) {
		GPIOA->ODR &= ~GPIO_ODR_ODR10;
	} else {
		GPIOA->ODR |= GPIO_ODR_ODR10;
	}
}

/*
* set LED 3 to ON if state is true, OFF if state is false
*/
void setLED3(uint16_t state) {
	//PA11
	if(state) {
		GPIOA->ODR &= ~GPIO_ODR_ODR11;
	} else {
		GPIOA->ODR |= GPIO_ODR_ODR11;
	}
}

/*
* set LED 4 to ON if state is true, OFF if state is false
*/
void setLED4(uint16_t state) {
	//PA12
	if(state) {
		GPIOA->ODR &= ~GPIO_ODR_ODR12;
	} else {
		GPIOA->ODR |= GPIO_ODR_ODR12;
	}
}



/*********************************************************
									Debugging functions
**********************************************************/

/*
* Run all debug functions from this library together
*/
void debugIO(void) {
	testSW1();
	testSW2345();
	testUSERLED();
}

/*
* Map USER SW to LEDs, when switch turns on, turn on all LEDs
*/
void testUSERLED(void) {
	setLED1(getSWUser());
	setLED2(getSWUser());
	setLED3(getSWUser());
	setLED4(getSWUser());
}

/*
*	Map SW1 (dipswitch) to LEDs, when switch turns on, turn on corresponding LED
*/
void testSW1(void) {
	setLED1(getSW1_1());
	setLED2(getSW1_2());
	setLED3(getSW1_3());
	setLED4(getSW1_4());
}

/*
*	Map other switches to LEDs, when switch turns on, turn on corresponding LED
*/
void testSW2345(void) {
	setLED1(getSW2());
	setLED2(getSW3());
	setLED3(getSW4());
	setLED4(getSW5());
}

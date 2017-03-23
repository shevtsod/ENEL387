/*
* FILENAME: main.c
*
*	DESCRIPTION:
*		Main program entry point
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Jan. 24, 2017
*/

#include "lib_clock.h"
#include "lib_io.h"
#include "lib_lcd.h"
#include "lib_pwm.h"
#include "lib_adc1.h"
#include "lib_interrupt.h"

int text = 0;

int main() {
	//Functions to execute once
	initializeClock();
	initializeIO();
	initializeLCD();
	initializePWM();
	initializeADC1();
	initializeSysTick();
	
	setPWMEnabled(0);
	
	//Functions to execute continuously
	while(1) {
		uint32HexToLCD(getValueFromChannel(0), 1);
		uint32HexToLCD(getValueFromChannel(1), 2);
		text ? println3("True") : println3("False");
		setPWMEnabled(text);
	}
	
}

void SysTick_Handler(void) {
	text = !text;
}

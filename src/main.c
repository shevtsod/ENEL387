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


int main() {
	//Functions to execute once
	initializeClock();
	initializeLCD();
	initializePWM();
	initializeADC1();
	initializeSysTick();
	initializeIO();
	
	setPWMEnabled(0);
	
	//Functions to execute continuously
	while(1) {
		//uint32HexToLCD(getValueFromChannel(0), 1);
		//uint32HexToLCD(getValueFromChannel(1), 2);
		
		//setLED1(getA());
		//setLED2(getB());
		//setLED3(getMenu());
		
		setLED1(getPosX());
		setLED3(getNegX());
		setLED4(getPosY());
		setLED2(getNegY());
		
		//setPWMEnabled(1);
	}
	
}

void SysTick_Handler(void) {

}

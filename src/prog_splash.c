/*
* FILENAME: prog_splash.h
*
*	DESCRIPTION:
*		Splash state
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*/

#include "prog_splash.h"

#define TIME_TO_WAIT 		15

static int counter = 0;

void stateSplash(void) {
	println1("   TINY GAME   ");
	println2("  CONSOLE v1.1    ");
	println4(" DANIEL SHEVTSOV");
	
	//Enable buzzer for duration of splash screen
	if(counter < 3)
		setPWMEnabled(1);
	
	// LED pattern corresponding to current counter value
	if (counter > 4 * TIME_TO_WAIT / 5) {
		setLED1(1);
	} else if (counter > 3 * TIME_TO_WAIT / 5) {
		setLED2(1);
	} else if (counter > 2 * TIME_TO_WAIT / 5) {
		setLED3(1);
	} else if (counter > TIME_TO_WAIT / 5) {
		setLED4(1);
	}
	
	if(counter < TIME_TO_WAIT) {
		counter++;
	} else {
		setLED1(0);
		setLED2(0);
		setLED3(0);
		setLED4(0);
		setPWMEnabled(0);
		setState(STATE_MAIN_MENU);
	}
}

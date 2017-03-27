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

int counter = 0;

void stateSplash(void) {
	println1("   TINY GAME   ");
	println2("    CONSOLE    ");
	println4(" DANIEL SHEVTSOV");
	
	if(counter < TIME_TO_WAIT)
		counter++;
	else
		setState(STATE_MAIN_MENU);
}

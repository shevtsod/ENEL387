/*
* FILENAME: lib_fsm.c
*
*	DESCRIPTION:
*		Finite State Machine library
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*/

#include "lib_fsm.h"
#include "lib_lcd.h"

//Reset value for currentState is Splash State
static int currentState = STATE_SPLASH;

/*
* Get the current state of the state machine
*/
int getState(void) {
	return currentState;
}

/*
* Set a new state for the statemachine
*/
void setState(int newState) {
	currentState = newState;
	//Clear the screen for the new state
	println1("");
	println2("");
	println3("");
	println4("");
}

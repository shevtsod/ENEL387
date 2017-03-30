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

//Libraries
#include <stdlib.h>

#include "lib_clock.h"
#include "lib_io.h"
#include "lib_lcd.h"
#include "lib_pwm.h"
#include "lib_adc1.h"
#include "lib_interrupt.h"
#include "lib_fsm.h"

#include "prog_splash.h"
#include "prog_main.h"
#include "prog_snake.h"
#include "prog_tictactoe.h"
#include "prog_connect4.h"

//For debugging purposes, you can set the initial state 
//(i.e. debug a certain game or menu)
#define INITIAL_STATE STATE_GAME_TICTACTOE

int main() {
	//Initialize required modules of STM32F100RB
	initializeClock();
	initializeIO();
	initializeLCD();
	initializePWM();
	initializeADC1();
	initializeEXTI();
	
	//Seed random number generator for games that require it
	//NOTE: Tried to include time.h and call srand(time(NULL)), but
	//      this caused the program to crash. See notes in
	//      doc/03_final_report.docx
	srand(0);
	
	//Reset all games
	resetSnake();
	resetTicTacToe();
	resetConnect4();
	
	//Reset outputs
	setLED1(0);
	setLED2(0);
	setLED3(0);
	setLED4(0);
	setPWMEnabled(0);
	
	setState(INITIAL_STATE);
	
	//Functions to execute continuously
	while(1) {
		//Based on currentState, call the function of that state
		switch(getState()) {
			case STATE_SPLASH: 
				stateSplash();
				break;
			case STATE_MAIN_MENU: 
				stateMain();
				break;
			case STATE_GAME_SNAKE: 
				stateGameSnake();
				break;
			case STATE_GAME_TICTACTOE: 
				stateGameTicTacToe();
				break;
			case STATE_GAME_CONNECT4: 
				stateGameConnect4();
				break;
			default: 
				break;
		}
	}
	
}

/**********************************************************************************
*                             INTERRUPT HANDLERS
**********************************************************************************/

/*
 EXTI2_IRQHandler is an interrupt handler for when the menu button (PD2) is pressed.
*/
void EXTI2_IRQHandler(void) {
	//Clear pending register for this interrupt
	EXTI->PR |= EXTI_PR_PR2;
	
	//For any state other than splash and main menu, set the state to main menu state
	if(getState() != STATE_SPLASH && getState() != STATE_MAIN_MENU)
		setState(STATE_MAIN_MENU);
	else
		return;
	
	//Reset all games
	resetSnake();
	resetTicTacToe();
	resetConnect4();
	
	//Clear outputs
	println1("");
	println2("");
	println3("");
	println4("");
	setLED1(0);
	setLED2(0);
	setLED3(0);
	setLED4(0);
	setPWMEnabled(0);
}

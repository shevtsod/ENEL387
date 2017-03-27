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

int main() {
	//Initialize
	initializeClock();
	initializeIO();
	initializeLCD();
	initializePWM();
	initializeADC1();
	initializeEXTI();
	
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

/*
 SysTick_Handler is an interrupt handler that executes when a timer expires
*/
void SysTick_Handler(void) {

}

/*
 EXTI2_IRQHandler is an interrupt handler for when the menu button (PD2) is pressed.
*/
void EXTI2_IRQHandler(void) {
	//Clear pending register for this interrupt
	EXTI->PR |= EXTI_PR_PR2;
	
	//For any state other than splash and main menu, set the state to main menu state
	if(getState() != STATE_SPLASH && getState() != STATE_MAIN_MENU)
		setState(STATE_MAIN_MENU);
}

/*
* FILENAME: prog_main.c
*
*	DESCRIPTION:
*		Main Menu state
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*/

#include "prog_main.h"

#define NUM_GAMES			3

static int currentSelection = 1;

void stateMain(void) {
	setPWMEnabled(0);
	println1("      MENU");
	
	//If user selects a game (presses A), then go to that game
	if(getA()) {
		//Reset outputs
		setLED4(0);
		setLED3(0);
		setLED2(0);
		
		switch(currentSelection) {
			case 1:
				setState(STATE_GAME_SNAKE);
				return;
			case 2:
				setState(STATE_GAME_TICTACTOE);
				return;
			case 3:
				setState(STATE_GAME_CONNECT4);
				return;
		}
	}
	
	//Allow user to change selected of game on the menu using the thumbstick
	if(getPosY()) {
		//Move selection up
		if(currentSelection == 1)
			currentSelection = NUM_GAMES;
		else
			currentSelection--;
		
	}
	if(getNegY()) {
		//Move selection down
		if(currentSelection == NUM_GAMES)
			currentSelection = 1;
		else
			currentSelection++;
	}
	
	//Display UI based on currently selected game
	switch(currentSelection) {
		case 1:
			println2(">SNAKE");
			println3(" TIC-TAC-TOE");
			println4(" CONNECT FOUR");
		
			setLED4(1);
			setLED3(0);
			setLED2(0);
			break;
		case 2:
			println2(" SNAKE");
			println3(">TIC-TAC-TOE");
			println4(" CONNECT FOUR");
		
			setLED4(0);
			setLED3(1);
			setLED2(0);
			break;
		case 3:
			println2(" SNAKE");
			println3(" TIC-TAC-TOE");
			println4(">CONNECT FOUR");
		
			setLED4(0);
			setLED3(0);
			setLED2(1);
			break;
	}
}

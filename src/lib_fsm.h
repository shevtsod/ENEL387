/*
* FILENAME: lib_fsm.h
*
*	DESCRIPTION:
*		Finite State Machine library
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*/

/* CONSTANTS */
#define STATE_SPLASH 					0
#define STATE_MAIN_MENU 			1
#define STATE_GAME_SNAKE 			2
#define STATE_GAME_TICTACTOE 	3
#define STATE_GAME_CONNECT4 	4

/* FUNCTION PROTOTYPES */
int getState(void);
void setState(int);

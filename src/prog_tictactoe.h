/*
* FILENAME: prog_tictactoe.h
*
*	DESCRIPTION:
*		Game 2 - Tic-Tac-Toe state
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*/

/* LIBRARY INCLUSIONS */
#include "lib_fsm.h"

#include "lib_lcd.h"
#include "lib_io.h"
#include "lib_adc1.h"
#include "lib_pwm.h"

/* FUNCTION PROTOTYPES */
void stateGameTicTacToe(void);
void resetTicTacToe(void);

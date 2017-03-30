/*
* FILENAME: prog_snake.h
*
*	DESCRIPTION:
*		Game 1 - Snake state
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*/

/* LIBRARY INCLUSIONS */
#include "lib_lcd.h"
#include "lib_io.h"
#include "lib_adc1.h"
#include "lib_pwm.h"
#include "lib_fsm.h"

/* FUNCTION PROTOTYPES */
void stateGameSnake(void);
void resetSnake(void);

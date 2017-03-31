/*
* FILENAME: prog_connect4.h
*
*	DESCRIPTION:
*		Game 3 - Connect Four state
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
void stateGameConnect4(void);
void resetConnect4(void);

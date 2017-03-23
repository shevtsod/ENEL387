/*
* FILENAME: lib_io.h
*
*	DESCRIPTION:
*		Function prototypes to initialize and use 
*		switches and LEDs on the ENEL 387 board.
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Jan. 24, 2017
*/

#include "stm32f10x.h"

/* FUNCTION PROTOTYPES */
void initializeIO(void);

//Get input values
uint16_t getSWUser(void);		//On-board USER Switch

uint16_t getSW1_1(void);		//Dipswitch 1
uint16_t getSW1_2(void);		//Dipswitch 2
uint16_t getSW1_3(void);		//Dipswitch 3
uint16_t getSW1_4(void);		//Dipswitch 4

uint16_t getSW2(void);			//2 - Red Button
uint16_t getSW3(void);			//3 - Green Button
uint16_t getSW4(void);			//4 - Blue Button
uint16_t getSW5(void);			//5 - Black Button

//Set output values
void setLED1(uint16_t state);
void setLED2(uint16_t state);
void setLED3(uint16_t state);
void setLED4(uint16_t state);

//Debugging functions
void debugIO(void);

void testUSERLED(void);
void testSW1(void);
void testSW2345(void);

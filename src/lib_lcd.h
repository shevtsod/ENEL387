/*
* FILENAME: lib_lcd.h
*
*	DESCRIPTION:
*		Function prototypes to initialize and use 
*		LCD on the ENEL 387 board.
*		The LCD used is the Hitachi HD44780U
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Jan. 31, 2017
*/

#include "stm32f10x.h"
#include "lib_clock.h"

/* CONSTANTS */
//The constants below are courtesy of Dave Duguid

//Commands for Hitachi 44780 compatible LCD controllers
#define LCD_8B2L 	0x38 	// Enable 8 bit data, 2 display lines
#define LCD_DCB 	0x0F 	// Enable Display, Cursor, Blink
#define LCD_MCR 	0x06 	// Set Move Cursor Right
#define LCD_CLR 	0x01 	// Home and clear LCD
#define LCD_LN1 	0x80 	// Set DDRAM to start of line 1
#define LCD_LN2 	0xC0 	// Set DDRAM to start of line 2

// Control signal manipulation for LCDs on 352/384/387 board
// PB0:RS PB1:ENA PB5:R/W*
#define LCD_CM_ENA 	0x00210002
#define LCD_CM_DIS 	0x00230000
#define LCD_DM_ENA 	0x00200003
#define LCD_DM_DIS 	0x00220001

/* FUNCTION PROTOTYPES */
void initializeLCD(void);

void toLCD(uint8_t mode, uint8_t data);
void stringToLCD(char* str);

void clearLCD(void);
void setCursorLine1(void);
void setCursorLine2(void);
void setCursorLine3(void);
void setCursorLine4(void);

void println1(char* str);
void println2(char* str);
void println3(char* str);
void println4(char* str);

void uint32HexToLCD(uint32_t hexValue, int line);

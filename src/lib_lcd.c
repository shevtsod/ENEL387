/*
* FILENAME: lib_lcd.c
*
*	DESCRIPTION:
*		Functions to initialize and use LCD
*		on the ENEL 387 board, based on definitions
*		in lib_lcd.h
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Jan. 31, 2017
*/

#include "lib_lcd.h"

/*
* Initializes the LCD according to the HD44780U instructions
*/
void initializeLCD(void) {
	//APB2 peripheral clock enable register
	//Enable clocks for port B, C
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN 
								| RCC_APB2ENR_IOPCEN;
	
	//Set PB0, PB1, PB5, and PC0 to PC7 as outputs	
	GPIOB->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE5;
	GPIOB->CRL &= ~GPIO_CRL_CNF0 
							& ~GPIO_CRL_CNF1 
							& ~GPIO_CRL_CNF5;
	GPIOC->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1
							| GPIO_CRL_MODE2 | GPIO_CRL_MODE3
							| GPIO_CRL_MODE4 | GPIO_CRL_MODE5
							| GPIO_CRL_MODE6 | GPIO_CRL_MODE7;
	GPIOC->CRL &= ~GPIO_CRL_CNF0 & ~GPIO_CRL_CNF1 
							& ~GPIO_CRL_CNF2 & ~GPIO_CRL_CNF3 
							& ~GPIO_CRL_CNF4 & ~GPIO_CRL_CNF5
							& ~GPIO_CRL_CNF6 & ~GPIO_CRL_CNF7;
	
	//Wait for 20ms
	delayMS(20);
	
	//Send 0x38 to display
	toLCD(0, LCD_8B2L);
	
	//Wait 5ms
	delayMS(5);
	
	//Send 0x38 to display
	toLCD(0, LCD_8B2L);
	
	//Wait 200us
	delay(1200);
	
	//Send 0x38 to display
	toLCD(0, LCD_8B2L);
	
	//Send final initialization commands
	toLCD(0, LCD_8B2L);
	toLCD(0, 0x8);
	toLCD(0, LCD_CLR);
	toLCD(0, 0x6);
	
	//Enable display
	toLCD(0, 0xC);
	
	//Show cursor (for debugging purposes)
	//toLCD(0, 0xF);
	
}

/*
* Sends 8-bit data to the LCD.
*	mode = 1 -> Data to display
* mode = 0 -> Command (Instruction)
*
* Note: Portions of this function are courtesy of Dave Duguid
*/
void toLCD(uint8_t mode, uint8_t data) {
	if(mode == 1)
		GPIOB->BSRR = LCD_DM_ENA;
	else
		GPIOB->BSRR = LCD_CM_ENA;
	
	GPIOC->ODR &= 0xFF00;
	GPIOC->ODR |= data;
	
	delay(5000);
	
	if(mode == 1)
		GPIOB->BSRR = LCD_DM_DIS;
	else
		GPIOB->BSRR = LCD_CM_DIS;
	
	delay(10000);
}

/*
* Sends a C string (array of chars terminated by \0) 
* to output to the LCD.
*/
void stringToLCD(char* str) {
	int i = 0;
	while(str[i] != '\0') {
		toLCD(1, str[i++]);
	}
	
	while(i < 16) {
		toLCD(1, ' ');
		i++;
	}
}

/*
* Clears the LCD screen from all characters that were stored in it
*/
void clearLCD(void) {
	toLCD(0, LCD_CLR);
}

/*
* Returns the cursor to the first character posititon on line 1
*/
void setCursorLine1(void) {
	toLCD(0, 0x80); //Position 00
}

/*
* Returns the cursor to the first character posititon on line 2
*/
void setCursorLine2(void) {
	toLCD(0, 0xC0); //Position 40
}

/*
* Returns the cursor to the first character posititon on line 3
*/
void setCursorLine3(void) {
	toLCD(0, 0x90); //Position 10
}

/*
* Returns the cursor to the first character posititon on line 4
*/
void setCursorLine4(void) {
	toLCD(0, 0xD0); //Position 50
}

/*
* Prints a string str to line 1
*/
void println1(char* str) {
	setCursorLine1();
	stringToLCD(str);
}

/*
* Prints a string str to line 2
*/
void println2(char* str) {
	setCursorLine2();
	stringToLCD(str);
}

/*
* Prints a string str to line 3
*/
void println3(char* str) {
	setCursorLine3();
	stringToLCD(str);
}

/*
* Prints a string str to line 4
*/
void println4(char* str) {
	setCursorLine4();
	stringToLCD(str);
}


/*
* Helper function to convert a 32 bit hex value to a string
*/
void uint32HexToLCD(uint32_t hexValue, int line) {
	char outputString[10];
	
	int shift = 28;
	int i = 2;
	int tempHex;
	char tempHexChar;
	
	outputString[0] = '0';
	outputString[1] = 'x';
	
	do {
		tempHex = (hexValue >> shift) & 0xF;

		if(tempHex >= 0 && tempHex <= 9)
			tempHexChar = tempHex + 48;
		else if(tempHex >= 10 && tempHex <= 15)
			tempHexChar = tempHex + 55;
		
		outputString[i++] = tempHexChar;
		
		shift -= 4;
		
	} while (i != 10);
	
	outputString[i] = '\0';
	
	switch(line) {
		case 1:
			println1(outputString);
			break;
		case 2:
			println2(outputString);
			break;
		case 3:
			println3(outputString);
			break;
		case 4:
			println4(outputString);
			break;
		default: break;
		
	}
}

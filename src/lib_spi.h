/*
* FILENAME: lib_spi.h
*
*	DESCRIPTION:
*		Function prototypes to initialize and use SPI
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Feb. 28, 2017
*/

#include "stm32f10x.h"

/* FUNCTION PROTOTYPES */
void initializeSPI2(void);

uint16_t useSPI2(uint16_t data);

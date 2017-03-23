/*
* FILENAME: lib_spi.c
*
*	DESCRIPTION:
*		Functions to initialize and use SPI
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*
*	DATE: Feb. 28, 2017
*/

#include "lib_spi.h"

/*
 Initializes SPI2 by configuring its required registers
*/
void initializeSPI2(void) {
	//Turn on clocks for SPI2, GPIOB, AFIO
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN
								| RCC_APB2ENR_IOPBEN;
	
	//Configure I/O ports:
	//MOSI (PB15) = alternate function push-pull output
	//MISO (PB14) = floating input (default already sets this)
	//SCK (PB13) = alternate function push-pull output
	//NSS (PB12) = general purpose push-pull output
	GPIOB->CRH |= GPIO_CRH_MODE15_1 | GPIO_CRH_MODE15_0;
	GPIOB->CRH |= GPIO_CRH_CNF15_1;
	GPIOB->CRH &= ~GPIO_CRH_CNF15_0;
	
	GPIOB->CRH |= GPIO_CRH_MODE13_1 | GPIO_CRH_MODE13_0;
	GPIOB->CRH |= GPIO_CRH_CNF13_1;
	GPIOB->CRH &= ~GPIO_CRH_CNF13_0;
	
	GPIOB->CRH |= GPIO_CRH_MODE12_1 | GPIO_CRH_MODE12_0;
	GPIOB->CRH &= ~GPIO_CRH_CNF12_1 & ~GPIO_CRH_CNF12_0;
	
	
	//Alternative to the above
	//GPIOB->CRH = 0xB4B30000;
	
	//Set NSS (PB12) high
	GPIOB->BSRR |= GPIO_BSRR_BS12;
	
	//SPI2_CR2: SSOE is OFF
	SPI2->CR2 = 0x0;
	
	//SPI2_CR1: DFF=1, SMM=1, SSI=1, BR= pclk/64, MSTR=1
	SPI2->CR1 = 0xB2C;
	
	//Enable SPI2 by setting the SPE bit
	SPI2->CR1 |= SPI_CR1_SPE;
	
}

/*
 Writes data to SPI2 MOSI and returns MISO value
*/
uint16_t useSPI2(uint16_t data) {
	//Drive NSS (PB12) low
	GPIOB->BSRR &= ~GPIO_BSRR_BS12;
	GPIOB->BSRR |= GPIO_BSRR_BR12;
	
	//Wait for TxE bit in SPI2_SR to be 1
	while((SPI2->SR & SPI_SR_TXE) == 0) {
		//Empty waiting loop
	}		
	
	//Write to SPI2_DR the data value to transmit
	SPI2->DR = data;
	
	//Wait for RxNE bit in SPI2_SR to be 1
		while((SPI2->SR & SPI_SR_RXNE) == 0) {
		//Empty waiting loop
	}
	
	//Drive NSS (PB12) high
	GPIOB->BSRR &= ~GPIO_BSRR_BR12;
	GPIOB->BSRR |= GPIO_BSRR_BS12;
	
	//Read from SPI2_DR to clear RxNE flag in SPI2_SR
	return SPI2->DR;
}

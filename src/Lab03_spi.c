//----------------------------------
// Lab 3 - Part 3: SPI - Lab03_spi.c
//----------------------------------
//

#include "init.h"
#include <assert.h>

// If needed:
//#include <stdio.h>
//#include <stdlib.h>
uint8_t byte;
unsigned char input;
unsigned int var = 0;
/*
 * For convenience, configure the SPI handler here
 */
// See 769 Description of HAL drivers.pdf, Ch. 58.1 or stm32f7xx_hal_spi.c
void configureSPI()
{
	hspi.Instance = SPI2; // Please use SPI2!
	hspi.Init.Mode = SPI_MODE_MASTER; // Set master mode
	hspi.Init.TIMode = SPI_TIMODE_DISABLE; // Use Motorola mode, not TI mode
	hspi.Init.Direction = SPI_DIRECTION_2LINES;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi.Init.NSS = SPI_NSS_HARD_OUTPUT;
/*
 * ... You get the idea.
 */

	HAL_SPI_Init(&hspi);
	//
	// Note: HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
	//
	// HAL_SPI_Init() will call HAL_SPI_MspInit() after reading the properities of
	// the passed SPI_HandleTypeDef. After finishing the MspInit call, it will set
	// the SPI property bits. This is how all HAL_[peripheral]_Init() functions work.
}

/*
 * This is called upon SPI initialization. It handles the configuration
 * of the GPIO pins for SPI.
 */
 // Do NOT change the name of an MspInit function; it needs to override a
 // __weak function of the same name. It does not need a prototype in the header.
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	// SPI GPIO initialization structure here
	GPIO_InitTypeDef gpio;
	if (hspi->Instance == SPI2)
	{
		// Enable SPI GPIO port clocks, set HAL GPIO init structure's values for each
		// SPI-related port pin (SPI port pin configuration), enable SPI IRQs (if applicable), etc.
		__SPI2_CLK_ENABLE();
		__GPIOA_CLK_ENABLE();
		__GPIOB_CLK_ENABLE();

		//PA12 SCK
		gpio.Mode = GPIO_MODE_AF_PP;
		gpio.Alternate = GPIO_AF5_SPI2;
		gpio.Speed = GPIO_SPEED_LOW;
		gpio.Pull = GPIO_PULLUP;
		gpio.Pin = GPIO_PIN_12;
		HAL_GPIO_Init(GPIOA, &gpio);

		//PA11 CS
		gpio.Pin = GPIO_PIN_11;
		HAL_GPIO_Init(GPIOA, &gpio);

		//PB14 MISO
		gpio.Pin = GPIO_PIN_14;
		HAL_GPIO_Init(GPIOB, &gpio);

		//PB15 MOSI
		gpio.Pin = GPIO_PIN_15;
		HAL_GPIO_Init(GPIOB, &gpio);


	}
}


int main(void)
{
	Sys_Init();

	// For convenience
	configureSPI();

    printf("\033[2J Stuff\r\n");
	while(1) {
		input = getchar();
		printf("%c", input);
		fflush(stdout);
		HAL_SPI_TransmitReceive_DMA(&hspi, (uint8_t*)&input, &byte, 1);
		HAL_Delay(1);
		printf("\033[39C%c\r\n", byte);

	}

// See 769 Description of HAL drivers.pdf, Ch. 58.2.3 or stm32f7xx_hal_spi.c
//
//	HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
//
}

void DMA1_Stream3_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&spi_rx);
}

void DMA1_Stream4_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&spi_tx);

}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI2){
		var = 1;
	}
}



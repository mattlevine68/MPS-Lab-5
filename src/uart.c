#include "uart.h"

// Initialize Hardware Resources
// Peripheral's clock enable
// Peripheral's GPIO Configuration
void HAL_UART_MspInit(UART_HandleTypeDef *huart){
	GPIO_InitTypeDef  GPIO_InitStruct;

	if (huart->Instance == USART1) {
		// Enable GPIO Clocks
		__GPIOA_CLK_ENABLE();

		// Initialize TX Pin
		GPIO_InitStruct.Pin       = GPIO_PIN_9;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); //TX Config

		// Initialize RX Pin
		GPIO_InitStruct.Pin = GPIO_PIN_10;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); //RX Config

		// Enable UART Clocking
		__USART1_CLK_ENABLE();

		///////////////////////////////////////////////
		// Add DMA initializations here
		///////////////////////////////////////////////
		//UART1_TX
		__HAL_RCC_DMA1_CLK_ENABLE();
		__HAL_RCC_DMA2_CLK_ENABLE();
		hdma_tx.Instance = DMA2_Stream7;
		hdma_tx.Init.Channel = DMA_CHANNEL_4;
		hdma_tx.Init.Mode = DMA_NORMAL;
		hdma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_tx.Init.PeriphDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

		HAL_DMA_Init(&hdma_tx);

		//UART1_RX
		hdma_rx.Instance = DMA2_Stream5;
		hdma_rx.Init.Channel = DMA_CHANNEL_4;
		hdma_rx.Init.Mode = DMA_NORMAL;
		hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_rx.Init.PeriphDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

		HAL_DMA_Init(&hdma_rx);
	    __HAL_LINKDMA(&USB_UART, hdmarx, hdma_rx);
	    __HAL_LINKDMA(&USB_UART, hdmatx, hdma_tx);

	    //SPI2_TX
		spi_tx.Instance = DMA1_Stream4;
		spi_tx.Init.Channel = DMA_CHANNEL_0;
		spi_tx.Init.Mode = DMA_NORMAL;
		spi_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		spi_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		spi_tx.Init.MemInc = DMA_MINC_ENABLE;
		spi_tx.Init.Priority = DMA_PRIORITY_HIGH;
		spi_tx.Init.PeriphDataAlignment = DMA_MDATAALIGN_BYTE;
		spi_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		spi_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

		HAL_DMA_Init(&spi_tx);
		//SPI2_RX
		spi_rx.Instance = DMA1_Stream3;
		spi_rx.Init.Channel = DMA_CHANNEL_0;
		spi_rx.Init.Mode = DMA_NORMAL;
		spi_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		spi_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		spi_rx.Init.MemInc = DMA_MINC_ENABLE;
		spi_rx.Init.Priority = DMA_PRIORITY_HIGH;
		spi_rx.Init.PeriphDataAlignment = DMA_MDATAALIGN_BYTE;
		spi_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		spi_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

		HAL_DMA_Init(&spi_rx);
	    //SPI2 Priority
	    __HAL_LINKDMA(&hspi, hdmarx, spi_rx);
	    __HAL_LINKDMA(&hspi, hdmatx, spi_tx);

	    HAL_NVIC_SetPriority(DMA1_Stream3_IRQn,0,0);
	    HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);

	    HAL_NVIC_SetPriority(DMA1_Stream4_IRQn,1,1);
	    HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);





	} else if (huart->Instance == USART6) {
		// Enable GPIO Clocks
		__GPIOC_CLK_ENABLE();

		// Initialize TX Pin
		GPIO_InitStruct.Pin       = GPIO_PIN_6;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); //TX Config

		// Initialize RX Pin
		GPIO_InitStruct.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); //RX Config

		// Enable UART Clocking
		__USART6_CLK_ENABLE();

	}
}

//UART Initialization
void initUart(UART_HandleTypeDef* Uhand, uint32_t Baud, USART_TypeDef* Tgt) {
	Uhand->Instance        = Tgt;

	Uhand->Init.BaudRate   = Baud;
	Uhand->Init.WordLength = UART_WORDLENGTH_8B;
	Uhand->Init.StopBits   = UART_STOPBITS_1;
	Uhand->Init.Parity     = UART_PARITY_NONE;
	Uhand->Init.Mode       = UART_MODE_TX_RX;
	Uhand->Init.HwFlowCtl  = UART_HWCONTROL_NONE;

	HAL_UART_Init(Uhand);
}

/* ============================================================================

Reassigning _write and _read to USB_UART by default.

Note the following for an explanation of syntax:

HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)

HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)

============================================================================= */

///////////////////////////////////////////////
// Change _write() and _read() to use DMAs
///////////////////////////////////////////////

// Make printf(), putchar(), etc. default to work over USB UART
int _write(int file, char *ptr, int len) {
	HAL_DMA_Start(&hdma_tx, (uint32_t)ptr,(uint32_t)&USB_UART.Instance->TDR,len);
	USB_UART.Instance->CR3 |= USART_CR3_DMAT;
	HAL_UART_Transmit_DMA(&USB_UART, (uint8_t*) ptr, len);
	HAL_DMA_PollForTransfer(&hdma_tx, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
	USB_UART.Instance->CR3 &= ~USART_CR3_DMAT;
	return len;
}

// Make scanf(), getchar(), etc. default to work over USB UART
int _read(int file, char *ptr, int len) {

	*ptr = 0x00; // Clear the character buffer because scanf() is finicky
	len = 1; // Again because of scanf's finickiness, len must = 1
	HAL_DMA_Start(&hdma_rx,(uint32_t)&USB_UART.Instance->RDR,(uint32_t)ptr,len);
	USB_UART.Instance->CR3 |= USART_CR3_DMAR;
	HAL_UART_Receive_DMA(&USB_UART, (uint8_t*) ptr, len);
	HAL_DMA_PollForTransfer(&hdma_rx, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
	USB_UART.Instance->CR3 &= ~USART_CR3_DMAR;
	return len;
}

/* ============================================================================

Custom UART functions that can be mapped to any UART of your choice when called

Note the following for an explanation of syntax:

HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)

HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)

============================================================================= */

// Print a string on the specified UART. (Basically a redirectable puts)
void uart_print(UART_HandleTypeDef *huart, char* string) {
    HAL_UART_Transmit(huart, (uint8_t*) string, strlen((const char*)string), 1000);
}

// Get one character
// 'echo' means enable (1) or disable (0) echoing of characters
char uart_getchar(UART_HandleTypeDef *huart, uint8_t echo) {
	char input[1];
	HAL_UART_Receive(huart, (uint8_t *)input, 1, HAL_MAX_DELAY);
	if (echo) HAL_UART_Transmit(huart, (uint8_t*) input, 1, 1000);
	return (char)input[0];
}

// Send one character
void uart_putchar(UART_HandleTypeDef *huart, char * input) {
	HAL_UART_Transmit(huart, (uint8_t*) input, 1, 1000);
}

// Collects characters until size limit or an endline is recieved
// Returns number of characters collected
// 'max size' should match the size of the array or be smaller
int uart_getline(UART_HandleTypeDef *huart, char * input, int max_size)
{
  char single;
  int i = 0;

	while(1)
	{
		if (i > max_size)
      {
				break;
			}

		single = uart_getchar(huart, 1); // Get one character

  	if (single == '\n' || single == '\r') // Unix & co. use \n, Windows uses \r\n
			break;
  	else
			input[i] = single;
  	i++;
	}
  return i; // The way this is set up, it will always report the wrong size
}

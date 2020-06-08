//------------------------------------------------------------------------------------
// Hello.c
//------------------------------------------------------------------------------------
//
// Test program to demonstrate serial port I/O.  This program writes a message on
// the console using the printf() function, and reads characters using the getchar()
// function.  An ANSI escape sequence is used to clear the screen if a '2' is typed.
// A '1' repeats the message and the program responds to other input characters with
// an appropriate message.
//
// Any valid keystroke turns on the green LED on the board; invalid entries turn it off
//


//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include "stm32f769xx.h"
#include "init.h"

#include<stdint.h>
#include <stdlib.h>
#include <stdio.h>

UART_HandleTypeDef huart;
DMA_HandleTypeDef hdma_tx;
DMA_HandleTypeDef hdma_rx;

//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
int main(void)
	{
    Sys_Init(); // This always goes at the top of main (defined in init.c)
    //initUart(&huart, 115200, USART1);
    HAL_UART_MspInit(&huart);

    printf("\033[2J\033[;H"); // Erase screen & move cursor to home position
  //  fflush(stdout); // Need to flush stdout after usSing printf that doesn't end in \n
    printf("\033[33;44m");
    //fflush(stdout);
    char choice = '*';
    int row =12;
//	char in[3];
//   int size = 3;

    printf("\033[2;25H");
    fflush(stdout);
    printf("PRESS <ESC> OR <CTL>+[ TO QUIT\r\n");
    printf("\033[6;1H");
    fflush(stdout);

     //__HAL_RCC_GPIOJ_CLK_ENABLE(); // Need to enable clock for peripheral bus on GPIO Port J

    volatile uint32_t * RCC_AHB1_CLOCK_ENABLE = (uint32_t*) 0x40023830U; // Enable clock for peripheral bus on GPIO Port J
    *RCC_AHB1_CLOCK_ENABLE |= 512U; // Bitmask for RCC AHB1 initialization: 0x00000200U or 512U in decimal

    GPIOJ->MODER |= 1024U; //Bitmask for GPIO J Pin 5 initialization (set it to Output mode): 0x00000400U or 1024U in decimal
    GPIOJ->BSRR = (uint16_t)GPIO_PIN_5; // Turn on Green LED (LED2)
    GPIOJ->BSRR = (uint32_t)GPIO_PIN_5 << 16; // Turn off Green LED (LED2)
    GPIOJ->ODR ^= (uint16_t)GPIO_PIN_5; // Toggle LED2

// It doesn't get lower level than this!
//    volatile uint32_t * GREENLEDMODER = (uint32_t*) 0x40022400U; // Init GPIO J Pin 5 (LED2 with no Alt. func.) to Output
//    *GREENLEDMODER |= 1024U; // Bitmask for GPIO J Pin 5 initialization: 0x00000400U or 1024U in decimal

    volatile uint32_t * GREENLEDBSRR = (uint32_t*) 0x40022418U; // Address of GPIO J Bit Set/Reset Register
    *GREENLEDBSRR = (uint16_t)0x0020U; // Turn on Green LED (LED2)

    HAL_Delay(1000); // Pause for a second

//    volatile uint32_t * GREENLEDODR = (uint32_t*) 0x40022414U; // Address of GPIO J Output Data Register
//    *GREENLEDODR ^= (uint16_t)0x0020U; // Toggle Green LED (LED2)

    while(1)
    {
    	printf("\033[6;1H"); //set cursor postion to line 6
    	fflush(stdout);
        printf("The keyboard character is ");
        fflush(stdout);
        printf("\033[31;44m"); // changes to red text blue background
        fflush(stdout);
        printf("%c\r\n",choice);
        printf("\033[33;44m"); // changes to yellow text blue background
        fflush(stdout);
        // ** delete printf("( Welcome to Microprocessor Systems )\r\n\n\n");
        // ** delete printf("1=repeat, 2=clear, 0=quit.\r\n\n"); // Menu of choices
				// Don't forget to end printf with newline or run fflush(stdout) after it!

//        choice = uart_getchar(&USB_UART, 1);
				choice = getchar();
				int output = choice;
				//putchar(choice);

// Messing around with stuff:
//        putchar('9'); // Putchar is weird, man.
//				choice = uart_getchar(&USB_UART, 0);
//				uart_putchar(&USB_UART, &choice);
//				puts("stuff\r\n");

        // select which option to run
//        HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_5, GPIO_PIN_SET);         // Turn green LED on (GPIO_PIN_SET == 1)
        *GREENLEDBSRR = (uint16_t)0x0020U; // Turn on Green LED (LED2)
        if (output == 27) {
            return 1;
        }

        if(output <= 31){
        	printf("\033[12;24r");//if it reaches line 24 its starts scrolling
        	fflush(stdout);
        	printf("\a\n");
        	if (row == 12){
        		printf("\033[12;1H"); //start at line 12
        		fflush(stdout);
        		printf("\033[33;44;5m"); // changes to yellow text blue background and blink
        		fflush(stdout);
        		printf("\033[s"); //save cursor
        		fflush(stdout);
        		printf("\aThe keyboard character $0%x", choice);
        		fflush(stdout);
        		printf(" is ");
        		fflush(stdout);
        		printf("\033[4m 'not printable.'\r\n");
        		fflush(stdout);
        		printf("\033[0m");
        		fflush(stdout);
        		printf("\033[33;44m"); // changes to yellow text blue background
        		fflush(stdout);
        		row++;
        	}
        	else if(row!=12){
        		printf("\033[u"); //restore cursor
        		fflush(stdout);
        		printf("\033[B"); // move down cursor
        		fflush(stdout);
        		printf("\033[s"); //save cursor
        		fflush(stdout);
        		printf("\033[33;44;5m"); // changes to yellow text blue background and blink
				fflush(stdout);
				printf("\aThe keyboard character $0%x", choice);
				fflush(stdout);
				printf(" is ");
				fflush(stdout);
				printf("\033[4m 'not printable.'\r\n");
				fflush(stdout);
				printf("\033[0m");
				fflush(stdout);
				printf("\033[33;44m"); // changes to yellow text blue background
				fflush(stdout);
        	}

        }
        /*
        else if(choice == '1')
            printf("\r\n\nHere we go again.\r\n\n");
        else if(choice == '2')          // clear the screen with <ESC>[2J
        {
            printf("\033[2J\033[;H");
            fflush(stdout);
        }
        */

//        else
//        {
//            // inform the user how bright he is
//            *GREENLEDBSRR = (uint32_t)0x0020U << 16; // Turn off Green LED (LED2)
//            printf("\r\nA \"");
//						putchar(choice);
////						uart_print(&USB_UART, choice);
//            printf("\" is not a valid choice.\r\n\n");
//        }


// Messing around with more stuff
//				printf("Enter an alphanumeric sequence (press <enter> if you want to send less than %d characters): \r\n", size + 1);
//				int a = uart_getline(&USB_UART, in, size);
//				printf("\r\nuart_getline result: %d\r\n", a);
//
		}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "global.h"
#include "avr_uart.h"

#define BUFFER_LENGTH 	80
#define UART_PROMPT		"IO>"

int main()
{
	char *cmd, *param;
	unsigned char num_of_params = 0;
	uint8_t printCMD = 0;			// Disabling command and parameter printing on cmd processing
	
	configSTDIO();					// Configure stdin and stdout to be connected to UART
	initUART(115200, PARITY_NO);	// Initialize UART with custom bitrate and partiy setting unsing 8 bit data, 1 stop bit

	printf("\nUART Command Line Interface\nCompiled on: %s at %s\n\n", __DATE__, __TIME__);
	printUARTPrompt(UART_PROMPT); 	// print UART prompt to show the user, that the ISR-driven UART interface is available

	while (1)
	{
		if (UART_CMD_RECEIVED)		// If receive interrupt enable bit (RXCIE0) is deactivated by ISR, a recevied command line can be processed
		{
			num_of_params = processCMD(printCMD); 	// mandatory function to process and print received commands and parameters regarding printCMD being 0 or 1

			// getUARTCmd() returns the first string received, which is defined to be the command
			if ((cmd = getUARTCmd()) == NULL)
				printf("\n");							// No command has been received

			// Set onboard LED
			else if(strcmp(cmd, "led") == 0)
			{
				if((param = getUARTParam()) != NULL)	// Each time getUARTParam() is called, the next parameter of the input buffer gets returned as char*
				{
					if((atoi(param)) == 1)
					{
						DDRB |= (1 << PB5);
						PORTB |= (1 << PB5);
						printf("Onboard LED on.\n");
					}
					else if((atoi(param)) == 0) 
					{
						PORTB &= ~(1 << PB5);
						printf("Onboard LED off.\n");
					}
					else
						printf("Wrong parameter: %d\n", atoi(param));
				}
				else printf("Parameter missing [0/1]!\n");
			}

			else printf("Unknown command\n");

			printUARTPrompt(UART_PROMPT);				// to be used to re-enable interrupt controlled character reception
		}
	}
}
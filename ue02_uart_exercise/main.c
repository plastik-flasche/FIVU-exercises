#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

int main() {
    DDRB = (1 << PB5);
    PORTB &= ~(1 << PB5);

    // Initialize the UART with the settings: 57600/8N1

    // Note: Register UBRR0 is a 16-bit register.
    UBRR0H = 0;
    UBRR0L = 34;
    UCSR0A = (1 << 1);

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    char text[100] = "Hello World!\n";
    for (uint8_t i = 0; i < sizeof(text); i++) {
        // Wait until the transmit buffer is ready to receive new data -> see register UCSR0A on page 200
        //
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        UDR0 = text[i];
    }

    while (1) {
        if (UCSR0A & (1 << RXC0)) {
            char receivedKey = UDR0;
            switch (receivedKey) {
                case '1':  // turn on the onboard led on port PB5
                {
                    // The following text will be sent to the computer in a later step.
                    strcpy(text, "LED switched on!\n");
                    PORTB |= (1 << PB5);
                    break;
                }

                case '0':  // turn off the onboard led on port PB5
                {
                    // The following text will be sent to the computer in a later step.
                    strcpy(text, "LED switched off!\n");
                    PORTB &= ~(1 << PB5);
                    break;
                }

                default: {
                    // The following text will be sent to the computer in a later step.
                    strcpy(text, "unknown command!\n");
                }
            }

            // A response is sent to the computer.
            for (uint8_t i = 0; text[i] != 0; i++) {
                // Wait until the transmit buffer is ready to receive new data -> see register UCSR0A on page 200
                while (!(UCSR0A & (1 << UDRE0)))
                    ;
                UDR0 = text[i];
            }
            text[0] = '\0';
        }
    }
    return 0;
}
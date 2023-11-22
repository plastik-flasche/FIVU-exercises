# avr_uart_CLI

This is a demo project providing a command line interface for megaAVR in particular for ATmega48A/PA/88A/PA/168A/PA/328/P, tested
with ATmega328p on an Arduino Uno R3, to show how to use different possibilities for receiving serial data from PuTTY, Serial
Monitor (VSC), HTerm or any other programme using COM-Ports for serial communication.

String termination is \r (CR = Carriage Return) or \r\n (CR LF = Carriage Return Line Feed).
Standard baud rate is 115200, 8 data bits, 1 stop bit and no parity.
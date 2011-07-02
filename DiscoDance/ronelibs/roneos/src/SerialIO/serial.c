/**
 * @file serial.c
 *
 *  Created on: Jul 21, 2010
 *      Author: sjb2
 */
#include <stdio.h>

#include "inc/lm3s8962.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/ssi.h"
#include "driverlib/interrupt.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "roneos.h"

//#include "usb_serial_structs.h"
#include "roneos.h"

#define RX_QUEUE_SIZE 200
#define PORTDELAY 1000
char serial_rx_queue[RX_QUEUE_SIZE];
int next_char = 0;
int start = 0;
int msg_avail = 0;

osSemaphoreHandle rxSem;

/**
 * 	@brief Sends out a character.
 *
 * 	Sends the character c to the transmit FIFO for the port specified by UARTO_BASE (base address).
 * 	@param c is the character to be transmitted
 * 	@returns void
 */
void sputchar(char c) {
	UARTCharPut(UART0_BASE, c);
}

//void serial_send(const char* buffer, uint32 size) {
//	int i;
//	for (i = 0; i < size; i++) {
//		// Write the next character to the UART.
//		UARTCharPut(UART0_BASE, buffer[i]);
//	}
//}
//
//
//void serial_send_string(const char* string) {
//	const char *cPtr = string;
//	do {
//		while (!UARTSpaceAvail(UART0_BASE)) { }
//		UARTCharPut(UART0_BASE, *cPtr++);
//	} while (*cPtr != 0);
//}

/**
 * 	@brief Function that allows us to print binary.
 *
 * 	Creates a binary version of the input character and points the input pointer to it.
 *	@param *string is the char pointer that will point to the binary bitstring of val
 *	@param val is the value to be converted to binary
 *	@return a pointer to the binary string converted from val
 */
char * bitString8(char * string, uint8 val) {
	uint8 i;
	char * stringTemp = string;

	for (i = 0; i < 8; i++) {
		if (val & 0b10000000) {
			*stringTemp++ = '1';
		} else {
			*stringTemp++ = '0';
		}
		val = val << 1;
	}
	*stringTemp = '\0';
	return (string);
}

/**
 * @brief Function used to handle UART interrupts
 *
 * @returns void
 */
void uart_int_handler(void) {
	unsigned long ulStatus;
	char rxChar;
	portBASE_TYPE val;
	portBASE_TYPE taskWoken = pdFALSE;

	// Get the interrupt status.
	ulStatus = MAP_UARTIntStatus(UART0_BASE, true);

	// Clear the asserted interrupts.
	MAP_UARTIntClear(UART0_BASE, ulStatus);

	// Loop while there are characters in the receive FIFO.

	while (MAP_UARTCharsAvail(UART0_BASE)) {
		// Read the next character from the UART and write it back to the UART.
		//next line doesnt work anyhow
		rxChar = UARTCharGetNonBlocking(UART0_BASE);

		switch (rxChar) {
		case '\b': {
			if (next_char > start) {
				next_char = (next_char - 1) % RX_QUEUE_SIZE;
				MAP_UARTCharPut(UART0_BASE, '\b');
				MAP_UARTCharPut(UART0_BASE, ' ');
				MAP_UARTCharPut(UART0_BASE, '\b');
			} else {
				return;
			}
			break;
		}
		case '\r': {
			MAP_UARTCharPut(UART0_BASE, '\r');
			MAP_UARTCharPut(UART0_BASE, '\n');
			break;
		}
		default:
			MAP_UARTCharPut(UART0_BASE, rxChar);
			break;

		}
	}
	//TODO store this char in an string
	serial_rx_queue[next_char] = rxChar;
	//MAP_UARTCharPut(UART0_BASE, serial_rx_queue[next_char]);
	if (rxChar == '\r') {
		osSemaphoreTake(rxSem, PORTDELAY);
		//MAP_UARTCharPut(UART0_BASE, 'Y');
		msg_avail++;

		osSemaphoreGiveFromISR(rxSem, &taskWoken);
	}
	next_char = (next_char + 1) % RX_QUEUE_SIZE;
}

/**
 * Get a message up to the newline.
 * Return the length of message retrieved including newline.
 * Need to make this blocking.
 */
int serial_get_string(char * buffer, int buflen) {
	int i;
	if (buflen < 1) {
		return -1;
	}
	//busy wait
	while (msg_avail < 1) {
		i = 0;
	}

	for (i = 0; i < buflen; i++) {
		buffer[i] = serial_rx_queue[start];
		start = (start + 1) % RX_QUEUE_SIZE;
		if (buffer[i] == '\r') {
			osSemaphoreTake(rxSem, PORTDELAY);
			msg_avail--;
			osSemaphoreGive(rxSem);
			buffer[i + 1] = '\0';
			return (i + 1);
		}
	}

	//osSemaphoreGive(rxSem);
	return buflen;
}

void __attribute__ ((interrupt)) __cs3_isr_uart0(void) {
	uart_int_handler();
}

/**
 * 	@brief Initializes serial I/O.
 *
 * 	Enable the peripherals used by this example.
 * 	Enable processor interrupts.
 * 	Set GPIO A0 and A1 as UART pins.
 * 	Configure the UART for 115,200, 8-N-1 operation.
 *	Enable the UART interrupt.
 *	@returns void
 */
void serial_init() {
	// Enable the peripherals used by this example.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	// Enable processor interrupts.
	//TODO why do we enable interrupts here?
	MAP_IntMasterEnable();

	// Set GPIO A0 and A1 as UART pins.
	MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	// Configure the UART for 115,200, 8-N-1 operation.
	MAP_UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	// Enable the UART interrupt.
	MAP_IntEnable(INT_UART0);
	MAP_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

	//Create semaphore for receive queue;
	osSemaphoreCreateBinary(rxSem);

}

#include <string.h>

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
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#include "driverlib/debug.h"
#include "driverlib/pwm.h"

#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"

#include "roneos.h"
#include "msp430.h"
#include "bump_sensor.h"

void msp430Init(void) {
}

#define MSP430_MESSAGE_LENGTH	4
#define MSP430_SPI_DELAY 		120

void msp430GetData(uint8 cmd) {
	uint32 data, i;
	uint8 msgIn[MSP430_MESSAGE_LENGTH];
	uint8 msgOut[MSP430_MESSAGE_LENGTH] = {0};
	msgOut[0] = cmd;

	SPISelectDevice(SPI_MSP430);
	SysCtlDelay(MSP430_SPI_DELAY);

	for (i = 0; i < MSP430_MESSAGE_LENGTH; ++i) {
		MAP_SSIDataPut(SSI0_BASE, (uint32)msgOut[i]);
		MAP_SSIDataGet(SSI0_BASE, &data);
		msgIn[i] = data;
		SysCtlDelay(MSP430_SPI_DELAY);
	}
	SPIDeselect();
	cprintf("put: %02X get: %02X,%02X,%02X,%02X   ", msgOut[0], msgIn[0], msgIn[1], msgIn[2], msgIn[3]);
	update_bumpers(msgIn[1]);
	bumper_debug_print();
}



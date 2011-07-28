//test

/*
 * @file heartbeat.c
 *
 *  Created on: Jul 26, 2010
 */

#define HEARTBEAT_PERIOD 16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef PART_LM3S9B92
#include "inc/lm3s9b92.h"
#endif

#ifdef PART_LM3S8962
#include "inc/lm3s8962.h"
#endif

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_nvic.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/ssi.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/flash.h"

#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"

#include "roneos.h"


void initTiles(void);
/*
 * The idle hook is used to run a test of the scheduler context switch
 * mechanism.
 */
void vApplicationIdleHook(void) {
}

void vApplicationTickHook(void) {
}

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName ) {
	for(;; );
}

volatile unsigned long ulHighFrequencyTimerTicks;

void systemHeartbeatTask(void* parameters);

/**
 * @brief Pre-initializes rone by starting the core hardware.
 *
 * Initalizes roneID, charger, blinky, buttons, IRBeacon, SPI, LED, and serial.
 * Rone blinks three times after the initializations are done.
 * @returns void
 */

void systemPreInit(void) {
	int i;
//	unsigned long val;
//	xTaskHandle blinkyHandle;

	MAP_IntMasterDisable();
	// increase LDO voltage so that PLL operates properly
	MAP_SysCtlLDOSet(SYSCTL_LDO_2_75V);
	#ifdef PART_LM3S8962
	MAP_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
	#endif

	#ifdef PART_LM3S9B92
	MAP_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	#endif

	MAP_SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

	//startup core hardware

	initTiles();
	led_init();
}

/**
 * @brief Initializes the rest of rone after the pre-initialization.
 *
 * Initializes encoder, light sensor, motor, gyro, accelerometer, IR_comms, radio, ad cfprintf.
 * Prints out the date, time, and roneID after everything is initialized.
 * Rone starts heartbeat after this initialization.
 * @returns void
 */
void systemInit(void) {
	unsigned long val;
	// startup the rest of the hardware

	osTaskCreate( /* function */systemHeartbeatTask,
						/* name */"heartbeat",
				  /* stack size */512,
			 /* *char parameter */NULL,
	/* priority */HEARTBEAT_TASK_PRIORITY);

}

void systemShutdown(void) {
	//TODO turn off all the hardware and sit still
}

uint32 systemUSBConnected(void) {
	//TODO put actual code here
	return false;
}


//60hz interrupt.  Actually called every 16ms, or 62.5 hertz
#define HEARTBEAT_10HZ_COUNTER	6

/**
 * @brief Background tasks performed during each heartbeat.
 *
 * Each heartbeat = every 16 milliseconds.
 * Updates blinky, IRBeacon, leds, accelerometer, motor velocity, pose, and motor command timer.
 * @returns void
 */
void systemHeartbeatTask(void* parameters) {
	uint8 heart_beat_10hz_timer = HEARTBEAT_10HZ_COUNTER;
	portTickType lastWakeTime;

	lastWakeTime = osTaskGetTickCount();

	for (;;) {
		//MAP_IntMasterEnable();
		for(tileLoopCtr = 0; tileLoopCtr < NUM_TILES; tileLoopCtr++) {
				leds_update(tiles[tileLoopCtr]);
			}

		//MAP_IntMasterDisable();
		osTaskDelayUntil(&lastWakeTime, HEARTBEAT_PERIOD);
	}
}

void systemBootloader(void) {
	/*
	 *	Disable interrupts directly.
	 */
	HWREG( NVIC_DIS0) = 0xffffffff;
	HWREG( NVIC_DIS1) = 0xffffffff;

	//
	// Also disable the SysTick interrupt.
	//
	MAP_SysTickIntDisable();

	/*
	 * Jump to Bootloader
	 *
	 */
	(*((void(*)(void)) (*(unsigned long *) 0x2c)))();
}

void initTile(Tile tile, int32 sysctlperiph, int32 port, int32 pin) {
	tile.LED_SEL_SYSCTL = sysctlperiph;
	tile.LED_SEL_PORT = port;
	tile.LED_SEL_PIN = pin;
}

void initTiles(void) {
	initTile(tiles[0], SYSCTL_PERIPH_GPIOA, GPIO_PORTA_BASE, GPIO_PIN_3);
	initTile(tiles[1], SYSCTL_PERIPH_GPIOC, GPIO_PORTC_BASE, GPIO_PIN_4);
	initTile(tiles[2], SYSCTL_PERIPH_GPIOC, GPIO_PORTC_BASE, GPIO_PIN_6);
	initTile(tiles[3], SYSCTL_PERIPH_GPIOE, GPIO_PORTE_BASE, GPIO_PIN_0);
	initTile(tiles[4], SYSCTL_PERIPH_GPIOE, GPIO_PORTE_BASE, GPIO_PIN_2);
	initTile(tiles[5], SYSCTL_PERIPH_GPIOG, GPIO_PORTG_BASE, GPIO_PIN_0);
	initTile(tiles[6], SYSCTL_PERIPH_GPIOB, GPIO_PORTB_BASE, GPIO_PIN_0);
	initTile(tiles[7], SYSCTL_PERIPH_GPIOB, GPIO_PORTB_BASE, GPIO_PIN_2);
	initTile(tiles[8], SYSCTL_PERIPH_GPIOB, GPIO_PORTB_BASE, GPIO_PIN_4);
	initTile(tiles[9], SYSCTL_PERIPH_GPIOD, GPIO_PORTD_BASE, GPIO_PIN_0);
	initTile(tiles[10], SYSCTL_PERIPH_GPIOD, GPIO_PORTD_BASE, GPIO_PIN_1);
	initTile(tiles[11], SYSCTL_PERIPH_GPIOD, GPIO_PORTD_BASE, GPIO_PIN_4);
	initTile(tiles[12], SYSCTL_PERIPH_GPIOC, GPIO_PORTC_BASE, GPIO_PIN_5);
	initTile(tiles[13], SYSCTL_PERIPH_GPIOC, GPIO_PORTC_BASE, GPIO_PIN_7);
	initTile(tiles[14], SYSCTL_PERIPH_GPIOE, GPIO_PORTE_BASE, GPIO_PIN_1);
}

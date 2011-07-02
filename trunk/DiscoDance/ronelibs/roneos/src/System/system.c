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

uint8 roneID;

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
	roneID = systemGetId();

#ifdef PART_LM3S8962
	charger_init();
#endif

	blinky_led_init();

#ifdef PART_LM3S8962
	buttons_init();
	ir_beacon_init();
	SPIInit();
	led_init();
	serial_init();
#endif

	srand(roneID);

	// triple flash
	for (i = 0; i < 3; i++) {
		uint32 j;
		blinkyLedSet(1);
		for (j = 0; j < 150000;) {
			j++;
		}
		blinkyLedSet(0);
		for (j = 0; j < 250000;) {
			j++;
		}
	}
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
#ifdef PART_LM3S8962
	encoder_init();
	light_sensor_init();
	motor_init();
	gyro_init();
	//accelerometer_init();
	ir_comms_init();
	radio_init();
	cfprintfInit();

	cprintf("roneos build %s %s\n", __DATE__, __TIME__);
	cprintf("robot id: %d\n", roneID);
#endif

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

/**
 * @brief Gets the file name from path.
 *
 * @param filepathString the file path
 * @returns a pointer that points to the file name
 */
char* sysGetFilenameFromPath(char* filepathString) {
	return (strrchr(filepathString, '/') + 1);
}

void _sysPrintFilename(char* fileName) {
	cprintf("%s\n", sysGetFilenameFromPath(fileName));
}


/**
 * @brief Gets the robotID.
 *
 * @returns robotID
 */
uint32 systemGetId(void) {
	uint32 ureg0;
	uint32 ureg1;
	uint32 id = 0;
	int i;

	MAP_FlashUserGet(&ureg0, &ureg1);
	for (i = 0; i < 2; i++) {
		id = id << 8;
		ureg1 = ureg1 >> 8;
		id |= (ureg1 & 0xFF);
	}
	return id;
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
		// enable nested interrupts for the ir_comms system
		//radioIntDisable();
		//MAP_IntMasterEnable();

		// blink the blinky LED
		blinkyUpdate();
#ifdef PART_LM3S8962
		// update the beacon LED
		// // Commented out because the call to this method was moved to
		// // ir_beacon.c where it is called in time with Timer2's 60hz
		// // timer.
		//ir_beacon_update(); //jl71 call from clocked interrupt

		// update the LEDs
		leds_update();

		// read the accelerometer
		//accelerometer_update();

		// run the velocity controller
		motor_velocity_update();

		// estimate the pose
		encoder_pose_update();

		// 10 hz interrupt functions
		heart_beat_10hz_timer--;
		if (heart_beat_10hz_timer == 0) {
			heart_beat_10hz_timer = HEARTBEAT_10HZ_COUNTER;

			// enable charge mode if the motors have not been driven in a while
			motor_command_timer_update();
		}
		//MAP_IntMasterDisable();
		//radio_int_enable();
#endif
		osTaskDelayUntil(&lastWakeTime, HEARTBEAT_PERIOD);
	}
}

/**
 * @brief Print the heap and stack usage.
 *
 * @returns void
 */
void systemPrintMemUsage(void) {
	uint8 i;

	//
	cprintf("FreeRTOS heap: %d free bytes\n", xPortGetFreeHeapSize());
	cprintf("%d tasks:\n", (int) osTaskGetNumberOfTasks());
	for (i = 0; i < sysTaskCount; ++i) {
		cprintf("  %s: stack use %d/%d\n", osTaskGetName(sysTaskHandles[i]),
				sysTaskStackSizes[i] - (uint32) osTaskGetStackHighWaterMark(
						sysTaskHandles[i]), sysTaskStackSizes[i]);
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
	radioIntDisable();

	/*
	 * Jump to Bootloader
	 *
	 */
	(*((void(*)(void)) (*(unsigned long *) 0x2c)))();
}


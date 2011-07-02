/**
 * @file ir_beacon.c
 *
 *  Created on: Jul 22, 2010
 *      Author: jamesm
 */
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

#include "roneos.h"
#include "swarmCamLookupTable.h"

#define IR_BEACON_PERIPH 		SYSCTL_PERIPH_GPIOB
#define IR_BEACON_BASE 			GPIO_PORTB_BASE
#define IR_BEACON_PIN 			GPIO_PIN_5

#define IR_BEACON_CLOCK_INTERVAL	60 //Hz
#define IR_BEACON_COMMAND_TIMEOUT	60

uint32 ir_beacon_data = 0;
uint32 ir_beacon_command_timer = 0;

uint8 ir_beacon_transmit_bit = 19;
uint8 ir_beacon_transmit_phase = 2;
uint32 ir_beacon_transmit_bits = 0;

/**
 * 	@brief Turns the IRBeacon LED on.
 *
 * 	@returns void
 */
void ir_beacon_LED_on(void) {
	GPIOPinWrite(IR_BEACON_BASE, IR_BEACON_PIN, IR_BEACON_PIN);
}

/**
 * 	@brief Turns the IRbeacon LED off.
 *
 * 	@returns void
 */
void ir_beacon_LED_off(void) {
	GPIOPinWrite(IR_BEACON_BASE, IR_BEACON_PIN, 0);
}

/**
 * 	@brief Initializes IRBeacon.
 *
 * 	Enables the IRBeacon pin as an output. Turns IRBeacon off in the process.
 * 	@returns void
 */
void ir_beacon_init(void) {
	MAP_SysCtlPeripheralEnable(IR_BEACON_PERIPH);
	MAP_GPIOPinTypeGPIOOutput(IR_BEACON_BASE, IR_BEACON_PIN);
	ir_beacon_LED_off();

	// Configure and enable a 60Hz clock on timer 2 for use with the IR Beacon // jl71
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
	MAP_TimerConfigure(TIMER2_BASE, TIMER_CFG_32_BIT_PER);
	//	MAP_TimerLoadSet(TIMER2_BASE, TIMER_A, SysCtlClockGet()
	//			/ IR_BEACON_CLOCK_INTERVAL * 4 /*Hz*/);
	int clockspeedtestvariable = SysCtlClockGet();
	MAP_TimerLoadSet(TIMER2_BASE, TIMER_A, SysCtlClockGet()
			/ IR_BEACON_CLOCK_INTERVAL /*60 Hz*/);

	MAP_IntEnable(INT_TIMER2A); // Sets up interrupt
	MAP_TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

	MAP_TimerEnable(TIMER2_BASE, TIMER_A);
}

/**
 * @brief Enables ir_beacon clock.
 *
 * @returns void
 *
 * Currently unused
 */
void ir_beacon_int_enable() {
	MAP_IntEnable(INT_TIMER2A);
}

/**
 * @brief Disables ir_beacon clock.
 *
 * @returns void
 *
 * Currently unused
 */
void ir_beacon_int_disable() {
	MAP_IntDisable(INT_TIMER2A);
}

/**
 * @brief Interrupt function
 *
 * Called when Timer2 goes off (@ 60hz (16.6667 ms))
 *
 * jl71
 */
void __attribute__ ((interrupt)) __cs3_isr_timer2a(void) {

	ir_beacon_update();
	TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
}

/**
 * 	@brief Sets the data in IRBeacon.
 *
 * 	Sets what the IRBeacon is going to output; also sets the timer for IRBeacon to 60.
 * 	@param data the output data
 * 	@returns void
 */
void ir_beacon_set_data(uint32 data) {
	ir_beacon_data = data;
	ir_beacon_command_timer = IR_BEACON_COMMAND_TIMEOUT;
}

/**
 *	@brief Disables IRBeacon.
 *
 *	Turns off IRBeacon LED and setting the timer to 0.
 *	@returns void
 */
void ir_beacon_disable(void) {
	ir_beacon_command_timer = 0;
	ir_beacon_LED_off();
}
/**
 * @brief Updates IRBeacon.
 *
 * This function needs to be called at 60hz.
 * Updates command timer, transmit phase, and transmit bit/bits.
 * Turns IRBeacon LED on or off accordingly
 * @returns void
 */
void ir_beacon_update(void) {
	if (ir_beacon_command_timer > 0) {
		ir_beacon_command_timer--; //updates the timer
		if (ir_beacon_transmit_phase < 2) {
			ir_beacon_transmit_phase++; //updates the phase
		} else {
			ir_beacon_transmit_phase = 0;
			if (ir_beacon_transmit_bit < 19) {
				ir_beacon_transmit_bit++; //update which
			} else {
				ir_beacon_transmit_bit = 0;
				ir_beacon_transmit_bits = ircodes[ir_beacon_data]; //gets the right code..?
			}
		}
		/* Framing = 110000 */
		if (ir_beacon_transmit_bit == 0 && ir_beacon_transmit_phase <= 1) {
			ir_beacon_LED_on();
			//return;
		} else if (ir_beacon_transmit_bit <= 1) {
			ir_beacon_LED_off();
			//return;
		} else if (ir_beacon_transmit_phase == 0) {
			/* Bits are transmitted 0=100, 1=111 */
			ir_beacon_LED_on();
			//return;
		} else if (((ir_beacon_transmit_bits >> (19 - ir_beacon_transmit_bit))
				& 1) == 1) {
			ir_beacon_LED_on();
		} else {
			ir_beacon_LED_off();
		}
	} else {
		ir_beacon_LED_off();
	}
}

/**
 * @brief This temporary ir_beacon_update method is used to test the frequency with which
 * it is called.
 *
 * Originally, it was being called at 16ms intervals, which is not
 * the 60Hz that is needed to sync with the (expensive) tracking system setup.
 */

//void ir_beacon_update(void) {
//	// Used to test frequency of this function's calling (confirmed to be ~16ms
//	static int irState = 1;
//	if (irState == 1) {
//		ir_beacon_LED_on();
//		irState = 1 - irState;
//	} else {
//		ir_beacon_LED_off();
//		irState = 1 - irState;
//	}
//}

/**
 * @file blinky_led.c
 * Functions that control the blinky_led
 */

#include "inc/lm3s8962.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

#include "roneos.h"

#ifdef PART_LM3S8962
	#include "inc/lm3s8962.h"
	#define BLINKY_LED_PERIPH 		SYSCTL_PERIPH_GPIOA
	#define BLINKY_LED_BASE 		GPIO_PORTA_BASE
	#define BLINKY_LED_PIN 			GPIO_PIN_6	
#endif



/**
 * @brief Sets the blinky on or off.
 *
 * Sets the blinky on or off depending on the parameter.
 * @param state	determines whether the pin should be on or off (active low: 0 is on, 1 is off)
 * @returns void
 */
void blinkyLedSet(uint32 state) {
	if (state == 0) {
		MAP_GPIOPinWrite(BLINKY_LED_BASE, BLINKY_LED_PIN, BLINKY_LED_PIN);
	} else {
		MAP_GPIOPinWrite(BLINKY_LED_BASE, BLINKY_LED_PIN, 0);
	}
}

/**
 *	@brief Initializes blinky.
 *
 * 	Initializes blinky with port B, pin 4 as output. Blinky is turned off with initialization.
 * 	@returns void
 */
void blinky_led_init(void) {
	MAP_SysCtlPeripheralEnable(BLINKY_LED_PERIPH);
	MAP_GPIOPinTypeGPIOOutput(BLINKY_LED_BASE, BLINKY_LED_PIN);
	blinkyLedSet(FALSE);
}

/**
 * @brief Flashes the blinky once with delay.
 *
 * Flashes the blinky once (turns it on and then off) with a specified delay in between).
 * @param delay	determines how long the delay is
 * @returns void
 */
void blinky_led_flash(uint32 delay) {
	blinkyLedSet(1);
	SysCtlDelay(delay);
	blinkyLedSet(0);
}


#define BLINKY_TIMER 		60
#define BLINKY_TIMER_ON 	4

/**
 * @brief Updates the blinky.
 *
 * Updates the blinky timer and turns blinky on or off depending on the timer.
 * @returns void
 */
void blinkyUpdate(void) {
	static uint32 blinkyTimer = 0;

	if (blinkyTimer > 0) {
		blinkyTimer--;
	}
	if (blinkyTimer == 0) {
		blinkyTimer = BLINKY_TIMER;
	}
	if (blinkyTimer < BLINKY_TIMER_ON) {
		blinkyLedSet(1);
	} else {
		blinkyLedSet(0);
	}
}

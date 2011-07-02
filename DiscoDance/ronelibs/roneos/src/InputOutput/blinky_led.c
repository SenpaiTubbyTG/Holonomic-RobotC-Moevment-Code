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
	#if defined(rone_v6)
		#define BLINKY_LED_PERIPH 		SYSCTL_PERIPH_GPIOB
		#define BLINKY_LED_BASE 		GPIO_PORTB_BASE
		#define BLINKY_LED_PIN 			GPIO_PIN_4
	#elif defined(rone_v8)
		#define BLINKY_LED_PERIPH 		SYSCTL_PERIPH_GPIOE
		#define BLINKY_LED_BASE 		GPIO_PORTe_BASE
		#define BLINKY_LED_PIN 			GPIO_PIN_1
	#else
		#error "robot version not defined. one of rone_v6 or rone_v8"
	#endif
#endif

#ifdef PART_LM3S9B92
	#include "inc/lm3s9b92.h"
	#define BLINKY_LED_PERIPH 		SYSCTL_PERIPH_GPIOD
	//For our boards
	#define BLINKY_LED_BASE 		GPIO_PORTD_BASE
	#define BLINKY_LED_PIN 			GPIO_PIN_4 | GPIO_PIN_0
	//0 is for eval board.
	//for 9b96 eval board
//	#define BLINKY_LED_PERIPH 		SYSCTL_PERIPH_GPIOF
//	#define BLINKY_LED_BASE 		GPIO_PORTF_BASE
//	#define BLINKY_LED_PIN 			GPIO_PIN_3
#endif

/**
 *	@brief Initializes blinky.
 *
 * 	Initializes blinky with port B, pin 4 as output. Blinky is turned off with initialization.
 * 	@returns void
 */
void blinky_led_init(void) {
	MAP_SysCtlPeripheralEnable(BLINKY_LED_PERIPH);
	MAP_GPIOPinTypeGPIOOutput(BLINKY_LED_BASE, BLINKY_LED_PIN);
	blinkyLedSet(false);
}


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

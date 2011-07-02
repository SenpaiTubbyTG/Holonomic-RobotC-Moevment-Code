/**
 * 	@file buttons.c
 *
 *  Created on: Jul 21, 2010
 *      Author: jamesm
 */

#include "inc/lm3s8962.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

#include "roneos.h"

#define BUTTON_RED_PERIPH 			SYSCTL_PERIPH_GPIOC
#define BUTTON_RED_BASE 			GPIO_PORTC_BASE
#define BUTTON_RED_PIN 				GPIO_PIN_7

#define BUTTON_GREEN_PERIPH 		SYSCTL_PERIPH_GPIOG
#define BUTTON_GREEN_BASE 			GPIO_PORTG_BASE
#define BUTTON_GREEN_PIN 			GPIO_PIN_0

#define BUTTON_BLUE_PERIPH 			SYSCTL_PERIPH_GPIOF
#define BUTTON_BLUE_BASE 			GPIO_PORTF_BASE
#define BUTTON_BLUE_PIN 			GPIO_PIN_2

/**
 *	@brief Initializes the buttons.
 *
 *	Initializes the red, green, and blue buttons as input.
 *	@returns void
 */
void buttons_init(void) {
	MAP_SysCtlPeripheralEnable(BUTTON_RED_PERIPH);
	MAP_SysCtlPeripheralEnable(BUTTON_GREEN_PERIPH);
	MAP_SysCtlPeripheralEnable(BUTTON_BLUE_PERIPH);

	MAP_GPIOPinTypeGPIOInput(BUTTON_RED_BASE, BUTTON_RED_PIN);
	MAP_GPIOPinTypeGPIOInput(BUTTON_GREEN_BASE, BUTTON_GREEN_PIN);
	MAP_GPIOPinTypeGPIOInput(BUTTON_BLUE_BASE, BUTTON_BLUE_PIN);
}

/**
 *	@brief Gets the state of the specified button.
 *
 *	Tells you whether the specified button is on or off
 *	@param	button specifies which button to check (BUTTON_RED, BUTTON_BLUE, or BUTTON_GREEN)
 *	@returns void
 */
uint32 buttons_get(uint32 button) {
	uint8 val = false;
	switch (button) {
	case BUTTON_RED:
		if (MAP_GPIOPinRead(BUTTON_RED_BASE, BUTTON_RED_PIN)) {
			val = false;
		} else {
			val = true;
		}
	break;
	case BUTTON_GREEN:
		if (MAP_GPIOPinRead(BUTTON_GREEN_BASE, BUTTON_GREEN_PIN)) {
			val = false;
		} else {
			val = true;
		}
	break;
	case BUTTON_BLUE:
		if (MAP_GPIOPinRead(BUTTON_BLUE_BASE, BUTTON_BLUE_PIN)) {
			val = false;
		} else {
			val = true;
		}
	break;
		default:
			val = false;
			break;
	}
	return val;
}



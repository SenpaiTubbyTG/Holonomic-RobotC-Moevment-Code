/**
 * @file charger.c
 */

#ifdef PART_LM3S9B92
	#include "inc/lm3s9b92.h"
#endif

#ifdef PART_LM3S8962
	#include "inc/lm3s8962.h"
#endif
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

#include "roneos.h"


#define CHARGER_PERIPH 	SYSCTL_PERIPH_GPIOB
#define CHARGER_PIN 	GPIO_PIN_6
#define CHARGER_BASE 	GPIO_PORTB_BASE

/**
 * @brief Initializes charger.
 *
 * Enables peripheral and sets the charger pin as output.
 * @returns void
 */
void charger_init(void) {
	SysCtlPeripheralEnable(CHARGER_PERIPH);
	GPIOPinTypeGPIOOutput(CHARGER_BASE, CHARGER_PIN);
}


void charger_enable(void) {
	/**
	 * Enables the charger
	 */
	GPIOPinWrite(CHARGER_BASE, CHARGER_PIN, 0);
}

/**
 * @brief Disables the charger.
 *
 * @returns void
 */
void charger_disable(void) {
	GPIOPinWrite(CHARGER_BASE, CHARGER_PIN, CHARGER_PIN);
}

/**
 * @brief Gets the status of the charger.
 *
 * @returns true if the charger is enabled, false otherwise
 */
uint32 charger_get_status(void) {

	return (GPIOPinRead(CHARGER_BASE, CHARGER_PIN) ? false : true);
}


#include "inc/lm3s8962.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

#include "roneos.h"
#include "capSensor.h"


void initCapSensor() {
	MAP_SysCtlPeripheralEnable(CAP_SENSOR_PERIPH);
	MAP_GPIOPinTypeGPIOInput(CAP_SENSOR_BASE, CAP_SENSOR_PIN);
}

boolean getCapSensor(uint8 base, uint8 pin) {
	boolean val;
	if (MAP_GPIOPinRead(base, pin)) {
		val = true;
	} else {
		val = false;
	}
	return val;
}


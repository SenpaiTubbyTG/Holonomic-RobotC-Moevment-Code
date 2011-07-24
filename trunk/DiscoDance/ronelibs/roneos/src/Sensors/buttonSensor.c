#include "inc/lm3s8962.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

#include "roneos.h"
#include "buttonSensor.h"


void initButtonSensor() {
	MAP_SysCtlPeripheralEnable(BUTTON_SENSOR_PERIPH);
	MAP_GPIOPinTypeGPIOInput(BUTTON_SENSOR_BASE, BUTTON_SENSOR_PIN);
}

boolean getButtonSensor(uint32 base, uint32 pin) {
//	boolean val;
//	if (MAP_GPIOPinRead(base, pin)) {
//		val = true;
//	} else {
//		val = false;
//	}
//	return val;

	return MAP_GPIOPinRead(base, pin);

	//return MAP_GPIOPinRead(base, pin) ? true : false;

}


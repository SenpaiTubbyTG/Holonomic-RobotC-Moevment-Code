#ifndef CAPSENSOR_H_
#define CAPSENSOR_H_

#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

#define CAP_SENSOR_PERIPH 			SYSCTL_PERIPH_GPIOC
#define CAP_SENSOR_BASE 			GPIO_PORTC_BASE
#define CAP_SENSOR_PIN 				GPIO_PIN_7


void initCapSensor();
boolean getCapSensor(uint8 base, uint8 pin);


#endif /* CAPSENSOR_H_ */

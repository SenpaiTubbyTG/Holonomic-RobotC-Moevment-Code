#ifndef BUTTONSENSOR_H_
#define BUTTONSENSOR_H_

#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

#define BUTTON_SENSOR_PERIPH 			SYSCTL_PERIPH_GPIOC
#define BUTTON_SENSOR_BASE 			GPIO_PORTC_BASE
#define BUTTON_SENSOR_PIN 				GPIO_PIN_7


void initButtonSensor();
boolean getButtonSensor(uint32 base, uint32 pin);


#endif /* BUTTONSENSOR_H_ */

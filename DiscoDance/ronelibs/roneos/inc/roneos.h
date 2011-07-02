/*
 * rone.h
 *
 *  Created on: Mar 19, 2011
 *      Author: jamesm
 */

#ifndef RONE_H_
#define RONEOS_H_

// Free RTOS includes
#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"

// system includes
#include "../src/System/typedefs.h"
#include "../src/System/intMath.h"
#include "../src/System/system.h"
#include "../src/System/charger.h"
#include "../src/System/spi.h"

#include "../src/InputOutput/buttons.h"
#include "../src/InputOutput/leds.h"
#include "../src/InputOutput/blinky_led.h"
#include "../src/InputOutput/ir_beacon.h"
#include "../src/InputOutput/radio.h"
#include "../src/InputOutput/msp430.h"
#include "../src/InputOutput/bump_sensor.h"
#include "../src/InputOutput/sd_card.h"

#include "../src/IRComms/ir_comms.h"
#include "../src/IRComms/neighbors.h"

#include "../src/Motors/motor.h"
#include "../src/Motors/encoder.h"

#include "../src/Sensors/gyro.h"
#include "../src/Sensors/light_sensor.h"
#include "../src/Sensors/accelerometer.h"

#include "../src/SerialIO/serial.h"
#include "../src/SerialIO/cfprintf.h"
#include "../src/System/bl_commands.h"

#include "../src/crc/crctest.h"	//TESTING

#endif /* RONE_H_ */

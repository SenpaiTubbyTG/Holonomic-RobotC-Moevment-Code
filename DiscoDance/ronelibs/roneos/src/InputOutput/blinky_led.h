/*
 * blinky_led.h
 *
 *  Created on: Mar 26, 2011
 *      Author: jamesm
 */

#ifndef BLINKY_LED_H_
#define BLINKY_LED_H_

void blinky_led_init(void);
void blinkyLedSet(uint32 state); // python rone
void blinky_led_flash(uint32 delay);
void blinkyUpdate(void);

#endif /* BLINKY_LED_H_ */

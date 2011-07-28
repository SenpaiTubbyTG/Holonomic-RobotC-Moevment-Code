/*
 * leds.h
 *
 *  Created on: Mar 22, 2011
 *      Author: jamesm
 */

#ifndef LEDS_H_
#define LEDS_H_

//moved to typedefs.h; very silly hack
//#define LED_NUM_ELEMENTS				6
#define LED_NUM_ELEMENTS_PER_COLOR		5

#define LED_RED_START_IDX				0
#define LED_GREEN_START_IDX				5
#define LED_BLUE_START_IDX				10

#define LED_MAX_DIMMER					0x7F


#define LED_RED							0
#define LED_GREEN						1
#define LED_BLUE						2
#define LED_ALL							3

#define LED_PATTERN_ON					0
#define LED_PATTERN_BLINK				1
#define LED_PATTERN_PULSE				2
#define LED_PATTERN_CIRCLE				3
#define LED_PATTERN_COUNT				4
#define LED_PATTERN_MANUAL				5

#define LED_BRIGHTNESS_LOW				5
#define LED_BRIGHTNESS_MED				10
#define LED_BRIGHTNESS_HIGH				20

#define LED_RATE_SLOW					16
#define LED_RATE_MED					8
#define LED_RATE_FAST					4
#define LED_RATE_TURBO					2


void led_init();
void led_set_dimmer(Tile tile, uint32 led_idx, uint32 dimmer); // python rone
void led_set_dimmer_color(Tile tile, uint32 led_color, uint32 dimmer);
void led_set_dimmer_all(Tile tile, uint32 dimmer);

void leds_update(Tile tile);
void leds_set(Tile tile, uint8 color, uint8 pattern, uint8 brightness, uint8 rate);

#endif /* LEDS_H_ */

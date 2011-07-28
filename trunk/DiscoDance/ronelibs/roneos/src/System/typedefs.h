/*
 * mrone.h
 *
 *  Created on: Jul 20, 2010
 *      Author: sjb2
 */

#ifndef MRONE_H_
#define MRONE_H_

#define LED_NUM_ELEMENTS				6

typedef signed char int8;
typedef int int16;
typedef long int32;

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

typedef unsigned char boolean;


typedef struct Tile{
	int32 LED_SEL_SYSCTL;
	int32 LED_SEL_PORT;
	int32 LED_SEL_PIN;

	uint8 led_dimmers[LED_NUM_ELEMENTS];

} Tile;


#define FALSE 0
#define TRUE 1

#endif /* MRONE_H_ */

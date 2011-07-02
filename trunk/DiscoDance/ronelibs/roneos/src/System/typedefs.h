/*
 * mrone.h
 *
 *  Created on: Jul 20, 2010
 *      Author: sjb2
 */

#ifndef MRONE_H_
#define MRONE_H_

typedef signed char int8;
typedef int int16;
typedef long int32;

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

typedef unsigned char boolean;

typedef struct radio_packet {
	uint8 command;
	uint8 id;
	uint8 data[28];
} packet;


#define FALSE 0
#define TRUE 1

#endif /* MRONE_H_ */

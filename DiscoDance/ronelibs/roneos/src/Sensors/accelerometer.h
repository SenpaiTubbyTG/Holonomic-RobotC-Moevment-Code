/*
 * accelerometer.h
 *
 *  Created on: Mar 19, 2011
 *      Author: jamesm
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#define ACCELEROMETER_X             0
#define ACCELEROMETER_Y             1
#define ACCELEROMETER_Z             2

void accelerometer_init(void);
void accelerometer_update(void);
int32 accelerometer_get_value(uint32 axis); // external


#endif /* ACCELEROMETER_H_ */

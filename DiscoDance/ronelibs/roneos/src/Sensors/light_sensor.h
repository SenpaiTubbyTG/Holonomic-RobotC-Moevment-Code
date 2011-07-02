/*
 * light_sensor.h
 *
 *  Created on: Mar 26, 2011
 *      Author: jamesm
 */

#ifndef LIGHT_SENSOR_H_
#define LIGHT_SENSOR_H_

#define LIGHT_SENSOR_FRONT_RIGHT            0
#define LIGHT_SENSOR_FRONT_LEFT             1
#define LIGHT_SENSOR_REAR                   2

void light_sensor_init(void);
int32 light_sensor_get_value(uint32 light_sensor); // python rone

#endif /* LIGHT_SENSOR_H_ */

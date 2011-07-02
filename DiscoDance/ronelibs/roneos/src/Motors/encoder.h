/*
 * encoders.h
 *
 *  Created on: Mar 26, 2011
 *      Author: jamesm
 */

#ifndef ENCODERS_H_
#define ENCODERS_H_

#define ENCODER_LEFT            0
#define ENCODER_RIGHT            1
#define MOTOR_MICROMETERS_PER_ENCODER_COUNT 66
// wheel base is in mm
#define MOTOR_WHEEL_BASE  88

/**
 * x,y coordinates are stored in micrometers
 * theta is represented in microradians
 */


void encoder_init(void);
int32 encoder_get_ticks(uint32 enc);
int32 encoder_get_direction(uint32 enc);
int32 encoder_get_velocity(uint32 enc);
int32 encoder_delta_ticks(uint32 new, uint32 old);

void encoder_pose_update(void);
void encoder_pose_clear(void);
void encoder_get_pose(Pose* posePtr);
void encoder_set_pose(Pose* posePtr);
#endif /* ENCODERS_H_ */

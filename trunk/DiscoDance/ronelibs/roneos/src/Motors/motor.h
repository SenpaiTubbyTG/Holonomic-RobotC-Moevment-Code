/*
 * motor.h
 *
 *  Created on: Mar 23, 2011
 *      Author: jamesm
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTOR_LEFT                          0
#define MOTOR_RIGHT                         1

#define MOTORS_NUM		2

void motor_init(void);
void motor_command_timer_update(void);
void motor_brake(uint32 motor, int32 dutyCycle); // python rone
void motor_set_pwm(uint32 motor, int32 dutyCycle); // python rone
int32 motor_get_velocity(uint32 motor);
void motor_set_velocity(uint32 motor, int32 mm_per_second); // python rone
void motor_set_tv_rv(int32 tv, int32 rv);
void motor_get_tv_rv(int32* tvPtr, int32* rvPtr);

void motor_velocity_update(void);

#endif /* MOTOR_H_ */

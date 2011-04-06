#pragma config(Sensor, in1,    PotArm,              sensorPotentiometer)
#pragma config(Sensor, dgtl1,  EncoderR,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  EncoderL,            sensorQuadEncoder)
#pragma config(Sensor, dgtl12, TouchGoal,           sensorTouch)
#pragma config(Motor,  port1,           SuckR,         tmotorNormal, openLoop)
#pragma config(Motor,  port2,           DriveRB,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           DriveRF,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           DriveLB,       tmotorNormal, openLoop)
#pragma config(Motor,  port5,           DriveLF,       tmotorNormal, openLoop)
#pragma config(Motor,  port6,           ArmRL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           ArmRU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           ArmLL,         tmotorNormal, openLoop)
#pragma config(Motor,  port9,           ArmLU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          SuckL,         tmotorNormal, openLoop, reversed)

#include "Delta_Function_Library_1.0.c" //Main Funtion Library
#define FULL 127




task autonomous()
{
  pre_auton();
  int arm_in_position = 0;  //arm is down; 0 for false and 1 for true

drive_straight_suck(100,FULL,5);//speed,suckspeed,inches//drive straight and inhale the red stack at the same time



while(arm_in_position != 1) {
	  arm_in_position = lock(low_lock_point);
	}

turn(127,-90);//speed,degrees turn left

while(arm_in_position != 1) {//place tubes
	  arm_in_position = lock(low_descore_point);
	}

drive_straight(-FULL,5);// back up
turn(FULL,180); //left or shouldn't matter, turn to face blue stack

drive_straight_suck(FULL,FULL,10);//drive to blue stack//drive straight and inhale the blue stack at the same time

turn(FULL,90);//turn right
drive_straight(FULL,7);//drive straight
turn(FULL,-45);//turn left to face tower
drive_straight(FULL,7);//drive to tower
sucker(-FULL,3);//spit tube into tower
}

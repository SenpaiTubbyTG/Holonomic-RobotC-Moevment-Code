#pragma config(Sensor, in1,    PotArm,              sensorPotentiometer)
#pragma config(Sensor, dgtl1,  EncoderR,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  EncoderL,            sensorQuadEncoder)
#pragma config(Sensor, dgtl12, TouchGoal,           sensorTouch)
#pragma config(Motor,  port1,           DriveRB,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           DriveRF,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           DriveLF,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           ArmRL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           ArmLL,         tmotorNormal, openLoop)
#pragma config(Motor,  port6,           ArmRU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           ArmLU,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           SuckR,         tmotorNormal, openLoop)
#pragma config(Motor,  port9,           SuckL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          DriveLB,       tmotorNormal, openLoop, reversed)

#include "delta_lib_V2.c"

//RED CHEATER
task autonomous {
  drive_straight_suck_msec(127, 127, 1000); //drive forward and suck in stack, score cheater tube by driving
  lock_msec(127, 1000); //raise arm to y hieght
  turn_timed(127,-127,500); //turn left to face goal
  drive_straight_msec(127,500); //drive to goal
  lock_msec(-127, 700); //lower arm, scoring tubes
  drive_straight_suck_msec(-127, -127, 1000); //back up and spit out
}
//BLUE CHEATER
task autonomous {
  drive_straight_suck_msec(127, 127, 1000); //drive forward and suck in stack, score cheater tube by driving
  lock_msec(127, 1000); //raise arm to y hieght
  turn_timed(-127,127,500); //turn right to face goal
  drive_straight_msec(127,500); //drive to goal
  lock_msec(-127, 700); //lower arm, scoring tubes
  drive_straight_suck_msec(-127, -127, 1000); //back up and spit out
}
//RED
task autonomous {
drive_straight_suck_msec(127, 127, 1000); //drive forward and suck in stack
  lock_msec(127, 1000); //raise arm to y hieght
  turn_timed(-127,127,500); //turn right to face goal
  drive_straight_msec(127,500); //drive to goal
  lock_msec(-127, 700); //lower arm, scoring tubes
  drive_straight_suck_msec(-127, -127, 1000); //back up and spit out
}
//BLUE
task autonomous {
  drive_straight_suck_msec(127, 127, 1000); //drive forward and suck in stack
  lock_msec(127, 1000); //raise arm to y hieght
  turn_timed(127,-127,500); //turn left to face goal
  drive_straight_msec(127,500); //drive to goal
  lock_msec(-127, 700); //lower arm, scoring tubes
  drive_straight_suck_msec(-127, -127, 1000); //back up and spit out
}

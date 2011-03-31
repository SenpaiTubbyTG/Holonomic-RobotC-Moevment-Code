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

/////////////////////
drive_straight(100,5);//speed,inches
sucker(127,5);//speed,seconds//suck in red stack
lock(low_lock_point);//raise arm
turn(127,90);//speed,degrees turn left
lock(low_descore_point);//place tubes
drive_straight(-127,5);// back up
turn(127,180); //turn to face blue stack
drive_straight(127,10);//drive to blue stack
sucker(127,5);//suck in blue stack
turn(127,90);//turn right
drive_straight(127,7);//drive straight
turn(127,45);//turn to face tower
drive_straight(127,7);//drive to tower
suck(-127,3);//spit tube into tower
////////////////////

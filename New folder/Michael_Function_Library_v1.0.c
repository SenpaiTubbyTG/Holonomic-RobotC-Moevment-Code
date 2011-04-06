#pragma config(Sensor, in1,    LifterPot,           sensorPotentiometer)
#pragma config(Sensor, dgtl11, LeftTouch,           sensorTouch)
#pragma config(Sensor, dgtl12, RightTouch,          sensorTouch)
#pragma config(Motor,  port1,           LeftBottomLifter, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           RightUpperDrive, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           RightLowerDrive, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           LeftUpperDrive, tmotorNormal, openLoop)
#pragma config(Motor,  port5,           LeftLowerDrive, tmotorNormal, openLoop)
#pragma config(Motor,  port6,           LeftUpperLifter, tmotorNormal, openLoop)
#pragma config(Motor,  port7,           RightUpperLifter, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           LeftCollector, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port9,           RightCollector, tmotorNormal, openLoop)
#pragma config(Motor,  port10,          RightBottomLifter, tmotorNormal, openLoop, reversed)
/*
Pot values NOT CODE
arm_grounded = 1250
descore_lock_point = 1680 - 1250 = 430
low_lock_point = 2300 - arm grounded = 1050
high_lock_point = 2587 - arm_grounded = 1337

*/


}

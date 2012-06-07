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

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(200)


void pre_auton()
{

//Encoders:
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;

//Arm:
  arm_grounded = SensorValue[PotArm];    // sets ground point
  low_descore_point = arm_grounded + 500; // sets low descore arm pooint
  low_lock_point = arm_grounded + 800;   //...lowgoal
  high_lock_point = arm_grounded + 1100; // ...high goal
  arm_grounded += 250;
}

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "Delta_Function_Library_1.0.c" //Main Funtion Library
#include "Delta_Tele_1.0.c"             //Tele-Op Code goes here
#include "Delta_Auton_Cheater_Red_1.0.c"//Auton Modes go here, pick on and comment the rest
//#include "Delta_Auton_Red_1.0.c"
//#include "Delta_Auton_Cheater_Blue_1.0.c"
//#include "Delta_Auton_Blue_1.0.c"
//#include "Delta_Auton_Skills_1.0.c"

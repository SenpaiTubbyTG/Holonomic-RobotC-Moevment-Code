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
////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(200)

#include "delta_lib_V2.c" //Main Funtion Library
#include "PID Test.c"

//Standard Lock////////
int arm_grounded = SensorValue[PotArm];     // sets ground point
int low_descore_point = arm_grounded + 500; // sets low descore arm pooint
int low_lock_point = arm_grounded + 800;    //...lowgoal
int descore_high_point= arm_grounded + 1000;//...high descore
int high_lock_point = arm_grounded + 1100;  // ...high goal

//PID//////////////////

PIDController arm;

int goal_value = 1000;
int k_P = 1;
int k_I = 0;
int k_D = 0;


//Pre Auton///////////
void pre_auton()
{

  //Encoders:
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;

  //Standard Arm:
  arm_grounded = SensorValue[PotArm];    // sets ground point
  low_descore_point = arm_grounded + 500; // sets low descore arm pooint
  low_lock_point = arm_grounded + 800;   //...lowgoal
  descore_high_point= arm_grounded + 1000;//...high descore
  high_lock_point = arm_grounded + 1100; // ...high goal
  arm_grounded += 250;

  //PID:
  init(arm,PotArm,port4);
	setSetpoint(arm, goal_value);
	setPIDs(arm, k_P, k_I, k_D);
	enable(arm);


}

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

task usercontrol()
{
  pre_auton();

  int goal_lock = 0;
  //0 for unlocked, -1 for low gal, 1 for high goal
  //calibration for potentiometer setting the arm
  /*int low_lock_point = SensorValue[in1] + 703;
  //low goal potentiometer reading
  //sets the low lock point based on the starting potentiometer point int high_lock_point = SensorValue[in1] + 1000;
  //high goal potentiometer reading
  //end calibrarion*/
  while(true)
  {
    //Auto_Arm/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*
    if(vexRT[Btn7L] == 1)//auto button close loop
    {
      goal_lock = -1;   //sets to low lock
    }
    else if(vexRT[Btn7U] == 1) {
      goal_lock = 1;	//sets to high lock
    }
    else if(vexRT[Btn7D] == 1) {// descore/ score on low goal...
        goal_lock = 2;
    }

    if(goal_lock == -1)
      lock(low_lock_point); //brings to low lock point
    else if(goal_lock == 1)
      lock(high_lock_point);//moves arm to high lock point

    ///////////////////////////////////////////////////////////////NEW STUFF TAKE THIS OUT IF IT DOESNT WORK
    else if (goal_lock == 2)
      lock(low_descore_point);//moves arm to descore lock point
    else if(goal_lock == 3)
      lock(descore_high_point);
    //////////////////////////////////////////////////////////////


    //Manual_Arm/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*

    if(vexRT[Ch3] < 15 && vexRT[Ch3] > -15){//Trim, if stick is between 15 & negative 15 motors equal 0.
        setArmSpeed(0);
    }
    else{//motors = stick angle
        setArmSpeed(vexRT[Ch3]);
    }

    //Claw/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*
    switch(vexRT[Btn5U] - vexRT[Btn5D])
    {
    case  1:motor[SuckR] = FULL;
      motor[SuckL] = FULL;
      break;
    case -1:motor[SuckR] = -FULL;
      motor[SuckL] = -FULL;
      break;
    case  0:motor[SuckR] = 0;
      motor[SuckL] = 0;
      break;
    }//: switch

    //Drive_Train/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*
    setDriveRSpeed((vexRT[Ch2] - vexRT[Ch1]));// (y + x)
    setDriveLSpeed((vexRT[Ch2] + vexRT[Ch1]));// (y - x)

  }//while
}//taskusercontrol

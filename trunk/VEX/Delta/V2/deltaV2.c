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

int k_P = 127/160;
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
}

task autonomous()
{
  pre_auton();
  setArmSpeed(calculatePID(arm));
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

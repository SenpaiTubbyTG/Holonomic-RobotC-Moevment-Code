#pragma config(Sensor, in1,    LeftLine,            sensorLineFollower)
#pragma config(Sensor, in2,    CentreLeftLine,      sensorLineFollower)
#pragma config(Sensor, in3,    CentreRightLine,     sensorLineFollower)
#pragma config(Sensor, in4,    RightLine,           sensorLineFollower)
#pragma config(Sensor, in5,    Right2Line,          sensorLineFollower)
#pragma config(Sensor, in6,    GreyCentre,          sensorLineFollower)
#pragma config(Sensor, in7,    Grey,                sensorLineFollower)
#pragma config(Sensor, in8,    Pot_Arm,             sensorPotentiometer)
#pragma config(Sensor, dgtl1,  EncoderR,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  EncoderL,            sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  TouchRight,          sensorTouch)
#pragma config(Sensor, dgtl6,  TouchLeft,           sensorTouch)
#pragma config(Sensor, dgtl7,  Arm_limit,           sensorTouch)
#pragma config(Sensor, dgtl8,  Arm_closed,          sensorTouch)
#pragma config(Motor,  port1,           SuckerR,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           DriveR1,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           DriveR2,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           DriveL1,       tmotorNormal, openLoop)
#pragma config(Motor,  port5,           DriveL2,       tmotorNormal, openLoop)
#pragma config(Motor,  port6,           ArmLD,         tmotorNormal, openLoop)
#pragma config(Motor,  port7,           ArmLU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           ArmRD,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port9,           ArmRU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          SuckerL,       tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Delta_Function_Library_1.0.c"

int arm_grounded;
int low_lock_point;
int high_lock_point;
int pre_auton_complete = 0;

task usercontrol()
{
  int goal_lock = 0;  //0 for unlocked, -1 for low gal, 1 for high goal
  //calibration for potentiometer setting the arm
  //int low_lock_point = SensorValue[in1] + 703; //low goal potentiometer reading
                      //sets the low lock point based on the starting potentiometer point
  //int high_lock_point = SensorValue[in1] + 1000; //high goal potentiometer reading
  //end calibrarion

	while (true)
	{
	  //: Drive Train ARCADE
	 motor[DriveR1] = vexRT[Ch2] - vexRT[Ch1];
	 motor[DriveR2] = vexRT[Ch2] - vexRT[Ch1];
	 motor[DriveL1] = vexRT[Ch2] + vexRT[Ch1];
	 motor[DriveL2] = vexRT[Ch2] + vexRT[Ch1];

//: Arm
	 while(true)
	 {
	  //Arm/Curl//////////////////////////////////////////////////////////////////////////
		  if(vexRT[Btn7L] == 1)//auto button close loop
		  {
		    goal_lock = -1;   //sets to low lock
		  }
		  else if(vexRT[Btn7R] == 1) {
		    goal_lock = 1;    //sets to high lock
		  }

		  if(goal_lock == -1)
		    lock(low_lock_point); //brings to low lock point
		  else if(goal_lock == 1)
	      lock(high_lock_point);//moves arm to high lock point
      else {
		    motor[ArmRD] = vexRT[Ch3]; //assumes that positive values move arm up
        motor[ArmRU] = vexRT[Ch3];
        motor[ArmLD] = vexRT[Ch3];
        motor[ArmRU] = vexRT[Ch3];

		   }
   }

//: Suck
   switch(vexRT[Btn5U] - vexRT[Btn5D])
   {
    case  1:motor[SuckerR] = 127;
            motor[SuckerL] = 127;
            break;
    case -1:motor[SuckerR] = -127;
            motor[SuckerL] = -127;
            break;
    case  0:motor[SuckerR] = 0;
            motor[SuckerL] = 0;
            break;
   }//switch

   //SPINORBITCYCLEROTATETORQUEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHHH
   switch(vexRT[Btn6U] - vexRT[Btn6D])
   {
    case  1:motor[SuckerR] = -127;
            motor[SuckerL] = 127;
            break;
    case -1:motor[SuckerR] = 127;
            motor[SuckerL] = -127;
            break;
    case  0:motor[SuckerR] = 0;
            motor[SuckerL] = 0;
            break;

   }//switch
	}//while
}// task user control
#pragma config(Sensor, in1,    PotArm,                 sensorPotentiometer)
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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(200)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!


/* drive_straight
  * @purpose: autonomously drive robot forward for provided distance in inches
  * precondition: 4 inch wheels used; if other wheels, change the 4 in the while loop
  * @param speed: speed of motors, -127 to 127; negative values go reverse
  * @param distance: distance in inches
  * TODO: consider adding an acceleration loop
 *///there are 360 ticks in an encoder revolution
void drive_straight(int speed, float distance) {
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;
  while( ( (float) abs(SensorValue[EncoderL])  * 4 / 360 * PI) < distance &&
         ( (float) abs(SensorValue[EncoderR]) * 4 / 360 * PI) < distance) {
    if(abs(SensorValue[EncoderL]) > abs(SensorValue[EncoderR])) {
      motor[DriveRF] = -speed;
      motor[DriveRB] = -speed;
      motor[DriveLF]  = -speed + 1;
      motor[DriveLB]  = -speed + 1;
    }
    else if(abs(SensorValue[EncoderL]) < abs(SensorValue[EncoderR])) {
      motor[DriveRF] = -speed + 1;
      motor[DriveRB] = -speed + 1;
      motor[DriveLF]  = -speed;
      motor[DriveLB]  = -speed;
    }
    else {
      motor[DriveRF]  = -speed;
      motor[DriveRB]  = -speed;
      motor[DriveLF]  = -speed;
      motor[DriveLB]  = -speed;
    }
  }
      motor[DriveRF]  = 0;
      motor[DriveRB]  = 0;
      motor[DriveLF]  = 0;
      motor[DriveLB]  = 0;
}

/*
Pot values NOT CODE
arm_grounded = 1250
descore_lock_point = 1680 - 1250 = 430
low_lock_point = 2300 - arm grounded = 1050
high_lock_point = 2587 - arm_grounded = 1337

*/
int lock(int final_pos) //locks arm to final_pos potentiometer point
{
  int current_pos = SensorValue(in1); //reads potentiometer
  int direction;                      //up or down?
  int arm_diff = abs(current_pos - final_pos);//difference between current and desired points

  if(arm_diff > 100) {  //potentiometer is very precise, so
    if (current_pos > final_pos) {//arm too high
      direction = 1;    //will move down
    }
    else if(current_pos < final_pos) { //arm too low
      direction = -1; //will move up
    }
    motor[ArmRU] = 127 * direction; //sets motors
    motor[ArmRL] = 127 * direction;
    motor[ArmLU] = 127 * direction;
    motor[ArmLL] = 127* direction;
    return 0;
  }
    else {  //in hindsight, I don't think this is necessary
    motor[ArmRU] = 0;//no need to move for lock; will continue holding
    motor[ArmRL] = 0;
    motor[ArmLU] = 0;
    motor[ArmLL] = 0;
    return 1;
        }

}
/*
Pot values NOT CODE
arm_grounded = 1250
descore_lock_point = 1680 - 1250 = 430
low_lock_point = 2300 - arm grounded = 1050
descore_high_point =
high_lock_point = 2587 - arm_grounded = 1337

*/

int arm_grounded;
int low_descore_point;
int low_lock_point;
int descore_high_point;
int high_lock_point;

void pre_auton()
{

//Encoders:
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;
	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
  //Arm
    arm_grounded = SensorValue[PotArm];    // sets ground point
    low_descore_point = arm_grounded + 500; // sets low descore arm pooint
    low_lock_point = arm_grounded + 800;   //...lowgoal
    high_lock_point = arm_grounded + 1100; // ...high goal
    arm_grounded += 250;
  //
}

task autonomous()
{
   pre_auton();

 //raise arm
  int arm_in_position = 0;  //arm is down; 0 for false and 1 for true
  while(arm_in_position != 1)
   {
	  arm_in_position = lock(low_lock_point);
	 }
//drive forward to stack
  drive_straight(50, 2);


  {
   SensorValue[EncoderL] = 0;
   SensorValue[EncoderR] = 0;
   lock(low_lock_point);
  }
 }


//USER CONTROL/////////////////////////////////////////////////////////////////
task usercontrol()
{
 pre_auton();

 int goal_lock = 0;  //0 for unlocked, -1 for low gal, 1 for high goal
  //calibration for potentiometer setting the arm
  /*int low_lock_point = SensorValue[in1] + 703; //low goal potentiometer reading
                  	//sets the low lock point based on the starting potentiometer point
  int high_lock_point = SensorValue[in1] + 1000; //high goal potentiometer reading*/
  //end calibrarion


 while(true)
 {
  //Arm/////////////////////////////////////////////////////////////////////////
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
 	else if(vexRT[Btn7R] == 1) {//same as 7D...
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


//Manual Arm//////////////////////////////////////////////////////////////////////////
switch(vexRT[Btn6U] - vexRT[Btn6D]) //manual arm control
        	{
            	case  1:motor[ArmRU] = -127;
            	motor[ArmRL] = -127;
            	motor[ArmLL] = -127;
            	motor[ArmLU] = -127;
              goal_lock = 0;  //unlocks arm
              break;

              case -1:motor[ArmRU] = 127;
            	motor[ArmRL] = 127;
            	motor[ArmLU] = 127;
            	motor[ArmLL] = 127;
            	goal_lock = 0;  //unlocks arm
             	break;

             	case  0:if(goal_lock == 0 ) {
              motor[ArmRU] = 0;
            	motor[ArmRL] = 0;
            	motor[ArmLU] = 0;
            	motor[ArmLL] = 0;
            	break;
         	    }//switch
  	      }

//Claw
  	switch(vexRT[Btn5U] - vexRT[Btn5D])
    {
      case  1:motor[SuckR] = 127;
              motor[SuckL] = 127;
              break;
      case -1:motor[SuckR] = -127;
              motor[SuckL] = -127;
              break;
      case  0:motor[SuckR] = 0;
              motor[SuckL] = 0;
              break;
    }//: switch


//Drive Train
    	motor[DriveRB]  = (vexRT[Ch2] - vexRT[Ch1]);  // (y + x)
    motor[DriveRF]  = (vexRT[Ch2] - vexRT[Ch1]);  // (y + x)
    motor[DriveLB] = (vexRT[Ch2] + vexRT[Ch1]);  // (y - x)
    motor[DriveLF] = (vexRT[Ch2] + vexRT[Ch1]);  // (y - x)
  }//while
}//taskusercontrol
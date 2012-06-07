#include "delta.h"
#include "Delta_Function_Library_1.0.c"
#include "Delta_Main_1.0.c"

task autonomous()
{
  pre_auton();
  int arm_in_position = 0;  //arm is down; 0 for false and 1 for true

//pick up and score red stack//
  drive_straight_suck(100,127,5);//drive to and suck in red stack

  /*while(arm_in_position != 1) {//raise arm to low goal scoring position
	  arm_in_position = lock(low_lock_point);
  }*/

	turn(127,-45);//turn left to face goal

	drive_straight(127,3);//drive forward to goal
/*	while(arm_in_position != 1) {//lower arm to score tubes
	  arm_in_position = lock(low_descore_point);
	}

	*/
	drive_straight_suck(-127,-127,5);//back away from goal/spit out tubes

//pick up blue stack
  turn(127,-180);//turn around to face blue stack
  drive_straight_suck(127,127,5);//drive to and pick up blue stack

///drive to tower and dump bluestack//IDEALY WE WOULD DRIVE IN AN ARC TO TOWER TO SAVE TIME

  turn(127,90);//turn right
  drive_straight(127,10);//drive straight
  turn(127,-90);//turn left
  drive_straight(127,5);//drive straight
  /*while(arm_in_position != 1) {//raise arm to spit into tower
	  arm_in_position = lock(low_lock_point);
	}*/

  sucker(-127,3);//spit into tower
}

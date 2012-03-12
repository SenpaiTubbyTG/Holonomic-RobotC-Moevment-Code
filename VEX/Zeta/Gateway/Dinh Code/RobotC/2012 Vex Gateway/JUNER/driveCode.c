
/lkth// DRIVE CODE FOR LINEAR LIFT ROBOT...

	     int goal_lock = 0;  //0 for unlocked, 1 for low gal, 2 for high goal
  //calibration for potentiometer setting the arm
  /*int low_lock_point = SensorValue[in1] + 703; //low goal potentiometer reading
  //sets the low lock point based on the starting potentiometer point
  int high_lock_point = SensorValue[in1] + 1000; //high goal potentiometer reading*/
  //end calibrarion
while (true)
	{

    //Arm/////////////////////////////////////////////////////////////////////////
    if(vexRT[Btn7L] == 1)//auto button close loop
    {
      goal_lock = 1;   //lowgoal
    }
    else if(vexRT[Btn7U] == 1) {
      goal_lock = 2;	//medium goal
    }
    else if(vexRT[Btn7D] == 1) {//high goal
        goal_lock = 3;
    }
    else if(vexRT[Btn7R] == 1) {//same as 7D...
        goal_lock = 3;
    }
       else if(vexRT[Btn8D] == 1 && touchlow != 1)// not pressed make the arm go all the way down
    {
      goal_lock = 4;
    }




    ////////////////////////////////////////////////////////////////////////////////////////////////
      if(goal_lock == -1)
      lock(thirty_inch_goal); //brings to low lock point
    else if(goal_lock == 1)
      lock(twenty_inch_goal);//moves arm to high lock point
     else if (goal_lock == 2 )
      lock(ten_inch_goal);//moves arm to descore lock point
    else if(goal_lock == 3 )
      lock( all_the_way_down);//,------------------------------put this back in if case does not work...

    /////////////////////////////////////////////////////////////////////////////////////////

        //Finder: Arm control
    switch(vexRT[Btn5U] - vexRT[Btn5D]) //manual arm control
    {
    case  1:
      if(SensorValue[touchh] == 0) {
        motor[lift1] = -127;
        motor[lift2] = -127;
        motor[lift3] = -127;
        motor[lift4] = -127;
        goal_lock = 0;  //unlocks arm
        } else {
        motor[lift1] = 0;
        motor[lift2] = 0;
        motor[lift3] = 0;
        motor[lift4] = 0;
      }
      break;

    case -1:
      if(SensorValue[touchl] == 0) {
        motor[lift1] = 127;
        motor[lift2] = 127;
        motor[lift3] = 127;
        motor[lift4] = 127;
        goal_lock = 0;  //unlocks arm
        } else {
        motor[lift1] = 0;
        motor[lift2] = 0;
        motor[lift3] = 0;
        motor[lift4] = 0;
      }
      break;

    case  0:if(goal_lock == 0 ) {
        motor[lift1] = 0;
        motor[lift2] = 0;
        motor[lift3] = 0;
        motor[lift4] = 0;
        break;
      }//switch
    }

    // Finder: Claw
    switch(vexRT[Btn6D] - vexRT[Btn6U])
    {
    case  1:motor[Claw] = -127; //Close
      break;
    case -1:motor[Claw] = 127; //Open
      break;
    case  0:motor[Claw] = 0; //Do nothing
      break;
    }

    //scaling
     // Finder :Drive Train
    {	if(vexRT[Ch2] < 30 && vexRT[Ch2]> -30 && vexRT[Ch3] < 30 && vexRT[Ch3]> -30)
      {
        motor[DriveLeft] = 0;
        motor[DriveLeft2] = 0;
        motor[DriveRight] = 0;
        motor[DriveRight2] = 0;

      }
      motor[DriveLeft] = vexRT[Ch2];//left frotn motor
      motor[DriveLeft2] = vexRT[Ch2];//front right motor
      motor[DriveRight] = vexRT[Ch3];//right back motors
      motor[DriveRight2] = vexRT[Ch3];//Back left motor

    }

    if(Btn8D == 1)
    {
       goal_lock = 0;
       allMotorsOff();
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
}// while

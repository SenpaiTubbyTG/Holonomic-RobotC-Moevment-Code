 pre_auton();
  int goal_lock = 0;
  // User control code here, inside the loop
  //USER CONTROL/////////////////////////////////////////////////////////////////

  while(true)
  {
    //Arm/////////////////////////////////////////////////////////////////////////
    if(vexRT[Btn7L] == 1)//auto button close loop
    {
      goal_lock = 2;   //sets to medium goal
    }
    else if(vexRT[Btn7U] == 1) {
      goal_lock = 1;	//sets to high lock
    }
    else if(vexRT[Btn7D] == 1) {// descore/ score on low goal...
      goal_lock = -1;
    }
    else if(vexRT[Btn7R] == 1) {//same as 7D...
      goal_lock = 2;
    }




    if(goal_lock == -1)//if 7L is pressed...
      lock(ten_inch_goal); //brings to low lock point
    else if(goal_lock == 1)//if  7U is pressed...
      lock(thirty_inch_goal);
    else if (goal_lock == 2)
      lock(twenty_inch_goal);
    else if(goal_lock == 2)
      lock(twenty_inch_goal);
   ///////////Preset Arms///////////////////////////

    motor[leftBig] = motor[leftBack] = motor[leftFront] = vexRT[Ch3];
    motor[rightBig] = motor[rightBack] = motor[rightFront] = vexRT[Ch2];
    switch(vexRT[Btn5U] - vexRT[Btn5D]) //manual arm control
    {
    case  1:
      if(SensorValue[touchh] == 0) {
        motor[leftLift] = 127;
        motor[rightLift] = 127;
        goal_lock = 0;  //unlocks arm
        } else {
        stoparmmotors();
      }
      break;

    case -1:
      if(SensorValue[touchl] == 0) {
        motor[leftLift] = -80;
        motor[rightLift] = -80;
        goal_lock = 0;  //unlocks arm
        } else {
        stoparmmotors();
      }
      break;

    case  0:if(goal_lock == 0 ) {
        motor[leftLift] = 0;
        motor[rightLift] = 0;

        break;
      }//switch
    }

     motor[Collectors1] =  (vexRT[Btn6U] - vexRT[Btn6D])*full;
     motor[Collectors2] = (vexRT[Btn6U] - vexRT[Btn6D])*full;//collector


    // if(vexRT[Btn8D] == 1)
    // {
      // motor[rightBack] = (vexRT[Ch2]-vexRT[Ch1]);
      // motor[rightBig] = (vexRT[Ch2]-vexRT[Ch1]);//DriveTrain
      // motor[rightFront] =  (vexRT[Ch2]-vexRT[Ch1]);
      // motor[leftBig] = (vexRT[Ch2]+vexRT[Ch1]);
      // motor[leftBack] =  (vexRT[Ch2]+vexRT[Ch1]);
      // motor[leftFront] =  (vexRT[Ch2]+vexRT[Ch1]);
      // motor[Collectors1] =  (vexRT[Btn5D] - vexRT[Btn5U])*full;
      // motor[Collectors2] = (vexRT[Btn5D] - vexRT[Btn5U])*full;//collector
      // if (abs(vexRT[Ch3]) < 20)
      // {
        // stoparmmotors();

      // }
      // motor[rightLift] = motor[leftLift] = vexRT[Ch3];//arm

    // }




  }// while


///////////////////////////////////////////////////////////

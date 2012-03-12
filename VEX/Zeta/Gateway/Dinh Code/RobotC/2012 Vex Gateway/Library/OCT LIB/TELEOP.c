//USER CONTROL/////////////////////////////////////////////////////////////////
while(true)
{
  pre_auton();
  int goal_lock = 0;

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
      lock(ten_inch_goal); //brings to low lock point
    else if(goal_lock == 1)
      lock(twenty_inch_goal);//moves arm to high lock point
    ///////////////////////////////////////////////////////////////NEW STUFF TAKE THIS OUT IF IT DOESNT WORK
    else if (goal_lock == 2)
      lock(1350);//moves arm to descore lock point
    else if(goal_lock == 3)
      lock(thirty_inch_goal);
      }
    //////////////////////////////////////////////////////////////
    //////////////////////////collector junk//////////////

    while(true)
    {
      motor[left1] = motor[left2] = motor[left3] = vexRT[Ch3];
      motor[right1] = motor[right2] = motor[right3] = vexRT[Ch2];
      cool((vexRT[Btn6U] - vexRT[Btn6D])*full);
      Lift((vexRT[Btn5U] - vexRT[Btn5D])*full);
      if (vexRT[Btn7D] == 1)
      {
        SensorValue[PneuRoller1] = -1;
        SensorValue[PneuRoller2] = -1;
      }
    }
  //////////////////////////////////////////////////////////////
}

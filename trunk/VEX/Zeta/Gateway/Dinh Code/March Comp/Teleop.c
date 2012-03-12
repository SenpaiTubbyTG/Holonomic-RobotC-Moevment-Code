pre_auton();
int goal_lock = 0;

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
  {
    switch (typeDrive)
    {
    case  Drive:
      {
        SensorValue[pneu1] =   SensorValue[pneu2] =   SensorValue[pneu3] =   SensorValue[pneu4] = 0;
       motor[right1] = motor[right2] = motor[right3] = vexRT[Ch2];
        motor[left1] = motor[left2] = motor[left3] = vexRT[Ch3];

        if(vexRT[Btn8D] == 1)
          typeDrive = tracDrive;
      }// case
      break;
    case tracDrive:
      {

        SensorValue[pneu1] =   SensorValue[pneu2] =   SensorValue[pneu3] =   SensorValue[pneu4] = 1;
        motor[right1] = vexRT[Ch2];
        motor[right2] = -vexRT[Ch2];
        motor[right3] =-vexRT[Ch2];
        motor[left1] = vexRT[Ch3];
        motor[left2] = -vexRT[Ch3];
        motor[left3] = -vexRT[Ch3];
        if(vexRT[Btn8U] == 1)
          typeDrive = Drive;
      }//case
      break;
    }//switch

    // User control code here, inside the loop
}
}//while

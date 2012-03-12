///////////////////////////////Collector junk////////////////////////////

task CollectD()// multitask collector
{
  while(true)
  {
    motor[port8] = -127;
    motor[port9] = -127;
  }
}

///////////////////////Arm Tasks////////////////////////////////
task medTask()
{
  while(SensorValue[POT] < twenty_inch_goal)
  {
    motor[leftLift] = 127;
    motor[rightLift] = 127;
  }
  motor[leftLift] = 15;
  motor[rightLift] = 15;
}
task lowTask
{
  while(SensorValue[POT] < ten_inch_goal)
  {
    motor[leftLift] = 127;
    motor[rightLift] = 127;
  }
  motor[leftLift] = 15;
  motor[rightLift] = 15;
}
task highTask
{
  while(SensorValue[POT] < thirty_inch_goal)
  {
    motor[leftLift] = 127;
    motor[rightLift] = 127;
  }
  motor[leftLift] = 15;
  motor[rightLift] = 15;//lock the motors
}

task armDown
{
  while(SensorValue[touchl] !=1)
  {
    motor[leftLift] = -30;
    motor[rightLift] = -30;
  }
  stoparmmotors();
}
/////////////////////////////////////End of arm Tasks/////////////////////////////

void spit(float time)//collect objects
{
  motor[Collectors1] = 80;
  motor[Collectors2] = 80;
  wait1Msec(time*1000);
  motor[Collectors1] = 0;
  motor[Collectors2] = 0;

}


void collect(float time)
{
  ClearTimer(T4);

  {
    motor[Collectors1] = -127;
    motor[Collectors2] = -127;
    wait1Msec(time*1000);
    motor[Collectors1] = 0;
    motor[Collectors2] = 0;
  }
}

void cool(int speed)
{
  motor[Collectors1] = speed;//for teleop
  motor[Collectors2] = speed;
}
///////////////////end of Collector////////////////////////
void Lifter(int power)
{
  motor[leftLift] = power;
  motor[rightLift] = power;

}

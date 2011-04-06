task usercontrol()
{
  StopTask(followline);
  //Start Arm monitoring
  StartTask(autolevel);

  //Lower back of basket
  SensorValue[Basket] = 0;

  while (true)
  {
    //Drive
    motor[DriveLeft] = vexRT[Ch3];
    motor[DriveRight] = vexRT[Ch2];

    //Intake
    motor[Tracks] = vexRT[Ch2Xmtr2];
    motor[Intake] = vexRT[Ch2Xmtr2];

    //Pneumatics
    if(vexRT[Ch6Xmtr2] == 127)
    {
      SensorValue[Basket] = 1;
    }
    else if(vexRT[Ch6Xmtr2] == -127)
    {
      SensorValue[Basket] = 0;
    }

    //Lifter
    target = vexRT[Ch3Xmtr2];

  }
}

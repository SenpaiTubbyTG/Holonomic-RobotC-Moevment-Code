//Task for keeping arm level
int lifter = 10;
int target = 0;
bool limit = false;

//Raise Lifter
void raisearm()
{
  target = 127;
}

//Lower Lifter
void lowerarm()
{
  target = -127;
}

//Automaticly keeps the lifter level
task autolevel()
{
  while(true)
  {
    //Arm is within limits
    if((SensorValue(LiftEncoderLeft) + SensorValue(LiftEncoderRight) < 1130 && target > 0) || (SensorValue(LiftEncoderLeft) + SensorValue(LiftEncoderRight) > 0 && target < 0))
    {
      lifter = target + 10;
      limit = false;
    }
    //Arm is too high or low
    else
    {
      lifter = 10;
      limit = true;
    }
    //Left is higher than right
    if (SensorValue(LiftEncoderLeft) > SensorValue(LiftEncoderRight))
    {
      motor[LifterLeft] = lifter - (SensorValue[LiftEncoderLeft] - SensorValue[LiftEncoderRight]);
      motor[LifterLeft2] = lifter - (SensorValue[LiftEncoderLeft] - SensorValue[LiftEncoderRight]);
      motor[LifterRight] = lifter + (SensorValue[LiftEncoderLeft] - SensorValue[LiftEncoderRight]);
      motor[LifterRight2] = lifter + (SensorValue[LiftEncoderLeft] - SensorValue[LiftEncoderRight]);
    }
    //Right is higher than left
    else if (SensorValue(LiftEncoderRight) > SensorValue(LiftEncoderLeft))
    {
      motor[LifterRight] = lifter - (SensorValue[LiftEncoderRight] - SensorValue[LiftEncoderLeft]);
      motor[LifterRight2] = lifter - (SensorValue[LiftEncoderRight] - SensorValue[LiftEncoderLeft]);
      motor[LifterLeft] = lifter + (SensorValue[LiftEncoderRight] - SensorValue[LiftEncoderLeft]);
      motor[LifterLeft2] = lifter + (SensorValue[LiftEncoderRight] - SensorValue[LiftEncoderLeft]);
    }
    //Level
    else
    {
      motor[LifterLeft] = lifter;
      motor[LifterLeft2] = lifter;
      motor[LifterRight] = lifter;
      motor[LifterRight2] = lifter;
    }
  }
}

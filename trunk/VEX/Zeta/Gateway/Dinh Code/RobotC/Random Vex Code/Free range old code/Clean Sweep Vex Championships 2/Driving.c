bool stalled = false;
int lastencodervalue = 0;

//Return distance travelled
int distance()
{
  return SensorValue[EncoderLeft] + SensorValue[EncoderRight];
}

//Check each button and turn respective motors off
void checkindividualbuttons()
{
  if (SensorValue(LeftButton) == 1)
  {
    motor[DriveLeft] = 0;
  }
  if (SensorValue(RightButton) == 1)
  {
    motor[DriveRight] = 0;
  }
}

//Stop moving
void stop()
{
  motor[DriveLeft] = 0;
  motor[DriveRight] = 0;
}

//Check if the drive motors are stalled
void checkforstall()
{

  wait1Msec(100);
  if (distance() < prevencodervalue + 10)
  {
    stalled = true;
  }
  lastencodervalue = distance();
}

//Reset the drive encoders
void resetencoders()
{
  stalled = false;
  lastencodervalue = 0;
  SensorValue[EncoderLeft] = 0;
  SensorValue[EncoderRight] = 0;
}

//Move until it hits the wall
void hitwall(int timeout)
{
  stalled = false;
  resetencoders();
  ClearTimer(T1);
  wait1Msec(500);
  while ((SensorValue(LeftButton) != 1 || SensorValue(RightButton) != 1) && time1[T1] < timeout && stalled == false)
  {
    checkforstall();
    checkindividualbuttons();
  }
}

//Wait until the robot has travelled a certain distance
void waitfordistance(int amount, int timeout)
{
  ClearTimer(T1);
  resetencoders();
  while (distance() < amount && time1[T1] < timeout)
  {
  }
}

//Move forward
void forward(int amount, int speed)
{
  motor[DriveLeft] = speed;
  motor[DriveRight] = speed;
  resetencoders();
  while (distance() < amount)
  {
  }
}

//Move Reverse
void reverse(int amount, int speed)
{
  motor[DriveLeft] = -speed;
  motor[DriveRight] = -speed;
  resetencoders();
  while (distance() > -amount)
  {
  }
}

//Turn with both motors at different speeds
void advancedturn(int amount, int speedleft, int speedright)
{
  motor[DriveLeft] = speedleft;
  motor[DriveRight] = speedright;
  resetencoders();
  if (speedleft > 0 || speedright > 0)
  {
    while (distance() < amount)
    {
    }
  }
  if (speedleft < 0 || speedright < 0)
  {
    while (distance() > -amount)
    {
    }
  }
}

//Spin left
void spinleft(int amount, int speed)
{
  motor[DriveLeft] = -speed;
  motor[DriveRight] = speed;
  resetencoders();
  while (SensorValue(EncoderRight) - SensorValue(EncoderLeft) < amount)
  {
  }
}

//Spin right
void spinright(int amount, int speed)
{
  motor[DriveLeft] = speed;
  motor[DriveRight] = -speed;
  resetencoders();
  while (SensorValue(EncoderLeft) - SensorValue(EncoderRight) < amount)
  {
  }
}

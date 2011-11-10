


/// Variables to configure the encoder

float positionX;
float positionY;

int angle;
float maxDrive;
float turnDrive;
float driveWidth;
float wheelDiameter;
float wheelCir;

#define TC 0.5
#define minPow 15
#define startPow 50
#define brake  10

void encoderConfigure(float startX, float startY, float startAngle, float mDrive, float width, float wheelD) // wheel diameter and width must be in feet
{
    positionX = startX;
    positionY = startY;
    angle = startAngle;
    maxDrive  = mDrive;
    turnDrive = 0.4*maxDrive;
    driveWidth = width;
    wheelDiameter = wheelD;
    wheelCir = wheelDiameter*PI;

    /// any code needed to begin using an encoder

}

void encodersReset()
{
  SensorValue[EncoderRight] = 0;
  SensorValue[EncoderLeft]  = 0;
}

void encoderDriveStraight(float distance) // <----- in feet
{

  /// basic value instantiation
  float direction = distance/abs(distance);
  encodersReset();
  float velocity = 0;
  float output = 0;

  int leValue = sensorValue[EncoderRight];

  /// determining aceleration and deceleration periods
  float aPeriod;  // aceleration period
  float dPeriod;  // deceleration period

  if(abs(distance) >= 4)
  {
    aPeriod = 2;
    dPeriod = 2;
  }
  else
  {
    aPeriod = abs(distance/2.0);
    dPeriod = abs(distance/2.0);
  }

  ////resetting time
  time1[T1] = 0;

  while(!(velocity == 0 && abs(distance - (SensorValue[EncoderRight]/360.0)*wheelCir) < 0.1))
  {

    ////// determines the proportional output
    if(abs((SensorValue[EncoderRight]/360.0)*wheelCir) <= aPeriod)  // if the robot has not yet exited the aceleration zone.
    {
      output = (direction*abs(SensorValue[EncoderRight]/360.0)*wheelCir * 0.5 * maxDrive*(127-startPow))/127.0; ///// scales an aceleration (excludes vals lower than 15)
      if(output>0)
        output = output + startPow;
      else if(output<0)
        output = output - startPow;
      else
        output = startPow*direction;
    }
    else if(abs(distance-(SensorValue[EncoderRight]/360.0)*wheelCir) <= dPeriod)
    {
      output = ((distance-(SensorValue[EncoderRight]/360.0)*wheelCir)* 0.5 *maxDrive*(127-minPow))/127.0;
      if(output>0)
        output = output+minPow;
      else if(output<0)
        output = output-minPow;
      else
        output = 0;
    }
    //// called if not in aceleration or deceleration
    else
    {
      output = maxDrive*direction;
    }

    // Called to apply power and correct offset error
    if(abs(SensorValue[EncoderRight])>abs(SensorValue[EncoderLeft]))
    {
      motor[RightDrive] = output*TC;
      motor[LeftDrive]  = output;
    }
    else if(abs(SensorValue[EncoderRight])<abs(SensorValue[EncoderLeft]))
    {
      motor[RightDrive] = output;
      motor[LeftDrive]  = output*TC;
    }
    else
    {
      motor[RightDrive] = motor[LeftDrive] = output;
    }

    if(time1[T1]>100)
    {
      float eDistance = abs(leValue-SensorValue[EncoderRight]);
      velocity = eDistance/(time1[T1]/1000.0);
      leValue = SensorValue[EncoderRight];
      time1[T1] = 0;
    }
  }

  motor[RightDrive] = 0;
  motor[LeftDrive] = 0;

  positionX = positionX + distance * cos(degreesToRadians(angle));
  positionY = positionY + distance * sin(degreesToRadians(angle));
}

void encoderTurnDegrees(int degrees)
{
    degrees = degrees%360;

    float distance = ((degrees/360.0)*PI*driveWidth;
    float output;
    float stillTime = 0;

    encodersReset();

    while(stillTime < 100)
    {
      if((SensorValue[EncoderRight]/360.0)*wheelCir < distance)
        output = turnDrive;
      else if((SensorValue[EncoderRight]/360.0)*wheelCir > distance)
        output = -turnDrive;
      else
        output = 0;

      //// applying output
      if(abs(SensorValue[EncoderRight])>abs(SensorValue[EncoderLeft]))
      {
        motor[RightDrive] = output*TC;
        motor[LeftDrive]  = output;
      }
      else if(abs(SensorValue[EncoderRight])<abs(SensorValue[EncoderLeft]))
      {
        motor[RightDrive] = output;
        motor[LeftDrive]  = output*TC;
      }
      else
      {
        motor[RightDrive] = motor[LeftDrive] = output;
      }

      if(abs((SensorValue[EncoderRight]/360.0)*wheelCir - distance)<0.1 && abs((SensorValue[EncoderLeft]/360.0)*wheelCir + distance) < 0.1)
      {
        stillTime = time1[T1];
      }
      else
      {
        time1[T1] = 0;
      }
    }

    motor[RightDrive] = 0;
    motor[LeftDrive] = 0;

    angle = (angle + degrees)%360;
}

void encoderTurnToAngle(int degrees)
{
    double turnDegrees = (degrees-angle)%360;

    encoderTurnDegrees(turnDegrees);
}

void encoderSetRelativeWayPoint(double xFeet, double yFeet)
{
    double turnAngle;

    if(xFeet<0)
    {
        turnAngle = 180;
    }
    else
    {
        turnAngle = 0;
    }

    turnAngle = turnAngle + atan(yFeet/xFeet);

    encoderTurnToAngle(turnAngle);
    encoderDriveStraight(sqrt(pow(xFeet, 2)+pow(yFeet, 2)));
}

void encoderSetFieldWayPoint(double xFeet, double yFeet)
{
    encoderSetRelativeWayPoint(xFeet-positionX, yFeet-positionY);
}

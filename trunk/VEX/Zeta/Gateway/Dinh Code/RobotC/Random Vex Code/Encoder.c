
/// Variables to configure the encoder

double positionX;
double positionY;

double angle;
double maxDrive;
double driveWidth;
double wheelDiameter;
double wheelCir;

void encoderConfigure(double startX, double startY, double startAngle, double mDrive, double width, double wheelD) // wheel diameter and width must be in feet
{
    positionX = startX;
    positionY = startY;
    angle = startAngle;
    maxDrive  = mDrive;
    driveWidth = width;
    wheelDiameter = wheelD;
    wheelCir = wheelDiameter*3.1415926;

    /// any code needed to begin using an encoder

}

void encodersReset()
{
  SensorValue[EncoderRight] = 0;
  SensorValue[EncoderLeft]  = 0;
}

void encoderDriveStraight(double distance)
{
    encodersReset();

    while(SensorValue[EncoderRight] < 360*(distance/wheelCir))
    {
        if(SensorValue[EncoderRight] < 360*((distance-1)/wheelCir))
        {
            if(SensorValue[EncoderRight]> SensorValue[EncoderLeft])
            {
                motor[RightDrive] = maxDrive*0.8;
                motor[LeftDrive]  = maxDrive;
            }
            else if(SensorValue[EncoderRight] < SensorValue[EncoderLeft])
            {
                motor[RightDrive] = maxDrive;
                motor[LeftDrive]  = maxDrive*0.8;
            }
            else
            {
                motor[RightDrive] = maxDrive;
                motor[LeftDrive]  = maxDrive;
            }
        }
        else     // this is used to "slow down" the drive train to eliminate error at the stop point
        {
            if(SensorValue[EncoderRight]> SensorValue[EncoderLeft])
            {
                motor[RightDrive] = (distance - (SensorValue[EncoderRight]/360.0)*wheelCir) * maxDrive*0.8;
                motor[LeftDrive]  = (distance - (SensorValue[EncoderLeft]/360.0)*wheelCir) * maxDrive;
            }
            else if(SensorValue[EncoderRight] < SensorValue[EncoderLeft])
            {
                motor[RightDrive] = (distance - (SensorValue[EncoderRight]/360.0)*wheelCir) * maxDrive;
                motor[LeftDrive]  = (distance - (SensorValue[EncoderLeft]/360.0)*wheelCir) * maxDrive*0.8;
            }
            else
            {
                motor[RightDrive] = (distance - (SensorValue[EncoderRight]/360.0)*wheelCir) * maxDrive;
                motor[LeftDrive]  = (distance - (SensorValue[EncoderLeft]/360.0)*wheelCir) * maxDrive;
            }
        }
    }

    motor[RightDrive] = 0;
    motor[LeftDrive] = 0;

    positionX = positionX + distance * cos(angle);
    positionY = positionY + distance * sin(angle);
}

void encoderTurnDegrees(double degrees)
{
    degrees = degrees%360;

    double distance = ((degrees%360)/360.0)*3.1415926*driveWidth;

    double turnDrive = 0.4*maxDrive;

    encodersReset();

    while(SensorValue[EncoderRight] < 360*(distance/wheelCir) && -SensorValue[EncoderLeft] < 360*(distance/wheelCir))
    {
        if(SensorValue[EncoderRight]< 360*(distance-1/wheelCir) && -SensorValue[EncoderLeft] < 360*(distance/wheelCir))
        {
            if(SensorValue[EncoderRight] > -SensorValue[EncoderLeft])
            {
                motor[RightDrive] = turnDrive*0.8;
                motor[LeftDrive]  = -turnDrive;
            }
            else if(SensorValue[EncoderRight] < -SensorValue[EncoderLeft])
            {
                motor[RightDrive] = turnDrive;
                motor[LeftDrive]  = -turnDrive*0.8;
            }
            else
            {
                motor[RightDrive] = turnDrive;
                motor[LeftDrive]  = -turnDrive;
            }
        }
        else     // this is used to "slow down" the drive train to eliminate error at the stop point
        {
            if(SensorValue[EncoderRight]> SensorValue[EncoderLeft])
            {
                motor[RightDrive] = (distance - (SensorValue[EncoderRight]/360.0)*wheelCir) * turnDrive*0.8;
                motor[LeftDrive]  = -(distance - (-SensorValue[EncoderLeft]/360.0)*wheelCir) * turnDrive;
            }
            else if(SensorValue[EncoderRight] < SensorValue[EncoderLeft])
            {
                motor[RightDrive] = (distance - (SensorValue[EncoderRight]/360.0)*wheelCir) * turnDrive;
                motor[LeftDrive]  = -(distance - (-SensorValue[EncoderLeft]/360.0)*wheelCir) * turnDrive*0.8;
            }
            else
            {
                motor[RightDrive] = (distance - (SensorValue[EncoderRight]/360.0)*wheelCir) * turnDrive;
                motor[LeftDrive]  = -(distance - (-SensorValue[EncoderLeft]/360.0)*wheelCir) * turnDrive;
            }
        }
    }

    motor[RightDrive] = 0;
    motor[LeftDrive] = 0;

    angle = (angle + degrees)%360;
}

void encoderTurnToAngle(double degrees)
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
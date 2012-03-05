/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++
Mecanum Drive with Deadzone Thresholds
- This program allows you to remotely control a robot with mecanum wheels.
- The left joystick Y-axis controls the robot's forward and backward movement.
- The left joystick X-axis controls the robot's left and right movement.
- The right joystick X-axis controls the robot's rotation.
- This program incorportes a threshold/deadzone that allows very low Joystick values to be ignored.
This allows the robot to ignore values from the Joysticks when they fail to center at 0,
and provides a margin of error for the driver when they only want the robot to move in one axis.

[I/O Port]          [Name]              [Type]                [Description]
Motor Port 2        frontRight          VEX Motor             Front Right motor
Motor Port 3        backRight           VEX Motor             Back Right motor
Motor Port 4        frontLeft           VEX Motor             Front Left motor
Motor Port 5        backLeft            VEX Motor             Back Left motor
--------------------------------------------------------------------------------------------------*/

void simpleMechanumDrive(){

  int X1=0, X2=0, Y1=0, threshold = 15;
  //Create "deadzone" for Y1/Ch3
  if(abs(vexRT[Ch3]) > threshold)
    Y1 = vexRT[Ch3];
  else
    Y1 = 0;
  //Create "deadzone" for X1/Ch4
  if(abs(vexRT[Ch4]) > threshold)
    X1 = vexRT[Ch4];
  else
    X1 = 0;
  //Create "deadzone" for X2/Ch1
  if(abs(vexRT[Ch1]) > threshold)
    X2 = vexRT[Ch1];
  else
    X2 = 0;

  //Remote Control Commands
  motor[FrontRight1] = motor[FrontRight2] = Y1 - X2 + X1;
  motor[BackRight] =  Y1 - X2 - X1;
  motor[FrontLeft1] = motor[FrontLeft2] = Y1 + X2 - X1;
  motor[BackLeft] =  Y1 + X2 + X1;
  }

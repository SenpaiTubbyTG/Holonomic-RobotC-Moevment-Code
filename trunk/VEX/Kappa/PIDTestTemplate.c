#pragma config(Sensor, in1,    potArm,                 sensorPotentiometer)
#pragma config(Motor,  port1,           leftArm,       tmotorNormal, openLoop)
#pragma config(Motor,  port2,           rightArm,      tmotorNormal, openLoop)

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "PIDController.c"
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!


int MAX_ARM = 100;
int goalValue = 1000;
int KP = 1;
int KI = 0;
int KD = 0;
bool armPID = false;

controller PID;

void pre_auton()
{
init(PID,potArm,port4);
setSetpoint(PID, goalValue);
setPIDs(PID, Kp, KI, KD);
enable(PID);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
void armDrive()  {
  if(vexRT[Btn5U] == 1)
  {
    motor[rightArm] = MAX_ARM;
    motor[leftArm] = MAX_ARM;
  }
  else if(vexRT[Btn5D] == 1)
  {
    motor[leftArm] = -MAX_ARM;
    motor[rightArm] = -MAX_ARM;
  }
}


task autonomous()
{

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
    armDrive();
	}
}

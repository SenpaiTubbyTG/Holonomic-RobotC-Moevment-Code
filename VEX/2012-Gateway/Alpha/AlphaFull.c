#pragma config(Motor,  port1,           ArmLL,         tmotorNormal, openLoop)
#pragma config(Motor,  port2,           DriveLF,       tmotorNormal, openLoop)
#pragma config(Motor,  port3,           DriveLB,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           DriveRF,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           DriveRB,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           ArmLU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           ArmRU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           collector1,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           collector2,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          ArmRL,         tmotorNormal, openLoop)

#pragma platform(VEX)


//Competition Control and Duration Settings
#pragma competitionControl(Competition)`
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
    wait10Msec(30);

    motor[ArmLL] = 50; //Raise Arm
    motor[ArmRL] = 50;
    motor[ArmLU] = 50;
    motor[ArmRU] = 50;
    wait10Msec(120);

    motor[ArmLL] = 0; //Stop arm
    motor[ArmRL] = 0;
    motor[ArmLU] = 0;
    motor[ArmRU] = 0;

    motor[DriveLF]= 50; //drive forward
    motor[DriveLB]= 50;
    motor[DriveRB]= 50;
    motor[DriveRB]= 50;
    wait10Msec(90);

    motor[DriveLF]= 0; //stop driving
    motor[DriveLB]= 0;
    motor[DriveRB]= 0;
    motor[DriveRB]= 0;

    motor[collector1] = -100; //expell objects
    motor[collector2] = -100;
    wait10Msec(300);

    motor[collector1] = 0; //stop collector
    motor[collector2] = 0;

    motor[DriveLF]= -50; //drive backwards
    motor[DriveLB]= -50;
    motor[DriveRB]= -50;
    motor[DriveRB]= -50;
    wait10Msec(90);

    motor[DriveLF]= 0;
    motor[DriveLB]= 0;
    motor[DriveRB]= 0;
    motor[DriveRB]= 0;
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
   motor[DriveLF] = vexRT[Ch3];
   motor[DriveLB] = vexRT[Ch3];
   motor[DriveRF] = vexRT[Ch2];
   motor[DriveRB] = vexRT[Ch2];
   motor[ArmLL] = (vexRT[Btn6U] - vexRT[Btn6D])*127;
   motor[ArmLU] = (vexRT[Btn6U] - vexRT[Btn6D])*127;
   motor[ArmRL] = (vexRT[Btn6U] - vexRT[Btn6D])*127;
   motor[ArmRU] = (vexRT[Btn6U] - vexRT[Btn6D])*127;
   motor[collector1] = (vexRT[Btn5U] - vexRT[Btn5D])*127;
   motor[collector2] = (vexRT[Btn5U] - vexRT[Btn5D])*127;

   }
}

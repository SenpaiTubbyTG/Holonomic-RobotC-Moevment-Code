#pragma config(Sensor, dgtl1,  RightBumper,         sensorTouch)
#pragma config(Sensor, dgtl2,  LeftBumper,          sensorTouch)
#pragma config(Motor,  port1,           RightBottomLifter, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           RightDrive,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           LeftDrive,     tmotorNormal, openLoop)
#pragma config(Motor,  port4,           LeftBottomLifter, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           LeftUpperLifter, tmotorNormal, openLoop)
#pragma config(Motor,  port6,           Collector,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           Descorer,      tmotorNormal, openLoop)
#pragma config(Motor,  port10,          RightUpperLifter, tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
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
time1[T1] = 0;
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


  motor[port1] = -127;
  motor[port4] = -127;
  motor[port5] = -127;
  motor[port10] = -127;
  wait1Msec(950);                 //: Raises collector to dump preloads

  motor[port1] = 0;
  motor[port4] = 0;
  motor[port5] = 0;
  motor[port10] = 0;


  ClearTimer(T1);
  motor[port2] = 50;
  motor[port3] = 50;
  wait1Msec(1000);

  ClearTimer(T1);
  motor[port2] = 0;
  motor[port3] = 0;
  wait1Msec(100);





     motor[port2] = -25;  //:backs up to aim donut
     motor[port3] = -25;
     wait1Msec(350);


     motor[port2] = 0;
     motor[port3] = 0;
     motor[port6] = 127;  //:spins out donut
     wait1Msec(700);

     motor[port6] = 0;    //:Stops spinner








	AuonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
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
    {

	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................
	  // Insert user code here. This is where you use the joystick values to update your motors, etc.
	  // .....................................................................................

	  //Drive Train//////////////////////////////////////////////////////////////////
                       //Right Drive
                                                          if(vexRT[Ch2] < 20 && vexRT[Ch2] > -20)//If input is between 5 & -5...
                               {
                                 motor[port2] = 0;                    //...drive train motors = 0
                               }
                               else                                   //If input is greater then 5 or smaller then -5...
                               {
                                 motor[port2] = (vexRT[Ch2]);   //...drive trian motors = scale
                               }
                 //Left Drive
                               if (vexRT[Ch3] < 10 && vexRT[Ch3] > -10)//If input is between 15 & -15...
                               {
                                 motor[port3] = 0;                     //...drive train motors = 0
                               }
                               else                                    //If input is greater then 15 or smaller then -15...
                               {
                                 motor[port3] = (vexRT[Ch3]);    //...drive trian motors = scale
                               }

         switch(vexRT[Btn6D] - vexRT[Btn6U])  //: Lifting arm conditions
          {
             case  1:motor[port1] = -127;
                     motor[port4] = -127;
                     motor[port5] = -127;
                     motor[port10] = -127;
                     break;
             case -1:motor[port1] = 127;
                     motor[port4] = 127;
                     motor[port5] = 127;
                     motor[port10] = 127;
                     break;
             case  0:motor[port1] = 0;
                     motor[port4] = 0;
                     motor[port5] = 0;
                     motor[port10]= 0;
                     break;
          }

            switch(vexRT[Btn5D] - vexRT[Btn5U])  //: Collector/plunger conditions
          {
             case  1:motor[port6] = -127;
                     break;
             case -1:motor[port6] = 127;
                     break;
             case  0:motor[port6] = 0;
                     break;
          }



	  UserControlCodePlaceholderForTesting(); // Remove this function call once you have "real" code.
	  }
  }
}
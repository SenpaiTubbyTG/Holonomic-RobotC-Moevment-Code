#pragma config(Sensor, in1,    pot,                 sensorPotentiometer)
#pragma config(Sensor, in2,    l1,                  sensorLineFollower)
#pragma config(Sensor, in3,    l2,                  sensorLineFollower)
#pragma config(Sensor, in4,    l3,                  sensorLineFollower)
#pragma config(Sensor, dgtl1,  sonar,               sensorSONAR_cm)
#pragma config(Sensor, dgtl4,  ncoderR,             sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  ,                    sensorSONAR_inch)
#pragma config(Motor,  port1,           ,              tmotorNormal, openLoop)
#pragma config(Motor,  port2,           left,          tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           right,         tmotorNormal, openLoop)
#pragma config(Motor,  port6,           port6,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           port7,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           port8,         tmotorNormal, openLoop)
#pragma config(Motor,  port9,           port9,         tmotorNormal, openLoop)
#pragma config(Motor,  port10,          Claw,          tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
//#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
/*
there are three parts to the LCD program selection code.
first are the variable definitions.
secondly, there is a screen refresh function, to be placed with your other
voids/functions.
and lastly, there is the LCD code itself.
place this in your pre-auton section.
The code will output two variables:
redteam is the boolean variable that will output true or false
programselect is the program number you have selected.
totalprogramnumber is the constant you should modify right at the start.
this is the amount of programs you are loading.
*/


//variables:
int programselect = 1;
bool redteam = true;
bool programselecting = true;
const int totalprogramnumber = 5;

//function:
void screenrefresh()
{
  clearLCDLine(1);
  displayLCDPos(1,0);
  if (redteam == true)
  {
    displayNextLCDString("RED ");
  }
  if (redteam == false)
  {
    displayNextLCDString("BlUE");
  }
  displayNextLCDString("    ");
  displayNextLCDNumber(programselect);
  displayNextLCDString("     OK");
}
void stopallmotors()
{
  motor[right] = 0;
  motor[left] = 0;
}





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
  //main code-to be placed in pre-auton section:
  bLCDBacklight = true;
  displayLCDPos(0,0);
  displayNextLCDString("program select");
  redteam = true;
  screenrefresh();
  time1[T1] = 0;
  while (programselecting == true)
  {
    if (nLCDButtons & kLeftButton)
    {
      while (nLCDButtons & kLeftButton)
      {
      }
      if (redteam == true)
      {
        redteam = false;
      }
      else if (redteam == false)
      {
        redteam = true;
      }
      screenrefresh();
    }
    if (nLCDButtons & kCenterButton)
    {
      while (nLCDButtons & kCenterButton)
      {
      }
      programselect = programselect+1;
      if (programselect > totalprogramnumber)
      {
        programselect = 1;
      }
      screenrefresh();
    }
    if (nLCDButtons & kRightButton)
    {
      clearLCDLine(0);
      clearLCDLine(1);
      displayLCDPos(0,0);
      displayNextLCDString("Robot ready");
      wait1Msec(300);
      displayNextLCDString(".");
      wait1Msec(300);
      displayNextLCDString(".");
      wait1Msec(300);
      displayNextLCDString(".");
      wait1Msec(500);
      bLCDBacklight = false;
      programselecting = false;
    }
  }
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

  if (programselect == 1)

  {
    if (redteam == true)
    {

      motor[port2] = -127;
      motor[port3] = -127;
      wait1Msec(1000);//blue code for program 1 //red code for program 1
      motor[port2] = 0;
      motor[port3] = 0;

    }
    else //if (redteam == false)
    {
      motor[port2] = 127;
      motor[port3] = 127;
      wait1Msec(1000);//blue code for program 1
      motor[left] = 0;
      motor[port3] = 0;
    }



  }

  if (programselect == 2)
  {

    if (redteam == true)
    {
      while(true)
      {
        if(SensorValue(sonar) <50)		// Loop while robot's Ultrasonic sensor is further than 20 inches away from an object
        {
          stopallmotors();
          motor[right] = -127;			// Motor on port2 is run at half (63) power forward
          motor[left]  = 127;
          wait1Msec(750);
          stopallmotors();

        }
        else
        {
          motor[right] = 127;
          motor[left] = 127;
        }


      }
    }

  }
}
// .....................................................................................
// Insert user code here.
// .....................................................................................

// Remove this function call once you have "real" code.


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

//task usercontrol()



task usercontrol()

{


  //----------------------------------------------------------------


  while(true){
    motor[port2] = vexRT[Ch2];
    motor[right] = vexRT[Ch3];

  }






  // This is the main execution loop for the user control program. Each time through the loop
  // your program should update motor + servo values based on feedback from the joysticks.

  // .....................................................................................
  // Insert user code here. This is where you use the joystick values to update your motors, etc.
  // .....................................................................................

  // Remove this function call once you have "real" code.

}

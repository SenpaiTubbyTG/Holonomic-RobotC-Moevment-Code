#pragma config(Sensor, in1,    Program,             sensorPotentiometer)
#pragma config(Sensor, in2,    ArmPot,              sensorPotentiometer)
#pragma config(Sensor, dgtl1,  EncoderR,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  EncoderL,            sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  solenoid,            sensorDigitalOut)
#pragma config(Motor,  port1,           DriveRB,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           DriveRF,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           DriveLF,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           ArmRL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           ArmLL,         tmotorNormal, openLoop)
#pragma config(Motor,  port6,           ArmRU,         tmotorNormal, openLoop)
#pragma config(Motor,  port7,           ArmLU,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           SuckR,         tmotorNormal, openLoop)
#pragma config(Motor,  port9,           SuckL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          DriveLB,       tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//: Right and left are set using the back-view of robot nnn


//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20000000)
#pragma userControlDuration(80000000000000000000)

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

  SensorValue[EncoderR] = 0;
  SensorValue[EncoderL] = 0;
  time1[T1] = 0;
}


//////////////////////////////////////////////////////////////////////////////////////``  ///
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
//////////////////////////                        ///////////////////////////////////////////////////////////////

task autonomous()
{











}//: task auton.

task usercontrol()
{
  while (true)
//Drive train- arcade
  {
    motor[DriveRB]  = (vexRT[Ch2] - vexRT[Ch1]);  // (y + x)
    motor[DriveRF]  = (vexRT[Ch2] - vexRT[Ch1]);  // (y + x)
    motor[DriveLB] = (vexRT[Ch2] + vexRT[Ch1]);  // (y - x)
    motor[DriveLF] = (vexRT[Ch2] + vexRT[Ch1]);  // (y - x)

    //: Arm trim
            if(vexRT[Ch3] < 15 && vexRT[Ch3] > -15)//If input is between 15 & -15...
                {
                     motor[ArmRL] = 0;
                     motor[ArmRU] = 0;
                     motor[ArmLL] = 0;
                     motor[ArmLU] = 0;                //...drive train motors = 0
                } //: if
                else
                {


                    motor[ArmRL] = vexRT[Ch3];//:port6
                    motor[ArmRU] = vexRT[Ch3];//:port7
                    motor[ArmLL] = vexRT[Ch3];//:port8
                    motor[ArmLU] = vexRT[Ch3];//:port9
                } //: else
  //: Sucker


  switch(vexRT[Btn5U] - vexRT[Btn5D])
    {
      case  1:motor[SuckR] = 127;
              motor[SuckL] = 127;
              break;
      case -1:motor[SuckR] = -127;
              motor[SuckL] = -127;
              break;
      case  0:motor[SuckR] = 0;
              motor[SuckL] = 0;
              break;

          }//: switch

                                 // Loop Forever
  if(vexRT[Btn6U] == 1) {
      SensorValue[solenoid] = 0;  // ...activate the solenoid.
    }
    else if(vexRT[Btn6D] == 1) {
      SensorValue[solenoid] = -1;  // ..deactivate the solenoid.
    }



  }//: while
}//:task UserControl
#pragma config(Sensor, in1,    potArm,                 sensorPotentiometer)
#pragma config(Motor,  port1,           leftArm,       tmotorNormal, openLoop)
#pragma config(Motor,  port2,           rightArm,      tmotorNormal, openLoop)

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "PIDController.h"
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!


int maxArm = 100;
int goalValue = 1000;
int KP = 1;
int KI = 0;
int KD = 0;
bool armPID = false;

controller PID;

//set Values;
int armGround = SensorValue[potArm];
int lowScore = armGround// + value still to be tested;
int medScore = armGround// + value still to be tested;
int highScore = armGround// + value still to be tested;

void pre_auton()
{
init(PID,potArm,port4);
setSetpoint(PID, goalValue);
setPIDs(PID, Kp, KI, KD);
enable(PID);
}
void setArmSpeed(int speed){
  motor[leftArm] = speed;
  motor[rightArm] = speed;
}

/*int lockArm(int finalPos){
  int currentPos = sensorValue(PotArm);
  int direction;
  int diff = abs(currentPos - finalPos);

    if(diff > 200){
      if (currentPos > finalPos){
        direction = 1;
      }
      else if(currentPos < finalPos){
        direction = -1;
      }
      setArmSpeed(maxArm * direction);
      return 0;
  }
  else {
    setArmSpeed(0);
    return 1;
    }*/
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
    motor[rightArm] = maxArm;
    motor[leftArm] = maxArm;
  }
  else if(vexRT[Btn5D] == 1)
  {
    motor[leftArm] = -maxArm;
    motor[rightArm] = -maxArm;
  }
}


task autonomous()
{
  pre_auton();
  int armUp = 0;

  if(armUp != 1)
    lockArm(armGround);


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
            if((vexRT[Btn6D] - vexRT[Btn6U])!= 0){
              setArmSpeed((vexRT[Btn5D] - vexRT[Btn5U]) * maxArm);
              disable(PID);
            }
            else{
              setArmSpeed(calcPID(PID));
            }

            if(vexRT[Btn7U] == 1){
              setSetpoint(PID, highScore);
              enable(PID);
            }
            else if (vexRT[Btn7D] == 1){
              setSetpoint(PID, lowScore);
              enable(PID);
            }
            else if (vexRT[Btn7L] == 1){
              setSetpoint(PID, armGround);
              enable(PID);
            }
              else if (vexRT[Btn7L] == 1){
              disable(PID);
            }
        }
}

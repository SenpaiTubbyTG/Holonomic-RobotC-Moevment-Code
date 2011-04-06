#pragma config(Sensor, dgtl12,  TouchGoal,           sensorTouch)
#pragma config(Sensor, in1,    pot,                 sensorPotentiometer)
#pragma config(Motor,  port1,           ArmL, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           DriveR, tmotorNormal, openLoop)
#pragma config(Motor,  port3,           DriveR2, tmotorNormal, openLoop)
#pragma config(Motor,  port4,           DriveL, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           DriveL2, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           ArmBigL,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           ArmBigR,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           Claw,          tmotorNormal, openLoop)
#pragma config(Motor,  port10,          ArmR, tmotorNormal, openLoop, reversed)

/*
Pot values NOT CODE
arm_grounded = 1250
descore_lock_point = 1680 - 1250 = 430
low_lock_point = 2300 - arm grounded = 1050
high_lock_point = 2587 - arm_grounded = 1337

*/
int lock(int final_pos) //locks arm to final_pos potentiometer point
{
  int current_pos = SensorValue(in1); //reads potentiometer
  int direction;                      //up or down?
  int arm_diff = abs(current_pos - final_pos);//difference between current and desired points

  if(arm_diff > 100) {  //potentiometer is very precise, so
    if (current_pos > final_pos) {//arm too high
      direction = 1;    //will move down
    }
    else if(current_pos < final_pos) { //arm too low
      direction = -1; //will move up
    }
    motor[port1] = 127 * direction; //sets motors
    motor[port6] = 127 * direction;
    motor[port7] = 127 * direction;
    motor[port10] = 127* direction;
    return 0;
  }
    else {  //in hindsight, I don't think this is necessary
    motor[port1] = -10;//no need to move for lock; will continue holding
    motor[port6] = -10;
    motor[port7] = -10;
    motor[port10] = -10;
    return 1;
        }


}

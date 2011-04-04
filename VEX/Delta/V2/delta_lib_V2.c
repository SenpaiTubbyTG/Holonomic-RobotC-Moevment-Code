#pragma config(Sensor, in1,    PotArm,              sensorPotentiometer)
#pragma config(Sensor, dgtl1,  EncoderR,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  EncoderL,            sensorQuadEncoder)
#pragma config(Sensor, dgtl12, TouchGoal,           sensorTouch)
#pragma config(Motor,  port1,           SuckR,         tmotorNormal, openLoop)
#pragma config(Motor,  port2,           DriveRB,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           DriveRF,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           DriveLB,       tmotorNormal, openLoop)
#pragma config(Motor,  port5,           DriveLF,       tmotorNormal, openLoop)
#pragma config(Motor,  port6,           ArmRL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           ArmRU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           ArmLL,         tmotorNormal, openLoop)
#pragma config(Motor,  port9,           ArmLU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          SuckL,         tmotorNormal, openLoop, reversed)

#define FULL 127

int lock(int final_pos) //locks arm to final_pos potentiometer point
{
  int current_pos = SensorValue(PotArm); //reads potentiometer
  int direction;                      //up or down?
  int arm_diff = abs(current_pos - final_pos);//difference between current and desired points

  if(arm_diff > 100) {  //potentiometer is very precise, so
    if (current_pos > final_pos) {//arm too high
      direction = 1;    //will move down
    }
    else if(current_pos < final_pos) { //arm too low
      direction = -1; //will move up
    }
    motor[ArmRU] = FULL * direction; //sets motors
    motor[ArmRL] = FULL * direction;
    motor[ArmLU] = FULL * direction;
    motor[ArmLL] = FULL * direction;
    return 0;
  }
  else {  //in hindsight, I don't think this is necessary
    motor[ArmRU] = 0; //no need to move for lock; will continue holding
    motor[ArmRL] = 0;
    motor[ArmLU] = 0;
    motor[ArmLL] = 0;
    return 1;
  }
}

int sucker(int speed, int duration) { //positive numbers for out
  motor[SuckR] = -speed;
  motor[SuckL] = speed;
  wait1Msec(duration);
  motor[SuckR] = 0;
  motor[SuckL] = 0;
  return 1;
}

/* DRIVE FUNCTIONS
 * drive_forward_1msec
 * drive_straight
 * drive_straight_to_touch
 */

 /* drive_forward_msec
  * @purpose: autonomously drive robot forward for provided duration
  * @param speed: speed of motors, -127 to 127; negative values go reverse
  * @param duration: duration in milliseconds
 */

void drive_forward_msec(int speed, int duration) {
  motor[DriveRF] = speed;
  motor[DriveRB] = speed;
  motor[DriveLF] = speed;
  motor[DriveLB] = speed;
  wait1Msec(duration);
  motor[DriveRF] = 0;
  motor[DriveRB] = 0;
  motor[DriveLF] = 0;
  motor[DriveLB] = 0;
}

/* drive_straight_suck
  * @purpose: autonomously drive robot forward for provided distance in inches
  * precondition: 4 inch wheels used; if other wheels, change the 4 in the while loop
  * @param speed: speed of drive motors, -127 to 127; negative values go reverse
  * @param suckspeed: speed of suck motors. -127 to 127; negative values go reverse
  * @param distance: distance in inches
  * TODO: consider adding an acceleration loop
 *///there are 360 ticks in an encoder revolution

 void drive_straight_suck(int speed, int suckspeed, float distance) {
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;
  while( ( (float) abs(SensorValue[EncoderL])  * 4 / 360 * PI) < distance &&
         ( (float) abs(SensorValue[EncoderR]) * 4 / 360 * PI) < distance) {
    if(abs(SensorValue[EncoderL]) > abs(SensorValue[EncoderR])) {
      motor[DriveRF] = -speed;
      motor[DriveRB] = -speed;
      motor[DriveLF] = -speed + 1;
      motor[DriveLB] = -speed + 1;
      motor[SuckR] = suckspeed;
      motor[SuckL] = suckspeed;

    }
    else if(abs(SensorValue[EncoderL]) < abs(SensorValue[EncoderR])) {
      motor[DriveRF] = -speed + 1;
      motor[DriveRB] = -speed + 1;
      motor[DriveLF] = -speed;
      motor[DriveLB] = -speed;
      motor[SuckR] = suckspeed;
      motor[SuckL] = suckspeed;
    }
    else {
      motor[DriveRF] = -speed;
      motor[DriveRB] = -speed;
      motor[DriveLF] = -speed;
      motor[DriveLB] = -speed;
      motor[SuckR] = suckspeed;
      motor[SuckL] = suckspeed;
    }
  }
  motor[DriveRF] = 0;
  motor[DriveRB] = 0;
  motor[DriveLF] = 0;
  motor[DriveLB] = 0;
  motor[SuckR] = 0;
  motor[SuckL] = 0;
}

/* drive_straight
  * @purpose: autonomously drive robot forward for provided distance in inches
  * precondition: 4 inch wheels used; if other wheels, change the 4 in the while loop
  * @param speed: speed of motors, -127 to 127; negative values go reverse
  * @param distance: distance in inches
  * TODO: consider adding an acceleration loop
 *///there are 360 ticks in an encoder revolution

 void drive_straight(int speed, float distance) {
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;
  while( ( (float) abs(SensorValue[EncoderL])  * 4 / 360 * PI) < distance &&
         ( (float) abs(SensorValue[EncoderR]) * 4 / 360 * PI) < distance) {
    if(abs(SensorValue[EncoderL]) > abs(SensorValue[EncoderR])) {
      motor[DriveRF] = -speed;
      motor[DriveRB] = -speed;
      motor[DriveLF] = -speed + 1;
      motor[DriveLB] = -speed + 1;
    }
    else if(abs(SensorValue[EncoderL]) < abs(SensorValue[EncoderR])) {
      motor[DriveRF] = -speed + 1;
      motor[DriveRB] = -speed + 1;
      motor[DriveLF] = -speed;
      motor[DriveLB] = -speed;
    }
    else {
      motor[DriveRF] = -speed;
      motor[DriveRB] = -speed;
      motor[DriveLF] = -speed;
      motor[DriveLB] = -speed;
    }
  }
  motor[DriveRF] = 0;
  motor[DriveRB] = 0;
  motor[DriveLF] = 0;
  motor[DriveLB] = 0;
}

/* drive_straight_unlocked
  * @purpose: autonomously drive robot forward for provided distance in inches WHILE allowing
  * precondition: 4 inch wheels used; if other wheels, change the 4 in the while loop
  * @param speed: speed of motors, -127 to 127; negative values go reverse
  * @param distance: distance in inches
  * TODO: consider adding an acceleration loop
 *///there are 360 ticks in an encoder revolution

 int drive_straight_unlocked(int speed, float distance) {
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;
  if( ( (float) abs(SensorValue[EncoderL])  * 2 / 360 * PI) < distance &&
      ( (float) abs(SensorValue[EncoderR]) * 2 / 360 * PI) < distance) {
    if(abs(SensorValue[EncoderL]) > abs(SensorValue[EncoderR])) {
      motor[DriveRF] = -speed;
      motor[DriveRB] = -speed;
      motor[DriveLF] = -speed + 1;
      motor[DriveLB] = -speed + 1;
    }
    else if(abs(SensorValue[EncoderL]) < abs(SensorValue[EncoderR])) {
      motor[DriveRF] = -speed + 1;
      motor[DriveRB] = -speed + 1;
      motor[DriveLF] = -speed;
      motor[DriveLB] = -speed;
    }
    else {
      motor[DriveRF] = -speed;
      motor[DriveRB] = -speed;
      motor[DriveLF] = -speed;
      motor[DriveLB] = -speed;
    }
    return 0;
  }
  else
    return 1;
}

/* turn
  * @purpose: autonomously execute a point turn
  * @param speed: speed of motors, 0 to 127; no negative values
  * @param degrees: number of degrees to turn, positive degrees go to left
  * TODO: complete this function
 */
void turn(int speed, int degrees) {
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;
  while(SensorValue[EncoderL] < degrees || SensorValue[EncoderR] < degrees*2) {
    motor[DriveRF] = speed;
    motor[DriveRB] = speed;
    motor[DriveLF] = -speed;
    motor[DriveLB] = -speed;
  }
  motor[DriveRF] = 0;
  motor[DriveRB] = 0;
  motor[DriveLF] = 0;
  motor[DriveLB] = 0;
}

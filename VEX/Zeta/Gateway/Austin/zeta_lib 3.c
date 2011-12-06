/////////////////////////////////////////////////////////////////////////
//ZETA FUNCTION LIBRARY//////////////////////////////////////////////////
//-                                                                   -//
//-                                                                   -//

/////////////////////////////////*Drive*/////////////////////////////////
//-                                                                   -//
//-                                                                   -//

/*DEFINITIONS*/
#define FULL 127
#define gyroError 10
#define gyroCenter 0

/*Set Drive Left Speed*/
void setDriveLSpeed(int speed) {
  motor[leftFront] = motor[leftMiddle] = motor[leftBack] = speed;
}

/*Set Drive Right Speed*/
void setDriveRSpeed(int speed) {
  motor[rightFront] = motor[rightMiddle] = motor[rightBack] = speed;
}

/*Kill Drive*/
void killDrive() {
  setDriveLSpeed(0);
  setDriveRSpeed(0);
}

/*Drive msec*/
int drive_power;
int drive_duration;

   /*Drive msec*/
/*task task_drive_msec {
  setDriveLSpeed(drive_power);
  setDriveRSpeed(drive_power);
  wait1Msec(drive_duration);
  killDrive();
}

void drive_msec(int speed, int duration) {
  drive_power = speed;
  drive_duration = duration;
  StartTask (task_drive_msec);
}
*/

/*Drive msec*/
void  drive_msec(int speed, int duration) {
  setDriveLSpeed(FULL);
  setDriveRSpeed(FULL);
  wait1Msec(duration);
  killDrive();
}


/*Drive With Gyro for msec*/
// gyroError and gyro Center (at what gyro value is the robot maintaining a straight line?) are defined in main code using #define
void drive_gyro_msec(int speed, int duration, int direction) {
  ClearTimer(T1);
  while (time1[T1] < duration) {
    if (direction == 1) {//forwards
      if ((SensorValue[gyro] + gyroError) > (gyroCenter)) {
        setDriveLSpeed(speed - 1);
        setDriveRSpeed(speed);
      }
      else if ((SensorValue[gyro] - gyroError) < gyroCenter) {
        setDriveLSpeed(speed);
        setDriveRSpeed(speed - 1);
      }
      else {
        setDriveLSpeed(speed);
        setDriveRSpeed(speed);
      }
    }
    else if (direction == -1) {//backwards
      if ((SensorValue[gyro] - gyroError) > gyroCenter) {
        setDriveLSpeed(-speed + 1);
        setDriveRSpeed(-speed);
      }
      else if ((SensorValue[gyro] + gyroError) < gyroCenter) {
        setDriveLSpeed(-speed);
        setDriveRSpeed(-speed + 1);
      }
      else if (((gyroCenter + gyroError) < SensorValue[gyro]) && (SensorValue[gyro] > (gyroCenter - gyroError))){
        setDriveLSpeed(-speed);
        setDriveRSpeed(-speed);
      }
    }
  }
  killDrive();
}

/* drive_enc
* @purpose: autonomously drive robot forward for provided distance in inches
* precondition: 4 inch wheels used; if other wheels, change the 4 in the while loop
* @param speed: speed of motors, -127 to 127; negative values go reverse
* @param distance: distance in inches
* TODO: consider adding an acceleration loop
*///there are 360 ticks in an encoder revolution

void drive_enc(int speed, float distance) {
  SensorValue[encL] = 0;
  SensorValue[encR] = 0;
  while( ( (float) abs(SensorValue[encL])  * 4 / 360 * PI) < distance &&
    ( (float) abs(SensorValue[encR]) * 4 / 360 * PI) < distance) {
    if(abs(SensorValue[encL]) > abs(SensorValue[encR])) {
      setDriveLSpeed(speed -1);
      setDriveRSpeed(speed);
    }
    else if(abs(SensorValue[encL]) < abs(SensorValue[encR])) {
      setDriveLSpeed(speed);
      setDriveRSpeed(speed - 1);
    }
    else {
      setDriveLSpeed(speed);
      setDriveRSpeed(speed);    }
  }
  killDrive();
}

/*drive_to_tower*/
/*robot drive till it hits button
then continues to drive for a fraction of a second to align itself
1 = fwd, -1 = backwards
*/
/*void drive_to_tower(int speed, int direction) {
  if (direction == 1) {
    if (SensorValue(btnFrontL) == 0) {
      setDriveLSpeed(speed*direction);
      setDriveRSpeed(speed*direction);
    }
    else {
      setDriveLSpeed(speed*direction);
      setDriveRSpeed(speed*direction);
      wait1Msec(200);
    }
  }
  else if (direction == -1) {
    if (SensorValue(btnBackL) == 0) {
      setDriveLSpeed(speed*direction);
      setDriveRSpeed(speed*direction);
    }
    else {
      setDriveLSpeed(speed*direction);
      setDriveRSpeed(speed*direction);
      wait1Msec(200);
    }
  }
}
*/

/////nnnneeeeeddd improvment//////////
/*Drive FWD buttons*/ //1 = forward, -1 = backwards//
/*

void drive_btn(int speed, int direction) {
  if (direction == 1) {//forwards
    if (SensorValue(btnFrontL) == 0 && SensorValue(btnFrontR) == 0) {
      setDriveLSpeed(speed);
      setDriveRSpeed(speed);
    }
    else if (SensorValue(btnFrontL) == 0  && SensorValue(btnFrontR) == 1) {
      setDriveLSpeed(speed);
      setDriveRSpeed(0);
    }
    else if (SensorValue(btnFrontL) == 1  && SensorValue(btnFrontR) == 0) {
      setDriveLSpeed(0);
      setDriveRSpeed(speed);
    }
    else if (SensorValue(btnFrontL) == 1  && SensorValue(btnFrontR) == 1) {
      killDrive();
    }
  }
  else if (direction == -1) {//backwards
    if (SensorValue(btnBackL) == 0 && SensorValue(btnBackR) == 0) {
      setDriveLSpeed(-speed);
      setDriveRSpeed(-speed);
    }
    else if (SensorValue(btnBackL) == 0  && SensorValue(btnBackR) == 1) {
      setDriveLSpeed(-speed);
      setDriveRSpeed(0);
    }
    else if (SensorValue(btnBackL) == 1  && SensorValue(btnBackR) == 0) {
      setDriveLSpeed(0);
      setDriveRSpeed(-speed);
    }
    else if (SensorValue(btnBackL) == 1  && SensorValue(btnBackR) == 1) {
      killDrive();
    }
  }//
}//end function
*/

/*Left Drive msec*/
void drive_left_msec(int speed, int duration) {
  setDriveLSpeed(speed);
  wait1Msec(duration);
  killDrive();
}

/*Right Drive msec*/
void drive_right_msec(int speed, int duration) {
  setDriveRSpeed(speed);
  wait1Msec(duration);
  killDrive();
}

/*turn left*/
void turn_left_msec(int speed, int duration) {
  setDriveLSpeed(-speed);
  setDriveRSpeed(speed);
  wait1Msec(duration);
  killDrive();
}

/*turn right*/
void turn_right_msec(int speed, int duration) {
  setDriveLSpeed(speed);
  setDriveRSpeed(-speed);
  wait1Msec(duration);
  killDrive();
}

//////////////////////////////////*Lift*/////////////////////////////////
//-                                                                   -//
//-                                                                   -//

/*Set Lift Speed*/
void setLiftSpeed(int speed) {
  motor[liftL] = motor[liftR] = speed;
}

/*Set Lift L Speed*/
void setLiftLSpeed(int speed) {
  motor[liftL] = speed;
}

/*Set Lift R Speed*/
void setLiftRSpeed(int speed) {
  motor[liftR] = speed;
}

/*Kill lift*/
void killLift() {
  setLiftSpeed(0);
}

/*Lift msec*/
void lift_msec_raw(int speed, int duration) {
  setLiftSpeed(speed);
  wait1Msec(duration);
  killLift();
}

/*Lift High Goal-- one sensor*/
void lift_up(int speed) {
  if(SensorValue(btnLiftUpL) == 0) {
    setLiftSpeed(speed);
  }
  else {
    killLift();
  }
}

/*Auto Leveling Lift*/ //1 = up, -1 = down//
void lift_btn(int speed, int direction) {
  if (direction == 1) {//up
    if ((SensorValue(btnLiftUpL) == 0) && (SensorValue(btnLiftUpR) == 0)) {
      setLiftLSpeed(speed);
      setLiftRSpeed(speed);
    }
    else if ((SensorValue(btnLiftUpL) == 1) && (SensorValue(btnLiftUpR) == 0)) {
      setLiftLSpeed(0);
      setLiftRSpeed(speed);
    }
    else if ((SensorValue(btnLiftUpL) == 0) && (SensorValue(btnLiftUpR) == 1)) {
      setLiftLSpeed(speed);
      setLiftRSpeed(0);
    }
    else {
      killDrive();
    }
  }
  else if (direction == -1) {//down
    if ((SensorValue(btnLiftDownL) == 0) && (SensorValue(btnLiftDownR) == 0)) {
      setLiftLSpeed(-speed);
      setLiftRSpeed(-speed);
    }
    else if ((SensorValue(btnLiftDownL) == 1) && (SensorValue(btnLiftDownR) == 0)) {
      setLiftLSpeed(0);
      setLiftRSpeed(-speed);
    }
    else if ((SensorValue(btnLiftDownL) == 0) && (SensorValue(btnLiftDownR) == 1)) {
      setLiftLSpeed(-speed);
      setLiftRSpeed(0);
    }
    else if ((SensorValue(btnLiftDownL) == 1) && (SensorValue(btnLiftDownR) == 1)) {
      killLift();
    }

  }//
}//end function

/*Lift Down*/
void lift_down(int speed) {
  if(SensorValue(btnLiftDownL) == 0) {
    setLiftSpeed(-speed);
  }
  else {
    killLift();
  }
}

//////////////////////////////////*Suck*/////////////////////////////////
//-                                                                   -//
//-                                                                   -//

/*Set Suck Speed*/
void setSuckSpeed(int speed) {
  motor[suckL] = speed;
  motor[suckR] = speed;
}

/*Set Suck Speed*/
void setRotateSpeed(int speed) {
  motor[suckL] = speed;
  motor[suckR] = -speed;
}

/*Set Left Suck Speed*/
void setSuckLSpeed(int speed) {
  motor[suckL] = speed;
}

/*Set Right Suck Speed*/
void setSuckRSpeed(int speed) {
  motor[suckR] = speed;
}

/*Kill Suck*/
void killSuck() {
  setSuckSpeed(0);
}

/*suck msec*/
void suck_msec(int speed, int duration) {
  setSuckLSpeed(speed);
  setSuckRSpeed(speed);
  wait1Msec(duration);
  killSuck();
}

//-                                                                   -//
//-                                                                   -//
//END FUNCTION LIBRARY///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

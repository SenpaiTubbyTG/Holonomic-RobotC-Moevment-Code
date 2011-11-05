/////////////////////////////////////////////////////////////////////////
/*ZETA FUNCTION LIBRARY*/////////////////////////////////////////////////
//-
//-
/////////////////////////////////*Drive*/////////////////////////////////

/*Set Drive Left Speed*/
void setDriveLSpeed(int speed) {
  motor[leftF] = motor[leftUp] = motor[leftLow] = speed;
}

/*Set Drive Right Speed*/
void setDriveRSpeed(int speed) {
  motor[rightF] = motor[rightUp] = motor[rightLow] = speed;
}

/*Kill Drive*/
void killdrive() {
  setDriveLSpeed(0);
  setDriveRSpeed(0);
}

/*Drive msec*/
void drive_forward_msec(int speed, int duration) {
  setDriveLSpeed(speed);
  setDriveRSpeed(speed);
  wait1Msec(duration);
  killdrive();
}

/*Drive FWD buttons*/ //1 = forward, -1 = backwards//
void drive_btn(int speed, int direction) {
  if (direction == 1) {//forwards
    if (SensorValue(FrontL) == 0) {
      setDriveLSpeed(speed*direction);
    }
    else
    {
      killdrive();
    }
    if (SensorValue(FrontR) == 0) {
      setDriveRSpeed(speed*direction);
    }
    else
    {
      killdrive();
    }
  }
  else if (direction == -1) {//backwards
    if (SensorValue(BackL) == 0) {
      setDriveLSpeed(speed*direction);
    }
    else {
      killdrive();
    }
    if (SensorValue(BackR) == 0) {
      setDriveRSpeed(speed*direction);
    }
    else {
      killdrive();
    }
  }//
}//end function

/*Drive msec (Encoder)*/
void drive_l_msec(int speed, int duration) {

  if ((SensorValue(encL) == (SensorValue(EncR)) {
    setDriveLSpeed(speed);
    setDriveRSpeed(speed);
  }
  else if ((SensorValue(encL) > (SensorValue(encR)){
    setDriveLSpeed(speed);
    setDriveRSpeed(speed);
  }
  else if ((SensorValue(encL) < (SensorValue(encR)) {
    setDriveLSpeed(speed);
    setDriveRSpeed(speed);
  }
}


/*Left Drive msec*/
void drive_left_msec(int speed, int duration) {
  setDriveLSpeed(speed);
  wait1Msec(duration);
  killdrive();
}

/*Right Drive msec*/
void drive_right_msec(int speed, int duration) {
  setDriveRSpeed(speed);
  wait1Msec(duration);
  killdrive();
}

/*turn left*/
void turn_left_msec(int speed, int duration) {
  setDriveLSpeed(-speed);
  setDriveRSpeed(speed);
  wait1Msec(duration);
  killdrive();
}

/*turn right*/
void turn_right_msec(int speed, int duration) {
  setDriveLSpeed(speed);
  setDriveRSpeed(-speed);
  wait1Msec(duration);
  killdrive();
}

//////////////////////////////////*Lift*/////////////////////////////////
//-                                                                   -//
//-                                                                   -//

/*Set Lift Speed*/
void setLiftSpeed(int speed) {
  motor[liftL] = motor[liftR] = speed;
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

/*Lift High Goal*/
void lift_up(int speed) {
  if(SensorValue(liftUpSensor == 0)) {
    setLiftSpeed(speed);
  }
  else
  {
    killLift();
  }
}

/*Lift Down*/
void lift_down(int speed) {
  if(SensorValue(liftDownSensor == 0)) {
    setLiftSpeed(-speed);
  }
  else{
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
/*END FUNCTION LIBRARY*/////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

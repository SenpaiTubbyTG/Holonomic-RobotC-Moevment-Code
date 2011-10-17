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

/*Right Drive msec*/
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
void lift_msec(int speed, int duration) {
setLiftSpeed(speed);
wait1Msec(duration);
killLift();
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

//TELE OP

//SUCK

//Dual mirrored remotes; 6u = up, 6d = down, 8l = rotate left, 8r = rotate right
void suck() {
  if ((vexRT[Btn6U] == 1) || (vexRT[Btn6UXmtr2] == 1)) {
    setSuckSpeed(FULL);
  }
  else if ((vexRT[Btn6D] == 1) || (vexRT[Btn6DXmtr2] == 1)) {
    setSuckSpeed(-FULL);
  }
  else if ((vexRT[Btn8L] == 1) || (vexRT[Btn8LXmtr2] == 1)) {
    setSuckLSpeed(-FULL);
    setSuckRSpeed(FULL);
  }
  else if ((vexRT[Btn8R] == 1) || (vexRT[Btn8RXmtr2] == 1)) {
    setSuckLSpeed(FULL);
    setSuckRSpeed(-FULL);
  }
  else {
    killSuck();
  }
}

//LIFT

/*void lift() {
  setLiftSpeed(((vexRT[Btn5U] == 1) || (vexRT[Btn5DXmtr2] == 1 ))*FULL);
}*/

//Dual mirrored remotes; 5u = up, 6d = down, 7u/7l = left up/up, 7r/7d = right up/down
void lift() {
  if ((vexRT[Btn5U] == 1) || (vexRT[Btn5UXmtr2] == 1)) {
    setLiftSpeed(FULL);
  }
  else if ((vexRT[Btn5D] == 1) || (vexRT[Btn5DXmtr2] == 1)) {
    setLiftSpeed(-FULL);
  }
  else if ((vexRT[Btn7U] == 1) || (vexRT[Btn7UXmtr2] == 1)) {
    setLiftLSpeed(FULL);
  }
  else if ((vexRT[Btn7L] == 1) || (vexRT[Btn7LXmtr2] == 1)) {
    setLiftLSpeed(-FULL);
  }
  else if ((vexRT[Btn7R] == 1) || (vexRT[Btn7RXmtr2] == 1)) {
    setLiftRSpeed(FULL);
  }
  else if ((vexRT[Btn7D] == 1) || (vexRT[Btn7DXmtr2] == 1)) {
    setLiftRSpeed(-FULL);
  }
  else {
    killLift();
  }
}

//TANK
//Dual mirrored remotes
void tankDrive() {
  setDriveLSpeed(vexRT[Ch3] || vexRT[Ch3Xmtr2]);
  setDriveRSpeed(vexRT[Ch2] || vexRT[Ch2Xmtr2]);
}

//ARCADE
//Arcade functions: Enable this when enabling arcade
int joy_x;            // will hold the X value of the analog stick (choices below)
int joy_y;            // will hold the Y value of the analog stick (choices below)
int threshold = 10;   // helps to eliminate 'noise' from a joystick that isn't perfectly at (0,0)

void arcadeDrive() {
  joy_x = vexRT[Ch1];   // This is the RIGHT analog stick.  For LEFT, change 'Ch1' to 'Ch4'.
  joy_y = vexRT[Ch2];   // This is the RIGHT analog stick.  For LEFT, change 'Ch2' to 'Ch3'.

  // Forward, and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is POSITIVE)
  if((abs(joy_x) > threshold) && (abs(joy_y) > threshold) && (joy_y > 0))
  {
    //motor[leftBack] = motor[leftMiddle]= motor[leftFront] = (joy_y + joy_x)/2;
    setDriveLSpeed((joy_y + joy_x)/2);

    //motor[rightBack] = motor[rightMiddle] = motor[rightFront] = (joy_y - joy_x)/2;
    setDriveRSpeed((joy_y - joy_x)/2);
  }
  // Backwards and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is NEGATIVE)
  else if((abs(joy_x) > threshold) && (abs(joy_y) > threshold) && (joy_y < 0)) {
    //motor[leftBack] = motor[leftMiddle]= motor[leftFront] = (joy_y - joy_x)/2;
    setDriveLSpeed((joy_y - joy_x)/2);
    //motor[rightBack] = motor[rightMiddle] = motor[rightFront] = (joy_y + joy_x)/2;
    setDriveRSpeed((joy_y + joy_x)/2);
  }
  // Turning in place: (abs(X) is above the threshold, abs(Y) is below the threshold)
  else if((abs(joy_x) > threshold) && (abs(joy_y) < threshold)) {
    //motor[leftBack] = motor[leftMiddle]= motor[leftFront] = joy_x;
    setDriveLSpeed(joy_x);
    //motor[rightBack] = motor[rightMiddle] = motor[rightFront] = (-1 * joy_x);
    setDriveRSpeed(-1* joy_x);
  }
  // Standing still: (both abs(X) and abs(Y) are below the threshold)
  else {
    killDrive();
  }
}

////////////////////////Auto Controls////////////////////////////


//auto raise suck
void autoRaiseSuck() {
  if ((vexRT[Btn8U]) == 1 || (vexRT[Btn8UXmtr2] == 1)) {
    if (SensorValue[detectBall] < 200) {
      setSuckSpeed(FULL);
    }
    else {
      killSuck();
    }
  }
}
//auto raise lift
  void autoRaiseLift() {
    if ((vexRT[Btn7U]) == 1) {
      lift_btn(FULL, 1);
    }
  }

  //auto lower lift
  void autoLowerLift() {
    if ((vexRT[Btn7D]) == 1 || (vexRT[Btn7DXmtr2] == 1)) {
      lift_btn(FULL, -1);
    }
  }

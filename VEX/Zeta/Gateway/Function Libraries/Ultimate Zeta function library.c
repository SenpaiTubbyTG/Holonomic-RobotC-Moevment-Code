void setDriveLSpeed(int speed) {
  motor[backLTop] = motor[backLBottom] = motor[frontL] = motor[frontLTop] = speed;
}

/*Set Drive Right Speed*/
void setDriveRSpeed(int speed) {
  motor[backRTop] = motor[backRBottom] = motor[frontR] = motor[frontRTop] = speed;
}

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

/*Kill Suck Motors*/
void killsuck() {
  setSuckSpeed(0);
}

/*Kill Drive Train Motors*/
void killdrive() {
  setDriveLSpeed(0);
  setDriveRSpeed(0);
}

/*AUTON FUNCTIONS*////////////////////////////////
void drive_forward_msec(int speed, int duration) {
  setDriveLSpeed(speed);
  setDriveRSpeed(speed);
  wait1Msec(duration);
  killdrive();
}

/*AUTON FUNCTIONS*////////////////////////////////
void drive_left_msec(int speed, int duration) {
  setDriveLSpeed(speed);
  wait1Msec(duration);
  killdrive();
}

/*AUTON FUNCTIONS*////////////////////////////////
void drive_right_msec(int speed, int duration) {
  setDriveRSpeed(speed);
  wait1Msec(duration);
  killdrive();
}

/*AUTON FUNCTIONS*////////////////////////////////
void turn_right_msec(int speed, int duration) {
setDriveLSpeed(speed);
setDriveRSpeed(-speed);
  wait1Msec(duration);
  killdrive();
}

/*AUTON FUNCTIONS*////////////////////////////////
void turn_left_msec(int speed, int duration) {
setDriveLSpeed(-speed);
setDriveRSpeed(speed);
  wait1Msec(duration);
  killdrive();
}

void suck_msec(int speed, int duration) {
setSuckLSpeed(speed);
setSuckRSpeed(speed);
wait1Msec(duration);
killsuck();
}

void setDriveLSpeed(int speed) {
  motor[leftFront] = motor[leftUp] = motor[leftLow] = speed;
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
void drive_msec(int speed, int duration) {
  setDriveLSpeed(speed);
  setDriveRSpeed(speed);
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
void drive_to_tower(int speed, int direction) {
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

/////nnnneeeeeddd improvment//////////
/*Drive FWD buttons*/ //1 = forward, -1 = backwards//
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

void setDriveLSpeed(int speed) {
  motor[leftFront] = motor[leftUp] = motor[leftLow] = speed;
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


void stop_all() {
  motor[port1] = 0;
  motor[port2] = 0;
  motor[port3] = 0;
  motor[port4] = 0;
  motor[port5] = 0;
  motor[port6] = 0;
  motor[port7] = 0;
  motor[port8] = 0;
  motor[port9] = 0;
  motor[port10] = 0;
}

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
    motor[port5] = 127 * direction; //sets motors
    motor[port6] = 127 * direction;
    return 0;
  }
  else {  //in hindsight, I don't think this is necessary
    motor[port5] = -10; //no need to move for lock; will continue holding
    motor[port6] = -10;
    return 1;
  }
}

int sucker(int speed) { //positive numbers for out
  motor[port4] = -speed;
  motor[port7] = speed;
  wait1Msec(1000);
  motor[port4] = 0;
  motor[port7] = 0;
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
  motor[DriveR] = speed;
  motor[DriveL] = speed;
  wait1Msec(duration);
  motor[DriveR] = 0;
  motor[DriveL] = 0;
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
      motor[DriveR] = -speed;
      motor[DriveL]  = -speed + 1;
    }
    else if(abs(SensorValue[EncoderL]) < abs(SensorValue[EncoderR])) {
      motor[DriveR] = -speed + 1;
      motor[DriveL]  = -speed;
    }
    else {
      motor[DriveR] = -speed;
      motor[DriveL]  = -speed;
    }
  }
  motor[DriveR] = 0;
  motor[DriveL] = 0;
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

      motor[DriveR] = -speed;
      motor[DriveL] = -speed + 1;
    }
    else if(abs(SensorValue[EncoderL]) < abs(SensorValue[EncoderR])) {

      motor[DriveR] = -speed + 1;
      motor[DriveL]  = -speed;
    }
    else {
      motor[DriveR] = -speed;
      motor[DriveL]  = -speed;
    }
    return 0;
  }
  else
    return 1;
}

/* drive_to_touch
  * @purpose: autonomously drive robot forward until touch sensors are triggered
  * precondition: 2 touch sensors, left and right
  * @param speed: speed of motors, -127 to 127; negative values go reverse
 */
int drive_to_touch(int speed) {
  while((SensorValue[TouchLeft] == 0 || SensorValue[TouchRight] == 0)) {
    if(SensorValue[TouchLeft] == 0)
      motor[DriveL] = -speed;
    else
      motor[DriveL] = 0;
    if(SensorValue[TouchRight] == 0)
      motor[DriveR] = -speed;
    else
      motor[DriveR] = 0;
  }
  return (SensorValue[TouchLeft] == 1 && SensorValue[TouchRight] == 1);
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
  while(SensorValue[EncoderL] > -degrees || SensorValue[EncoderR] < degrees) {
    motor[DriveL] = speed;
    motor[DriveR] = -speed;
  }
  motor[DriveL] = 0;
  motor[DriveR] = 0;
}

void arm_vertical() {
  while(SensorValue[Arm_limit] == 0) {
    motor[port5] = -127;
    motor[port6] = -127;
  }
  motor[port5] = 0;
  motor[port6] = 0;
  while(SensorValue[Extend_limit] != 1) {
    motor[port8] = 127;
    motor[port9] = 127;
  }
  motor[port8] = 0;
  motor[port9] = 0;
  stop_all();
}

void pull_up() {
  while(SensorValue[Retract_limit] != 0) {
    motor[port8] = -127;
    motor[port9] = -127;
  }
  motor[port8] = 0;
  motor[port9] = 0;
  while(SensorValue[Arm_closed] == 0) {
    motor[port5] = 127;
    motor[port6] = 127;
  }
  motor[port5] = 0;
  motor[port6] = 0;
  stop_all();
}

/* MODE SELECTION FUNCTION
 * mode_select
 * @purpose use a potentiometer to set mode
 * high potentiometer values return 1, low potentiometer values return 0
 */

/*int mode_select() {
  if(SensorValue[Mode] >= 2000)
    return 1;
  else
    return 0;

}*/


/* LINE FOLLOWER FUNCTIONS
 * follow_line_msec
 * follow_line_distance
 */

 /*follow_line_msec
 * @purpose follow a line for provided duration using 3 light sensors
 * @param speed: speed of motors, 0 to 127
 * @param duration: duration of line following in milliseconds
 */
/*void follow_line_msec(int speed, int duration) {
  ClearTimer(T1);
  int threshold = 250;  //guessed threshold; low numbers are lighter
  while(time1[T1] < duration) {
    if(SensorValue[MidLine] < threshold) {  //middle sensor is on line
     motor[DriveL]  = speed;
     motor[DriveR] = speed;
    }
    else if(SensorValue[LeftLine] < threshold) {  //left sensor is on line
      motor[DriveL]  = speed - 1;
      motor[DriveR] = speed;
    }
    else if(SensorValue[RightLine] < threshold) { //right sensor is on line
      motor[DriveL]  = speed;
      motor[DriveR] = speed - 1;
    }
  }
}*/


 /*follow_line_distance
 * @purpose follow a line for provided duration using 3 light sensors
 * precondition: 4-inch wheels
 * @param speed: speed of motors, 0 to 127
 * @param distance: distance to travel in inches
 */
/*void follow_line_distance(int speed, float distance) {
  int threshold = 250;  //guessed threshold; low numbers are lighter
  while(((float)SensorValue[EncoderL]+(float)SensorValue[EncoderR])/2 * 4 / 360 * PI
                                                                      < distance){
    if(SensorValue[MidLine] < threshold) {  //middle sensor is on line
     motor[DriveL]  = speed;
     motor[DriveR] = speed;
    }
    else if(SensorValue[LeftLine] < threshold) {  //left sensor is on line
      motor[DriveL]  = speed - 1;
      motor[DriveR] = speed;
    }
    else if(SensorValue[RightLine] < threshold) { //right sensor is on line
      motor[DriveL]  = speed;
      motor[DriveR] = speed - 1;
    }
  }
}*/

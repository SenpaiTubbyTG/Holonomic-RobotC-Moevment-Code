void clearEncoder()
{
  nMotorEncoder(right3) = 0;
  nMotorEncoder(left3) = 0;
}

void drivetime(int speed, int time)
{
  ClearTimer(T4);
  while(time1[T4]<time*1000){
  motor[left1] = motor[left2] = motor[left3] = speed;
  motor[right1] = motor[right2] = motor[right3] = speed;
  }
 motor[left1] = motor[left2] = motor[left3] = 0;
  motor[right1] = motor[right2] = motor[right3] = 0;
}
void drive_Enc(int speed, float distance,int time)
{
  clearEncoder();
  ClearTimer(T4);
  //wait10Msec(23)
  while( ( ((float) nMotorEncoder(right3)  * 2.75 / 360 * PI)*3 < distance &&
    ( (float) abs(nMotorEncoder[left3])* 2.75 / 360 * PI)*3 < distance)&& time1[T4] < time*1000)  {

    if(nMotorEncoder[left3] > nMotorEncoder[left3]) {
      motor[left1] = speed -1;
      motor[left2]  = speed-1;
      motor[left3] = speed -1;
      motor[right1] = speed;
      motor[right2] = speed;
      motor[right3] = speed;
    }
    else if(nMotorEncoder[left3] < nMotorEncoder[right3]) {
      motor[left1] = speed;
      motor[left2]  = speed;
      motor[left3] = speed;
      motor[right1] = speed-1;
      motor[right2] = speed-1;
      motor[right3] = speed-1;
    }
    else {
      motor[left1] = speed;
      motor[left2]  = speed;
      motor[left3] = speed;
      motor[right1] = speed;
      motor[right2] = speed;
      motor[right3] = speed;
    }
  }//while
  stopdrivemotors();
}

void turnEnc(int speed, int ticks, int  direction, int time)
{
  clearEncoder();
  ClearTimer(T4);
  switch(direction){
  case right:
    while(abs(nMotorEncoder[left3]) < ticks)
    {
      motor[right1] = speed;
      motor[right2] = speed;
      motor[right3] = speed;
      motor[left1] = -speed;
      motor[left2] = -speed;
      motor[left3] = -speed;
    }
    case left:
    while(abs(nMotorEncoder[right3]) < ticks)
    {
      motor[right1] = -speed;
      motor[right2] = -speed;
      motor[right3] = -speed;
      motor[left1] = speed;
      motor[left2] = speed;
      motor[left3] = speed;
    }
  }//switch
}//void

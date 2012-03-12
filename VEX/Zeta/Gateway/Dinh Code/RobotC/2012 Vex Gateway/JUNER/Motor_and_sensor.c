

//---------------------------------------------------------------------------------
void stopdrivemotors()
{
  motor[right1] = 0;
  motor[right2] = 0;
  motor[right3] = 0;
  motor[left1] = 0;
  motor[left2] = 0;
  motor[left3] = 0;

}

void stoparmmotors()
{
  motor[rightLift] = 0;
  motor[leftLift = 0;
}

void drive_straight(int speed, float distance) {
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;
  while( ( (float) SensorValue[EncoderL]  * 4 / 360 * PI) < distance &&
         ( (float) SensorValue[EncoderR] * 4 / 360 * PI) < distance) {
    if(SensorValue[EncoderL] > SensorValue[EncoderR]) {
      motor[left1] = speed -1;
      motor[left2]  = speed-1;
      motor[left3] = speed -1;
      motor[right1] = speed;
      motor[right2] = speed;
      motor[right3] = speed;
    }
    else if(SensorValue[EncoderL] < SensorValue[EncoderR]) {
      motor[left1] = speed ;
      motor[left2]  = speed;
      motor[left3] = speed;
      motor[right1] = speed -1;
      motor[right2] = speed -1;
      motor[right3] = speed -1;
    }
    else {
      motor[left1] = speed;
      motor[left2]  = speed;
      motor[left3] = speed;
      motor[right1] = speed;
      motor[right2] = speed;
      motor[right3] = speed;
    }
  }
 allMotorsOff();
}

void clearencoder()
{

  SensorValue[EncoderLeft] = 0;
  SensorValue[EncoderRight] = 0;

}


//---7-------------------------------------------------------------------------------- jamming stuff

void RAMPAGE_TURN(bool right)
{
  if (right == true)
  {
  motor[port2] = 127;
  motor[port3] = 127;
  motor[port4] = -127;
  motor[port5] = -127;
  }
  else if (right == false)
  {
  motor[port2] = -127;
  motor[port3] = -127;
  motor[port4] = 127;
  motor[port5] = 127;
  }
  else
  stopdrivemotors();
}


}
//--------------=---------------------------end of jamming stugg---------=---------------------------------=-----------------------
/////////////////////////////////////drive stuff//////////////////////////////////
void TurnGyro(int speed, float degrees, float time)// speed and ticks and time
{
  ClearTimer(T4);
  clearencoder();
  while(Sensorvalue[Gyro] <= degrees*10 || time1[T4] < time *1000)// positive values go right. negative values go left
  {

    motor[DriveLeft] = -speed;//turn is defaulted to the left
    motor[DriveLeft2] = -speed;
    motor[DriveRight] = speed;
    motor[DriveRight2] = speed;
  }
  stopdrivemotors();
}




void Rampage(int speed)//move straight until you tell it to stop...
{
  clearencoder();
  if(SensorValue[EncoderLeft] > SensorValue[EncoderRight]) {
    motor[DriveLeft] = speed-1;
    motor[DriveLeft2] = speed -1;
    motor[DriveRight] = speed;
    motor[DriveRight2] = speed;
  }
  else if(SensorValue[EncoderLeft] < SensorValue[EncoderRight]) {
    motor[DriveLeft] = speed;
    motor[DriveLeft2] = speed;
    motor[DriveRight] = speed-1;
    motor[DriveRight2] = speed-1;
  }
  else {
    motor[DriveLeft] = speed;
    motor[DriveLeft2] = speed;
    motor[DriveRight] = speed;
    motor[DriveRight2] = speed;
  }
}




}
//---------------------------------end of drive stuff-------------------------------------------------
/////////////////////////////arm stuff..//////////////////////////////////////////////////////////////
  int lock(int final_pos) //locks arm to final_pos potentiometer point
{
  int current_pos = SensorValue(ArmPOT); //reads potentiometer
  int direction;                      //up or down?
  int arm_diff = abs(current_pos - final_pos);//difference between current and desired points

  if(arm_diff > 90) {  //potentiometer is very precise, so
      if (current_pos > final_pos) {//arm too high
        direction = 1;    //will move down
    }
    else if(current_pos < final_pos) { //arm too low
        direction = -1; //will move up
    }
    motor[port6] = 127 * direction; //sets motors
    motor[port7] = 127 * direction;
    motor[port8] = 127 * direction;
    motor[port9] = 127* direction;
    return 0;
  }
  else {  //in hindsight, I don't think this is necessary
      motor[port6] = 0;//no need to move for lock; will continue holding. put it back to -10 if it does not work
    motor[port7] = 0;
    motor[port8] = 0;
    motor[port9] = 0;
    return 1;
  }



}


void armdirection(short direction, int speed)
{
  switch (direction){
  case down://make the arm go down
  motor[lift1] = -speed;
  motor[lift2] = -speed;//speed of the arm
  motor[lift3] = -speed;
  motor[lift4] = -speed;
  case up://make the arm go up...
  motor[lift1] = speed;
  motor[lift2] = speed;
  motor[lift3] = speed;
  motor[lift4] = speed;
  }//case

}



void liftdown(float time)
{
  ClearTimer(T1);
  while(armenc > 90 || time1[T1] < time *1000)
  {
    armdirection(down, 127);
  }
  stoparmmotors();
}


void lift(int arm, float time)//which height for the arm???
{
  ClearTimer(T4);
  {
    switch(arm){

    case lowgoal:
    while(current_pos < mediumgoal || time1[T4] < time *1000 )
     {
      lock(ten_inch_goal);

        stoparmmotors();
      }
      break;

    case mediumgoal:
    while(current_pos < mediumgoal || time1[T4] < time *1000)
    {
      lock(twenty_inch_goal);
      stoparmmotors();
      }
      break;

    case highgoal:
      while(current_pos < thirty_inch_goal || time1[T4] < time *1000)
      {
      lock(thirty_inch_goal);
     }
      break;

    case gravitating:
    if (touchlow != 1)
    {
     armdirection(down, 127);
    }

    }//case
  }//while
stoparmmotors();
}// encd of func.

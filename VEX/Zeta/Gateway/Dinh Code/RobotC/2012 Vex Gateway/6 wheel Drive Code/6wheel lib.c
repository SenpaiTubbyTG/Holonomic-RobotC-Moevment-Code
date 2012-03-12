const bool Rightside = true;
const bool Leftside = false;
const bool Left = true;
const bool Right = false;
const bool Foward = true;
const bool Backward = false;
int distanceFromWall;

int getSonarLeft()
{
  return SensorValue[Lefteye];
}

int distance()
{
  return (abs(SensorValue[encL]) + abs(SensorValue[encR]))/2;
}

int getSonarRight()
{
  return SensorValue[Righteye];
}

void off()
{
  motor[port1] = 0;
  motor[Right1] = 0;
  motor[Right2] = 0;
  motor[Right3] = 0;
  motor[Left1] = 0;
  motor[Left2] = 0;
  motor[Left3] = 0;
  motor[port8] = 0;
  motor[port9] = 0;
  motor[port10] = 0;

}

void stopdrive()
{
  motor[Right1] = 0;
  motor[Right2] = 0;
  motor[Right3] = 0;
  motor[Left1] = 0;
  motor[Left2] = 0;
  motor[Left3] = 0;

}

void timedOff(int time)
{

  motor[port1] = 0;
  motor[Right1] = 0;
  motor[Right2] = 0;
  motor[Right3] = 0;
  motor[Left1] = 0;
  motor[Left2] = 0;
  motor[Left3] = 0;
  motor[port8] = 0;
  motor[port9] = 0;
  motor[port10] = 0;
  wait1Msec(time);
}



void clearenc()
{
  SensorValue[encL] = 0;
  SensorValue[encR] = 0;
}





void rampage(char power)
{
  if(SensorValue[encL] > SensorValue[encR])
  {
    motor[Right1] = power;
    motor[Right2] = power;
    motor[Right3] = power;
    motor[Left1] = power-1;
    motor[Left2] = power-1;
    motor[Left3] = power-1;

  }
  else if(SensorValue[encR]> SensorValue[encL])
  {
    motor[Right1] = power-1;
    motor[Right2] = power-1;
    motor[Right3] = power-1;
    motor[Left1] = power;
    motor[Left2] = power;
    motor[Left3] = power;
  }
  else
  {
    motor[Right1] = power;
    motor[Right2] = power;
    motor[Right3] = power;
    motor[Left1] = power;
    motor[Left2] = power;
    motor[Left3] = power;

  }


}

//////////////////////////////encoder///////////////////////////////////////
void Drive(bool direction, int ticks, char power)
{
  switch(direction){
  case Foward:
    clearenc();
    while(distance() < ticks)
    {
      if (SensorValue[encL] > SensorValue[encR])
      {
        motor[Right1] = power;
        motor[Right2] = power;
        motor[Right3] = power;
        motor[Left1] = power-1;
        motor[Left2] = power-1;
        motor[Left3] = power-1;
      }
      else if(SensorValue[encR] > SensorValue[encL])
      {
        motor[Right1] = power-1;
        motor[Right2] = power-1;
        motor[Right3] = power-1;
        motor[Left1] = power;
        motor[Left2] = power;
        motor[Left3] = power;
      }
      else
        motor[Right1] = power;
      motor[Right2] = power;
      motor[Right3] = power;
      motor[Left1] = power;
      motor[Left2] = power;
      motor[Left3] = power;
    }//while
    off();
    break;
    ///////////////backwards////////////////////////////////////////
  case Backward:
    clearenc();
    while(distance() < ticks)
    {
      if (SensorValue[encL] > SensorValue[encR])//if the left side is faster than the rightside...
      {
        motor[Right1] = -power+1;
        motor[Right2] = -power+1;
        motor[Right3] = -power+1;
        motor[Left1] = -power;
        motor[Left2] = -power;
        motor[Left3] = -power;
      }
      else if(SensorValue[encR] > SensorValue[encL])//if the right side is is faster than the right side...
      {
        motor[Right1] = -power;
        motor[Right2] = -power;
        motor[Right3] = -power;
        motor[Left1] = -power+1;
        motor[Left2] = -power+1;
        motor[Left3] = -power+1;
      }
      else
        motor[Right1] = -power;
      motor[Right2] = -power;
      motor[Right3] = -power;
      motor[Left1] = -power;
      motor[Left2] = -power;
      motor[Left3] = -power;
    }//while
    off();
    break;

  }//switch
  off();
  allMotorsOff();
}
void turn(bool direction,int ticks, int power)
{
  clearenc();
  ClearTimer(T4);
  switch(direction){
  case Right:
    clearenc();
    while(distance() <= ticks)
    {
      motor[Right1] = -power;
      motor[Right2] = -power;
      motor[Right3] = -power;
      motor[Left1] = power;
      motor[Left2] = power;
      motor[Left3] = power;


    }
    off();
    break;
  case Left:
    clearenc();
    while(distance() <= ticks ){
      motor[Right1] = power;
      motor[Right2] = power;
      motor[Right3] = power;
      motor[Left1] = -power;
      motor[Left2] = -power;
      motor[Left3] = -power;

    }//while
    off();
    break;

  }//switch
  off();
  allMotorsOff();

}

/////////////////////////////////motors///////////////////////////////////////
void veer(bool direction,char power)
{

  switch (direction){
  case Left:
    motor[Right1] = power;
    motor[Right2] = power;
    motor[Right3] = power;
    motor[Left1] = power-50;
    motor[Left2] = power-50;
    motor[Left3] = power-50;
    break;
  case Right:
    motor[Right1] = power-50;
    motor[Right2] = power-50;
    motor[Right3] = power-50;
    motor[Left1] = power;
    motor[Left2] = power;
    motor[Left3] = power;
    break;

  }


}//Case

////////////////////////////////sonars////////////////////////////////////////////////////
void Sonarstraight(short ticks,bool right)

{
  clearenc();
  ClearTimer(T4);
  switch(right){
  case Rightside:
    getSonarRight();
    distanceFromWall = getSonarLeft();
    while(SensorValue[encL] < ticks && SensorValue[encR] < ticks)
    {
      if(SensorValue[Righteye] > 10)//if the robot is more than 10 inches away from the wall...
        veer(Right,70);
      else if(SensorValue[Righteye] < distanceFromWall)
        veer(Left,70);
      else if (SensorValue[Righteye] > distanceFromWall && SensorValue[Righteye] < 10)
        rampage(70);
    }
    off();
    break;



  case Leftside:
    getSonarLeft();
    distanceFromWall = getSonarLeft();
    while(SensorValue[encL] < ticks && SensorValue[encR] < ticks)//SensorValue[encL] < ticks && SensorValue[encR] < ticks
    {
      if(SensorValue[Lefteye] > distanceFromWall + 7)// if you are to far from the wall veer in
        veer(Left,70);
      else if(SensorValue[Lefteye] < distanceFromWall)// if you are too close veer out.
        veer(Right,70);
      else if (SensorValue[Lefteye] > distanceFromWall && SensorValue[Lefteye] < distanceFromWall+7)// if you are neither close nor too far, go fowards with the encoders...
        rampage(70);
      else if(SensorValue[Lefteye] > 20) //in case your to far from the wall stop the robot...
        timedOff(25*1000);
    }
    off();
    break;
  }//end of func.
  allMotorsOff();
}




void foward_until_light(short time)
{
  while(SensorValue[M2] >200 || time1[T4] <= time)
  {
    rampage(127);
  }
  stopdrive();
}

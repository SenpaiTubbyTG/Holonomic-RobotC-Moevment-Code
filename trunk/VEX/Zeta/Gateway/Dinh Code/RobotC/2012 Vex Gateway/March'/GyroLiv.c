


void stopdrivemotors()
{
  motor[left1] = motor[left2] = motor[left3] = 0;
  motor[right1] = motor[right2] = motor[right3] = 0;
}

void ClearGyro()
{
  SensorType[in8] = sensorNone;
  wait1Msec(1000);
  SensorType[in8] = sensorGyro;
  wait1Msec(2000);
}
void mediumTurn(int direction)
{
  switch (direction){
  case left:
    motor[left1] = motor[left2] = motor[left3] = -20;
      motor[right1] = motor[right2] = motor[right3] = 20;
    break;
  case right:
     motor[left1] = motor[left2] = motor[left3] = 20;
      motor[right1] = motor[right2] = motor[right3] = 20;
  }

}

void holdPositionforever(int position)
{
  ClearTimer(T4);
  ClearGyro();
  while(1==1)
  {

    if (SensorValue[Gyro] <position*10 -60)
    {
      motor[left1] = motor[left2] = motor[left3] = -63;
      motor[right1] = motor[right2] = motor[right3] = 63;
    }
    else if (SensorValue[Gyro] >position*10 + 60)
    {
       motor[left1] = motor[left2] = motor[left3] = 63;
          motor[right1] = motor[right2] = motor[right3] =-63;//fourth power
    }
    else if (SensorValue[Gyro] < position*10 -30)
    {
      mediumTurn(left);
    }
    else if(SensorValue[Gyro] > position*10+ 30)
    {
      mediumTurn(right);//second power
    }
    else if (SensorValue[Gyro] <position*10 -15)
    {
      motor[left1] = motor[left2] = motor[left3] = -10;//third power
       motor[right1] = motor[right2] = motor[right3] =10;

    }
    else if(SensorValue[Gyro] >position*10+ 15)
    {
          motor[left1] = motor[left2] = motor[left3] = 10;
          motor[right1] = motor[right2] = motor[right3] =-10;

    }

    else
    stopdrivemotors();
  }//while


}//function

/*
 We need to test this function and tweak the motor values...
*/
void Gyro_turn2(int degrees, int direction, int speed)
{
  ClearGyro();
  switch (direction)
  {
  case right:
    {

      while(abs(SensorValue[Gyro]) < degrees*10 -10)
      {
         motor[left1] = motor[left2] = motor[left3] = speed;
          motor[right1] = motor[right2] = motor[right3] =-speed;
      }
     stopdrivemotors();
     }

    break;
  case left:
    {
           while(abs(SensorValue[Gyro]) > degrees*10 +10)
      {
          motor[left1] = motor[left2] = motor[left3] = -speed;
          motor[right1] = motor[right2] = motor[right3] =speed;
      }
           stopdrivemotors();
           }
}//switch
}

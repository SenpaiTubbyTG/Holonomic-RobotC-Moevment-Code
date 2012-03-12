void stoparmmotors()
{
  motor[leftLift] = motor[rightLift] = 0;
}
void lift(int arm)
{
  switch(arm){
  case medgoal:
    while(SensorValue[POT]<twenty_inch_goal)
    {
      motor[rightLift] = 127;
      motor[leftLift] = 127;
    }
    {
      motor[rightLift] = 15;
      motor[leftLift] = 15;
    }
    break;
  case lowgoal:
    while(SensorValue[POT]<ten_inch_goal)
    {
      motor[rightLift] = 127;
      motor[leftLift] = 127;
    }
    {
      motor[rightLift] = 15;
      motor[leftLift] = 15;
    }
    break;
  case highgoal:
    while(SensorValue[POT]<thirty_inch_goal)
    {
      motor[rightLift] = 127;
      motor[leftLift] = 127;
    }
    {
      motor[rightLift] = 15;
      motor[leftLift] = 15;
    }
    break;
  case gravityNot:
    {
      ClearTimer(T4);
      while(SensorValue[touchl] != 1 && time1[T4] < 2000)
      {
        {
          motor[rightLift] = -127;
          motor[leftLift] = -127;
        }

        stoparmmotors();

      }
    }
  }//switch
}


/////////////////////////////arm stuff..//////////////////////////////////////////////////////////////
int lock(int final_pos) //locks arm to final_pos potentiometer point
{
  int current_pos = SensorValue(POT); //reads potentiometer
  float direction;                      //up or down?
  int arm_diff = abs(current_pos - final_pos);//difference between current and desired points

  if(arm_diff > 80) {  //potentiometer is very precise, so
    if (current_pos > final_pos) {//arm too high
      direction = -0.5;    //will move down
    }
    else if(current_pos < final_pos) { //arm too low
      direction = 1; //will move up
    }
    motor[leftLift] = 127 * direction; //sets motors
    motor[rightLift] = 127 * direction;

    return 0;
  }
  else {  //in hindsight, I don't think this is necessary
    motor[leftLift] = 15;
    motor[rightLift] = 15;
    return 1;
  }



}

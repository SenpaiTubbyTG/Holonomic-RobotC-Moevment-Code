////////////////stoping motors//////////////////////////////

void Off()
{
  motor[rightBack] = 0;
  motor[rightBig] = 0;
  motor[rightFront] = 0;
  motor[leftBig] = 0;
  motor[leftFront] = 0;
  motor[leftBack] = 0;
  motor[rightLift] = 0;
  motor[leftLift] = 0;
  motor[Collectors1] = 0;
  motor[Collectors2] = 0;
}

void stopCollectors()
{
  motor[Collectors1] = 0;
  motor[Collectors2] = 0;
}

//---------------------------------------------------------------------------------
void stopdrivemotors()
{
  motor[rightBack] = 0;
  motor[rightBig] = 0;
  motor[rightFront] = 0;
  motor[leftBig] = 0;
  motor[leftFront] = 0;
  motor[leftBack] = 0;

}

////////////////end of stoping motors//////////////////////////////

///////////////////////////////////////////////



void stoparmmotors()
{
  motor[rightLift] = 0;
  motor[leftLift] = 0;
}


void clearencoder()
{

  SensorValue[EncoderLeft] = 0;
  SensorValue[EncoderRight] = 0;

}

void waitForBump()
{
  while(true)
  {
    if(SensorValue[bumper] != 0)
    {
      wait1Msec(5);
    }

    else
      Off();
  }
}
void resetGyro()
{
  SensorValue[Gyro] = sensorNone;
  wait1Msec(500);//HOPE THIS WORKS
  SensorValue[Gyro] = sensorGyro;
  wait1Msec(500);
}

void stopTime(float time)
{
  wait1Msec(time*1000);
}
//--------------=---------------------------end of jamming stugg---------=---------------------------------=-----------------------
/////////////////////////////////////drive stuff//////////////////////////////////

void drive_Enc(int speed, float distance,int time)
{
  SensorValue[EncoderLeft] = 0;
  SensorValue[EncoderRight] = 0;
  ClearTimer(T4);
  //wait10Msec(23)
  while( ( ((float) abs(SensorValue[EncoderLeft])  * 4 / 360 * PI) < distance &&
    ( (float) abs(SensorValue[EncoderRight]) * 4 / 360 * PI) < distance) && time1[T4] < time*1000) {

    if(SensorValue[EncoderLeft] > SensorValue[EncoderRight]) {
      motor[leftBig] = speed -1;
      motor[leftFront]  = speed-1;
      motor[leftBack] = speed -1;
      motor[rightBack] = speed;
      motor[rightBig] = speed;
      motor[rightFront] = speed;
    }
    else if(SensorValue[EncoderLeft] < SensorValue[EncoderRight]) {
      motor[leftBack] = speed ;
      motor[leftBig]  = speed;
      motor[leftFront] = speed;
      motor[rightBack] = speed -1;
      motor[rightBig] = speed -1;
      motor[rightFront] = speed -1;
    }
    else {
      motor[leftBig] = speed;
      motor[leftFront]  = speed;
      motor[leftBack] = speed;
      motor[rightBack] = speed;
      motor[rightBig] = speed;
      motor[rightFront] = speed;
    }
  }
  stopdrivemotors();
}

void TurnGyro(short direction,int speed, float degrees, float time)// speed and ticks and time
{

  ClearTimer(T4);
  resetGyro();
  switch(direction){
  case right:
    while(abs(SensorValue[Gyro]) <= degrees*10 || time1[T4] < time *1000) // positive values go right. negative values go left
    {

      motor[leftBig] = speed;//turn is defaulted to the left
      motor[leftFront] = speed;
      motor[leftBack] =  speed;
      motor[rightBack] = -speed;
      motor[rightBig] = -speed;
      motor[rightFront] = -speed;
    }
    stopdrivemotors();

    break;
  case left:

    while(abs(SensorValue[Gyro]) <= degrees*10 || time1[T4] < time *1000)// positive values go right. negative values go left
    {

      motor[leftBig] = -speed;//turn is defaulted to the left
      motor[leftFront] = -speed;
      motor[leftBack] = -speed;
      motor[rightBack] = speed;
      motor[rightBig] = speed;
      motor[rightFront] = speed;
    }
    stopdrivemotors();

    break;
  }
}

//---------------------------------end of drive stuff-------------------------------------------------
/////////////////////////////arm stuff..//////////////////////////////////////////////////////////////
int lock(int final_pos) //locks arm to final_pos potentiometer point
{
  int current_pos = SensorValue(ArmPOT); //reads potentiometer
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


//////////////End of Lift stuff////////////////////////////////////
void armdirection(short direction, int speed)
{
  switch (direction){
  case down://make the arm go down
    motor[rightLift] = -speed;
    motor[leftLift] = -speed;//speed of the arm

  case up://make the arm go up...
    motor[rightLift] = speed;
    motor[leftLift] = speed;

  }//case

}

void liftHieght(short hieght, int time)// Needs work.. Need to find out how to add a range.
{
  bool target = false;
  ClearTimer(T4)
  while(target == false)
  {
    if(SensorValue[ArmPOT] > hieght && time1[T4] < time)
    {
      motor[rightLift] = -80;
      motor[leftLift] = -80;
    } else if(SensorValue[ArmPOT] < hieght && time1[T4] < time)
    {
      motor[rightLift] = 127;
      motor[leftLift] = 127;
    }
   target = true;//get outta the while loop.
  }//while
}//end of func.

void lift(int arm)
{
  switch(arm){
  case medgoal:
    while(SensorValue[ArmPOT]<twenty_inch_goal)
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
    while(SensorValue[ArmPOT]<ten_inch_goal)
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
    while(SensorValue[ArmPOT]<thirty_inch_goal)
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

///////////////////////////////Collector junk////////////////////////////

task CollectD()// multitask collector
{
  while(true)
  {
    motor[port8] = -127;
    motor[port9] = -127;
  }
}

///////////////////////Arm Tasks////////////////////////////////
task medTask()
{
  while(SensorValue[ArmPOT] < twenty_inch_goal)
  {
    motor[leftLift] = 127;
    motor[rightLift] = 127;
  }
  motor[leftLift] = 15;
  motor[rightLift] = 15;
}
task lowTask
{
  while(SensorValue[ArmPOT] < ten_inch_goal)
  {
    motor[leftLift] = 127;
    motor[rightLift] = 127;
  }
  motor[leftLift] = 15;
  motor[rightLift] = 15;
}
task highTask
{
  while(SensorValue[ArmPOT] < thirty_inch_goal)
  {
    motor[leftLift] = 127;
    motor[rightLift] = 127;
  }
  motor[leftLift] = 15;
  motor[rightLift] = 15;
}

task armDown
{
  while(SensorValue[touchl] !=1)
  {
    motor[leftLift] = -30;
    motor[rightLift] = -30;
  }
  stoparmmotors();
}
/////////////////////////////////////End of arm Tasks/////////////////////////////

void spit(int time)//collect objects
{
  motor[Collectors1] = 80;
  motor[Collectors2] = 80;
  wait1Msec(time*1000);
  motor[Collectors1] = 0;
  motor[Collectors2] = 0;

}


void collect(float time)
{
  ClearTimer(T4);

  {
    motor[Collectors1] = -127;
    motor[Collectors2] = -127;
    wait1Msec(time*1000);
    motor[Collectors1] = 0;
    motor[Collectors2] = 0;
  }
}

void cool(int speed)
{
  motor[Collectors1] = speed;//for teleop
  motor[Collectors2] = speed;
}
///////////////////end of Collector////////////////////////
void Lifter(int power)
{
  motor[leftLift] = power;
  motor[rightLift] = power;

}
////////////auton////////////////////////////////////
void drive_Highgoal()
{
  drive_Enc(127,9.5,2);//drive foward
  Off();//zero-out the motors
  stopTime(1.75);//wait for arm
  drive_Enc(50, 27,2);//drive foward more...
  stopTime(1.5);//sit at the wall for three seconds.
  drive_Enc(-85,2.75,3.4);//back up and spit.
  spit(4);// spit
  drive_Enc(-100, 7,2);//back up
}
///////////Interaction Auton/////////////////
void Interaction_auton()
{
  collect(0.05);//unloadthe collector
  while(Start == false)
  {
    if(SensorValue[bumper] == 1)
    {
      Start = true;
      StartTask(highTask);//while lifting the arm...
      {
        drive_Highgoal();
      }// end of task
      StartTask(armDown);
      {
        drive_Enc(-80,30,2);
      }
    }//end of if
  }// end of while
  Start = false;
  while(Start == false)
  {
    if(SensorValue[bumper] == 1)
    {
      Start = true;
      lift(lowgoal);
    }
  }
  Start = false;
  while(Start == false)
  {
    if(SensorValue[bumper] == 1)
    {
      Start = true;
      spit(3);
    }
  }//while
  Off();
}

/*
Isolation zone program for both the Red and Blue alliance.
What it does:
1) Go foward to collect a ball to obtain three balls.
2) Back up and lift to score.
3) Put the arm down press the button to go foward to collect the three game-objects.
4) (If we have time)Come back to score the last three game-objects.
*/
void IsoZone()
{
  // Interaction_auton();
  collect(0.2);// Make the colect fall dwon
  stopTime(0.2);//wait  for the collector to fall down
  StartTask(CollectD);
  {
    drive_Enc(100,12,3);//drive foward while collecting
    stopTime(0.75);
    stopCollectors();
  }//end of task
  StopTask(CollectD);
  drive_Enc(-63,15,3);//come back to base
  stopTime(0.1);
  lift(highgoal);

  while(Start == false)
  {
    if(SensorValue[bumper] == 1)
    {
      Start = true;
      spit(3);
    }
  }//while
  drive_Enc(-63,3,2);
  lift(gravityNot);
  Start = false;
  while(Start == false)
  {
    if(SensorValue[bumper] == 1)
    {
      Start = true;
      StartTask(CollectD);
      {
        drive_Enc(63,46,4);
        stopTime(0.75);
        stopCollectors();//foward to collect three tubes
        StopTask(CollectD);
      }
      drive_Enc(-63,50,4);
      lift(highgoal);//lift when it comes back
    }//if
  }//while
  Start = false;
  while(Start == false)
  {
    if(SensorValue[bumper] == 1)
    {
      Start = true;
      spit(3);
    }
  }//while
  Off();



}
////////////Auton junk///////////////////////////////

void clearencoders()
{
  SensorValue[leftencoder] = 0;
  SensorValue[rightencoder] = 0;
}

void screenrefresh()
{
  clearLCDLine(1);
  displayLCDPos(1,0);
  if (redteam == true)
  {
    displayNextLCDString("RED ");
  }
  if (redteam == false)
  {
    displayNextLCDString("BlUE");
  }
  displayNextLCDString("    ");
  displayNextLCDNumber(programselect);
  displayNextLCDString("     OK");
}


void stopdrive()
{
  motor[leftmotor] = 0;
  motor[rightmotor] = 0;
  motor[leftsmall] = 0;
  motor[rightsmall] = 0;
}

void instantspeed()
{
  motor[leftmotor] = targetspeed;
  motor[rightmotor] = targetspeed;
  motor[leftsmall] = targetspeed;
  motor[rightsmall] = targetspeed;
}

void rampto()
{
  clearencoders();
  currentspeed = 0;
  if (targetspeed > 0)
  {
    while (currentspeed < targetspeed)
    {
      currentspeed = currentspeed + 2;
      motor[leftmotor] = currentspeed;
      motor[rightmotor] = currentspeed;
      motor[leftsmall] = currentspeed;
      motor[rightsmall] = currentspeed;
      wait1Msec(8);
    }
  }

  if (targetspeed < 0)
  {
    while (currentspeed > targetspeed)
    {
      currentspeed = currentspeed - 2;
      motor[leftmotor] = currentspeed;
      motor[rightmotor] = currentspeed;
      motor[leftsmall] = currentspeed;
      motor[rightsmall] = currentspeed;
      wait1Msec(8);
    }
  }
}

void drivestraight()
{
  motor[leftmotor] = targetspeed - SensorValue[leftencoder]*1 + SensorValue[rightencoder]*1;
  motor[rightmotor] = targetspeed - SensorValue[rightencoder]*1 + SensorValue[leftencoder]*1;
  motor[leftsmall] = targetspeed - SensorValue[leftencoder]*1 + SensorValue[rightencoder]*1;
  motor[rightsmall] = targetspeed - SensorValue[rightencoder]*1 + SensorValue[leftencoder]*1;
}

void forwardto()
{
  rampto();
  while (SensorValue[leftencoder] + SensorValue[rightencoder] < distance)
  {
    drivestraight();
  }
  targetspeed = -targetspeed/2;
  instantspeed();
  wait1Msec(100);
  stopdrive();
}

void backto()
{
  rampto();
  while (SensorValue[leftencoder] + SensorValue[rightencoder] > distance)
  {
    drivestraight();
  }
  targetspeed = -targetspeed/2;
  instantspeed();
  wait1Msec(100);
  stopdrive();
}

/*
void cwturn()
{
clearencoders();
motor[leftmotor] = power;
motor[leftsmall] = power;
motor[rightmotor] = -power;
motor[rightsmall] = -power;
while (SensorValue[leftencoder] - SensorValue[rightencoder] < spinamount)
{
}
motor[leftmotor] = -power/2;
motor[leftsmall] = -power/2;
motor[rightmotor] = power/2;
motor[rightsmall] = power/2;
wait1Msec(10);
while (SensorValue[leftencoder] - SensorValue[rightencoder] > spinamount)
{
}
stopdrive();
}
*/

void cwturn()
{
  clearencoders();
  while (SensorValue[leftencoder] - SensorValue[rightencoder] < spinamount*2)
  {
    targetspeedL = power + spinamount/2 - SensorValue[leftencoder]/3;
    targetspeedR = -power - spinamount/2 + SensorValue[rightencoder]/3;
    motor[leftmotor] = targetspeedL;
    motor[leftsmall] = targetspeedL;
    motor[rightmotor] = targetspeedR;
    motor[rightsmall] = targetspeedR;
  }
  motor[leftmotor] = -30;
  motor[leftsmall] = -30;
  motor[rightmotor] = 30;
  motor[rightsmall] = 30;
  wait10Msec(10);
  stopdrive();
}


void ccwturn()
{
  clearencoders();
  while (SensorValue[rightencoder] - SensorValue[leftencoder] < spinamount*2)
  {
    targetspeedL = -power - spinamount/2 + SensorValue[leftencoder]/3;
    targetspeedR = power + spinamount/2 - SensorValue[rightencoder]/3;
    motor[leftmotor] = targetspeedL;
    motor[leftsmall] = targetspeedL;
    motor[rightmotor] = targetspeedR;
    motor[rightsmall] = targetspeedR;
  }
  motor[leftmotor] = 30;
  motor[leftsmall] = 30;
  motor[rightmotor] = -30;
  motor[rightsmall] = -30;
  wait10Msec(10);
  stopdrive();
}

/*
void rightbackturn()
{
clearencoders();
motor[rightmotor] = -power;
motor[rightsmall] = -power;
while (SensorValue[rightencoder] > -spinamount)
{
//motor[leftmotor] = -SensorValue[leftencoder]*3;
//motor[leftsmall] = -SensorValue[leftencoder]*3;
}
motor[rightmotor] = power/2;
motor[rightsmall] = power/2;
motor[leftmotor] = 0;
motor[leftsmall] = 0;
wait1Msec(10);
while (SensorValue[rightencoder] < -spinamount)
{
}
stopdrive();
}
*/

/*
void ccwturn()
{
clearencoders();
motor[leftmotor] = -power;
motor[leftsmall] = -power;
motor[rightmotor] = power;
motor[rightsmall] = power;
while (SensorValue[rightencoder] - SensorValue[leftencoder] < spinamount)
{
}
motor[leftmotor] = power/2;
motor[leftsmall] = power/2;
motor[rightmotor] = -power/2;
motor[rightsmall] = -power/2;
wait1Msec(10);
while (SensorValue[rightencoder] - SensorValue[leftencoder] > spinamount)
{
}
stopdrive();
}
*/


void approachtarget()
{
  clearencoders();
  targetspeedL = 300;
  targetspeedR = 300;
  while (targetspeedL > 25 | targetspeedL < -25)
  {

    targetspeedL = distance/2 - SensorValue[leftencoder]*6/4;
    targetspeedR = distance/2 - SensorValue[rightencoder]*6/4;


    motor[leftmotor] = targetspeedL;
    motor[rightmotor] = targetspeedR;
    motor[leftsmall] = targetspeedL;
    motor[rightsmall] = targetspeedR;
  }
}

void prepstack()
{
  clearencoders();
  targetspeed = 80;
  rampto();
  //distance = 320;
  approachtarget();
  targetspeed = 25;
  instantspeed();
  while (SensorValue[ringbuttonR] == 0)
  {
  }
  stopdrive();
  wait1Msec(100);
  clearencoders();
  motor[intake] = 127;
  targetspeed = -40;
  distance = -150;
  backto();
}
void getstack()
{
  motor[intake] = 127;
  targetarmposition = lowerlimit;
  StartTask(raisearmtoposition);
  wait1Msec(400);
  targetspeed = 40;
  rampto();
  while (armraising == true)
  {
    drivestraight();
  }
  wait1Msec(300);
  clearencoders();
  targetspeed = -40;
  rampto();
  distance = -60;
  backto();
  targetarmposition = basefromdown;
  StartTask(raisearmtoposition);
}

void scoreongoal()
{
  targetspeed = 120;
  rampto();
  while (SensorValue[ringbuttonR] == 0)
  {
    drivestraight();
  }
  clearencoders();
  targetspeed = -80;
  distance = -190;
  backto();
  wait1Msec(500);
  motor[intake] = -127;

}

void linetowall()
{
  stopdrive();
  for(int i = 0; i < 3; i++)
  {
    while (SensorValue[leftsonar] > SensorValue[rightsonar])
    {
      motor[rightmotor] = 60;
      motor[rightsmall] = 60;
    }
    motor[rightmotor] = 0;
    motor[rightsmall] = 0;
    while (SensorValue[rightsonar] > SensorValue[leftsonar])
    {
      motor[leftmotor] = 60;
      motor[leftsmall] = 60;
    }
    motor[leftmotor] = 0;
    motor[leftsmall] = 0;
    wait1Msec(20);
  }
}

/*
void wallprepgoal()
{
motor[leftmotor] = 40;
motor[leftsmall] = 40;
motor[rightmotor] = 40;
motor[rightsmall] = 40;
while (SensorValue[leftsonar] < 14 | SensorValue[rightsonar] < 14)
{
if (SensorValue[leftsonar] > 13)
{
motor[leftmotor] = 0;
motor[leftsmall] = 0;
}
if (SensorValue[rightsonar] > 13)
{
motor[rightmotor] = 0;
motor[rightsmall] = 0;
}
}
stopdrive();
}
*/

void bumpandstop()
{
  while (SensorValue[ringbuttonR] == 0 | SensorValue[goalbuttonL] == 0)
  {
    drivestraight();
    if (SensorValue[ringbuttonR] == 1)
    {
      motor[rightmotor] = 0;
      motor[rightsmall] = 0;
    }
    /*
    if (SensorValue[ringbuttonR] == 0)
    {
      motor[rightmotor] = targetspeed;
      motor[rightsmall] = targetspeed;
    }
    */
    if (SensorValue[goalbuttonL] == 1)
    {
      motor[leftmotor] = 0;
      motor[leftsmall] = 0;
    }
    /*
    if (SensorValue[goalbuttonL] == 0)
    {
      motor[leftmotor] = targetspeed;
      motor[leftsmall] = targetspeed;
    }
    */
  }
}



void curve(int lspeed, int rspeed, int distance)
{
  clearencoders();
  motor[leftmotor] = lspeed;
    motor[leftsmall] = lspeed;
    motor[rightmotor] = rspeed;
    motor[rightsmall] = rspeed;
    while (SensorValue[leftencoder] > distance && SensorValue[rightencoder] > distance)
    {
    }
    motor[leftmotor] = -lspeed;
    motor[leftsmall] = -lspeed;
    motor[rightmotor] = -rspeed;
    motor[rightsmall] = -rspeed;
    wait1Msec(20);
    stopdrive();

}

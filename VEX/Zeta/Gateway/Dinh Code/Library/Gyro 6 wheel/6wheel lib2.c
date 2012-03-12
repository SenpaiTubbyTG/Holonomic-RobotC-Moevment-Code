const bool Rightside = true;
const bool Leftside = false;
const bool Left = true;
const bool Right = false;
const bool Foward = true;
const bool Backward = false;
int distanceFromWall;


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

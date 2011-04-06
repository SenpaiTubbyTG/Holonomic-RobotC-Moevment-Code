//Start sucking
void suck()
{
  motor[Intake] = -127;
  motor[Tracks] = -127;
}

//Start spitting out
void eject()
{
  motor[Intake] = 127;
  motor[Tracks] = 127;
}

//Stop the intake
void stopintake()
{
  motor[Intake] = 0;
  motor[Tracks] = 0;
}

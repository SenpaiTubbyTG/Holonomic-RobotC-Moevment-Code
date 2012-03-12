task raisearmtoposition
{
  armraising = true;
  oldliftperror = 0;
  liftperror = 500;
  while (liftperror > 5 | liftperror < -5)
  {
    liftperror = SensorValue[liftpot] - targetarmposition;
    liftderror = oldliftperror - liftperror;
    turnamount = liftperror + liftderror;
    if (turnamount < 0)
    {
      turnamount = turnamount - 20;
    }
    else if (turnamount > 0)
    {
      turnamount = turnamount + 20;
    }
    motor[lift1] = turnamount;
    motor[lift2] = turnamount;
    oldliftperror = liftperror;
  }
  armraising = false;
  motor[lift1] = trim;
  motor[lift2] = trim;
  StopTask(raisearmtoposition);
}

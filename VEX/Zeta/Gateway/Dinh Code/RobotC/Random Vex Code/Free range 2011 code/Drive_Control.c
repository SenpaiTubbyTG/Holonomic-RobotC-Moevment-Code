while (true)
{

    motor[leftmotor] = vexRT[Ch3]*97/100;
    motor[rightmotor] = vexRT[Ch2]*97/100;
      motor[leftsmall] = vexRT[Ch3]*97/100;
      motor[rightsmall] = vexRT[Ch2]*97/100;

    motor[intake] = vexRT[Ch2Xmtr2];
    motor[descore] = vexRT[Ch6];

    if (vexRT[Ch6] == 127)
    {
      descoreup = true;
    }
    if (vexRT[Ch6] == -127)
    {
      descoreup = false;
    }
    if (vexRT[Ch5] == 0)
    {
    time1[T3] = 0;
  }
  if (vexRT[Ch5] == 127 && time1[T3] > 50)
  {
    SensorValue[pneumatics] = 1;
  }
  if (vexRT[Ch5] == -127 && time1[T3] < 50)
  {
    SensorValue[pneumatics] = 0;
  }


    if (vexRT[Ch6] == 0)
    {
      if (descoreup == true)
      {
        motor[port8] = 10;
      }
      if (descoreup == false)
      {
        motor[port8] = -10;
      }
    }
    if (vexRT[Ch5Xmtr2] == 0 && vexRT[Ch6Xmtr2] == 0)
    {
      time1[T2] = 0;
    }
    if (vexRT[Ch6Xmtr2] > 0 && time1[T2] > 100)
    {
      targetarmposition = wallgoalheight;
      StartTask(raisearmtoposition);
    }
    if (vexRT[Ch5Xmtr2] > 0 && time1[T2] > 100)
    {
      if (SensorValue[liftpot] > basefromdown) targetarmposition = basefromdown;
      else targetarmposition = basefromup;
      StartTask(raisearmtoposition);
    }
    if (vexRT[Ch5Xmtr2] < 0 && time1[T2] > 100)
    {
      targetarmposition = descoreheight;
      StartTask(raisearmtoposition);
    }

    if (vexRT[Ch3Xmtr2] > 15 | vexRT[Ch3Xmtr2] < -15)
    {
      StopTask(raisearmtoposition);
      armraising = false;
    }



    if (vexRT[Ch3Xmtr2] < -20 && vexRT[Ch6Xmtr2] < 0 && time1[T2] > 100)
    {
      bossenabled = true;
    }
    if (bossenabled == true)
    {
      motor[lift1] = vexRT[Ch3Xmtr2];
      motor[lift2] = vexRT[Ch3Xmtr2];
    }

    if (bossenabled == false && armraising == false)
    {
      if (SensorValue[liftpot] < lowerlimit)
      {
        motor[lift1] = vexRT[Ch3Xmtr2]+trim;
        motor[lift2] = vexRT[Ch3Xmtr2]+trim;
      }
      if (SensorValue[liftpot] > lowerlimit)
      {
        if (vexRT[Ch3Xmtr2] > 0)
        {
          motor[lift1] = vexRT[Ch3Xmtr2]+trim;
          motor[lift2] = vexRT[Ch3Xmtr2]+trim;
        }
        if (vexRT[Ch3Xmtr2] < 1)
        {
          motor[lift1] = trim;
          motor[lift2] = trim;
        }
      }
    }
  }

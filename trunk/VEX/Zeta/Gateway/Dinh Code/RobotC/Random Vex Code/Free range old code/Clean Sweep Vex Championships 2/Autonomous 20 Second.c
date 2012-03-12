task autonomous()
{

  //Start intake to drop down sucker wheels
  suck();
  //Start arm monitoring
  StartTask(autolevel);

  //Lift arm
  raisearm();

  //Forward
  forward(0,127);

  //Wait to hit wall
  hitwall(4000);

  //Stop
  stop();

  //Spit out balls
  eject();

  if (fieldside != centre)
  {
    wait1Msec(1500);

    //Stop ejecting
    stopintake();

    //Find line while reversing
    findline(back,-80,2000);

    //Lower Arm
    lowerarm();

    //Start Intake
    suck();

    //Turn different ways depending on the side of field it started on
    switch(fieldside)
    {
    case left:
      //Look for the line while turning right
      findlineturn(right,80,2000);
      break;
    case right:
      //Look for the line while turning left
      findlineturn(left,80,2000);
      break;
    }

    //Follow line
    StartTask(followline);

    //Wait for first junction
    waitforjunction(5000);

    //Lower Basket
    SensorValue[Basket] = 0;
    wait1Msec(1000);

    switch (automode)
    {
    case 1:
      //Wait for second junction
      waitforjunction(10000);
      waitfordistance(2000,2000);
      break;

    case 2:
      break;
    }

    //Stop intake
    stopintake();

    //Stop following line
    StopTask(followline);

    //Lift arm
    raisearm();

    switch(fieldside)
    {
    case left:
      //Spin left
      spinleft(700,60);
      break;
    case right:
      //Spin right
      spinright(700,60);
      break;
    }

    //Forward
    forward(0,127);

    //Wait to hit wall
    hitwall(2000);

    //Stop
    stop();

    //Spit out balls
    eject();
    if (automode == 2)
    {
      wait1Msec(32000);
    }
    wait1Msec(3000);

    //Flick basket
    SensorValue[Basket] = 1;
    wait1Msec(4000);

    SensorValue[Basket] = 0;
  }
}

task autonomous()
{
  //Start arm monitoring
  StartTask(autolevel);

  suck();

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
  wait1Msec(1500);

  //Stop ejecting
  stopintake();

  //Find line while reversing
  findline(back,-80,2000);
  wait1Msec(100);

  //Lower Arm
  lowerarm();

  //Start Intake
  suck();

  //Look for the line while turning right
  findlineturn(left,80,2000);

  //Follow line
  StartTask(followline);

  //Wait for first junction
  waitforjunction(5000);

  //Lower Basket
  SensorValue[Basket] = 0;
  wait1Msec(1000);

  //Wait for second junction
  waitforjunction(10000);
  waitfordistance(2000,2000);

  //Stop intake
  stopintake();

  //Stop following line
  StopTask(followline);

  //Lift arm
  raisearm();

  //Spin left
  spinright(700,60);

  //Forward
  forward(0,127);

  //Wait to hit wall
  hitwall(2000);

  //Stop
  stop();

  //Spit out balls
  eject();
  wait1Msec(3000);

  //Flick basket
  SensorValue[Basket] = 1;

  wait1Msec(4000);

  SensorValue[Basket] = 0;

  //Reverse
  reverse(2400,127);

  //Lower Basket
  lowerarm();

  //Spin left
  spinright(610,127);

  //Start intake
  suck();

  //Forward
  forward(0,127);
  wait1Msec(2000);

  //Wait for line
  findline(back,127,10000);

  stop();
  wait1Msec(500);

  //Reverse
  reverse(1700,127);

  //Lift arm
  raisearm();

  //Spin right
  spinleft(630,127);

  //Forward
  forward(0,127);

  //Wait to hit wall
  hitwall(2000);

  //Stop
  stop();

  //Spit out balls
  eject();
  wait1Msec(2000);

  //Flick basket
  SensorValue[Basket] = 1;
  wait1Msec(2000);

  //Lower basket
  SensorValue[Basket] = 0;

  //Stop ejecting
  stopintake();

  //Find line while reversing
  findline(back,-80,2000);

  //Lower Arm
  lowerarm();

  //Look for the line while turning right
  findlineturn(left,80,2000);

  //Follow line
  StartTask(followline);

  //Wait for junction
  waitforjunction(5000);
  waitfordistance(2000,2000);

  //Stop following line
  StopTask(followline);

  //Lift arm
  raisearm();

  stop();
  wait1Msec(3000);

  //Spin left
  spinright(700,60);

  //Forward
  forward(0,127);

  //Wait to hit wall
  hitwall(2000);

  //Stop
  stop();

  //Spit out balls
  eject();
  wait1Msec(2000);

  //Flick basket
  SensorValue[Basket] = 1;

}

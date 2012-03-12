void waitForButton()
{
  while(SensorValue[button] == 0)
  {
    wait1Msec(5)
  }
}
void stopTime(float time)
{
  wait1Msec(time*1000);
}

void Scoremiddlegoal()
{  waitForButton();
  starttask(CollectD);
  {
    drive_Enc(63,7,4);
  }
  stopdrivemotors();
  StopTask(CollectD);
  StartTask(medgoal);
  {

    stopTime(1.75);//wait for arm
    drive_Enc(63,8,5);//drive foward
  }
  StopTask(medgoal);
  spit(0.75);
  drive_Enc(-63,4,2);
  spit(0.75);
  StartTask(armDown);
  {
    drive_Enc(-63,15,5);
  }
  StopTask(armDown);
  waitForButton();
  StartTask(CollectD);
  {
    drive_Enc(70,15,5);
  }
  StopTask(CollectD);

}
void BlockMiddleGoal()
{
  StartTask(medgoal);
  {
    drivetime(80,1.2)
  }
  StopTask(medgoal);
  spit(20);
}

void drive_Highgoal()
{
  spit(0.5);/// let the spinners roll out.
  drivetime(80,1.2);
  stopDrivemotors(); ;//zero-out the motors
  //stopTime(1.75);//wait for arm
  // drivetime(50,2);//drive foward more...
  stopTime(20);//sit at the wall for three seconds.
  // drive_Enc(-85,2.75,3.4);//back up and spit.
  // spit(4);// spit
  // drive_Enc(-100, 7,2);//back up
}

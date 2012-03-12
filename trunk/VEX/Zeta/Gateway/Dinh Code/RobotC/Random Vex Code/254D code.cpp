task autonomous()
{
  clearEncoders();
  switch(step)
  {
    /*case 0:
      setArm(LOW);
      ClearTimer(T1);
      while(abs(SensorValue[lEncoder])<(360*2.5) && time1[T1] < 4000)
        driveStraight(1, 100);
      stopDrive();*/
    case 0:
      setArm(LOW);
      motor[intake]=127;
      motor[intake2]=127;
      wait1Msec(300);
      motor[intake]=0;
      motor[intake2]=0;
      setArm(LOWEST);
      driveStraight(1,100,180);
      stopDrive();
      ClearTimer(T1);
      while(SensorValue[range_sensor]>9 && time1(T1) < 4000)
      {
        setLeftDrive(-70);
        setRightDrive(70);
      }
      stopDrive();
      while(SensorValue[range_sensor] > 4)
        driveStraight(1,60);
      stopDrive();
      //driveStraight(1,60,10);
      stopDrive();
      step++;
    case 1:
      motor[intake]=127;
      motor[intake2]=127;
      wait1Msec(1200);
      motor[intake]=0;
      motor[intake]=0;
      //driveStraight(1,100,distanceToEncoderVal(3));
      stopDrive();
      clearEncoders();
      step++;
    case 2:
      setArm(HIGH);
      turn(LEFT, 80, 360*2);
      driveStraight(1, 100, 360*3);
      stopDrive();
      motor[intake]=motor[intake2]=70;
      wait1Msec(700);
      motor[intake]=motor[intake2]=0;
    case 2:
      //setArm(HIGH);
      driveStraight(1,600,200);
      step++;
    case 3:
      if(SensorValue[jumper1]==1)
        turn(RIGHT,100,151); //old constant 220
      else
        turn(LEFT,100,45);
      clearEncoders();
      step++;
    case 4:
      while(abs(SensorValue[lEncoder])<179) //old constant 260
        driveStraight(1,80);
      stopDrive();
      clearEncoders();
      step++;
   case 5:
      setArm(LOW);
      step++;
    case 6:
      motor[intake]=-127;
      motor[intake2]=-127;
      wait1Msec(1000);
      motor[intake]=0;
      motor[intake]=0;
      step++;
    case 7:
      motor[rDrive1]=motor[rDrive2]=motor[lDrive1]=motor[lDrive2]=-127;
      wait1Msec(700);
      motor[rDrive1]=motor[rDrive2]=motor[lDrive1]=motor[lDrive2]=0;
  }
}

task usercontrol()
{
  
  if(SensorValue[jumper2]==0)
  {
    while(true)
	  {
	    //Logarithmic drive gives better control in extreme ranges
	    int RawSpeedR=vexRT[Ch2];
	    int RawSpeedL=vexRT[Ch3];
	    int LogSpeedR=logDrive(RawSpeedR);
	    int LogSpeedL=logDrive(RawSpeedL);
	    motor[rDrive1]=motor[rDrive2]=LogSpeedR;
	    motor[lDrive1]=motor[lDrive2]=LogSpeedL;

	    if(vexRT[Btn8U]==1 && !opAutoEnabled && vexRT[Btn5U]==0 && vexRT[Btn5D]==0)
	      opAutoEnabled = true;
	    else if(vexRT[Btn8U]==1 && opAutoEnabled)
	      opAutoEnabled = false;
	    //claw motor, controlled by operator
	    switch(opAutoEnabled)
	    {
	      case false:
	        if(vexRT[Btn5U]==1)
	            motor[lArmTop]=motor[lArmBott]=motor[rArmTop]=motor[rArmBott]=127;
	        else if(vexRT[Btn5D]==1)
	            motor[lArmTop]=motor[lArmBott]=motor[rArmTop]=motor[rArmBott]=-127;
	        else
	            motor[lArmTop]=motor[lArmBott]=motor[rArmTop]=motor[rArmBott]=0;
	        break;
	      case true:
	        motor[lArmTop]=motor[lArmBott]=motor[rArmTop]=motor[rArmBott]=30;
	        break;
	      default:
	        opAutoEnabled=false;
	        break;
	    }
	    //descore preset
	    if(vexRT[Btn7U]==1)
	    {
	      while(SensorValue[armPot]<DESCORE)
	        motor[lArmTop]=motor[lArmBott]=motor[rArmTop]=motor[rArmBott]=127;
	      motor[lArmTop]=motor[lArmBott]=motor[rArmTop]=motor[rArmBott]=0;
	    }
	    if(vexRT[Btn6U]==1)
	        motor[intake]=motor[intake2]=127;
	    else if(vexRT[Btn6D]==1)
	        motor[intake]=motor[intake2]=-127;
	    else
	        motor[intake]=motor[intake2]=0;

	    //fires hanging pBtn8U
	    if(vexRT[Btn8R]==1) SensorValue[ratchet_piston] = 1;
	    if(vexRT[Btn8L]==1) SensorValue[ratchet_piston] = 0;

	    if(vexRT[Btn7U]==1 && vexRT[Btn8U]==1 && !pistonEngaged){
	      SensorValue[arm_release]=1;
	      pistonEngaged=true;
	    }
	    else if(vexRT[Btn7D]==1 && vexRT[Btn8D]==1 && pistonEngaged){
	      SensorValue[arm_release]=0;
	      pistonEngaged=false;
	    }
	  }
  }
  else if(SensorValue[jumper2]==1)
  {
    while(true)
    {
    //r=2, l=3
    if(vexRT[Ch2] >0 && vexRT[Ch2]<=5) rDrive=0;
    else if(vexRT[Ch2]>5 && vexRT[Ch2]<=64) rDrive = vexRT[Ch2]+10;
    else if(vexRT[Ch2]>64 && vexRT[Ch2]<=85) rDrive = 74+18;
    else if(vexRT[Ch2]>85 && vexRT[Ch2]<=106) rDrive = 74+18+18;
    else if(vexRT[Ch2]>106 && vexRT[Ch2]<=127) rDrive = 74+18+18+18;
    else if(vexRT[Ch2]<-10 && vexRT[Ch2]>=-64) rDrive = vexRT[Ch2]-10;
    else if(vexRT[Ch2]<-64 && vexRT[Ch2]>=-85) rDrive = -74-18;
    else if(vexRT[Ch2]<-85 && vexRT[Ch2]>=-106) rDrive = -74-18-18;
    else if(vexRT[Ch2]<-106 && vexRT[Ch2]>=-127) rDrive = -74-18-18-18;

    if(vexRT[Ch3] >0 && vexRT[Ch3]<5) lDrive=0;
    else if(vexRT[Ch3]>5 && vexRT[Ch3]<=64) lDrive = vexRT[Ch3]+10;
    else if(vexRT[Ch3]>64 && vexRT[Ch3]<=85) lDrive = 74+18;
    else if(vexRT[Ch3]>85 && vexRT[Ch3]<=106) lDrive = 74+18+18;
    else if(vexRT[Ch3]>106 && vexRT[Ch3]<=127) lDrive = 74+18+18+18;
    else if(vexRT[Ch3]<0 && vexRT[Ch3]>=-64) lDrive = vexRT[Ch3]-10;
    else if(vexRT[Ch3]<-64 && vexRT[Ch3]>=-85) lDrive = -74-18;
    else if(vexRT[Ch3]<-85 && vexRT[Ch3]>=-106) lDrive = -74-18-18;
    else if(vexRT[Ch3]<-106 && vexRT[Ch3]>=-127) lDrive = -74-18-18-18;

    motor[rDrive1]=motor[rDrive2]=rDrive;
    motor[lDrive1]=motor[lDrive2]=lDrive;
    //claw motor, controlled by operator
    motor[intake]=motor[intake2]=-vexRT[Ch2Xmtr2];

    //fires hanging piston
    if(vexRT[Btn6UXmtr2]==1) SensorValue[ratchet_piston]=1;
    else if(vexRT[Btn6DXmtr2]==1) SensorValue[ratchet_piston]=0;

    if(vexRT[Btn5UXmtr2]==1&& vexRT[Btn5U]==1 && !pistonEngaged){
      SensorValue[arm_release]=1;
      pistonEngaged=true;
    }
    else if(vexRT[Btn5DXmtr2]==1&& vexRT[Btn5D]==1 && pistonEngaged)
    {
      SensorValue[arm_release]=0;
      pistonEngaged=false;
    }
    if(vexRT[Btn7DXmtr2] == 1 && !opAutoEnabled)
    {
      wait1Msec(30);
      if(vexRT[Btn7DXmtr2] == 0)
        opAutoEnabled=true;

    }
    else if(vexRT[Btn7DXmtr2] == 1 && opAutoEnabled)
    {
      wait1Msec(30);
      if(vexRT[Btn7DXmtr2] == 0)
        opAutoEnabled=false;

    }
    switch(opAutoEnabled)
    {
      case true:
		    if(SensorValue[armPot]<DESCORE-20)
		      motor[lArmTop]=motor[lArmBott]=motor[rArmTop]=motor[rArmBott]=30;
		    else if(SensorValue[armPot]>DESCORE+20)
		      motor[lArmTop]=motor[lArmBott]=motor[rArmTop]=motor[rArmBott]=-30;
			  else if (SensorValue[armPot]<DESCORE+20 && SensorValue[armPot]>DESCORE-20)
			  {
			    motor[lArmTop]=motor[lArmBott]=motor[rArmTop]=motor[rArmBott]=0;
			  }
			  break;
			case false:
			  motor[lArmTop]=motor[lArmBott]=motor[rArmTop]=motor[rArmBott]=vexRT[Ch3Xmtr2];
			  break;
	}

  }
}
}
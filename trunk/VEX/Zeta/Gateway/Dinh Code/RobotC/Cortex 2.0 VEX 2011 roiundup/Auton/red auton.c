 if(SensorValue[ppot] > 6 && SensorValue[ppot] < 1088) // if pot is set between 6 and 2100 it will run red auton.
  {
    // 2 Second Delay

    //Clear Encoders
    SensorValue[dgtl4] = 0;
    SensorValue[dgtl2] = 0;

    motor[port10] = 127;
    wait1Msec(600);
    motor[port10] = 10;
    wait1Msec(1);

    while(SensorValue[dgtl2 ] > -42)
    {
      //...turn
      motor[DriveLF] = 63;
      motor[DriveRF] = -63;
      motor[DriveRB] = -63;
      motor[DriveLB] = 63;
    }
    motor[port2] = 0;
    motor[port3] = 0;
    motor[port4] = 0;
    motor[port5] = 0;

    while(SensorValue[pot] < 1475)
    {
      motor[port6] = -100;
      motor[port7] = -100;
      motor[port8] = -100;
      motor[port9] =-100;
    }
    {

      motor[port6] =-5;
      motor[port7] = -5;
      motor[port8] = -5;
      motor[port9] = -5;
    }

    SensorValue[dgtl2] = 0;
    SensorValue[dgtl4] = 0;
    while(SensorValue[dgtl2] < 199)  // While less than 5 rotations on the leftEncoder...
    {
      //...Move Forward
      motor[port2] = 63;
      motor[port3] = 63;
      motor[port4] =63;
      motor[port5] = 63;
    }
    motor[port2] = 0;
    motor[port3] = 0;
    motor[port4] = 0;
    motor[port5] = 0;


    while(SensorValue[pot] > 937)
    {
      motor[port6] = 30;
      motor[port7] = 30;
      motor[port8] = 30;
      motor[port9] = 30;
    }


    motor[port6] = 0;
    motor[port7] = 0;
    motor[port8] = 0;
    motor[port9] = 0;


    motor[port10] = -127;
    wait1Msec(200);
    motor[port10] = 0;
    wait1Msec(1);
    while(SensorValue[dgtl2] > -215)  //while left encoder is less than -215 then...
    {
      //...Move back
      motor[port2] = -63;
      motor[port3] = -63;
      motor[port4] = -63;
      motor[port5] = -63;
    }
    motor[port2] = 0;
    motor[port3] = 0;
    motor[port4] = 0;
    motor[port5] = 0;





  }// auton red

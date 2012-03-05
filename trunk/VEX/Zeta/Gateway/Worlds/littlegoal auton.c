while(SensorValue[startAuton] == 0) {

wait1Msec(2000000)
}//end while

  motor[frontL] = motor[frontL2] = motor[backL] = -127;  //drives backwards to the little goal...
  motor[frontR] = motor[frontR2] = motor[backR] = -127;
  wait1Msec(300)
  killdrive();

  setSuckSpeed(127);                                     //scores tubes in low goal...
  wait1Msec(2000);
  setSuckSpeed(0);

  motor[frontL] = motor[frontL2] = motor[backL] = 127;  //drives backwards to the little goal...
  motor[frontR] = motor[frontR2] = motor[backR] = 127;
  wait1Msec(300)
  killDrive();

  wait1Msec(2000);

  motor[frontL] = motor[frontL2] = motor[backL] = 127;
  motor[frontR] = motor[frontR2] = motor[backR] = 127;
  wait1Msec(600);
  killDrive();

  motor[frontL] = motor[frontL2] = motor[backL] = -127;
  motor[frontR] = motor[frontR2] = motor[backR] = -127;
  wait1Msec(200);
  killDrive();

  motor[frontL] = motor[frontL2] = motor[backL] = -127;
  motor[frontR] = motor[frontR2] = motor[backR] = 127;
  wait1Msec(100);
  killDrive();

  motor[frontL] = motor[frontL2] = motor[backL] = 127;
  motor[frontR] = motor[frontR2] = motor[backR] = 127;
  wait1Msec(150);
  killDrive();

  setSuckSpeed(127);
  wait1Msec(4000);
  setSuckSpeed(0);

  motor[frontL] = motor[frontL2] = motor[backL] = 127;
  motor[frontR] = motor[frontR2] = motor[backR] = -127;
  wait1Msec(150);
  killDrive();

  motor[frontL] = motor[frontL2] = motor[backL] = -127;
  motor[frontR] = motor[frontR2] = motor[backR] = -127;
  wait1Msec(400);
  killDrive();

  motor[frontL] = motor[frontL2] = motor[backL] = 127;
  motor[frontR] = motor[frontR2] = motor[backR] = -127;
  wait1Msec(150);
  killDrive();

  motor[frontL] = motor[frontL2] = motor[backL] = -127;
  motor[frontR] = motor[frontR2] = motor[backR] = -127;
  wait1Msec(600);
  killDrive();

  setSuckSpeed(127);
  wait1Msec(5000);
  setSuckSpeed(0);




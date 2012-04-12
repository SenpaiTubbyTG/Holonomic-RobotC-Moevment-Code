void setSuckSpeed(int speed, int duration)   {
  motor[collectorL] = motor[collectorR] = speed;
  wait1Msec(duration);
  motor[collectorL] = motor[collectorR] = 0;
}//END void

void drive_forward_msec(int speed, int duration) {
  motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = speed;
  wait1Msec(duration);
  motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = 0;
}//END void

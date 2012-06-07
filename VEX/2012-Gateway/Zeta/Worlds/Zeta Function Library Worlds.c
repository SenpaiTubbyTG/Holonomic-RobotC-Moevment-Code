void drive_backward_msec(int speed, int duration){
    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = -speed;
    wait1Msec(duration);
    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = 0;
}//END void

void drive_forward_msec(int speed, int duration){
    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = speed;
    wait1Msec(duration);
    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = 0;
}//END void

void turn_right_msec(int speed, int duration){
    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = speed;
    motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = -speed;
    wait1Msec(duration);
    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = 0;
}

void turn_left_msec(int speed, int duration){
    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = -speed;
    motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = speed;
    wait1Msec(duration);
    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = 0;
}

void setSuckSpeed(int speed, int duration){
  motor[collectorL] = motor[collectorR] = speed;
  wait1Msec(duration);
  motor[collectorL] = motor[collectorR] = 0;
}//END void

void drive_collect_msec(int speed, int cspeed, int duration){
  motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = speed;
  motor[collectorR] = motor[collectorL] = cspeed;
  wait1Msec(duration);
  motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = 0;
  motor[collectorL] = motor[collectorR] = 0;
}//END void

//second parameter is the time limit given. If sensor doesn't trip, the method aborts after this amount of time.
/*bool drive_forward_dist(int power, int inches, int milAbort){
  SensorValue[encoderL] = 0;
  SensorValue[encoderR] = 0;
  time1[T1] = 0;
  int ticks = (int)360/(4*PI)*inches;
  while(SensorValue[encoderR] < ticks && time1[T1]<=milAbort){
    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = power;
  }
  motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = 0;
  if(time1[T1]>milAbort){f
    return false;
  }
  else{
    return true;
  }
} //<<--- THIS IS AN ENDING BRACKET AHHHHHHHHHHH! DON'T TOUCH!*/

//second parameter is the time limit given. If sensor doesn't trip, the method aborts after this amount of time.
bool drive_forward_until_touch(int power, int milAbort){
  time1[T1] = 0;
  while(SensorValue[rearTouch] != 1 && time1[T1] <= milAbort){
    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = power;
  }
  motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = 0;
  if(time1[T1]>milAbort){
    return false;
  }
  else{
    return true;
  }
} //<<--- THIS IS AN ENDING BRACKET AHHHHHHHHHHH! DON'T TOUCH!

/*bool drive_collect_dist(int power, int cspeed, int dist, int milAbort){
  motor[collectorR] = motor[collectorL] = cspeed;
  bool r = drive_forward_dist(power, dist, milAbort);
  motor[collectorL] = motor[collectorR] = 0;
  return r;
}//END void*/

/*bool turn_degrees(int degrees, int milAbort){
  int direction; // CLOCKWISE = 0; COUNTERCLOCKWISE = 1
  if(degrees<0){
    direction = -1;
  } else {
    direction = 1;
  }
  SensorValue[encoderL] = SensorValue[encoderR] = 0;
  time1[T1] = 0;
  float ticks = abs(1000*360/degrees);
  while(time1[T1]<=milAbort && abs(SensorValue[encoderR])<ticks){
    motor[frontL] = motor[frontL2] = -90*direction;
    motor[backL] = motor[backL2]   = -90*direction;
    motor[frontR] = motor[frontR2] = 90*direction;
    motor[backR] = motor[backR2]   = 90*direction;
  }
  motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = 0;
  if(time1[T1]>milAbort){
    return false;
  }
  else{
    return true;
  }
}//<<--- THIS IS AN ENDING BRACKET AHHHHHHHHHHH! DON'T TOUCH!*/

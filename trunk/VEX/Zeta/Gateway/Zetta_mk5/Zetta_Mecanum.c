
float driveAngle = 0;

float getDriveAngle(){

  float driveAngle;

  // Determine the correct driving angle
  if(vexRT[Ch1] < 0){
    driveAngle = atan(vexRT[Ch2]/(float)vexRT[Ch1])+PI;
  }else if(vexRT[Ch1] > 0){
    driveAngle = atan(vexRT[Ch2]/(float)vexRT[Ch1]);
  }else if(vexRT[Ch1] == 0){
      if(vexRT[Ch2]>0){
        driveAngle = PI/2.0;
      } else if(vexRT[Ch2]<0){
        driveAngle = (3*PI)/2.0;
      } else {
        driveAngle = 0;
      }
  }
  return driveAngle;
}

float getDriveMagnitude(){
  return sqrt(pow(vexRT[Ch1], 2) + pow(vexRT[Ch2], 2));
}

float getTurnAngle(){

  float turnAngle;

  // Determine the correct driving angle
  if(vexRT[Ch4] < 0){
    turnAngle = atan(vexRT[Ch3]/(float)vexRT[Ch4])+PI;
  }else if(vexRT[Ch4] > 0){
    turnAngle = atan(vexRT[Ch3]/(float)vexRT[Ch4]);
  }else if(vexRT[Ch4] == 0){
      if(vexRT[Ch3]>0){
        turnAngle = PI/2.0;
      } else if(vexRT[Ch3]<0){
        turnAngle = (3*PI)/2.0;
      } else {
        turnAngle = 0;
      }
  }
  return turnAngle;
}

float getTurnMagnitude(){
  return sqrt(pow(vexRT[Ch3], 2)+pow(vexRT[Ch4], 2));
}

float maximum(float a, float b, float c, float d){
  float max = a;

  if(max<b){
    max = b;
  } if(max<c){
    max = c;
  } if(max<d){
    max = d;
  }
  return max;
}

void mecanumDrive(){
  /* This method is used to apply motor inputs to control a mechanum drive system

     assuming

     ||1       2  ||
      ||         ||

      ||3       4||
     ||           ||

      ALL ANGLES ARE IN RADIANS
  */

  driveAngle = getDriveAngle();
  float driveMagnitude = getDriveMagnitude();
  float turnAngle = getTurnAngle();
  float turnMagnitude = getTurnMagnitude();

  // this variable is for driving without gyro

  float direction;  //-1 is clockwise, 1 = counter-clockwise
  if(turnAngle<PI/2.0 || turnAngle>=(3*PI)/2.0){
    direction = -1;
  } else if(turnAngle >= PI/2.0 && turnAngle<(3*PI)/2.0){
    direction = 1;
  }

  float turnInput = direction*10;  // 10 can be changed

  // (PI/2.0) is subtracted to shift the axes
  float flOutput = driveMagnitude*sin(driveAngle-(PI/2.0)) - turnInput;
  float frOutput = driveMagnitude*cos(driveAngle-(PI/2.0)) + turnInput;
  float blOutput = driveMagnitude*cos(driveAngle-(PI/2.0)) - turnInput;
  float brOutput = driveMagnitude*sin(driveAngle-(PI/2.0)) + turnInput;

  float max = maximum(flOutput, frOutput, blOutput, brOutput);

  flOutput = flOutput*(driveMagnitude/max);
  frOutput = frOutput*(driveMagnitude/max);
  blOutput = blOutput*(driveMagnitude/max);
  brOutput = brOutput*(driveMagnitude/max);

  motor[FrontLeft1]= motor[FrontLeft2] = flOutput;
  motor[FrontRight1] = motor[FrontRight2] = frOutput;
  motor[BackLeft] = blOutput;
  motor[BackRight] = brOutput;
}

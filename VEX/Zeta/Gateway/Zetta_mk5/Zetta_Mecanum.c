
float getDriveAngle(){

  float driveAngle=0;

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
  if(driveAngle < 0){
    driveAngle = driveAngle + 2*PI;
  }
  return driveAngle;
}

float getDriveMagnitude(){
  return sqrt(pow(vexRT[Ch1], 2) + pow(vexRT[Ch2], 2));
}

float getTurnAngle(){

  float turnAngle=0;

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
  if(turnAngle < 0){
    turnAngle = turnAngle + 2*PI;
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

  float driveAngle = getDriveAngle();
  float driveMagnitude = getDriveMagnitude();

  // (PI/2.0) is subtracted to shift the axes
  float flOutput = driveMagnitude*sin(driveAngle-(PI/2.0));
  float frOutput = driveMagnitude*cos(driveAngle-(PI/2.0));
  float blOutput = driveMagnitude*cos(driveAngle-(PI/2.0));
  float brOutput = driveMagnitude*sin(driveAngle-(PI/2.0));

  /*float max = maximum(abs(flOutput), abs(frOutput), abs(blOutput), abs(brOutput));

  flOutput = flOutput*(driveMagnitude/max);
  frOutput = frOutput*(driveMagnitude/max);
  blOutput = blOutput*(driveMagnitude/max);
  brOutput = brOutput*(driveMagnitude/max);*/

  motor[FrontLeft1]= flOutput;
  motor[FrontLeft2]= flOutput;
  motor[FrontRight1] = frOutput;
  motor[FrontRight2] = frOutput;
  motor[BackLeft] = blOutput;
  motor[BackRight] = brOutput;
}

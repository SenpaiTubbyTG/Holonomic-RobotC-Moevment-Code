
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

  float driveAngle,
        driveMagnitude,
        flOutput,
        frOutput,
        blOutput,
        brOutput,
        turnComponent,
        maxOutput;

  driveAngle = getDriveAngle();
  driveMagnitude = getDriveMagnitude();

  // this line determined the input to be for turning.
  turnComponent = vexRT[Ch4]/5.0;

  /*This line of code is used to scale the driveMagnitude if adding the
    turning component will exceed the max pwn value of 127 */
  if(driveMagnitude+turnComponent > 127){
    driveMagnitude = 127 - turnComponent;
  }

  /* (PI/4.0) is subtracted to shift the axes. These 4 lines assign motor values according
     angle and driveMagnitude only. Turning components are not considered here.         */
  flOutput = driveMagnitude*sin(driveAngle-(PI/4.0));
  frOutput = driveMagnitude*cos(driveAngle-(PI/4.0));
  blOutput = driveMagnitude*cos(driveAngle-(PI/4.0));
  brOutput = driveMagnitude*sin(driveAngle-(PI/4.0));

  /*This variable determines the output with greatest magnitude. The values will then be
    scaled so that the greatest output is equal to the driveMagnitude*/
  maxOutput = maximum(abs(flOutput), abs(frOutput), abs(blOutput), abs(brOutput));

  /* these 4 lines update the output variables so that they 1. have correctly scaled values,
     and 2. so that they incorporate the turning component*/
  flOutput = flOutput*(driveMagnitude/maxOutput) + turnComponent;
  frOutput = frOutput*(driveMagnitude/maxOutput) - turnComponent;
  blOutput = blOutput*(driveMagnitude/maxOutput) + turnComponent;
  brOutput = brOutput*(driveMagnitude/maxOutput) - turnComponent;

  motor[FrontLeft1]= motor[FrontLeft2]= flOutput;
  motor[FrontRight1] = motor[FrontRight2] = frOutput;
  motor[BackLeft] = blOutput;
  motor[BackRight] = brOutput;
}

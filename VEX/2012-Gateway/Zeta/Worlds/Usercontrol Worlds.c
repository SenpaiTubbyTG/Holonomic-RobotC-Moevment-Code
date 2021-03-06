void twotrigger() {
 if(vexRT[Btn6U] == 1 && vexRT[Btn6D] == 1) {
  SensorValue[solenoidB] = 0;
  motor[collectorL] = motor[collectorR] = 100;
 } // END if
} // END void

void fourtrigger() {
 if(vexRT[Btn6D] == 1 && vexRT[Btn6U] == 1 && vexRT[Btn5D] == 1 && vexRT[Btn5U] == 1) {
   motor[collectorL] = motor[collectorR] = 50;
 } // END if
} // END void

void diagonaltrigger() {
  if(vexRT[Btn5D] == 1 && vexRT[Btn6U] == 1) {
    motor[collectorL] = 127;
    motor[collectorR] = -127;
 } // END if
} // END void

//////////////////////// PNEUMATIC BLOCK/////////////////////////////////////////////////////////////////////////////////////
void block() {
    if(SensorValue[solenoidB] == 1 && vexRT[Btn7U] == 1) {
     SensorValue[solenoidB] = 0;
     while(vexRT[Btn7U] != 0);
    }// END if
    if(SensorValue[solenoidB] == 0 && vexRT[Btn7U] == 1) {
     SensorValue[solenoidB] = 1;
     while(vexRT[Btn7U] != 0);
    }// END if
}// END void
//////////////////////////////LIFT////////////////////////////////////////////////////////////////////////////////////////////
void lift() {
    if(vexRT[Btn5U] == 1)   {                               // If button 5U is pressed:
      SensorValue[solenoidL] = SensorValue[solenoidR] = 1;  // ...both pneumatics shoot out.
    }//end if

    else if(vexRT[Btn5D] == 1)  {                           // If button 5D is pressed:
      SensorValue[solenoidL] = SensorValue[solenoidR] = 0;  // ...both pneumatics shoot in.
    }//end else if
}//end void lift
    //////////////////////////COLLECTOR///////////////////////////////////////////////////////////////////////////////////////
void collector(){
    if(vexRT[Btn6U] == 1) {
      motor[collectorL] = motor[collectorR] = 127;   // if btn 6u is pressed turn both sides of the collector in at full
    }//end if
    else if(vexRT[Btn6D] == 1) {
      motor[collectorL] = motor[collectorR] = -127;  // if btn 6d is pressed turn both sides of the collector out at full speed
    }//end else if
    else if(vexRT[Btn8U] == 1) {                     // if btn 8u is pressed turn both sides of the collector in at 100 speed
      motor[collectorL] = motor[collectorR] = 100;
    }//end else if
    else if(vexRT[Btn8D] == 1) {                     // if btn 8d is pressed turn both sides of the collector out at 100 speed
    motor[collectorL] = motor[collectorR] = -100;
    }//end else if
    else if(vexRT[Btn8R] == 1) {                     // if btn 8r is pressed turn both sides of the collector in oppisite directions
      motor[collectorL] = 127;
      motor[collectorR] = -127;
    }//end else if
    else if(vexRT[Btn8L] == 1) {                     // if btn 8l is pressed turn both sides of the collector in oppisite directions
      motor[collectorL] = -127;                      // (oppisite to the previous else if)
      motor[collectorR] = 127;
    }//end else if
    else {
      motor[collectorL] = motor[collectorR] = 0;     // if no btn is pressed turn neither side of the collector
    }//end else
}//end void collector
    //////////////////////////DRIVETRAIN///////////////////////////////////////////////////////////////////////////////////////
void drivetrain() {
	if (vexRT[Btn7L] == 0){
	    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = vexRT[Ch3];//L drivetrain speed = y axis of L joystick values
	    motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = vexRT[Ch2];//R drivetrain speed = y axis of R joystick values
	}// end if

	else if (vexRT[Btn7L] == 1){
	    motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = vexRT[Ch3]*0.5;//L drivetrain speed = y axis of L joystick values divided by 2
	    motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = vexRT[Ch2]*0.5;//R drivetrain speed = y axis of R joystick values divided
  }// end else
}//end void drivtrain

// control of the brake
void brake(){
  if(vexRT[Btn7D] == 1){
    SensorValue[solenoidBrake] = (SensorValue[solenoidBrake]+1)%2;
    while(vexRT[Btn7D] != 0);
  }
}

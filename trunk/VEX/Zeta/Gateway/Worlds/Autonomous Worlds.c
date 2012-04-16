void skillsAutonomous(){
  while(true) {
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;      // raise the arm
        SensorValue[solenoidB] = 0;                               // open the block
        while(SensorValue[AutonHigh] == 0);                       // wait for btn to be pressed (AutonHigh)
        drive_forward_until_touch(-127,1500);                     // drive backwards until touch or 1.5 seconds... to high goal
        wait1Msec(200);                                           // wait one 5th of a second
        setSuckSpeed(100,3500);                                   // collector scores at 100 speed for 3.5 seconds
        drive_forward_msec(127,1250);                             // drive back to starting square for 1.25 seconds
        SensorValue[solenoidL] = SensorValue[solenoidR] = 0;      // lowers arm
        while(SensorValue[AutonHigh] == 0);                       // wait for btn to be pressed (AutonHigh)
        SensorValue[solenoidB] = 1;                               // close block
        drive_collect_msec(100,127,2000);                         // drive to doubler and collect for 2 seconds
        setSuckSpeed(127,300);                                    // collect doubler for 1 third of a second
        drive_backward_msec(127,1600);                            // drive back to starting square
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;      // raises arm
        SensorValue[solenoidB] = 0;                               // open block
        while(SensorValue[AutonHigh] == 0);                       // wait for btn to be pressed (AutonHigh)
        drive_forward_until_touch(-127,1500);                     // drive backwards until touch or 1.5 seconds... to high goal
        wait1Msec(200);                                           // wait one 5th of a second
        setSuckSpeed(100,300);                                    // score doubler in high goal for one third of a second at 100/127 speed
        drive_forward_msec(127,1250);                             // drive back to starting square for 1.25 seconds
        SensorValue[solenoidB] = 1;                               // close block
        while(SensorValue[AutonHigh] == 0);                       // wait for btn to be pressed (AutonHigh) (Put in any remaining matchloads)
        setSuckSpeed(127,1000);                                   // collect stack of two by starting tile
        wait1Msec(100);                                           // wait one 10th of a second
        setSuckSpeed(-127,200);                                   // lower stack in collector for two tenths of a second
        SensorValue[solenoidB] = 0;                               // open block
        while(SensorValue[AutonHigh] == 0);                       // wait for btn to be pressed (AutonHigh)
        drive_forward_until_touch(-127,500);                      // drive backwards to little goal
        setSuckSpeed(100,1000);                                   // score stack in little goal at 100/127 speed for 1 second
        drive_forward_msec(127,300);                              // drives back to starting square
        while(SensorValue[AutonHigh] == 0);                       // wait for btn to be pressed (AutonHigh)
      }
    }

void redIntAutonomous(){
  while(true) {
    if(SensorValue[AutonHigh] == 1){                              // if btn autonHigh is pressed...
      if(SensorValue[solenoidL] == 0) {                           // if the arm is lowered...
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;      // raise the arm
        wait10Msec(50);                                           // wait half a second
      } // END 2nd if
      else {                                                      // else
        if(drive_forward_until_touch(-127, 1500)){                // drive backwards at full power until touch or 2 sec
	        wait10Msec(50);                                         // wait 1 second
	        setSuckSpeed(100,3500);                                 // collector scores at 100 speed for 3.5 seconds
        }
        drive_forward_msec(127,1000);                             // drive forward at full power for 0.5 seconds
      } // END else
    } // END 1st if

    if(SensorValue[AutonLow] == 1)  {                             // if btn autonLow is pressed...
      if(SensorValue[solenoidL] == 1) {                           // if the arm is raised
        SensorValue[solenoidL] = SensorValue[solenoidR] = 0;      // lower the arm
        wait10Msec(50);                                           // wait .5 seconds
      } // END 2nd if
      else {                                                      // else
        if(drive_forward_until_touch(-100, 1000)){                // drive backwards at 100 until touch or 2 sec
          setSuckSpeed(100,3000);                                 // collector scores at 100 speed for 3.0 seconds
        }
        drive_forward_msec(127,400);                              // drive forward at full power for 0.4 seconds
      } // END else
    } // END 1st if
  } // END while
} // END void



void redIntAutonomous2() {
   while(true) {
    if(SensorValue[AutonHigh] == 1) {                             // if btn autonHigh is pressed...
      if(SensorValue[solenoidL] == 0) {                           // if the arm is lowered...
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;      // raise the arm
        wait10Msec(50);                                           // wait no time
      } // END 2nd if
      else {                                                      // else
        drive_forward_msec(-127,1150);                            // drive backwards at full power for 1.15 seconds
        wait1Msec(1000);                                          // wait 1 second
        setSuckSpeed(100,3500);                                   // collector scores at 100 speed for 3.5 seconds
        drive_forward_msec(127,1000);                             // drive forward at full power for 0.5 seconds
      } // END else
    } // END 1st if

    if(SensorValue[AutonLow] == 1){                               // if btn autonLow is pressed...
      if(SensorValue[solenoidL] == 1){                            // if the arm is raised
        SensorValue[solenoidL] = SensorValue[solenoidR] = 0;      // lower the arm
        wait10Msec(50);                                           // wait .5 seconds
      } // END 2nd if
      else{                                                       // else
        drive_forward_msec(-127,350);                             // drive backwards at full power for 0.35 seconds
        drive_forward_msec(127,70);                               // drive forward at full power for 0.07 seconds
        setSuckSpeed(100,3000);                                   // collector scores at 100 speed for 3.0 seconds
        drive_forward_msec(127,400);                              // drive forward at full power for 0.4 seconds
      } // END else
    } // END 1st if
  } // END while
} // END void




void redIsoAutonomous() {
  while(true) {
    if(SensorValue[AutonHigh] == 1) {                             // if btn autonHigh is pressed...
      drive_collect_msec(127,127,3500);
      drive_forward_msec(-127,3500);
    }
    if(SensorValue[AutonLow] == 1){                               // if btn autonLow is pressed...
      if(SensorValue[solenoidL] == 0){
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;
        wait10Msec(50);
      } else {
        drive_forward_msec(-127, 1500);
        setSuckSpeed(100, 3000);
        drive_forward_msec(127, 1500);
      }
    } // END 1st if
  } // END while
} // END void




void redIsoAutonomous2() {
} // END void




void blueIntAutonomous(){
  while(true) {
    if(SensorValue[AutonHigh] == 1){                              // if btn autonHigh is pressed...
      if(SensorValue[solenoidL] == 0) {                           // if the arm is lowered...
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;      // raise the arm
        wait10Msec(50);                                           // wait no time
      } // END 2nd if
      else {                                                      // else
        if(drive_forward_until_touch(-127, 1500)){                // drive backwards at full power until touch or 2 sec
	        wait10Msec(50);                                         // wait 1 second
	        setSuckSpeed(100,3500);                                 // collector scores at 100 speed for 3.5 seconds
        }
        drive_forward_msec(127,1000);                             // drive forward at full power for 0.5 seconds
      } // END else
    } // END 1st if

    if(SensorValue[AutonLow] == 1)  {                             // if btn autonLow is pressed...
      if(SensorValue[solenoidL] == 1) {                           // if the arm is raised
        SensorValue[solenoidL] = SensorValue[solenoidR] = 0;      // lower the arm
        wait10Msec(50);                                           // wait .5 seconds
      } // END 2nd if
      else {                                                      // else
        if(drive_forward_until_touch(-100, 1000)){                // drive backwards at 100 until touch or 2 sec
          setSuckSpeed(100,3000);                                 // collector scores at 100 speed for 3.0 seconds
        }
        drive_forward_msec(127,400);                              // drive forward at full power for 0.4 seconds
      } // END else
    } // END 1st if
  } // END while
} // END void




void blueIntAutonomous2(){
while(true) {
    if(SensorValue[AutonHigh] == 1) {                             // if btn autonHigh is pressed...
      if(SensorValue[solenoidL] == 0) {                           // if the arm is lowered...
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;      // raise the arm
        wait10Msec(50);                                           // wait no time
      } // END 2nd if
      else {                                                      // else
        drive_forward_msec(-127,1150);                            // drive backwards at full power for 1.15 seconds
        wait1Msec(1000);                                          // wait 1 second
        setSuckSpeed(100,3500);                                   // collector scores at 100 speed for 3.5 seconds
        drive_forward_msec(127,1000);                             // drive forward at full power for 0.5 seconds
      } // END else
    } // END 1st if

    if(SensorValue[AutonLow] == 1){                               // if btn autonLow is pressed...
      if(SensorValue[solenoidL] == 1){                            // if the arm is raised
        SensorValue[solenoidL] = SensorValue[solenoidR] = 0;      // lower the arm
        wait10Msec(50);                                           // wait .5 seconds
      } // END 2nd if
      else{                                                       // else
        drive_forward_msec(-127,350);                             // drive backwards at full power for 0.35 seconds
        drive_forward_msec(127,70);                               // drive forward at full power for 0.07 seconds
        setSuckSpeed(100,3000);                                   // collector scores at 100 speed for 3.0 seconds
        drive_forward_msec(127,400);                              // drive forward at full power for 0.4 seconds
      } // END else
    } // END 1st if
  } // END while
} // END void




void blueIsoAutonomous(){
   while(true) {
    if(SensorValue[AutonHigh] == 1){                              // if btn autonHigh is pressed...
      drive_collect_msec(127,127,2500);
      drive_backward_msec(127,2500);
    }
    if(SensorValue[AutonLow] == 1){                               // if btn autonLow is pressed...
      if(SensorValue[solenoidL] == 0){
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;
        wait10Msec(50);
      } else {
        drive_forward_until_touch(-127, 2000);                    // Choses the red pill and allows us to enter the matrix
        setSuckSpeed(100, 3000);
        drive_forward_msec(127, 1500);
      }
    } // END 1st if
  } // END while*/
} // END while




void blueIsoAutonomous2(){
} // END void

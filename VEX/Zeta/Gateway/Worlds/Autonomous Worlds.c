void skillsAutonomous() {
setSuckSpeed(127,1000);
}

void redIntAutonomous() {
  while(true) {
    if(SensorValue[AutonHigh] == 1) {                             // if btn autonHigh is pressed...
      if(SensorValue[solenoidL] == 0) {                           // if the arm is lowered...
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;      // raise the arm
        wait10Msec(50);                                            // wait no time
      } // END 2nd if
      else {                                                      // else
        drive_forward_msec(-127,1150);                            // drive backwards at full power for 1.15 seconds
        wait1Msec(1000);                                          // wait 1 second
        setSuckSpeed(100,3500);                                   // collector scores at 100 speed for 3.5 seconds
        drive_forward_msec(127,1000);                             // drive forward at full power for 0.5 seconds
      } // END else
    } // END 1st if

    if(SensorValue[AutonLow] == 1)  {                             // if btn autonLow is pressed...
      if(SensorValue[solenoidL] == 1) {                           // if the arm is raised
        SensorValue[solenoidL] = SensorValue[solenoidR] = 0;      // lower the arm
        wait10Msec(50);                                           // wait .5 seconds
      } // END 2nd if
      else {                                                      // else
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
      if(SensorValue[solenoidL] == 0) {                           // if the arm is lowered...
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;      // raise the arm
        wait10Msec(0);                                            // wait no time
      } // END 2nd if
      else {                                                      // else
        drive_forward_msec(-127,1150);                            // drive backwards at full power for 1.15 seconds
        wait1Msec(1000);                                          // wait 1 second
        setSuckSpeed(100,3500);                                   // collector scores at 100 speed for 3.5 seconds
        drive_forward_msec(127,1000);                             // drive forward at full power for 0.5 seconds
      } // END else
    } // END 1st if

    if(SensorValue[AutonLow] == 1)  {                             // if btn autonLow is pressed...
      if(SensorValue[solenoidL] == 1) {                           // if the arm is raised
        SensorValue[solenoidL] = SensorValue[solenoidR] = 0;      // lower the arm
        wait10Msec(50);                                           // wait .5 seconds
      } // END 2nd if
      else {                                                      // else
        drive_forward_msec(-127,350);                             // drive backwards at full power for 0.35 seconds
        drive_forward_msec(127,70);                               // drive forward at full power for 0.07 seconds
        setSuckSpeed(100,3000);                                   // collector scores at 100 speed for 3.0 seconds
        drive_forward_msec(127,400);                              // drive forward at full power for 0.4 seconds
      } // END else
    } // END 1st if
  } // END while
} // END void

void blueIntAutonomous() {
  while(true) {
    if(SensorValue[AutonHigh] == 1) {                             // if btn autonHigh is pressed...
      if(SensorValue[solenoidL] == 0) {                           // if the arm is lowered...
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;      // raise the arm
        wait10Msec(0);                                            // wait no time
      } // END 2nd if
      else {                                                      // else
        drive_forward_msec(-127,1150);                            // drive backwards at full power for 1.15 seconds
        wait1Msec(1000);                                          // wait 1 second
        setSuckSpeed(100,3500);                                   // collector scores at 100 speed for 3.5 seconds
        drive_forward_msec(127,1000);                             // drive forward at full power for 0.5 seconds
      } // END else
    } // END 1st if

    if(SensorValue[AutonLow] == 1)  {                             // if btn autonLow is pressed...
      if(SensorValue[solenoidL] == 1) {                           // if the arm is raised
        SensorValue[solenoidL] = SensorValue[solenoidR] = 0;      // lower the arm
        wait10Msec(50);                                           // wait .5 seconds
      } // END 2nd if
      else {                                                      // else
        drive_forward_msec(-127,350);                             // drive backwards at full power for 0.35 seconds
        drive_forward_msec(127,70);                               // drive forward at full power for 0.07 seconds
        setSuckSpeed(100,3000);                                   // collector scores at 100 speed for 3.0 seconds
        drive_forward_msec(127,400);                              // drive forward at full power for 0.4 seconds
      } // END else
    } // END 1st if
  } // END while
} // END void

void blueIsoAutonomous() {
  while(true) {
    if(SensorValue[AutonHigh] == 1) {                             // if btn autonHigh is pressed...
      if(SensorValue[solenoidL] == 0) {                           // if the arm is lowered...
        SensorValue[solenoidL] = SensorValue[solenoidR] = 1;      // raise the arm
        wait10Msec(0);                                            // wait no time
      } // END 2nd if
      else {                                                      // else
        drive_forward_msec(-127,1150);                            // drive backwards at full power for 1.15 seconds
        wait1Msec(1000);                                          // wait 1 second
        setSuckSpeed(100,3500);                                   // collector scores at 100 speed for 3.5 seconds
        drive_forward_msec(127,1000);                             // drive forward at full power for 0.5 seconds
      } // END else
    } // END 1st if

    if(SensorValue[AutonLow] == 1)  {                             // if btn autonLow is pressed...
      if(SensorValue[solenoidL] == 1) {                           // if the arm is raised
        SensorValue[solenoidL] = SensorValue[solenoidR] = 0;      // lower the arm
        wait10Msec(50);                                           // wait .5 seconds
      } // END 2nd if
      else {                                                      // else
        drive_forward_msec(-127,350);                             // drive backwards at full power for 0.35 seconds
        drive_forward_msec(127,70);                               // drive forward at full power for 0.07 seconds
        setSuckSpeed(100,3000);                                   // collector scores at 100 speed for 3.0 seconds
        drive_forward_msec(127,400);                              // drive forward at full power for 0.4 seconds
      } // END else
    } // END 1st if
  } // END while
} // END void

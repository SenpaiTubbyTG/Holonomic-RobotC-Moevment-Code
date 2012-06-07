void autonHighLow() {

  wait1Msec(200);
  SensorValue[solenoidL] = SensorValue[solenoidR] = 1;  // raise lift
  while(SensorValue[startAuton] == 0);                  // wait until touch sensor startauton is pressed

  drive_forward_msec(-127,1150);                        // drive backwards at full power for 1.15 seconds

  wait1Msec(1000);                                      // wait 1 second
  setSuckSpeed(100,3500);                               // collector scores at 100 speed for 3.5 seconds

  drive_forward_msec(127,500);                          // drive forward at full power for 0.5 seconds

  SensorValue[solenoidL] = SensorValue[solenoidR] = 0;  // lowers lift

  drive_forward_msec(127,500);                          // drive forward at full power for 0.5 seconds (will end up back in starting square)

  while(SensorValue[startAuton] == 0);                  // wait until touch sensor startauton is pressed

  drive_forward_msec(-127,350);                         // drive backwards at full power for 0.35 seconds

  drive_forward_msec(127,70);                           // drive forward at full power for 0.07 seconds

  setSuckSpeed(100,3000);                               // collector scores at 100 speed for 3.0 seconds

  drive_forward_msec(127,400);                          // drive forward at full power for 0.4 seconds
}

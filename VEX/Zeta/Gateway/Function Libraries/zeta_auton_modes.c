///////////////AUTON MODES////////////////

/*Auton Houston 1*/
void autonHoustonOne() {
  //deploy collector extension
  suck_msec(FULL, 300);
  //wait for match loads & raise lift part of the way
  lift_msec_raw(FULL, 2800); //wait1Msec(2000);
  //drive backwards to low goal
  drive_msec(-FULL, 900);
  //raise lift the rest of the way
  lift_msec_raw(FULL, 2800);
  //spit out preload
  suck_msec(FULL, 4500);
  //return home
  drive_msec(FULL, 1000);
  //lower lift, load peices for small goal, aim at small goal
  lift_msec_raw(-FULL, 4000);
  //drive to small goal
  drive_msec(-FULL, 3500);
  //score low goal
  suck_msec(FULL, 5000); //
  //return home
  drive_msec(FULL, 300);  //20
  //If the rest of this is sped up then take a preload and put it in the floor goal or the  isolation zone
}
////

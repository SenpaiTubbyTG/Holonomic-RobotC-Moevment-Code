void ballBlock(int direction) {
    SensorValue[ballPneu] = direction;
}

//
void tensionCtrlAuton(int direction) {
    SensorValue[launchPneu] = direction;
}
/*
void telePneumatics() {
  if(vexRT[Btn6U] == 1){
    pneu1++;
    if(pneu1%2 == 0){
      SensorValue[ballPneu] = 1;
    }
    else {
      SensorValue[ballPneu] = 0;
    }
  }

//One Button Launch Pneu
void tensionCtrlTele(){

if(vexRT[Btn7U= 1){
  pneu2++;
  if(pneu2%2) {
    SensorValue[launchPneu] = 1;
  }
  else {
    SensorValue[launchPneu] = 0;
  }
 }
}
*/

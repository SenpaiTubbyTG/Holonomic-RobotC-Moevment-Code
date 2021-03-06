#pragma config(Motor,  port2,           DriveR,        tmotorNormal, openLoop)
#pragma config(Motor,  port3,           DriveL,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           BackR,         tmotorNormal, openLoop)
#pragma config(Motor,  port5,           BackL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           LaunchR,       tmotorNormal, openLoop)
#pragma config(Motor,  port7,           LaunchL,       tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main(){
  while(true){
    motor[DriveR] = vexRT[Ch2];
    motor[DriveL] = vexRT[Ch3];
    motor[BackR] = motor[BackL] = (vexRT[Btn5U]-vexRT[Btn5D])*127;
    motor[LaunchR] = motor[LaunchL] = (vexRT[Btn6U]-vexRT[Btn6D])*127;
  }
}

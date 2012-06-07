#pragma config(Motor,  port1,           ArmLL,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           DriveLF,       tmotorNormal, openLoop)
#pragma config(Motor,  port3,           DriveLB,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           DriveRF,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           DriveRB,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           ArmLU,         tmotorNormal, openLoop)
#pragma config(Motor,  port7,           ArmRU,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           collector1,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           collector2,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          ArmRL,         tmotorNormal, openLoop, reversed)



task main()
{
  while(true)
  {
   motor[DriveLF] = vexRT[Ch3];
   motor[DriveLB] = vexRT[Ch3];
   motor[DriveLF] = vexRT[Ch3];
   motor[DriveRB] = vexRT[Ch2];
   motor[armLL] = (vexRT[Btn6U] - vexRT[Btn6D])*127;
   motor[armLU] = (vexRT[Btn6U] - vexRT[Btn6D])*127;
   motor[ArmRL] = (vexRT[Btn6U] - vexRT[Btn6D])*127;
   motor[armRU] = (vexRT[Btn6U] - vexRT[Btn6D])*127;
   motor[collector1] = (vexRT[Btn5U] - vexRT[Btn5D])*127;
   motor[collector2] = (vexRT[Btn5U] - vexRT[Btn5D])*127;

   }

}

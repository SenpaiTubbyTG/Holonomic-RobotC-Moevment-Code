#pragma config(Motor,  port1,           ArmLL,         tmotorNormal, openLoop)
#pragma config(Motor,  port2,           DriveLF,       tmotorNormal, openLoop)
#pragma config(Motor,  port3,           DriveLB,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           DriveRF,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           DriveRB,       tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           ArmLU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           ArmRU,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port8,           collector1,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           collector2,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          ArmRL,         tmotorNormal, openLoop)

void autonomous1()
{
    wait10Msec(30);

    motor[ArmLL] = 100;
    motor[ArmRL] = 100;
    motor[ArmLU] = 100;
    motor[ArmRU] = 100;
    motor[DriveLF]= 100;
    motor[DriveLB]= 100;
    motor[DriveRB]= 100;
    motor[DriveRB]= 100;
    wait10Msec(65);

    motor[ArmLL] = 0;
    motor[ArmRL] = 0;
    motor[ArmLU] = 0;
    motor[ArmRU] = 0;

    wait10Msec(50);

    motor[DriveLF]= 0;
    motor[DriveLB]= 0;
    motor[DriveRB]= 0;
    motor[DriveRB]= 0;
    motor[collector1] = -100;
    motor[collector2] = -100;
    wait10Msec(500);

    motor[collector1] = 0;
    motor[collector2] = 0;
}
/*void autonomous2()
{
    wait10Msec(30);

    motor[ArmLL] = 100;
    motor[ArmRL] = 100;
    motor[ArmLU] = 100;
    motor[ArmRU] = 100;
    wait10Msec(30);

    motor[ArmLL] = 0;
    motor[ArmRL] = 0;
    motor[ArmLU] = 0;
    motor[ArmRU] = 0;
    motor[DriveLF]= 100;
    motor[DriveLB]= 100;
    motor[DriveRB]= 100;
    motor[DriveRB]= 100;
    wait10Msec(30);

    motor[DriveLF]= 0;
    motor[DriveLB]= 0;
    motor[DriveRB]= 0;
    motor[DriveRB]= 0;
    motor[collector1] = 100;
    motor[collector2] = 100;
    wait10Msec(500);

    motor[collector1] = 100;
    motor[collector2] = 100;
}
void autonomous3()
{
    wait10Msec(30);

    motor[ArmLL] = 100;
    motor[ArmRL] = 100;
    motor[ArmLU] = 100;
    motor[ArmRU] = 100;
    wait10Msec(30);

    motor[ArmLL] = 0;
    motor[ArmRL] = 0;
    motor[ArmLU] = 0;
    motor[ArmRU] = 0;
    motor[DriveLF]= 100;
    motor[DriveLB]= 100;
    motor[DriveRB]= 100;
    motor[DriveRB]= 100;
    wait10Msec(30);

    motor[DriveLF]= 0;
    motor[DriveLB]= 0;
    motor[DriveRB]= 0;
    motor[DriveRB]= 0;
    motor[collector1] = 100;
    motor[collector2] = 100;
    wait10Msec(500);

    motor[collector1] = 100;
    motor[collector2] = 100;
}
void autonomous4()
{
    wait10Msec(30);

    motor[ArmLL] = 100;
    motor[ArmRL] = 100;
    motor[ArmLU] = 100;
    motor[ArmRU] = 100;
    wait10Msec(30);

    motor[ArmLL] = 0;
    motor[ArmRL] = 0;
    motor[ArmLU] = 0;
    motor[ArmRU] = 0;
    motor[DriveLF]= 100;
    motor[DriveLB]= 100;
    motor[DriveRB]= 100;
    motor[DriveRB]= 100;
    wait10Msec(30);

    motor[DriveLF]= 0;
    motor[DriveLB]= 0;
    motor[DriveRB]= 0;
    motor[DriveRB]= 0;
    motor[collector1] = 100;
    motor[collector2] = 100;
    wait10Msec(500);

    motor[collector1] = 100;
    motor[collector2] = 100;
}*/

task main()
{
  while(true)
  {
    if(vexRT[Btn8U] == 1)
    {
      autonomous1();
    }
    /*if(vexRT[Btn8R] == 1)
    {
      autonomous2();
    }
    if(vexRT[Btn8D] == 1)
    {
      autonomous3();
    }
    if(vexRT[Btn8L] == 1)
    {
      autonomous4();
    }*/
  }
}

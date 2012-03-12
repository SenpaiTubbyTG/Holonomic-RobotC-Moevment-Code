task main()

{
  while (true)
  {
    motor[port2] = vexRT[Ch3];
    motor[port3] = vexRT[Ch3];
    motor[port4] = -vexRT[Ch3];
    motor[port5] =  -vexRT[Ch2];
    motor[port6] =  -vexRT[Ch2];
    motor[port7] =  vexRT[Ch2];
  }

}

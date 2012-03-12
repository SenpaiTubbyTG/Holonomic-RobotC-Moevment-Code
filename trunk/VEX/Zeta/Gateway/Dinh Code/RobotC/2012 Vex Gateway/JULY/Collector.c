task main()
{


  char power = 127;
  while (true)


  {
    switch(vexRT[Btn6U] - vexRT[Btn6D])
    {
    case 1:
      motor[port1] = 127;
      break;

    case 0:
      motor[port1] = 0;
      break;

    case -1:
      motor[port1] =-127;
      break;
    }//case2

    switch(vexRT[Btn5D] - vexRT[Btn5U])
    {
    case 1:
      motor[port2] = 127;
      motor[port3] = 127;
      break;

    case 0:
      motor[port2] = 0;
      motor[port3] = 0;
      break;
    case -1:
      motor[port2] = -power;
      motor[port3] = -power;
      break;

    }// 2nd case

  }//else
  //while
}//task main

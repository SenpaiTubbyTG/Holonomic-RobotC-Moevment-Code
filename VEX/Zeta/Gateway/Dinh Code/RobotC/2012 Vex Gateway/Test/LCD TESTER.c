//main code-to be placed in pre-auton section:
bLCDBacklight = true;
  displayLCDPos(0,0);
  displayNextLCDString("program select");
  redteam = true;
  screenrefresh();
  time1[T1] = 0;
  while (programselecting == true)
  {
    if (nLCDButtons & kLeftButton)
    {
      while (nLCDButtons & kLeftButton)
      {
      }
      if (redteam == true)
      {
        redteam = false;
      }
      else if (redteam == false)
      {
        redteam = true;
      }
      screenrefresh();
    }
    if (nLCDButtons & kCenterButton)
    {
      while (nLCDButtons & kCenterButton)
      {
      }
      programselect = programselect+1;
      if (programselect > totalprogramnumber)
      {
        programselect = 1;
      }
      screenrefresh();
    }
    if (nLCDButtons & kRightButton)
    {
      clearLCDLine(0);
      clearLCDLine(1);
      displayLCDPos(0,0);
      displayNextLCDString("Robot ready");
      wait1Msec(300);
      displayNextLCDString(".");
      wait1Msec(300);
      displayNextLCDString(".");
      wait1Msec(300);
      displayNextLCDString(".");
      wait1Msec(500);
      bLCDBacklight = false;
      programselecting = false;
    }
  }

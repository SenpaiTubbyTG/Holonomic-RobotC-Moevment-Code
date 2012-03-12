
void waitForPress()
{
  while(nLCDButtons == 0)
  {
    wait1Msec(5);
  }
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
  while(nLCDButtons != 0)
  {
    wait1Msec(5);
  }
}
//----------------------------------------------------------------

//Function to increment and decriment count - small savings on space
void menuTracker()
{
  if(nLCDButtons == leftButton)
  {
    waitForRelease();
    count--;
  }
  else if(nLCDButtons == rightButton)
  {
    waitForRelease();
    count++;
  }
}

void clearLCD()
{
  clearLCDLine(1);
  clearLCDLine(0);

}

void LCDER(string here)

{
  clearLCDLine(1);
  bLCDBacklight = true;
  displayLCDPos(1,11);
  displayNextLCDString(here);
}

void clearwhichline(char line)
{
clearLCDLine(line);

}








void RobotReady()
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
}


void Autonchooser()
{

  clearLCDLine(0);
  clearLCDLine(1);//clean up
  waitForRelease();

  while (on == false)
  {


    bLCDBacklight = true;
    switch (count){
    case 0:
      displayLCDCenteredString(0, "Isolation Zone");
      displayLCDCenteredString(1, "<    Enter     >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        clearLCD();
        on = true;
        waitForRelease();
        Iso = true;

        displayLCDCenteredString(0, "Isolation Zone");
        displayLCDCenteredString(1, "   Selected      ");
        wait1Msec(500);
      }

      else if(nLCDButtons == leftButton)
      {
        waitForRelease();
        count = 1;
      }

      else if(nLCDButtons == rightButton)
      {
        waitForRelease();
        count++;
      }
      break;



    case 1:
      displayLCDCenteredString(0, "Interaction Zone");
      displayLCDCenteredString(1, "<    Enter     >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        clearLCD();
        on = true;
        waitForRelease();
        Iso = false;
        displayLCDCenteredString(0, "Interaction Zone");
        displayLCDCenteredString(1, "    Selected        ");
        wait1Msec(500);
      }

      else if(nLCDButtons == rightButton)
      {
        waitForRelease();
        count = 0;
      }

      else if(nLCDButtons == leftButton)
      {
        waitForRelease();
        count--;
      }
      break;
    }//case








  }//while
  //----------------------------------------------------------------------
  //which color?
  count = 0;
  while(color == false)
  {


    bLCDBacklight = true;

    switch (count){

    case 0:
      displayLCDCenteredString(0, "Red Alliance");
      displayLCDCenteredString(1, "<     Enter    >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        clearLCD();
        color = true;
        waitForRelease();
        red = true;

        displayLCDCenteredString(0, "Red Alliance");
        displayLCDCenteredString(1, "   Selected      ");
        wait1Msec(500);
      }

      else if(nLCDButtons == leftButton)
      {
        waitForRelease();
        count = 1;
      }

      else if(nLCDButtons == rightButton)
      {
        waitForRelease();
        count++;
      }
      break;



    case 1:
      displayLCDCenteredString(0, "Blue Alliance");
      displayLCDCenteredString(1, "<     Enter    >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        clearLCD();
        color = true;
        waitForRelease();
        red = false;
        displayLCDCenteredString(0, "Blue Alliance");
        displayLCDCenteredString(1, "   Selected        ");
        wait1Msec(500);
      }

      else if(nLCDButtons == rightButton)
      {
        waitForRelease();
        count = 0;
      }

      else if(nLCDButtons == leftButton)
      {
        waitForRelease();
        count--;
      }
      break;


    }//Case
  }//while

  //-----------------------------------------------------------------------------
  //which auton?
  count = 0;
  while(Program == false)
  {
    switch(count){
    case 0:
      displayLCDCenteredString(0," Autonomous 1");
      displayLCDCenteredString(1,"<    Enter     >");
      waitForPress();
      if (nLCDButtons == centerButton)
      {
        waitForRelease();
        Program = true;
        programselect = 1;
        displayLCDCenteredString(0," Autonomous 1");
        displayLCDCenteredString(1," Selected    ");
        wait1Msec(1000);
        RobotReady();
      }

      else if(nLCDButtons == rightButton)
      {
        waitForRelease();
        count++;
      }

      else if(nLCDButtons == leftButton)
      {
        waitForRelease();
        count = 2;

      }
      break;

    case 1:
      displayLCDCenteredString(0," Autonomous 2");
      displayLCDCenteredString(1,"<    Enter     >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        waitForRelease();
        Program = true;
        programselect = 2;
        displayLCDCenteredString(0," Autonomous 2");
        displayLCDCenteredString(1," Selected    ");
        wait1Msec(1000);
        RobotReady();

      }
      else
      {
        menuTracker();
      }


      break;
    case 2:
      displayLCDCenteredString(0," Autonomous 3");
      displayLCDCenteredString(1,"<    Enter     >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        waitForRelease();
        Program = true;
        programselect = 3;
        displayLCDCenteredString(0," Autonomous 3");
        displayLCDCenteredString(1," Selected    ");
        wait1Msec(1000);
        RobotReady();


      }
      else if(nLCDButtons == leftButton)
      {
        waitForRelease();
        count-- ;
      }
      else if (nLCDButtons == rightButton)
      {
        waitForRelease();
        count =  0;

      }
      break;






    }//case


  }//3rd while
}
/*
The Following is a bit confusing so this comment should help...
Finder:1 = Isolation Zone red
Finder:2 = Interaction Zone red
Finder:3 = Isolation Zone Blue
Finder:4 = Interaction Zone Blue
*/
void Autonfilter()
{
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //Finder:1 Isolation Zone Red
  //-----------------------------------------------------------------------------------------
  if (Iso == true)// if your in the Isolation zone
    if (red == true)// and you are on the red team
    if (programselect == 1)//and program 1 is selected
  {
    Isolation_RED_Program = 1;// the make everything to this
  }



  if (Iso == true)
    if (red == true)
    if (programselect == 2)
  {
    Isolation_RED_Program = 2;
  }



  if (Iso == true)
    if (red == true)
    if (programselect == 3)
  {
    Isolation_RED_Program = 3;
  }
  /*
  ////////////////Above is the 3 autons////////////////////////////////////////////////////////////////
  ////////////////As long as your in the red zone
  ////////////////and you are in the Isolation zone then you can run the program above/////////////////
  */

  //Finder:2 Interaction Zone Red
  //------------------------------------------------------------------------------------
  if (Iso == false)
    if (red == true)
    if (programselect == 1)
  {
    Interaction_RED_Program = 1;
  }
  if (Iso == false)
    if (red == true)
    if (programselect == 2)
  {
    Interaction_RED_Program = 2;
  }

  if (Iso == false)
    if (red == true)
    if (programselect == 3)
  {
    Interaction_RED_Program = 3;
  }
  /*
  ///////////////Above is for is for the Interaction zone//////////////////////////////////////
  ////////////////also red = true//////////////////////////////////////////////////////////////


  //Finder:3 Isolation Zone Blue
  //-------------------------------------------------------------------------------------------
  */
  if (Iso == true)//isolation zone = true
    if (red == false)// red is false
    if (programselect == 1)
  {
    Isolation_BLUE_Program = 1;
  }

  if (Iso == true)
    if (red == false)
    if (programselect == 2)
  {
    Isolation_BLUE_Program = 2;
  }

  if (Iso == true)
    if (red == false)
    if (programselect == 3)
  {
    Isolation_BLUE_Program = 3;
  }

  ///////////Above is auton for Isolation and Blue/////////////////////////////////////////////////////////

  //Finder:4 Interaction Zone Blue
  //-----------------------------------------------------------------------------------------------
  if (Iso == false)
    if (red == false)
    if (programselect == 1)
  {
    Interaction_BLUE_Program = 1;
  }
  if (Iso == false)
    if (red == false)
    if (programselect == 2)
  {
    Interaction_BLUE_Program = 2;
  }

  if (Iso == false)
    if (red == false)
    if (programselect == 3)
  {
    Interaction_BLUE_Program = 3;
  }

}//end function

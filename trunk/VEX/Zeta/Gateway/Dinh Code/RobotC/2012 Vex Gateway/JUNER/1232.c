
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
short count = 0;
bool Iso = false;
bool on  = false;
bool red = false;
bool Program = false;
bool color = false;
int programselect = 0;

void waitForPress()
{
  while(nLCDButtons == 0);
  {
    wait1Msec(5);
  }
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
  while(nLCDButtons != 0);
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
  clearLCDLine(2);

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
        displayLCDCenteredString(0, "Isolation");
        displayLCDCenteredString(1, "<    Enter     >");
        waitForPress();
        if(nLCDButtons == centerButton)
        {
          clearLCD();
          on = true;
          waitForRelease();
          Iso = true;

          displayLCDCenteredString(0, "Isolation Zone");
          displayLCDCenteredString(1, "  Selected      ");
          wait1Msec(2000);
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
          Iso = true;
          displayLCDCenteredString(0, "Interaction Zone");
          displayLCDCenteredString(1, "    Selected        ");
          wait1Msec(2000);
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
          wait1Msec(2000);
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
          wait1Msec(2000);
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
      }

      else if(nLCDButtons == rightButton)
      {
       waitForRelease();
       count++;
      }

      else if(nLCDButtons == leftButton)
      {
      waitForRelease();
      count = 9;

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

      }
      else
      {
      menuTracker();
      }

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

      }

      else
      {
      menuTracker();
      }
       break;

        case 3:
        displayLCDCenteredString(0," Autonomous 4");
      displayLCDCenteredString(1,"<    Enter     >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        waitForRelease();
        Program = true;
        programselect = 4;
         displayLCDCenteredString(0," Autonomous 4");
         displayLCDCenteredString(1," Selected    ");

      }
      else
      {
      menuTracker();
      }
       break;

        case 4:
        displayLCDCenteredString(0," Autonomous 5");
      displayLCDCenteredString(1,"<    Enter     >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        waitForRelease();
        Program = true;
        programselect = 5;
         displayLCDCenteredString(0," Autonomous 5");
         displayLCDCenteredString(1," Selected    ");

      }
      else
      {
      menuTracker();
      }
       break;

        case 5:
        displayLCDCenteredString(0," Autonomous 6");
      displayLCDCenteredString(1,"<    Enter     >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        waitForRelease();
        Program = true;
        programselect = 6;
         displayLCDCenteredString(0," Autonomous 6");
         displayLCDCenteredString(1," Selected    ");

      }
      else
      {
      menuTracker();
      }
       break;

        case 6:
        displayLCDCenteredString(0," Autonomous 7");
      displayLCDCenteredString(1,"<    Enter     >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        waitForRelease();
        Program = true;
        programselect = 7;
         displayLCDCenteredString(0," Autonomous 7");
         displayLCDCenteredString(1," Selected    ");

      }
      else
      {
      menuTracker();
      }
       break;

       case 7:
        displayLCDCenteredString(0," Autonomous 8");
      displayLCDCenteredString(1,"<    Enter     >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        waitForRelease();
        Program = true;
        programselect = 8;
         displayLCDCenteredString(0," Autonomous 8");
         displayLCDCenteredString(1," Selected    ");

      }
      else
      {
      menuTracker();
      }
       break;
       case 8:
        displayLCDCenteredString(0," Autonomous 9");
      displayLCDCenteredString(1,"<    Enter     >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        waitForRelease();
        Program = true;
        programselect = 9;
         displayLCDCenteredString(1," Autonomous 9");
         displayLCDCenteredString(0," Selected    ");

      }
      else
      {
      menuTracker();
      }
       break;




        case 9:
        displayLCDCenteredString(1," Autonomous 10");
      displayLCDCenteredString(0,"<    Which Program     >");
      waitForPress();
      if(nLCDButtons == centerButton)
      {
        waitForRelease();
        Program = true;
        programselect = 10;
         displayLCDCenteredString(1," Autonomous 10");
         displayLCDCenteredString(0," Selected    ");
         wait1Msec(1000);
         clearLCD();
         displayLCDCenteredString(1, "Robot Ready");
         displayLCDCenteredString(1, "           .");
         wait1Msec(300);
           displayLCDCenteredString(1, "            .");
         wait1Msec(300);

           displayLCDCenteredString(1, "             .");
         wait1Msec(300);


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

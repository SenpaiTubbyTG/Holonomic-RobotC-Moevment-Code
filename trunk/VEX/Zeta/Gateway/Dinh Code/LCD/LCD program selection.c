/*
there are three parts to the LCD program selectition code.
first are the variable definitions.
secondly, there is a screen refresh function, to be placed with your other
voids/functions.
and lastly, there is the LCD code itself.
place this in your pre-auton section.
The code will output two variables:
redteam is the boolean variable that will output true or false
programselect is the program number you have selected.
totalprogramnumber is the constant you should modify right at the start.
this is the amount of programs you are loading.
*/


//variables:
int programselect = 1;
bool redteam = true;
bool programselecting = true;
const int totalprogramnumber = 5;

//function:
void screenrefresh()
{
  clearLCDLine(1);
  displayLCDPos(1,0);
  if (redteam == true)
  {
    displayNextLCDString("RED ");
  }
  if (redteam == false)
  {
    displayNextLCDString("BlUE");
  }
  displayNextLCDString("    ");
  displayNextLCDNumber(programselect);
  displayNextLCDString("     OK");
}


//main code-to be placed in pre-auton section:
bLCDBacklight = true;
  displayLCDPos(0,0);
  displayNextLCDString("program select");
  redteam = true;
  screenrefresh();
  time1[T1] = 0;
  while (programselecting == true)  {
    if (nLCDButtons & kLeftButton)  {
      while (nLCDButtons & kLeftButton)  {
      }
      if (redteam == true)  {
        redteam = false;
      }
      else if (redteam == false)  {
        redteam = true;
      }
      screenrefresh();
    }
    if (nLCDButtons & kCenterButton)  {
      while (nLCDButtons & kCenterButton)  {
      }
      programselect = programselect+1;
      if (programselect > totalprogramnumber)
      {
        programselect = 1;
      }
      screenrefresh();
    }
    if (nLCDButtons & kRightButton)  {
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

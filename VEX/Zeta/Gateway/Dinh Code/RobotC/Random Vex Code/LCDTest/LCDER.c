



const int number = 5;
bool red = false;
bool Isolation ;
short centerbutton = 2;
short RightButton = 4;
short LeftButton = 1;
int zone = 1;
bool zoner = false;
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





  void Interationpicker(int Zonenumber)
{
    clearLCDLine(1);
  displayLCDPos(1,0);
  displayNextLCDString("<  Interaction  >");
          Isolation = false;
          zone = Zonenumber;

}

void Isolationpicker(int Zonenumber)
{
  clearLCDLine(1);
    displayLCDPos(1,0);
  displayNextLCDString("<  Isolation  >");
          Isolation = true;
          zone = Zonenumber;

}

void waitForRelease()
{
  while(nLCDButtons != 0);
  {
    wait1Msec(5);
  }
}

void waitForPress()
{
  while(nLCDButtons == 0);
  {
    wait1Msec(5);
  }
}

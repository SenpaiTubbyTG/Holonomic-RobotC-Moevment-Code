
const int number = 5;
bool red = false;
bool Isolation = false ;
short centerbutton = 2;
short RightButton = 4;
short LeftButton = 1;
int zone = 1;
bool zoner = false;


void Interationpicker (int Zonenumber)
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

/*void LCDpick();
{

  while(zoner = false)
    {
      if(nLCDButtons == LeftButton && zone == 0 || zone == 1)
        {
        Isolationpicker(2);//if left is pressed then make zone to two...

        }

       else if(nLCDButtons == LeftButton && zone == 2)
        {
         Interationpicker(1);
        }

        else if(nLCDButtons == LeftButton && zone == 2)
        {
         Isolationpicker(2);
        }


         else if(nLCDButtons == LeftButton && zone == 2)
        {
         Interationpicker(1);
        }

        else if(nLCDButtons == centerbutton)
        {
          clearLCDLine(1);
         zoner = true;//gets outta loop
         displayLCDCenteredString(1, "DONE!");
         wait1Msec(300);

        }
      }

}*/

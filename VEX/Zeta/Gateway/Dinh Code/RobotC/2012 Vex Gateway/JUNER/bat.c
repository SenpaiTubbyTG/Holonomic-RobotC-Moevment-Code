

//int arm_grounded;



//variables:



void LCD(){

{
    clearLCDLine(0);
    clearLCDLine(1);                                      // Clear LCD Bottom Line
    displayLCDPos(1,0);                                   // Set the cursor to bottom line, first position
    displayNextLCDString("Arm: ");                   // Print "Potentio: " starting at the cursor position
    displayNextLCDNumber(SensorValue(ncoderR));    // Display the reading of the Potentiometer to current cursor position
    displayLCDPos(0,5);
    displayNextLCDString("Touch: ");
    displayNextLCDNumber(SensorValue(touchh));

}
}

void LCDER(string here, short position1, short position2)
{
  {
          clearLCDLine(1);
          bLCDBacklight = true;
          displayLCDPos(position1,postition 2);
          displayNextLCDString(here);
}
}
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

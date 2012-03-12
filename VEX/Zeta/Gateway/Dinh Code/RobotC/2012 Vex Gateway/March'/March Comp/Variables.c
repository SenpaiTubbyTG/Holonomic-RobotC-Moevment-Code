//LCD STUFF///////////////
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
short count = 0;
bool Iso = false;
bool on  = false;
bool red = false;
bool Program = false;
bool color = false;
char programselect = 0;//save space
bool stall = false;
short Isolation_RED_Program = 0;
short Interaction_RED_Program = 0;
short Isolation_BLUE_Program = 0;
short Interaction_BLUE_Program = 0;
///OTHER STUFF//////////////
const int left = 1;
const int right = 2;
const int full = 127;
int typeDrive = 1;
const int Drive = 1;
const int tracDrive = 2;

////////////////////////////////////////Arm values/////////////////////////////////////////////
const short ten_inch_goal = 400;
const short twenty_inch_goal = 875;
const short thirty_inch_goal = 1510;




 /////////////////////////////////////////////////////////////////////////
 //CASES
const char down = 0;// case down
 const char up = 1;//case up
 const char gravityNot = 4;// Make the arm come down on the lift func.
 const char lowgoal = 0;//stuff for cases
 const char medgoal = 1;
 const char highgoal = 2;//junk
  short direction;//direction for robot
int full = 127;

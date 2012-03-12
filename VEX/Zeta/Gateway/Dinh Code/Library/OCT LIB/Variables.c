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

 //////////////////////encoder...///////////////////////////////////////
// int prevencodervalue = 0;
 //int armencodervalue = 0;
 //////////////////////////////////////////////////////////////////

 ///////////////////////////Line tracker Vairables below...//////////////////////////////////////
 /*
short brightest = 1024;
short i = 0;
short lineaverage;
short lasttask;
bool junction = false;
const char left = 0;
const char right = 1;
//const int center = 2;
const bool front = true;
const bool back = false;
*/






////////////////////////////////////////Arm values/////////////////////////////////////////////
const short ten_inch_goal = 630;
const short twenty_inch_goal = 950;
const short thirty_inch_goal = 1500;




 /////////////////////////////////////////////////////////////////////////
 //CASES
const char down = 0;// case down
 const char up = 1;//case up
 const char gravityNot = 4;// Make the arm come down on the lift func.
 const char lowgoal = 0;//stuff for cases
 const char medgoal = 1;
 const char highgoal = 2;//junk
  short direction;//direction for robot
  const bool right = false;//left and right on the Gyro. we may use it for  encoder.
  const bool left = true;
  int full = 127;
  bool Start = false;



 ///////////////////////////////////////////////////////////////////
 //DriveTrain Constant Variables

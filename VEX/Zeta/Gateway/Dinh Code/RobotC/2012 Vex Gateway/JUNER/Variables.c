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
 int prevencodervalue = 0;
 int armencodervalue = 0;
 //////////////////////////////////////////////////////////////////

 ///////////////////////////Line tracker Vairables below...//////////////////////////////////////
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







////////////////////////////////////////Arm values/////////////////////////////////////////////
const short ten_inch_goal = 320;
const short twenty_inch_goal = 420;
const short thirty_inch_goal = 220;
const short all_the_way_down = 0;


 /////////////////////////////////////////////////////////////////////////
 //CASES
 const char down = 0;// case down
 const char up = 1;//case up
 const char lowgoal = 0;//stuff for cases
 const char mediumgoal = 1;
 const char highgoal = 2;
 const char gravitating = 3;


 ///////////////////definitions for sensors ////////////////////////////////////////////////
short armenc = SensorValue[Encoderarm];
 short rightenc = SensorValue[EncoderLeft];
 short leftenc = SensorValue[EncoderRight];
 char touchhigh = SensorValue[touchh];
 char touchlow = SensorValue[touchl];
 short counter = SensorValue[Tubecounter];
////////////////////////////////////////////////////////////////



 ///////////////////////////////////////////////////////////////////
 //DriveTrain Constant Variables

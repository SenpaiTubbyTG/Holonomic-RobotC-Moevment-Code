// main.h
#ifndef _main_h_
#define _main_h_

#include "API.h"
#include "UserInclude.h"


#define Descore_Wall_Goal   109
#define Movable_Weighted_Base   136
#define Descore_Movable_Weighted_Base   39
#define Wall_Goal   171
#define Ladder  213
#define Manual  7
#define Threshold   400
#define Forward 3
#define Dead_Zone   6
#define Brake   15
#define Pickup  -1  //!= 0
#define Back    2
#define Moving  10
#define On  1
#define Off 0
#define Ready   11
#define Line_Track  10
#define Drive   13
#define Encoder_Track   11
#define Wall_Track  12
#define Script_Ready    22
#define Line    16
#define Coast   21
#define Lift_Ready  14
#define No_Line 18
#define Cross_Line  17
#define Right   19
#define Left    20
#define Gripper_Time    150
#define Tube    26
#define Right_Encoder_Track 27
#define Left_Encoder_Track  28
#define Proximity   29
#define Match   30
#define RSC 31
#define Infield 32
#define Outfield    33
#define Red 24
#define Blue    25
#define PSC 34
#define Line2   35
#define No_Line2    36
#define Ultrasonic_Time 50
#define Lift_C  13
#define Descore_Wall_Goal2  87
#define Ready2  55

extern double Ch4 ; //Joystick Channel 4
extern double Ch3 ; //Joystick Channel 3
extern unsigned char Ch6u ; //Joystick Channel 6 - Up Button
extern unsigned char Ch5u ; //Joystick Channel 5 - Up Button
extern unsigned char Ch7u ; //Joystick Channel 7 - Up Button
extern unsigned char Ch6d ; //Joystick Channel 6 - Down Button
extern int Ch7r ; //Joystick Channel 7 - Right Button
extern unsigned char Ch7l ; //Joystick Channel 7 - Left Button
extern unsigned char Ch5d ; //Joystick Channel 5 - Down Button
extern unsigned char Ch7d ; //Joystick Channel 7 - Down Button
extern unsigned char Ch8u ; //Joystick Channel 8 - Up Button
extern unsigned char Ch8d ; //Joystick Channel 8 - Down Button
extern unsigned char Ch8r ; //Joystick Channel 8 - Right Button
extern int Left_Line ; //Left Line Sensor
extern int Center_Line ; //Center Line Sensor
extern int Right_Line ; //Right Line Sensor
extern unsigned char Ch8l ; //Joystick Channel 8 - Left Button
extern long Right_Encoder ; //Right Drive Encoder
extern int Error ;
extern int Lift_Encoder ; //Lift Encoder
extern long Left_Encoder ; //Left Drive Encoder
extern char Gripper ;
extern int Lift_Status ;
extern int Lift_Setpoint ;
extern int Script ;
extern int Gripper_Limit ;
extern float Angle ;
extern float Timer1 ;
extern int Timer2 ;
extern int Timer4 ;
extern char Mode ;
extern int Timer5 ;
extern char Armed2 ;
extern int Stage ;
extern char Tilt ;
extern int Lift_Motor ;
extern float Left_Motor ;
extern int Ultrasonic ;
extern float Right_Motor ;
extern int LF_Line ;
extern int Lift_Limit ;
extern float Left_Error ;
extern char Armed1 ;
extern char Right_Motor_Status ;
extern char Armed3 ;
extern float Ultrasonic_Error ;
extern char Left_Motor_Status ;
extern float I_Error ;
extern float Right_Error ;
extern float D_Error ;
extern char Last_Line ;
extern float D_Out ;
extern float I_Out ;
extern float P_Out ;
extern float Last_Error ;
extern float Output ;
extern int Left_Pot ;
extern int Line_Position ;
extern int Secondary_Script ;
extern int Event ;
extern int Right_Pot ;
extern int Alliance ;
extern int Position ;
extern int Autonomous_Code ;
extern int Last_Left_Pot ;
extern int Last_Right_Pot ;
extern int Ch6u_Armed ;
extern int Ch6d_Armed ;
extern int Lift_Reset ;
extern int Last_Goal ;
extern int Ch5d_Armed ;
extern int Hang ;
extern int Timer6 ;
extern int Finish_Time ;
extern int Preload ;
extern int Ultra ;
extern unsigned char B1 ;
extern unsigned char B2 ;
extern unsigned char B3 ;
extern int Descore_Armed ;

void Initialize ( void ) ;
void Autonomous ( unsigned long ulTime ) ;
void OperatorControl ( unsigned long ulTime ) ;
void Driver_Control ( void ) ;
void Motor_Drive ( void ) ;
void Script_Functions ( void ) ;
void Autonomous_Control ( int Navigation_Type, float Left_Motor_Setpoint, float Right_Motor_Setpoint, int Left_Encoder_Setpoint, int Right_Encoder_Setpoint, int Ultrasonic_Direction, int Ultrasonic_Setpoint, int Lift_Height_Setpoint, int Gripper_Setpoint, int Script_Setpoint, int Tilt_Setpoint, int Max_Time, int Min_Time, int Stop, int Break_Option ) ;
void Programming_Skills_Challenge ( void ) ;
void High_Hang ( void ) ;
void Auton_Routines ( void ) ;
void User_Settings ( void ) ;

#endif // _main_h_

// Globals.c start
#include "Main.h"

double Ch4; // Joystick Channel 4
double Ch3; // Joystick Channel 3
unsigned char Ch6u; // Joystick Channel 6 - Up Button
unsigned char Ch5u = 0; // Joystick Channel 5 - Up Button
unsigned char Ch7u; // Joystick Channel 7 - Up Button
unsigned char Ch6d; // Joystick Channel 6 - Down Button
int Ch7r; // Joystick Channel 7 - Right Button
unsigned char Ch7l; // Joystick Channel 7 - Left Button
unsigned char Ch5d = 0; // Joystick Channel 5 - Down Button
unsigned char Ch7d; // Joystick Channel 7 - Down Button
unsigned char Ch8u; // Joystick Channel 8 - Up Button
unsigned char Ch8d; // Joystick Channel 8 - Down Button
unsigned char Ch8r; // Joystick Channel 8 - Right Button
int Left_Line; // Left Line Sensor
int Center_Line; // Center Line Sensor
int Right_Line; // Right Line Sensor
unsigned char Ch8l; // Joystick Channel 8 - Left Button
long Right_Encoder; // Right Drive Encoder
int Error;
int Lift_Encoder; // Lift Encoder
long Left_Encoder; // Left Drive Encoder
char Gripper = Off;
int Lift_Status = Ready;
int Lift_Setpoint = Pickup;
int Script = 0;
int Gripper_Limit;
float Angle;
float Timer1;
int Timer2;
int Timer4 = 0;
char Mode = Manual;
int Timer5;
char Armed2 = On;
int Stage = 0;
char Tilt = Forward;
int Lift_Motor = 0;
float Left_Motor;
int Ultrasonic;
float Right_Motor;
int LF_Line;
int Lift_Limit = 0;
float Left_Error;
char Armed1 = On;
char Right_Motor_Status;
char Armed3 = On;
float Ultrasonic_Error;
char Left_Motor_Status;
float I_Error = 0;
float Right_Error;
float D_Error = 0;
char Last_Line = -3;
float D_Out;
float I_Out;
float P_Out;
float Last_Error = 0;
float Output = 0;
int Left_Pot;
int Line_Position;
int Secondary_Script = Off;
int Event = 1;
int Right_Pot;
int Alliance = 0;
int Position = 1;
int Autonomous_Code = 0;
int Last_Left_Pot = -1;
int Last_Right_Pot = -1;
int Ch6u_Armed = On;
int Ch6d_Armed = On;
int Lift_Reset = Off;
int Last_Goal = Movable_Weighted_Base;
int Ch5d_Armed = On;
int Hang = Off;
int Timer6;
int Finish_Time = 0;
int Preload = On;
int Ultra = Off;
unsigned char B1 = 0;
unsigned char B2 = 0;
unsigned char B3 = 0;
int Descore_Armed = Off;

// Globals.c end

#include "Main.h"

void main ( void )
{
      Initialize ( ) ;
      Autonomous ( 0 ) ;
      OperatorControl ( 0 ) ;
}

void Initialize ( void )
{
      InitLCD ( 2 ) ;
      SetLCDLight ( 2 , 1 ) ;
      StartLCDButtonsWatcher ( 2 ) ;
      StartQuadEncoder ( 9 , 10 , 0 ) ;
      StartQuadEncoder ( 5 , 6 , 0 ) ;
      StartQuadEncoder ( 7 , 8 , 0 ) ;
      StartTimer ( 1 ) ; // Match Clock
      StartTimer ( 2 ) ; // Autonomous Control
      StartTimer ( 4 ) ; // Script_Functions
      StartTimer ( 5 ) ; // PID
      StartTimer ( 6 ) ; // Ultrasonics
      PresetQuadEncoder ( 9 , 10 , 0) ;
      while ( ! IsEnabled() )
      {
            GetLCDButtonsWatcher ( 2 , &B1 , &B2 , &B3 ) ;
            User_Settings ( ) ;
            if ( B1 == 0 && B2 == 1 && B3 == 0 )
            {
                  GlobalData(1) = Off ;
                  SetLCDText ( 2 , 1 , "" ) ;
                  SetLCDText ( 2 , 2 , "" ) ;
                  SetLCDLight ( 2 , 0 ) ;
                  break ;
            }
      }
      if ( Position == Outfield && Autonomous_Code == 1 )
      {
            Gripper = On ;
            SetDigitalOutput ( 11 , On ) ;
      }
}

void Autonomous ( unsigned long ulTime )
{
      User_Settings ( ) ;
      SetLCDText ( 2 , 1 , "" ) ;
      SetLCDText ( 2 , 2 , "" ) ;
      SetLCDLight ( 2 , 0 ) ;
      PresetTimer ( 1 , 0 ) ;
      Auton_Routines (   ) ;
      Timer1 = GetTimer ( 1 ) ;
      SetMotor ( 1 , 0 ) ;
      SetMotor ( 2 , 0 ) ;
      SetMotor ( 3 , 0 ) ;
      SetMotor ( 4 , 0 ) ;
      SetMotor ( 5 , 0 ) ;
      SetMotor ( 6 , 0 ) ;
      SetMotor ( 7 , 0 ) ;
      SetMotor ( 8 , 0 ) ;
      SetMotor ( 9 , 0 ) ;
      SetMotor ( 10 , 0 ) ;
      SetLCDText ( 2 , 2 , "Time = %.1f sec" , (float)(Timer1 / 1000) ) ;
}


void OperatorControl ( unsigned long ulTime )
{
      User_Settings ( ) ;
      SetLCDText ( 2 , 1 , "" ) ;
      SetLCDText ( 2 , 2 , "" ) ;
      SetLCDLight ( 2 , 0 ) ;
      PresetTimer ( 1 , 0 ) ;
      Driver_Control ( ) ;
      Timer1 = GetTimer ( 1 ) ;
      SetMotor ( 1 , 0 ) ;
      SetMotor ( 2 , 0 ) ;
      SetMotor ( 3 , 0 ) ;
      SetMotor ( 4 , 0 ) ;
      SetMotor ( 5 , 0 ) ;
      SetMotor ( 6 , 0 ) ;
      SetMotor ( 7 , 0 ) ;
      SetMotor ( 8 , 0 ) ;
      SetMotor ( 9 , 0 ) ;
      SetMotor ( 10 , 0 ) ;
      SetLCDText ( 2 , 2 , "Time = %.1f sec" , (float)(Finish_Time / 1000) ) ;
}

#include "Main.h"

void User_Settings ( void )
{
      Left_Pot = GetAnalogInput ( 5 ) ;
      Left_Pot = (Left_Pot/190) ;
      Right_Pot = GetAnalogInput ( 6 ) ;
      Right_Pot = (Right_Pot/190) ;
      if ( Left_Pot != Last_Left_Pot || Last_Right_Pot != Right_Pot  )
      {
            if ( Left_Pot == 0  )
            {
                  Event = Match ;
                  Alliance = Red ;
                  Position = Infield ;
                  SetLCDText ( 2 , 1 , " Red Infield" ) ;
            }
            if ( Left_Pot == 1  )
            {
                  Event = Match ;
                  Alliance = Blue ;
                  Position = Infield ;
                  SetLCDText ( 2 , 1 , " Blue Infield" ) ;
            }
            if ( Left_Pot == 2  )
            {
                  Event = Match ;
                  Alliance = Red ;
                  Position = Outfield ;
                  SetLCDText ( 2 , 1 , " Red Outfield" ) ;
            }
            if ( Left_Pot == 3  )
            {
                  Event = Match ;
                  Alliance = Blue ;
                  Position = Outfield ;
                  SetLCDText ( 2 , 1 , " Blue Outfield" ) ;
            }
            if ( Left_Pot == 4  )
            {
                  SetLCDText ( 2 , 1 , "     Robot" ) ;
                  SetLCDText ( 2 , 2 , "Skills Challenge" ) ;
                  Event = RSC ;
                  Alliance = 0 ;
                  Position = 0 ;
                  Autonomous_Code = 0 ;
            }
            if ( Left_Pot >= 5 )
            {
                  SetLCDText ( 2 , 1 , "  Programming   " ) ;
                  SetLCDText ( 2 , 2 , "Skills Challenge" ) ;
                  Event = PSC ;
                  Alliance = 0 ;
                  Position = 0 ;
                  if ( Right_Pot < 3 )
                  {
                        Autonomous_Code = 2 ;
                  }
                  if ( Right_Pot >= 3 )
                  {
                        Autonomous_Code = 1 ;
                  }
            }
            if ( Right_Pot >= 5 && Event == Match )
            {
                  Autonomous_Code = 1 ;
                  SetLCDText ( 2 , 2 , " Autonomous #1" ) ;
            }
            if ( Right_Pot == 4 && Event == Match )
            {
                  Autonomous_Code = 2 ;
                  SetLCDText ( 2 , 2 , " Autonomous #2" ) ;
            }
            if ( Right_Pot == 3 && Event == Match )
            {
                  Autonomous_Code = 3 ;
                  SetLCDText ( 2 , 2 , " Autonomous #3" ) ;
            }
            if ( Right_Pot == 2 && Event == Match )
            {
                  Autonomous_Code = 4 ;
                  SetLCDText ( 2 , 2 , " Autonomous #4" ) ;
            }
            if ( Right_Pot == 1 && Event == Match )
            {
                  Autonomous_Code = 5 ;
                  SetLCDText ( 2 , 2 , " Autonomous #5" ) ;
            }
            if ( Right_Pot == 0 &&  Event == Match )
            {
                  Autonomous_Code = 0 ;
                  SetLCDText ( 2 , 2 , " Autonomous OFF" ) ;
            }
      }
      Last_Left_Pot = Left_Pot ;
      Last_Right_Pot = Right_Pot ;
}
#include "Main.h"

void Auton_Routines ( void )
{
      if ( Autonomous_Code == Off )
      {
      }
      if ( Event == Match && Position == Infield && Autonomous_Code == 1 )
      {
            Autonomous_Control ( Encoder_Track, 63, 63, 41, 41, 0, 0, Movable_Weighted_Base, On, 0, 0, 500, 0, Brake, Encoder_Track ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, -15, 63, 0, 198, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Right_Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, 63, -15, 180, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Left_Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 1200, 0, Coast, Lift_Ready ) ;
            Autonomous_Control ( Drive, 63, 63, 93, 93, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Movable_Weighted_Base, On, Movable_Weighted_Base, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 150 ) ; // #1
            Autonomous_Control ( Line_Track, 63, 63, -90, -90, 0, 0, 0, 0, 0, 0, 2000, 0, Brake, Encoder_Track ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Drive, -63, 10, -117, 0, 0, 0, Pickup, 0, 0, 0, 2500, 0, 0, Left_Encoder_Track ) ;
                  Autonomous_Control ( Encoder_Track, -63, 63, -237, 237, 0, 0, Pickup, 0, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 300, 300, Left, 4, Pickup, 0, 0, 0, 3000, 0, 0, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 0, 0, Left, 4, Pickup, 0, 0, 0, 3000, 100, 0, No_Line ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 254, 254, Left, 4, Pickup, 0, 0, 0, 4000, 0, 0, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 95, 95, Left, 4, Pickup, Ready2, 0, 0, 4000, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Encoder_Track, -63, 10, -397, 0, 0, 0, Wall_Goal, On, 0, 0, 2000, 0, Brake, Left_Encoder_Track ) ;
                  Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 3000, 0, 0, Lift_Ready ) ;
                  Autonomous_Control ( Wall_Track, 50, 50, 0, 0, Right, 38, Wall_Goal, On, 0, 0, 1100, 0, Coast, 0 ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, 10, -63, 0, -119, 0, 0, Pickup, 0, 0, 0, 2500, 0, 0, Right_Encoder_Track ) ;
                  Autonomous_Control ( Encoder_Track, 63, -63, 235, -235, 0, 0, Pickup, 0, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 300, 300, Right, 4, Pickup, 0, 0, 0, 3000, 0, 0, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 0, 0, Right, 4, Pickup, 0, 0, 0, 3000, 100, 0, No_Line ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 250, 250, Right, 4, Pickup, 0, 0, 0, 4000, 0, 0, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 95, 95, Right, 4, Pickup, Ready2, 0, 0, 4000, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Encoder_Track, 10, -63, 0, -387, 0, 0, Wall_Goal, On, 0, 0, 2000, 0, Brake, Right_Encoder_Track ) ;
                  Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 3000, 0, 0, Lift_Ready ) ;
                  Autonomous_Control ( Wall_Track, 50, 50, 0, 0, Left, 38, Wall_Goal, On, 0, 0, 1100, 0, 0, 0 ) ;
            }
            Autonomous_Control ( Drive, 20, 20, 0, 0, 0, 0, Wall_Goal, On, Wall_Goal, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 500 ) ; // #2
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, (Descore_Wall_Goal + 20), 0, 0, 0, 1500, 0, Coast, Lift_Ready ) ;
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, 0, 0, Descore_Wall_Goal, 0, 2000, 0, Coast, Script_Ready ) ;
            Autonomous_Control ( Encoder_Track, -63, -63, -50, -50, 0, 0, Wall_Goal, On, 0, 0, 2000, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Encoder_Track, -63, -63, -80, -80, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, Brake, Encoder_Track ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, 63, -63, 371, -371, 0, 0, Movable_Weighted_Base, On, 0, 0, 1800, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 75, 75, 370, 370, Left, 39, Movable_Weighted_Base, On, 0, 0, 3000, 0, 0, Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, -63, 63, -395, 395, 0, 0, Movable_Weighted_Base, On, 0, 0, 1800, 0, Brake, Left_Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 75, 75, 370, 370, Right, 39, Movable_Weighted_Base, On, 0, 0, 3000, 0, 0, Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, (Movable_Weighted_Base - 55), On, 0, 0, 2000, 0, Coast, Lift_Ready ) ;
            Autonomous_Control ( Drive, -80, -80, -100, -100, 0, 0, Pickup, 0, 0, 0, 2000, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Pickup, 0, 0, 0, 2000, 0, 0, Lift_Ready ) ;
      }
      if ( Event == Match && Position == Infield && Autonomous_Code == 2 )
      {
            Autonomous_Control ( Drive, -110, -110, 0, 0, 0, 0, 100, On, 0, 0, 2000, 250, 0, No_Line ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, -70, -70, -564, -564, 0, 0, 100, On, 0, 0, 3500, 0, Brake, Left_Encoder_Track ) ;
                  Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, 0, On, 0, 0, 350, 0, Coast, 0 ) ;
                  Autonomous_Control ( Encoder_Track, -15, 70, 0, 392, 0, 0, Movable_Weighted_Base, On, 0, 0, 2500, 0, Brake, Right_Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 340, 340, Left, 39, Movable_Weighted_Base, On, 0, 0, 3000, 0, Coast, Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, -70, -70, -525, -525, 0, 0, 100, On, 0, 0, 3500, 0, Brake, Left_Encoder_Track ) ;
                  Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, 0, On, 0, 0, 300, 0, Coast, 0 ) ;
                  Autonomous_Control ( Encoder_Track, 70, -15, 360, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 2500, 0, Brake, Left_Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 300, 300, Right, 39, Movable_Weighted_Base, On, 0, 0, 3000, 0, Coast, Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Movable_Weighted_Base, On, Movable_Weighted_Base, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 150 ) ; // #1
            Autonomous_Control ( Encoder_Track, -63, -63, -40, -40, 0, 0, 0, 0, 0, 0, 500, 0, Brake, Encoder_Track ) ;
            Autonomous_Control ( Drive, 10, 10, 0, 0, 0, 0, (Movable_Weighted_Base - 40), 0, 0, 0, 1500, 0, Coast, Lift_Ready ) ;
            Autonomous_Control ( Drive, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 250, 0, 0, 0 ) ;
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, 0, 0, Descore_Movable_Weighted_Base, 0, 2000, 0, Coast, Script_Ready ) ;
            Autonomous_Control ( Encoder_Track, -63, -63, -125, -125, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, Brake, Encoder_Track ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, -63, 63, -398, 398, 0, 0, Movable_Weighted_Base, On, 0, 0, 2250, 0, Brake, Left_Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 55, 55, 375, 375, Right, 38, Wall_Goal, On, 0, 0, 3000, 0, 0, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 55, 55, 0, 0, Right, 38, Wall_Goal, On, 0, 0, 300, 0, 0, 0 ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, 63, -63, 370, -370, 0, 0, Movable_Weighted_Base, On, 0, 0, 2250, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 55, 55, 350, 350, Left, 39, Wall_Goal, On, 0, 0, 3000, 0, 0, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 55, 55, 0, 0, Left, 39, Wall_Goal, On, 0, 0, 300, 0, 0, 0 ) ;
            }
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Wall_Goal, On, Wall_Goal, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 150  ) ; // #2
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, (Wall_Goal - 50), 0, 0, 0, 500, 0, Coast, Lift_Ready ) ;
            Autonomous_Control ( Encoder_Track, -63, -63, -150, -150, 0, 0, 0, 0, 0, 0, 1500, 0, Coast, Encoder_Track ) ;
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Pickup, 0, 0, 0, 2000, 0, 0, Lift_Ready ) ;
      }
      if ( Event == Match && Position == Outfield && Autonomous_Code == 1 )
      {
            Autonomous_Control ( Encoder_Track, 50, 50, 70, 70, 0, 0, Wall_Goal, On, 0, 0, 1000, 0, Brake, Encoder_Track ) ;
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 5000, 1000, Coast, Lift_Ready ) ;
            Autonomous_Control ( Drive, 55, 55, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 500, 0, 0, 0 ) ;
            Autonomous_Control ( Drive, 10, 10, 0, 0, 0, 0, Wall_Goal, On, Wall_Goal, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 150 ) ; // #1
            Autonomous_Control ( Drive, -63, -63, -65, -65, 0, 0, 0, 0, 0, 0, 1000, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Encoder_Track, -63, -63, -70, -70, 0, 0, Pickup, 0, 0, 0, 1000, 0, Brake, Encoder_Track ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, -63, 10, -210, 0, 0, 0, Pickup, 0, 0, 0, 1000, 0, Brake, Left_Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, 10, -63, 0, -217, 0, 0, Pickup, 0, 0, 0, 1000, 0, Brake, Right_Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 63, 63, 60, 60, 0, 0, Pickup, 0, 0, 0, 2000, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Drive, 63, 63, 90, 90, 0, 0, Pickup, Ready, 0, 0, 1000, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Drive, 63, 63, 0, 0, 0, 0, Pickup, On, 0, 0, 100, 100, Brake, 0 ) ;
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 300, 300, 0, 0 ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, -63, 63, -160, 160, 0, 0, Movable_Weighted_Base, On, 0, 0, 1200, 0, Brake, Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, 63, -63, 136, -136, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, 0, Lift_Ready ) ;
            Autonomous_Control ( Drive, 63, 63, 160, 160, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Movable_Weighted_Base, On, Movable_Weighted_Base, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 150 ) ; // #2
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, 10, -63, 0, -180, 0, 0, 0, 0, 0, 0, 1000, 0, Coast, Right_Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, -63, 10, -150, 0, 0, 0, 0, 0, 0, 0, 1000, 0, Coast, Left_Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, -127, -127, -50, -50, 0, 0, 0, 0, 0, 0, 1000, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Encoder_Track, -127, -127, -440, -440, 0, 0, Pickup, 0, 0, 0, 2500, 0, Coast, Encoder_Track ) ;
            Wait ( 200 ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, -63, 63, -100, 100, 0, 0, 0, 0, 0, 0, 1500, 0, Coast, Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, 63, -63, 70, -70, 0, 0, 0, 0, 0, 0, 1000, 0, Coast, Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 63, 63, 200, 200, 0, 0, 0, 0, 0, 0, 2000, 0, Coast, Encoder_Track ) ;
      }
      if ( Event == Match && Position == Outfield && Autonomous_Code == 2 )
      {
            Autonomous_Control ( Encoder_Track, 55, 55, 60, 60, 0, 0, Wall_Goal, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 200, 0, Coast, 0 ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, 10, -63, 0, -405, 0, 0, Wall_Goal, On, 0, 0, 2500, 0, Brake, Right_Encoder_Track ) ;
                  Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 3000, 0, 0, Lift_Ready ) ;
                  Autonomous_Control ( Wall_Track, 55, 55, 175, 175, Left, 38, Wall_Goal, On, 0, 0, 2000, 0, 0, Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, -63, 10, -420, 0, 0, 0, Wall_Goal, On, 0, 0, 2500, 0, Brake, Left_Encoder_Track ) ;
                  Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 3000, 0, 0, Lift_Ready ) ;
                  Autonomous_Control ( Wall_Track, 55, 55, 175, 175, Right, 38, Wall_Goal, On, 0, 0, 2000, 0, 0, Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 25, 25, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 200, 0, 0, 0 ) ;
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Wall_Goal, On, Wall_Goal, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 1000 ) ; // #1
            Autonomous_Control ( Encoder_Track, -50, -50, -100, -100, 0, 0, 0, 0, 0, 0, 1500, 0, Coast, Encoder_Track ) ;
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Pickup, 0, 0, 0, 2000, 0, 0, Lift_Ready ) ;
      }
      if ( Event == Match && Autonomous_Code == 3 )
      {
            Autonomous_Control ( Encoder_Track, 80, 80, 115, 115, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 600, 0, Coast, Lift_Ready ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Drive, -20, 75, 0, 325, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, 0, Right_Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Drive, 70, -20, 325, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, 0, Left_Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 80, 80, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 400, 0, 0, 0 ) ;
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Movable_Weighted_Base, On, Movable_Weighted_Base, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 150 ) ; // #1
            Autonomous_Control ( Line_Track, 63, 63, -100, -100, 0, 0, 0, 0, 0, 0, 1000, 0, Brake, Encoder_Track ) ;
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Pickup, 0, 0, 0, 2000, 0, 0, Lift_Ready ) ;
      }
      if ( Event == Match && Autonomous_Code == 4 )
      {
            Autonomous_Control ( Encoder_Track, 63, 63, 43, 43, 0, 0, Movable_Weighted_Base, On, 0, 0, 700, 0, Brake, Encoder_Track ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, -10, 63, 0, 200, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, Brake, Right_Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, 63, -10, 177, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, Brake, Left_Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 1300, 0, Coast, Lift_Ready ) ;
            Autonomous_Control ( Drive, 63, 63, 93, 93, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Movable_Weighted_Base, On, Movable_Weighted_Base, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 150 ) ; // #1
            Autonomous_Control ( Drive, -55, -55, -30, -30, 0, 0, 0, 0, 0, 0, 1000, 0, Brake, Encoder_Track ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, 10, -80, 0, -730, 0, 0, 0, 0, 0, 0, 5000, 0, Brake, Right_Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, -80, 10, -743, 0, 0, 0, 0, 0, 0, 0, 5000, 0, Brake, Left_Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, -55, -55, 0, 0, 0, 0, 15, 0, 0, 0, 1500, 0, 0, Line ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, -55, -55, -55, -55, 0, 0, 15, 0, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Drive, -58, 58, 0, 0, 0, 0, 0, 0, 0, 0, 1500, 0, Brake, Line ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, -55, -55, -55, -55, 0, 0, 15, 0, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Drive, 58, -58, 0, 0, 0, 0, 0, 0, 0, 0, 1500, 0, Brake, Line ) ;
            }
            High_Hang ( ) ;
      }
      if ( Event == Match && Position == Infield && Autonomous_Code == 5 )
      {
            Autonomous_Control ( Drive, -100, -127, 0, 0, 0, 0, 100, On, 0, 0, 2000, 250, 0, No_Line ) ;
            Autonomous_Control ( Drive, -105, -127, -190, -190, 0, 0, 100, On, 0, 0, 3500, 0, 0, Left_Encoder_Track ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Drive, 10, -127, 0, -210, 0, 0, 100, On, 0, 0, 2000, 0, 0, Right_Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Drive, -127, 10, -255, 0, 0, 0, 100, On, 0, 0, 2000, 0, 0, Left_Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, -105, -127, -320, -320, 0, 0, 100, On, 0, 0, 3500, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Encoder_Track, -63, -63, -310, -310, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, Brake, Encoder_Track ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, -63, 63, -130, 130, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 225, 225, Right, 38, Movable_Weighted_Base, On, 0, 0, 2500, 0, 0, Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, 63, -63, 130, -130, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 225, 225, Left, 38, Movable_Weighted_Base, On, 0, 0, 2500, 0, 0, Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Movable_Weighted_Base, On, Movable_Weighted_Base, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 150 ) ; // #1
            Autonomous_Control ( Encoder_Track, -63, -63, -150, -150, 0, 0, 0, 0, 0, 0, 1500, 0, Coast, Encoder_Track ) ;
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Pickup, 0, 0, 0, 2000, 0, Coast, Lift_Ready ) ;
      }
      if ( Event == Match && Position == Outfield && Autonomous_Code == 5 )
      {
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 500, 0, Coast, Lift_Ready ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, 55, 55, 60, 60, 0, 0, Wall_Goal, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 200, 0, Coast, 0 ) ;
                  Autonomous_Control ( Encoder_Track, 15, -70, 0, -388, 0, 0, Wall_Goal, On, 0, 0, 2500, 0, Brake, Right_Encoder_Track ) ;
                  Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 1000, 0, 0, Lift_Ready ) ;
                  Autonomous_Control ( Wall_Track, 55, 55, 175, 175, Left, 38, Wall_Goal, On, 0, 0, 1300, 0, 0, Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, 55, 55, 68, 68, 0, 0, Wall_Goal, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 200, 0, Coast, 0 ) ;
                  Autonomous_Control ( Encoder_Track, -70, 15, -397, 0, 0, 0, Wall_Goal, On, 0, 0, 3000, 0, Brake, Left_Encoder_Track ) ;
                  Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 3000, 0, 0, Lift_Ready ) ;
                  Autonomous_Control ( Wall_Track, 55, 55, 175, 175, Right, 38, Wall_Goal, On, 0, 0, 1300, 0, 0, Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 25, 25, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 200, 0, 0, 0 ) ;
            Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Wall_Goal, On, Wall_Goal, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 150 ) ; // #1
            Autonomous_Control ( Drive, -63, -63, -50, -50, 0, 0, 0, 0, 0, 0, 1500, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Encoder_Track, -63, -63, -173, -173, 0, 0, Pickup, 0, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, -63, 63, -194, 194, 0, 0, Pickup, 0, 0, 0, 2000, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Descore_Movable_Weighted_Base, 0, 0, 0, 1000, 1000, 0, 0 ) ;
                  Autonomous_Control ( Wall_Track, 75, 75, 245, 245, Right, 16, Descore_Movable_Weighted_Base, 0, 0, 0, 2500, 0, 0, Encoder_Track ) ;
                  Autonomous_Control ( Drive, 25, 25, 0, 0, 0, 0, Descore_Movable_Weighted_Base, On, Descore_Movable_Weighted_Base, 0, 3000, 0, Coast, Script_Ready ) ;
                  Autonomous_Control ( Encoder_Track, -63, -63, -260, -260, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Encoder_Track, -63, 63, -206, 206, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, 63, -63, 186, -186, 0, 0, Pickup, 0, 0, 0, 2000, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Descore_Movable_Weighted_Base, 0, 0, 0, 1000, 1000, 0, 0 ) ;
                  Autonomous_Control ( Wall_Track, 75, 75, 245, 245, Left, 16, Descore_Movable_Weighted_Base, 0, 0, 0, 2500, 0, 0, Encoder_Track ) ;
                  Autonomous_Control ( Drive, 25, 25, 0, 0, 0, 0, Descore_Movable_Weighted_Base, On, Descore_Movable_Weighted_Base, 0, 3000, 0, Coast, Script_Ready ) ;
                  Autonomous_Control ( Encoder_Track, -63, -63, -260, -260, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Encoder_Track, 63, -63, 175, -175, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 75, 75, 50, 50, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Encoder_Track, 75, 75, 50, 50, 0, 0, Movable_Weighted_Base, Off, 0, 0, 2000, 0, Brake, Encoder_Track ) ;
            Autonomous_Control ( Encoder_Track, -63, -63, -190, -190, 0, 0, Pickup, Off, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
            if ( Alliance == Red )
            {
                  Autonomous_Control ( Encoder_Track, 10, -75, 0, -353, 0, 0, Pickup, 0, 0, 0, 3000, 0, Brake, Right_Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 0, 0, Right, 5, Pickup, 0, 0, 0, 3000, 0, 0, No_Line ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 30, 30, Right, 5, Pickup, Ready, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Encoder_Track, -15, 70, 0, 190, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Right_Encoder_Track ) ;
            }
            if ( Alliance == Blue )
            {
                  Autonomous_Control ( Encoder_Track, -75, 10, -355, 0, 0, 0, Pickup, 0, 0, 0, 3000, 0, Brake, Left_Encoder_Track ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 0, 0, Left, 5, Pickup, 0, 0, 0, 3000, 0, 0, No_Line ) ;
                  Autonomous_Control ( Wall_Track, 63, 63, 45, 45, Left, 5, Pickup, Ready, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
                  Autonomous_Control ( Encoder_Track, 70, -15, 185, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Left_Encoder_Track ) ;
            }
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, 0, Lift_Ready ) ;
            Autonomous_Control ( Drive, 75, 75, 130, 130, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, Coast, Encoder_Track ) ;
            Autonomous_Control ( Drive, 20, 20, 0, 0, 0, 0, (Movable_Weighted_Base - 40), On, 0, 0, 2000, 0, Coast, Lift_Ready ) ;
            Autonomous_Control ( Encoder_Track, -75, -75, -120, -120, 0, 0, Pickup, 0, 0, 0, 2000, 0, Coast, Encoder_Track ) ;
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Pickup, 0, 0, 0, 2000, 0, Coast, Lift_Ready ) ;
      }
      if ( Event == PSC )
      {
            Programming_Skills_Challenge ( ) ;
      }
}

#include "Main.h"

void Autonomous_Control ( int Navigation_Type, float Left_Motor_Setpoint, float Right_Motor_Setpoint, int Left_Encoder_Setpoint, int Right_Encoder_Setpoint, int Ultrasonic_Direction, int Ultrasonic_Setpoint, int Lift_Height_Setpoint, int Gripper_Setpoint, int Script_Setpoint, int Tilt_Setpoint, int Max_Time, int Min_Time, int Stop, int Break_Option )
{
      float P = 0; // 6
      float I = 0; // .2
      float D = 0; // 18
      int D_Time = 0; // 750
      int Max_Output = 0;

      if ( Navigation_Type != Wall_Track && Ultra != Off )
      {
            if ( Ultra == Left )
            {
                  StopUltrasonic ( 1 , 2 ) ;
                  Ultra = Off ;
            }
            if ( Ultra == Right )
            {
                  StopUltrasonic ( 3 , 4 ) ;
                  Ultra = Off ;
            }
      }
      if ( Lift_Height_Setpoint != 0 )
      {
            Lift_Setpoint = Lift_Height_Setpoint ;
      }
      if ( Script != Script_Setpoint && Stage == 0 )
      {
            Stage = 1 ;
            Script = Script_Setpoint ;
      }
      if ( Gripper_Setpoint == On )
      {
            Gripper = On ;
      }
      if ( Gripper_Setpoint == Off )
      {
            Gripper = Off ;
      }
      if ( Tilt_Setpoint != Back )
      {
            Tilt = Forward ;
      }
      if ( Tilt_Setpoint == Back )
      {
            Tilt = Back ;
      }
      if ( Navigation_Type == Wall_Track || Navigation_Type == Line_Track )
      {
            Left_Motor_Setpoint = Abs ( Left_Motor_Setpoint ) ;
            Right_Motor_Setpoint = Abs ( Right_Motor_Setpoint ) ;
      }
      if ( Navigation_Type == Encoder_Track )
      {
            if ( Left_Encoder_Setpoint != 0 )
            {
                  Left_Motor_Setpoint = Abs ( Left_Motor_Setpoint ) ;
            }
            if ( Right_Encoder_Setpoint != 0 )
            {
                  Right_Motor_Setpoint = Abs ( Right_Motor_Setpoint ) ;
            }
      }
      if ( Navigation_Type == Wall_Track )
      {
            if ( Ultrasonic_Direction == Right && Ultra != Right )
            {
                  if ( Ultra == Left )
                  {
                        StopUltrasonic ( 1 , 2 ) ;
                  }
                  StartUltrasonic ( 3 , 4 ) ;
                  Ultra = Right ;
            }
            if ( Ultrasonic_Direction == Left && Ultra != Left )
            {
                  if ( Ultrasonic_Direction == Right )
                  {
                        StopUltrasonic ( 3 , 4 ) ;
                  }
                  StartUltrasonic ( 1 , 2 ) ;
                  Ultra = Left ;
            }
            P = 6 ;
            I = .2 ;
            Max_Output = 10 ;
            if ( Ultrasonic_Setpoint == 8 && Ultrasonic_Direction == Right )
            {
                  Max_Output = 15 ;
            }
            if ( Left_Motor_Setpoint <= 60 && Ultrasonic_Setpoint != 8 )
            {
                  Max_Output = 8 ;
            }
            D = Max_Output ;
            D_Time = 500 ;
            if ( Left_Motor_Setpoint > 100 )
            {
                  Left_Motor_Setpoint = 100 ;
            }
            if ( Right_Motor_Setpoint > 100 )
            {
                  Right_Motor_Setpoint = 100 ;
            }
      }
      if ( Navigation_Type == Line_Track  )
      {
            P = 1.5 ;
            I = .12 ;
            if ( Tilt == Back && Lift_Encoder > 50 )
            {
                  Max_Output = 9 ;
            }
            else
            {
                  Max_Output = 12 ;
            }
            D = 15 ;
            D_Time = 100 ;
            Last_Line = 1 ;
            if ( Left_Motor_Setpoint > 63 )
            {
                  Left_Motor_Setpoint = 63 ;
            }
            if ( Right_Motor_Setpoint > 63 )
            {
                  Right_Motor_Setpoint = 63 ;
            }
            Left_Motor_Setpoint = (Left_Motor_Setpoint * -1) ;
            Right_Motor_Setpoint = (Right_Motor_Setpoint * -1) ;
      }
      PresetQuadEncoder ( 5 , 6 , 0) ;
      PresetQuadEncoder ( 7 , 8 , 0) ;
      PresetTimer ( 2 , 0 ) ;
      while ( IsEnabled() )
      {
            Timer2 = GetTimer ( 2 ) ;
            Left_Line = GetAnalogInput ( 1 ) ;
            Center_Line = GetAnalogInput ( 2 ) ;
            Right_Line = GetAnalogInput ( 3 ) ;
            LF_Line = GetAnalogInput ( 8 ) ;
            Left_Encoder = GetQuadEncoder ( 5 , 6 ) ;
            Right_Encoder = GetQuadEncoder ( 7 , 8 ) ;
            Gripper_Limit = GetAnalogInput ( 7 ) ;
            if ( Gripper_Limit < 10 && Lift_Limit < 10 && Gripper == Off && (Gripper_Setpoint == Ready || Gripper_Setpoint == Ready2) )
            {
                  Gripper = On ;
                  Lift_Setpoint = Movable_Weighted_Base ;
            }
            if ( Navigation_Type == Drive )
            {
                  Left_Motor = (-Left_Motor_Setpoint) ;
                  Right_Motor = (Right_Motor_Setpoint) ;
            }
            Left_Error = (Left_Encoder_Setpoint - Left_Encoder) ;
            Right_Error = (Right_Encoder_Setpoint - Right_Encoder) ;
            if ( Right_Encoder_Setpoint == 0 )
            {
                  Right_Motor_Status = Ready ;
            }
            if ( Left_Encoder_Setpoint == 0 )
            {
                  Left_Motor_Status = Ready ;
            }
            if ( Left_Encoder_Setpoint > 0 )
            {
                  if ( Left_Error > 0 )
                  {
                        Left_Motor_Status = Moving ;
                  }
                  if ( Left_Error <= 0 )
                  {
                        Left_Motor_Status = Ready ;
                  }
            }
            if ( Right_Encoder_Setpoint > 0 )
            {
                  if ( (Right_Error > 0)  )
                  {
                        Right_Motor_Status = Moving ;
                  }
                  if ( Right_Error <= 0 )
                  {
                        Right_Motor_Status = Ready ;
                  }
            }
            if ( Left_Encoder_Setpoint < 0 )
            {
                  if ( Left_Error < 0 )
                  {
                        Left_Motor_Status = Moving ;
                  }
                  if ( Left_Error >= 0 )
                  {
                        Left_Motor_Status = Ready ;
                  }
            }
            if ( Right_Encoder_Setpoint < 0 )
            {
                  if ( (Right_Error < 0) )
                  {
                        Right_Motor_Status = Moving ;
                  }
                  if ( Right_Error >= 0 )
                  {
                        Right_Motor_Status = Ready ;
                  }
            }
            if ( Navigation_Type == Encoder_Track )
            {
                  Left_Motor = (Left_Error * -.02) ;
                  Right_Motor = (Right_Error * .02) ;
                  if ( Left_Motor > 1 )
                  {
                        Left_Motor = 1 ;
                  }
                  if ( Left_Motor < -1 )
                  {
                        Left_Motor = -1 ;
                  }
                  if ( Right_Motor > 1 )
                  {
                        Right_Motor = 1 ;
                  }
                  if ( Right_Motor < -1 )
                  {
                        Right_Motor = -1 ;
                  }
                  if ( Left_Encoder_Setpoint != 0 )
                  {
                        Left_Motor = (Left_Motor * Left_Motor_Setpoint) ;
                  }
                  if ( Left_Encoder_Setpoint == 0 )
                  {
                        Left_Motor = (-Left_Motor_Setpoint) ;
                  }
                  if ( Right_Encoder_Setpoint != 0 )
                  {
                        Right_Motor = (Right_Motor * Right_Motor_Setpoint) ;
                  }
                  if ( Right_Encoder_Setpoint == 0 )
                  {
                        Right_Motor = (Right_Motor_Setpoint) ;
                  }
            }
            // ultrasonic
            Timer6 = GetTimer ( 6 ) ;
            if ( Ultrasonic_Direction == Left && Timer6 >= Ultrasonic_Time )
            {
                  Ultrasonic = GetUltrasonic ( 1 , 2 ) ;
                  PresetTimer ( 6 , 0 ) ;
            }
            if ( Ultrasonic_Direction == Right && Timer6 >= Ultrasonic_Time )
            {
                  Ultrasonic = GetUltrasonic ( 3 , 4 ) ;
                  PresetTimer ( 6 , 0 ) ;
            }
            if ( Navigation_Type == Wall_Track )
            {
                  Ultrasonic_Error = (Ultrasonic_Setpoint - Ultrasonic) ;
                  if ( Ultrasonic_Error < -5 || Ultrasonic_Error > 5 )
                  {
                        Ultrasonic_Error = 0 ;
                  }
                  if ( Ultrasonic_Direction == Right && Ultrasonic_Setpoint == 8  )
                  {
                        if ( Ultrasonic > 9 )
                        {
                              Ultrasonic_Error = -2 ;
                        }
                        if ( Ultrasonic < 7 )
                        {
                              Ultrasonic_Error = (Ultrasonic_Error + .5) ;
                        }
                  }
                  if ( Ultrasonic_Error == 0 )
                  {
                        I_Error = 0 ;
                  }
                  P_Out = (Ultrasonic_Error * P) ;
                  if ( Output <= Max_Output && Output >= (Max_Output * -1) )
                  {
                        I_Error = (P_Out + I_Error) ;
                  }
                  I_Out = (I_Error * I) ;
                  D_Error  = (Ultrasonic_Error - Last_Error) ;
                  Last_Error = Ultrasonic_Error ;
                  Timer5 = GetTimer ( 5 ) ;
                  if ( D_Error != 0 || Timer5 > D_Time )
                  {
                        D_Out = (D_Error * D) ;
                        PresetTimer ( 5 , 0 ) ;
                  }
                  Output = (P_Out + I_Out + D_Out) ;
                  if ( Output > (Max_Output) )
                  {
                        Output = (Max_Output) ;
                  }
                  if ( Output < (Max_Output * -1) )
                  {
                        Output = (Max_Output * -1) ;
                  }
                  if ( Ultrasonic_Direction == Left )
                  {
                        Left_Motor = (-Left_Motor_Setpoint - Output) ;
                        Right_Motor = (Right_Motor_Setpoint - Output) ;
                  }
                  if ( Ultrasonic_Direction == Right )
                  {
                        Left_Motor = (-Left_Motor_Setpoint + Output) ;
                        Right_Motor = (Right_Motor_Setpoint + Output) ;
                  }
            }
            // Line
            if ( Navigation_Type == Line_Track )
            {
                  if ( Left_Line >= Threshold && Center_Line >= Threshold && Right_Line >= Threshold && Last_Line == -1 )
                  { // -3
                        Line_Position = -3 ;
                  }
                  if ( Left_Line < Threshold && Center_Line >= Threshold && Right_Line >= Threshold )
                  { // -2
                        Last_Line = -1 ;
                        Line_Position = -2 ;
                  }
                  if ( Center_Line <  Threshold )
                  {
                        if ( Left_Line < Threshold && Right_Line >= Threshold )
                        { // -1
                              Last_Line = -1 ;
                              Line_Position = -1 ;
                        }
                        if ( Left_Line >= Threshold && Right_Line >= Threshold )
                        { // 0
                              Last_Line = 0 ;
                              Line_Position = 0 ;
                        }
                        if ( Right_Line < Threshold && Left_Line >= Threshold )
                        { // 1
                              Last_Line = 1 ;
                              Line_Position = 1 ;
                        }
                  }
                  if ( Right_Line < Threshold && Center_Line >= Threshold && Left_Line >= Threshold )
                  { // 2
                        Last_Line = 1 ;
                        Line_Position = 2 ;
                  }
                  if ( Left_Line >= Threshold && Center_Line >= Threshold && Right_Line >= Threshold && Last_Line == 1 )
                  { // 3
                        Line_Position = 3 ;
                  }
                  if ( Line_Position == 0 )
                  {
                        I_Error = 0 ;
                  }
                  P_Out = (Line_Position * P) ;
                  if ( Output <= Max_Output && Output >= (Max_Output * -1) )
                  {
                        I_Error = (P_Out + I_Error) ;
                  }
                  I_Out = (I_Error * I) ;
                  D_Error  = (Line_Position  - Last_Error) ;
                  Last_Error = Line_Position ;
                  Timer5 = GetTimer ( 5 ) ;
                  if ( D_Error != 0 || Timer5 > D_Time )
                  {
                        D_Out = (D_Error * D) ;
                        PresetTimer ( 5 , 0 ) ;
                  }
                  Output = (P_Out + I_Out + D_Out) ;
                  if ( Output > (Max_Output) )
                  {
                        Output = (Max_Output) ;
                  }
                  if ( Output < (Max_Output * -1) )
                  {
                        Output = (Max_Output * -1) ;
                  }
                  Left_Motor = (-Left_Motor_Setpoint + Output) ;
                  Right_Motor = (Right_Motor_Setpoint + Output) ;
            }
            if ( Left_Motor > 127 )
            {
                  Left_Motor = 127 ;
            }
            if ( Left_Motor < -127 )
            {
                  Left_Motor = -127 ;
            }
            if ( Right_Motor > 127 )
            {
                  Right_Motor = 127 ;
            }
            if ( Right_Motor < -127 )
            {
                  Right_Motor = -127 ;
            }
            Motor_Drive ( ) ;
            if ( LF_Line < Threshold && Break_Option == Line2 && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( LF_Line >= Threshold && Break_Option == No_Line2 && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( (Left_Line < Threshold || Center_Line < Threshold || Right_Line < Threshold) && Break_Option == Line && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( Left_Line < Threshold && Center_Line < Threshold &&  Right_Line < Threshold && Break_Option == Cross_Line && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( Left_Line >= Threshold && Center_Line >= Threshold &&  Right_Line >= Threshold && Break_Option == No_Line && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( Break_Option == Encoder_Track && Left_Motor_Status == Ready && Right_Motor_Status == Ready && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( Break_Option == Right_Encoder_Track && Right_Motor_Status == Ready && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( Break_Option == Left_Encoder_Track && Left_Motor_Status == Ready && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( Timer2 > Max_Time && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( Break_Option == Lift_Ready && Lift_Status == Ready && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( Break_Option == Script_Ready && Lift_Status == Ready && Stage == 0 && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( Break_Option == Tube && Gripper_Limit < 10 && Timer2 > Min_Time )
            {
                  break ;
            }
            if ( Break_Option == Proximity && Ultrasonic < 10 && Timer2 > Min_Time )
            {
                  break ;
            }
      }
      if ( Gripper_Setpoint == Ready2 )
      {
            Gripper = On ;
            SetDigitalOutput ( 11 , On ) ;
      }
      if ( Stop == Brake )
      {
            if ( Navigation_Type == Drive  )
            {
                  if ( Left_Motor_Setpoint > 0 )
                  {
                        Left_Motor = -Brake ;
                  }
                  if ( Left_Motor_Setpoint < 0 )
                  {
                        Left_Motor = Brake ;
                  }
                  if ( Left_Motor_Setpoint == 0 )
                  {
                        Left_Motor = 0 ;
                  }
                  if ( Right_Motor_Setpoint > 0 )
                  {
                        Right_Motor = -Brake ;
                  }
                  if ( Right_Motor_Setpoint < 0 )
                  {
                        Right_Motor = Brake ;
                  }
                  if ( Right_Motor_Setpoint == 0 )
                  {
                        Right_Motor = 0 ;
                  }
                  SetMotor ( 2 , Right_Motor ) ;
                  SetMotor ( 1 , Left_Motor ) ;
                  SetMotor ( 7 , -Left_Motor ) ;
                  SetMotor ( 8 , Right_Motor ) ;
                  Wait ( 150 ) ;
            }
            if ( Navigation_Type == Line_Track  )
            {
                  SetMotor ( 2 , (Brake) ) ;
                  SetMotor ( 1 , (Brake) ) ;
                  SetMotor ( 7 , (-Brake) ) ;
                  SetMotor ( 8 , (Brake) ) ;
                  Wait ( 150 ) ;
            }
            if ( Navigation_Type == Encoder_Track  )
            {
                  if ( Left_Encoder_Setpoint > 0 )
                  {
                        Left_Motor = -Brake ;
                  }
                  if ( Left_Encoder_Setpoint < 0 )
                  {
                        Left_Motor = Brake ;
                  }
                  if ( Left_Encoder_Setpoint == 0 )
                  {
                        Left_Motor = 0 ;
                  }
                  if ( Right_Encoder_Setpoint > 0  )
                  {
                        Right_Motor = -Brake ;
                  }
                  if ( Right_Encoder_Setpoint < 0  )
                  {
                        Right_Motor = Brake ;
                  }
                  if ( Right_Encoder_Setpoint == 0 )
                  {
                        Right_Motor = 0 ;
                  }
                  SetMotor ( 2 , Right_Motor ) ;
                  SetMotor ( 1 , Left_Motor ) ;
                  SetMotor ( 7 , -Left_Motor ) ;
                  SetMotor ( 8 , Right_Motor ) ;
                  Wait ( 150 ) ;
            }
            if ( Navigation_Type == Wall_Track )
            {
                  SetMotor ( 1 , (-Brake) ) ;
                  SetMotor ( 2 , (-Brake) ) ;
                  SetMotor ( 7 , (Brake) ) ;
                  SetMotor ( 8 , (-Brake) ) ;
                  Wait ( 150 ) ;
            }
      }
      if ( Stop == Coast || Stop == Brake  )
      {
            SetMotor ( 1 , 0 ) ;
            SetMotor ( 2 , 0 ) ;
            SetMotor ( 8 , 0 ) ;
            SetMotor ( 7 , 0 ) ;
            if ( Navigation_Type == Wall_Track  )
            {
                  I_Error = 0 ;
                  Output = 0  ;
                  Last_Error = 0 ;
            }
      }
}

#include "Main.h"

void Driver_Control ( void )
{
      StopQuadEncoder ( 5 , 6 ) ;
      StopQuadEncoder ( 7 , 8 ) ;
      Gripper = Off ;
      if ( Autonomous_Code == 4 )
      {
            Hang = On ;
      }
      while ( 1 )
      {
            Ch3 = GetJoystickAnalog( 1 , 3 ) ;
            Ch4 = GetJoystickAnalog( 1 , 4 ) ;
            Ch5d = GetJoystickDigital ( 1 , 5 , 1 ) ;
            Ch5u = GetJoystickDigital ( 1 , 5 , 2 ) ;
            Ch6d = GetJoystickDigital ( 1 , 6 , 1 ) ;
            Ch6u = GetJoystickDigital ( 1 , 6 , 2 ) ;
            Ch7d = GetJoystickDigital ( 1 , 7 , 1 ) ;
            Ch7u = GetJoystickDigital ( 1 , 7 , 2 ) ;
            Ch7r = GetJoystickDigital ( 1 , 7 , 4 ) ;
            Ch7l = GetJoystickDigital ( 1 , 7 , 3 ) ;
            Ch8d = GetJoystickDigital ( 1 , 8 , 1 ) ;
            Ch8u = GetJoystickDigital ( 1 , 8 , 2 ) ;
            Ch8l = GetJoystickDigital ( 1 , 8 , 3 ) ;
            Ch8r = GetJoystickDigital ( 1 , 8 , 4 ) ;
            Gripper_Limit = GetAnalogInput ( 7 ) ;
            if ( Event == RSC  )
            {
                  Timer1 = GetTimer ( 1 ) ;
                  if ( Finish_Time == 0 && Tilt == Back && Lift_Limit < 10 && Timer1 > 40000 )
                  {
                        Finish_Time = Timer1 ;
                  }
                  if ( Timer1 >= 60000 )
                  {
                        break ;
                  }
            }
            // Manual Lift Control
            if ( Ch5u == 1 && Ch5d == 0 ) // up
            {
                  if ( Descore_Armed != Off && Gripper_Limit > 10 && Lift_Setpoint >= 30 )
                  {
                        Last_Goal = Descore_Armed ;
                        Descore_Armed = Off ;
                  }
                  if ( Script == Wall_Goal && Stage == 2 && Lift_Encoder >= (Wall_Goal - 30) )
                  {
                        Lift_Setpoint = Wall_Goal ;
                        Lift_Reset = On ;
                  }
                  if ( Script == Movable_Weighted_Base && Stage == 2 && Lift_Encoder >= (Movable_Weighted_Base - 30) )
                  {
                        Lift_Setpoint = Movable_Weighted_Base ;
                        Lift_Reset = On ;
                  }
                  if ( Script == Off && Lift_Reset == Off )
                  {
                        Lift_Motor = 127 ;
                        if ( Lift_Limit < 10 )
                        {
                              Lift_Setpoint = Pickup ;
                        }
                        if ( Lift_Limit >= 10  )
                        {
                              Lift_Setpoint = (Lift_Encoder + 5) ;
                        }
                        if ( Lift_Setpoint == Wall_Goal || Lift_Setpoint == Movable_Weighted_Base || Lift_Setpoint == Descore_Wall_Goal ||  Lift_Setpoint == Descore_Wall_Goal2 || Lift_Setpoint == Descore_Movable_Weighted_Base )
                        {
                              Lift_Setpoint = (Lift_Setpoint + 1) ;
                        }
                        Lift_Status = Ready ;
                  }
                  if ( !(((Script == Descore_Movable_Weighted_Base) || (Script == Descore_Wall_Goal)) && Gripper_Limit < 10) )
                  {
                        Script = 0 ;
                        Stage = 0 ;
                  }
            }
            if ( Ch5u == 0  )
            {
                  if ( Lift_Status == Ready && Lift_Reset == On )
                  {
                        Lift_Reset = Off ;
                  }
            }
            if ( Ch5u == 1 && Ch5d == 1 && Tilt == Back )
            {
                  Lift_Motor = 0 ;
                  Lift_Setpoint = (Lift_Encoder) ;
                  Lift_Status = Ready ;
                  Script = 0 ;
                  Stage = 0 ;
            }
            if ( Ch5d == 1 && (Ch6u == 1 || Ch6d == 1 ) && Ch5d_Armed == On && Tilt == Forward && Gripper == On )
            {
                  Ch5d_Armed = Off ;
            }
            if ( Ch5d == 1 && Ch8l == 1 && Ch5d_Armed == On && Tilt == Back && Gripper == Off )
            {
                  Ch5d_Armed = Off ;
            }
            if ( Ch5u == 0 && Ch5d == 1 && Ch5d_Armed == On ) // down
            {
                  Lift_Motor = -127 ;
                  if ( Lift_Limit < 10 && Tilt == Forward )
                  {
                        Lift_Motor = -10 ;
                  }
                  if ( Lift_Limit < 10 || Lift_Encoder <= 12 )
                  {
                        Lift_Setpoint = Pickup ;
                  }
                  if ( Lift_Limit >= 10 && Lift_Encoder > 12 )
                  {
                        Lift_Setpoint = (Lift_Encoder - 12) ;
                  }
                  if ( Lift_Setpoint == Wall_Goal || Lift_Setpoint == Movable_Weighted_Base || Lift_Setpoint == Descore_Wall_Goal || Lift_Setpoint == Descore_Movable_Weighted_Base )
                  {
                        Lift_Setpoint = (Lift_Setpoint + 1) ;
                  }
                  Lift_Status = Ready ;
                  Script = 0 ;
                  Stage = 0 ;
            }
            if ( Ch5d == 0 && Ch5d_Armed == Off )
            {
                  Ch5d_Armed = On ;
            }
            // Drive_Train
            Angle = (Ch3 / Ch4) ;
            Angle = Fabs ( Angle ) ;
            if ( Angle > 1 )
            {
                  Angle = (1 / Angle) ;
            }
            Angle = (Angle * .15) ;
            Ch4 = ((Ch4 * Angle) + Ch4) ;
            Ch3 = ((Ch3 * Angle) + Ch3) ;
            if ( Ch4 > 0 )
            {
                  Ch4 = Pow ( Ch4 , 1.3 ) ;
                  Ch4 = (Ch4 * .2339) ;
            }
            if ( Ch4 < 0 )
            {
                  Ch4 = Fabs ( Ch4 ) ;
                  Ch4 = Pow ( Ch4 , 1.3 ) ;
                  Ch4 = (Ch4 * -.2339) ;
            }
            if ( Ch4 > 127 )
            {
                  Ch4 = 127 ;
            }
            if ( Ch4 < -127 )
            {
                  Ch4 = -127 ;
            }
            if ( Ch3 > 127 )
            {
                  Ch3 = 127 ;
            }
            if ( Ch3 < -127 )
            {
                  Ch3 = -127 ;
            }
            if ( Tilt == Back )
            {
                  Ch4 = (Ch4 * .6) ;
                  Ch3 = (Ch3 * .7) ;
            }
            Left_Motor  = (-Ch4 - Ch3) ;
            Right_Motor = (-Ch4 + Ch3) ;
            if ( Left_Motor > 127 )
            {
                  Left_Motor = 127 ;
            }
            if ( Left_Motor < -127 )
            {
                  Left_Motor = -127 ;
            }
            if ( Right_Motor > 127 )
            {
                  Right_Motor = 127 ;
            }
            if ( Right_Motor < -127 )
            {
                  Right_Motor = -127 ;
            }
            SetMotor ( 1 , -Left_Motor ) ;
            SetMotor ( 7 , Left_Motor ) ;
            SetMotor ( 2 , Right_Motor ) ;
            SetMotor ( 8 , Right_Motor ) ;
            // Script Input
            if ( Ch8u == 1 && Ch8r == 0 && Ch8l == 0 && Ch8d == 0 && Ch7l == 0 && Ch7d == 0 && Ch7r == 0 && Lift_Setpoint != Wall_Goal && Tilt == Forward )
            { // Ch8u
                  Lift_Setpoint = Wall_Goal ;
            }
            if ( Ch8u == 0 && Ch8r == 1 && Ch8l == 0 && Ch8d == 0 && Ch7l == 0 && Ch7d == 0 && Ch7r == 0 && Lift_Setpoint != Movable_Weighted_Base && Tilt == Forward )
            { // Ch8r
                  Lift_Setpoint = Movable_Weighted_Base ;
            }
            if ( Ch8u == 0 && Ch8r == 0 && Ch8l == 1 && Ch8d == 0 && Ch7l == 0 && Ch7r == 0 && Ch7d == 0 )
            { // Ch8l
                  Lift_Setpoint = Pickup ;
                  Gripper = Off ;
                  Tilt = Forward ;
            }
            if ( Ch8u == 0 && Ch8r == 0 && Ch8l == 0 && Ch8d == 0 && Ch7l == 1 && Ch7r == 0 && Ch7d == 0 && Gripper == Off && Tilt == Forward )
            { // Ch7l
                  Lift_Setpoint = Descore_Wall_Goal ;
            }
            if ( Ch8u == 0 && Ch8r == 0 && Ch8l == 0 && Ch8d == 0 && Ch7l == 0 && Ch7d == 0 && Ch7r == 1 && Gripper == Off && Tilt == Forward )
            { // Ch7r
                  Lift_Setpoint = Descore_Wall_Goal2 ;
            }
            if ( Ch8u == 0 && Ch8r == 0 && Ch8l == 0 && Ch8d == 0 && Ch7l == 0 && Ch7d == 1 && Ch7r == 0 && Gripper == Off && Tilt == Forward )
            { // Ch7d
                  Lift_Setpoint = Descore_Movable_Weighted_Base ;
            }
            if ( Ch8u == 0 && Ch8r == 0 && Ch8l == 0 && Ch8d == 1 && Ch7l == 0 && Ch7r == 0 && Ch7d == 0 )
            { // Ch8d
                  Script = 0 ;
                  Stage = 0 ;
                  Lift_Setpoint = (Lift_Encoder) ;
                  Lift_Status = Ready ;
                  Last_Goal = Pickup ;
                  if ( Gripper == Off && Armed2 == On )
                  {
                        Gripper = On ;
                        Armed2 = Off ;
                  }
                  if ( Gripper == On && Armed2 == On )
                  {
                        Gripper = Off ;
                        Armed2 = Off ;
                  }
            }
            if ( Ch8u == 0 && Ch8r == 0 && Ch8l == 0 && Ch8d == 0 && Ch7l == 0 && Ch7d == 0 && Armed2 == Off )
            {
                  Armed2 = On ;
            }
            if ( Ch7u == 1 && Ch7r == 0 && Ch7l == 0 && Ch7d == 0 && Lift_Status == Ready )
            {
                  if ( Tilt == Back && Armed1 == On )
                  {
                        if ( Lift_Limit < 10 )
                        {
                              Script = Ladder  ;
                              Stage = -1 ;
                              Secondary_Script = On ;
                        }
                        if ( Lift_Limit > 10 )
                        {
                              Tilt = Forward ;
                        }
                        Armed1 = Off ;
                  }
                  if ( Tilt == Forward && Armed1 == On  )
                  {
                        if ( Lift_Limit <= 10 )
                        {
                              Script = Ladder  ;
                              Stage = 1 ;
                              Secondary_Script = Off ;
                        }
                        if ( Lift_Limit > 10 && Lift_Encoder < 50 )
                        {
                              Lift_Setpoint = (Ladder - 38) ;
                              Tilt = Back ;
                        }
                        if ( Lift_Limit > 10 && Lift_Encoder >= 50 && Hang == On )
                        {
                              Tilt = Back ;
                        }
                        Armed1 = Off ;
                  }
            }
            if ( Ch7u == 0 && Armed1 == Off )
            {
                  Armed1 = On ;
            }
            if ( ((Gripper_Limit < 10) || (Ch6u == 1 && Ch6u_Armed == On) || (Ch6d == 1 && Ch6d_Armed == On)) && Lift_Encoder > 75 && Lift_Encoder < 165 && Last_Goal == Descore_Wall_Goal && Lift_Status == Ready && Script == 0 && Gripper == Off )
            {
                  Script = Descore_Wall_Goal ;
                  Stage = 1 ;
                  Ch6d_Armed = Off ;
                  Ch6u_Armed = Off ;
                  Last_Goal = Pickup ;
                  Lift_Reset = On ;
            }
            if ( ((Gripper_Limit < 10) || (Ch6u == 1 && Ch6u_Armed == On) || (Ch6d == 1 && Ch6d_Armed == On)) && Lift_Encoder > 25 && Lift_Encoder < 125 &&  Last_Goal == Descore_Movable_Weighted_Base && Lift_Status == Ready && Script == 0 && Gripper == Off )
            {
                  Script = Descore_Movable_Weighted_Base ;
                  Stage = 1 ;
                  Ch6d_Armed = Off ;
                  Ch6u_Armed = Off ;
                  Last_Goal = Pickup ;
                  Lift_Reset = On ;
            }
            if ( Ch6u == 0 && Ch6d == 1  )
            {
                  if ( Ch6d_Armed == On && Last_Goal == Wall_Goal && Lift_Setpoint <= (Wall_Goal + Lift_C) && Lift_Setpoint >= (Wall_Goal - Lift_C) && Lift_Status == Ready && Script == 0 && Gripper == On )
                  {
                        Script = Wall_Goal ;
                        Stage = 1 ;
                        Secondary_Script = On ;
                        Ch6d_Armed = Off ;
                  }
                  if ( Ch6d_Armed == On && Last_Goal == Movable_Weighted_Base && Lift_Setpoint <= (Movable_Weighted_Base + Lift_C) && Lift_Setpoint >= (Movable_Weighted_Base - Lift_C) && Lift_Status == Ready && Script == 0 && Gripper == On )
                  {
                        Script = Movable_Weighted_Base ;
                        Stage = 1 ;
                        Secondary_Script = On ;
                        Ch6d_Armed = Off ;
                  }
                  if ( Ch6d_Armed == On && Lift_Status == Ready && Script == Off && Tilt == Forward && Gripper == On && Lift_Setpoint <= (Last_Goal - Lift_C) && ((Lift_Setpoint >= (Wall_Goal - 70) && Last_Goal == Wall_Goal) || (Lift_Setpoint >= (Movable_Weighted_Base - 105) && Last_Goal == Movable_Weighted_Base)) )
                  {
                        Gripper = Off ;
                        Ch6d_Armed = Off ;
                  }
                  if (  Ch6d_Armed == On && Lift_Limit < 10 && Lift_Status == Ready && Script == 0 && Gripper == Off && Tilt == Forward )
                  {
                        Script = Pickup ;
                        Stage = 1 ;
                        Secondary_Script = Off ;
                        Ch6d_Armed = Off ;
                  }
                  if ( Ch6d_Armed == On &&  Gripper == Off && Gripper_Limit > 10 && Tilt == Forward && Lift_Setpoint != Descore_Wall_Goal && Lift_Setpoint != Descore_Movable_Weighted_Base && Lift_Limit >= 10 && Script == Off && Lift_Setpoint != Pickup && Lift_Status == Ready )
                  {
                        Lift_Setpoint = Pickup ;
                        Gripper = Off ;
                        Ch6d_Armed = Off ;
                  }
            }
            if ( Ch6d == 0 && Ch6u == 1  )
            {
                  if ( Last_Goal == Wall_Goal && Lift_Setpoint <= (Wall_Goal + Lift_C) && Lift_Setpoint >= (Wall_Goal - 46) && Lift_Status == Ready && Script == 0 && Tilt == Forward && Gripper == On && Ch6u_Armed == On )
                  {
                        Script = Wall_Goal ;
                        Stage = 1 ;
                        Secondary_Script = Off ;
                        Ch6u_Armed = Off ;
                  }
                  if ( Last_Goal == Movable_Weighted_Base && Lift_Setpoint <= (Movable_Weighted_Base + Lift_C) && Lift_Setpoint >= (Movable_Weighted_Base - 75) && Lift_Status == Ready && Script == 0 && Tilt == Forward && Gripper == On && Ch6u_Armed == On )
                  {
                        Script = Movable_Weighted_Base ;
                        Stage = 1 ;
                        Secondary_Script = Off ;
                        Ch6u_Armed = Off ;
                  }
                  if ( Ch6u_Armed == On && Lift_Status == Ready && Script == Off && Tilt == Forward && Gripper == On && Lift_Setpoint <= (Last_Goal - Lift_C) && ((Lift_Setpoint >= (Wall_Goal - 70) && Last_Goal == Wall_Goal) || (Lift_Setpoint >= (Movable_Weighted_Base - 105) && Last_Goal == Movable_Weighted_Base)) )
                  {
                        Gripper = Off ;
                        Ch6u_Armed = Off ;
                  }
                  if ( Lift_Limit < 10 && Script == 0 && Gripper == Off && Tilt == Forward && Ch6u_Armed == On )
                  {
                        Script = Pickup ;
                        Stage = 1 ;
                        Secondary_Script = Off ;
                        Ch6u_Armed = Off ;
                  }
                  if ( Gripper == Off && Tilt == Forward && Lift_Limit >= 10 && Script == Off && Ch6u_Armed == On && Lift_Setpoint != Pickup && Lift_Status == Ready )
                  {
                        Lift_Setpoint = Pickup ;
                        Gripper = Off ;
                        Ch6u_Armed = Off ;
                  }
                  if ( Lift_Encoder > 100 && Tilt == Back && Script == 0 && Ch6u_Armed == On )
                  {
                        Lift_Setpoint = Ladder ;
                        Ch6u_Armed = Off ;
                  }
            }
            if ( Ch6u == 0 && Ch6u_Armed == Off )
            {
                  Ch6u_Armed = On ;
            }
            if ( Ch6d == 0 && Ch6d_Armed == Off )
            {
                  Ch6d_Armed = On ;
            }
            if ( Lift_Setpoint == Wall_Goal )
            {
                  Last_Goal = Wall_Goal ;
            }
            if ( Lift_Setpoint == Movable_Weighted_Base )
            {
                  Last_Goal = Movable_Weighted_Base ;
            }
            if ( Lift_Setpoint == Descore_Wall_Goal || Lift_Setpoint == Descore_Wall_Goal2 )
            {
                  Last_Goal = Descore_Wall_Goal ;
            }
            if ( Lift_Setpoint == Descore_Movable_Weighted_Base )
            {
                  Last_Goal = Descore_Movable_Weighted_Base ;
            }
            if ( Hang == On && Gripper == On && Tilt == Forward )
            {
                  Hang = Off ;
            }
            if ( Lift_Limit < 10 || Lift_Setpoint == Pickup )
            {
                  if ( Tilt == Back && Hang == Off && Lift_Limit < 10 )
                  {
                        Hang = On ;
                  }
                  Last_Goal = Pickup ;
                  Descore_Armed = Off ;
            }
            Motor_Drive ( ) ;
      }
}

#include "Main.h"

void High_Hang ( void )
{
      Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, 0, 0, 0, Back, 200, 0, 0, 0 ) ;
      Autonomous_Control ( Line_Track, -50, -50, 0, 0, 0, 0, 40, 0, 0, Back, 2000, 0, 0, Line2 ) ;
      Autonomous_Control ( Line_Track, -50, -50, -20, -20, 0, 0, (Ladder - 39), 0, 0, Back, 1000, 0, 0, Encoder_Track ) ;
      Autonomous_Control ( Drive, 5, 15, 0, 0, 0, 0, (Ladder - 39), 0, 0, Back, 3000, 0, Coast, Lift_Ready ) ;
      Autonomous_Control ( Line_Track, -50, -50, -65, -65, 0, 0, (Ladder - 39), 0, 0, Back, 1000, 0, 0, Encoder_Track ) ;
      Autonomous_Control ( Drive, 6, 6, 0, 0, 0, 0, Ladder, 0, 0, Back, 2000, 250, 0, Lift_Ready ) ;
      Autonomous_Control ( Drive, -80, -80, 0, 0, 0, 0, Ladder, 0, 0, Back, 500, 0, 0, 0 ) ;
      Autonomous_Control ( Drive, -5, -5, 0, 0, 0, 0, Pickup, 0, 0, Back, 7000, 0, Coast, Lift_Ready ) ;
      SetMotor ( 3 , -127 ) ;
      SetMotor ( 4 , 127 ) ;
      SetMotor ( 5 , 127 ) ;
      SetMotor ( 6 , 127 ) ;
      SetMotor ( 9 , -127 ) ;
      SetMotor ( 10 , 127 ) ;
      Wait ( 400 ) ;
}

#include "Main.h"

void Motor_Drive ( void )
{
      Lift_Encoder = GetQuadEncoder ( 9 , 10 ) ;
      Lift_Limit = GetAnalogInput ( 4 ) ;
      if ( Lift_Limit < 10  )
      {
            PresetQuadEncoder ( 9 , 10 , 0) ;
      }
      if ( Script != Off )
      {
            Script_Functions (   ) ;
      }
      if ( (Ch5u == 0 && Ch5d == 0) || Lift_Reset == On || Ch5d_Armed == Off )
      {
            Error = (Lift_Setpoint - Lift_Encoder) ;
            if ( Error >= -Dead_Zone && Error <= Dead_Zone )
            {
                  if ( Lift_Setpoint == Pickup && Lift_Limit >= 10  )
                  {
                        Lift_Motor = -127 ;
                  }
                  if ( Lift_Setpoint == Pickup && Lift_Limit < 10 )
                  {
                        Lift_Status = Ready ;
                        if ( Tilt == Forward )
                        {
                              Lift_Motor = -5 ;
                        }
                        if ( Tilt == Back )
                        {
                              Lift_Motor = -10 ;
                        }
                  }
                  if ( Lift_Setpoint != Pickup && Lift_Limit >= 10 )
                  {
                        Lift_Motor = 10 ;
                        Lift_Status = Ready ;
                  }
            }
            if ( Error > Dead_Zone || Error < -Dead_Zone )
            {
                  if ( Error > 0 && Lift_Setpoint != Pickup && Lift_Setpoint <= Wall_Goal )
                  {
                        Lift_Motor = ((Error * 3) + 80) ;
                  }
                  if ( Error > 0 && Lift_Setpoint > Wall_Goal )
                  {
                        Lift_Motor = 127 ;
                  }
                  if ( Error > 0 && Lift_Setpoint == Pickup )
                  {
                        Lift_Motor = -45 ;
                  }
                  if ( Error < 0 && Lift_Setpoint == Pickup )
                  {
                        Lift_Motor = -127 ;
                  }
                  if ( Error < 0 && Lift_Setpoint != Pickup )
                  {
                        Lift_Motor = ((Error * 1.8) + 22) ;
                  }
                  Lift_Status = Moving ;
            }
            if ( Lift_Motor > 127 )
            {
                  Lift_Motor = 127 ;
            }
            if ( Lift_Motor < -127 )
            {
                  Lift_Motor = -127 ;
            }
            if ( Lift_Limit < 10 && Lift_Motor < -15 && Tilt == Forward )
            {
                  Lift_Motor = -15 ;
            }
      }
      if ( Lift_Encoder > (Ladder + 6) && Lift_Motor > 10 )
      {
            Lift_Motor = 10 ;
      }
      SetMotor ( 3 , Lift_Motor ) ;
      SetMotor ( 4 , (-Lift_Motor) ) ;
      SetMotor ( 5 , (-Lift_Motor) ) ;
      SetMotor ( 6 , (-Lift_Motor) ) ;
      SetMotor ( 9 , Lift_Motor ) ;
      SetMotor ( 10 , (-Lift_Motor) ) ;
      if ( Tilt == Back )
      {
            SetDigitalOutput ( 12 , 1 ) ;
      }
      if ( Tilt == Forward  )
      {
            SetDigitalOutput ( 12 , 0 ) ;
      }
      if ( Gripper == On )
      {
            SetDigitalOutput ( 11 , 1 ) ;
      }
      if ( Gripper == Off )
      {
            SetDigitalOutput ( 11 , 0 ) ;
      }
      SetMotor ( 1 , -Left_Motor ) ;
      SetMotor ( 2 , Right_Motor ) ;
      SetMotor ( 8 , Right_Motor ) ;
      SetMotor ( 7 , Left_Motor ) ;
}
#include "Main.h"

void Programming_Skills_Challenge ( void )
{
      Autonomous_Control ( Encoder_Track, 50, 50, 44, 44, 0, 0, Movable_Weighted_Base, On, 0, 0, 800, 0, Brake, Encoder_Track ) ;
      Autonomous_Control ( Encoder_Track, -15, 50, 0, 216, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Right_Encoder_Track ) ;
      Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 1000, 0, 0, Lift_Ready ) ;
      Autonomous_Control ( Encoder_Track, 50, 50, 145, 145, 0, 0, Movable_Weighted_Base, On, 0, 0, 1100, 0, Coast, Encoder_Track ) ;
      Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Movable_Weighted_Base, On, Movable_Weighted_Base, 0, 1300, 0, Coast, Script_Ready ) ;
      Wait ( 300 ) ; // #1
      Autonomous_Control ( Line_Track, -50, -50, -60, -60, 0, 0, 0, 0, 0, 0, 2000, 0, 0, Left_Encoder_Track ) ;
      Autonomous_Control ( Line_Track, -58, -58, -90, -90, 0, 0, 0, 0, 0, 0, 2000, 0, Brake, Left_Encoder_Track ) ;
      Autonomous_Control ( Encoder_Track, -63, 85, -101, 478, 0, 0, Pickup, 0, 0, 0, 2800, 0, Brake, Right_Encoder_Track ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 0, 0, Left, 16, 0, 0, 0, 0, 4000, 350, 0, Line2 ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 100, 100, Left, 17, 0, 0, 0, 0, 2000, 0, 0, Encoder_Track ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 0, 0, Left, 17, Pickup, Ready, 0, 0, 2000, 100, 0, No_Line2 ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 306, 306, Left, 17, Movable_Weighted_Base, On, 0, 0, 4000, 0, Brake, Encoder_Track ) ;
      Autonomous_Control ( Encoder_Track, 63, -63, 196, -197, 0, 0, Movable_Weighted_Base, On, 0, 0, 1000, 0, Brake, Encoder_Track ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 135, 135, Left, 39, Movable_Weighted_Base, On, 0, 0, 2000, 0, 0, Encoder_Track ) ;
      Autonomous_Control ( Wall_Track, 55, 55, 135, 135, Left, 39, Movable_Weighted_Base, On, 0, 0, 1500, 0, Coast, Encoder_Track ) ;
      Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Movable_Weighted_Base, On, Movable_Weighted_Base, 0, 2000, 0, Coast, Script_Ready ) ;
      Wait ( 150 ) ; // #2
      Autonomous_Control ( Encoder_Track, 80, 80, -130, -130, 0, 0, 0, 0, 0, 0, 2000, 0, Brake, Encoder_Track ) ;
      Autonomous_Control ( Encoder_Track, 63, 63, -143, 143, 0, 0, Pickup, 0, 0, 0, 1200, 0, Brake, Left_Encoder_Track ) ;
      Autonomous_Control ( Encoder_Track, 63, 63, 272, 272, 0, 0, Pickup, 0, 0, 0, 3000, 0, Brake, Encoder_Track ) ;
      Autonomous_Control ( Encoder_Track, 63, -10, 218, 0, 0, 0, Pickup, 0, 0, 0, 3000, 0, Brake, Left_Encoder_Track ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 0, 0, Left, 17, Pickup, 0, 0, 0, 3000, 0, 0, Line2 ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 100, 100, Left, 17, Pickup, Ready, 0, 0, 3000, 0, 0, Left_Encoder_Track ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 80, 80, Left, 17, Movable_Weighted_Base, On, 0, 0, 3000, 0, 0, Left_Encoder_Track ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 0, 0, Left, 17, Movable_Weighted_Base, On, 0, 0, 4000, 100, 0, No_Line2 ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 85, 85, Left, 17, Movable_Weighted_Base, On, 0, 0, 4000, 0, Coast, Left_Encoder_Track ) ;
      Autonomous_Control ( Drive, -10, -10, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 250, Coast, Lift_Ready ) ;
      Autonomous_Control ( Wall_Track, 55, 55, 160, 160, Left, 18, Movable_Weighted_Base, On, 0, 0, 2500, 0, Coast, Left_Encoder_Track ) ;
      Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Movable_Weighted_Base, On, Movable_Weighted_Base, 0, 2000, 0, Coast, Script_Ready ) ;
      Wait ( 150 ) ; // #3
      Autonomous_Control ( Encoder_Track, -63, -63, -160, -160, 0, 0, 0, 0, 0, 0, 3000, 0, Brake, Encoder_Track ) ;
      Autonomous_Control ( Encoder_Track, 63, -63, 106, -106, 0, 0, Pickup, 0, 0, 0, 1200, 0, Brake, Encoder_Track ) ;
      Autonomous_Control ( Drive, 63, 63, 0, 0, 0, 0, Pickup, 0, 0, 0, 1500, 200, 0, Line ) ;
      Autonomous_Control ( Encoder_Track, 63, 63, 52, 52, 0, 0, Pickup, 0, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
      Autonomous_Control ( Encoder_Track, 63, -10, 162, 0, 0, 0, Pickup, 0, 0, 0, 2500, 0, Brake, Left_Encoder_Track ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 0, 0, Left, 16, Pickup, 0, 0, 0, 3000, 500, 0, No_Line2 ) ;
      Autonomous_Control ( Wall_Track, 63, 63, 50, 50, Left, 16, Movable_Weighted_Base, On, 0, 0, 3000, 0, Coast, Left_Encoder_Track ) ;
      Autonomous_Control ( Drive, -7, -7, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 3000, 0, Coast, Lift_Ready ) ;
      Autonomous_Control ( Wall_Track, 55, 55, 175, 175, Left, 16, Movable_Weighted_Base, On, 0, 0, 3000, 0, Coast, Left_Encoder_Track ) ;
      Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Movable_Weighted_Base, On, Movable_Weighted_Base, 0, 2000, 0, Coast, Script_Ready ) ;
      Wait ( 150 ) ; // #4
      Autonomous_Control ( Encoder_Track, -63, -63, -243, -243, 0, 0, 0, 0, 0, 0, 2000, 0, Brake, Left_Encoder_Track ) ;
      Autonomous_Control ( Encoder_Track, 63, -63, 90, -91, 0, 0, Pickup, 0, 0, 0, 1000, 0, Brake, Encoder_Track ) ;
      Autonomous_Control ( Drive, 63, 63, 215, 215, 0, 0, 0, 0, 0, 0, 2000, 0, 0, Encoder_Track ) ;
      Autonomous_Control ( Wall_Track, 61, 61, 255, 255, Right, 8, Pickup, 0, 0, 0, 2000, 0, 0, Left_Encoder_Track ) ;
      // //
      Autonomous_Control ( Drive, 63, 63, 0, 0, 0, 0, Pickup, Ready, 0, 0, 2000, 0, 0, Line2 ) ;
      Autonomous_Control ( Drive, 63, 63, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 2000, 0, Brake, Line ) ;
      Autonomous_Control ( Drive, -7, -7, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 200, 0, 0, 0 ) ;
      Autonomous_Control ( Encoder_Track, -63, -63, -105, -105, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
      Autonomous_Control ( Encoder_Track, 63, 63, -285, 285, 0, 0, Movable_Weighted_Base, On, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
      Autonomous_Control ( Drive, 60, 60, 0, 0, 0, 0, Movable_Weighted_Base, On, 0, 0, 250, 250, 0, 0 ) ;
      Autonomous_Control ( Wall_Track, 60, 60, 260, 260, Right, 16, Movable_Weighted_Base, On, 0, 0, 3000, 0, 0, Left_Encoder_Track ) ;
      Autonomous_Control ( Drive, 15, 15, 0, 0, 0, 0, Movable_Weighted_Base, On, Movable_Weighted_Base, 0, 2000, 0, Coast, Script_Ready ) ;
      Wait ( 150 ) ; // #5
      if ( Autonomous_Code == 1 )
      {
            Autonomous_Control ( Encoder_Track, -63, -63, -125, -125, 0, 0, 0, 0, 0, 0, 2000, 0, Brake, Encoder_Track ) ;
            Autonomous_Control ( Encoder_Track, -63, 63, -380, 380, 0, 0, Pickup, 0, 0, 0, 3000, 0, Brake, Left_Encoder_Track ) ;
            Autonomous_Control ( Wall_Track, 61, 61, 400, 400, Left, 17, Pickup, 0, 0, 0, 2500, 0, 0, Left_Encoder_Track ) ;
            Autonomous_Control ( Wall_Track, 61, 61, 0, 0, Left, 17, Pickup, 0, 0, 0, 2500, 150, Brake, No_Line2 ) ;
            Autonomous_Control ( Drive, -12, -12, 0, 0, 0, 0, 0, 0, 0, 0, 100, 0, Coast, 0 ) ;
            Autonomous_Control ( Encoder_Track, 10, -63, 0, -190, 0, 0, 0, 0, 0, 0, 1000, 0, Brake, Right_Encoder_Track ) ;
            Autonomous_Control ( Drive, 60, 60, 0, 0, 0, 0, 15, 0, 0, 0, 2000, 700, 0, Line2 ) ;
            Autonomous_Control ( Drive, 50, 50, 0, 0, 0, 0, 15, 0, 0, 0, 1000, 0, Brake, Line ) ;
            Autonomous_Control ( Encoder_Track, 50, 50, -100, -100, 0, 0, 15, 0, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
            Autonomous_Control ( Drive, -55, 55, 0, 0, 0, 0, 0, 0, 0, 0, 1500, 0, Brake, Line ) ;
      }
      if ( Autonomous_Code == 2 )
      {
            Autonomous_Control ( Encoder_Track, -85, 10, -500, 0, 0, 0, 0, 0, 0, 0, 2000, 0, 0, Left_Encoder_Track ) ;
            Autonomous_Control ( Encoder_Track, -63, 63, -140, 140, 0, 0, Pickup, 0, 0, 0, 1200, 0, Brake, Encoder_Track ) ;
            Autonomous_Control ( Drive, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 100, 0, 0, 0 ) ;
            Autonomous_Control ( Wall_Track, 63, 63, 300, 300, Left, 5, Pickup, 0, 0, 0, 3000, 0, 0, Left_Encoder_Track ) ;
            Autonomous_Control ( Wall_Track, 63, 63, 0, 0, Left, 5, Pickup, 0, 0, 0, 2500, 50, 0, No_Line2 ) ;
            Autonomous_Control ( Wall_Track, 63, 63, 0, 0, Left, 5, Pickup, Ready, 0, 0, 1000, 50, 0, No_Line ) ;
            Autonomous_Control ( Wall_Track, 63, 63, 15, 15, Left, 5, Wall_Goal, On, 0, 0, 1000, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Drive, -15, -15, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 250, 0, 0, 0 ) ;
            Autonomous_Control ( Encoder_Track, -63, 18, -405, 0, 0, 0, Wall_Goal, On, 0, 0, 2000, 0, Brake, Left_Encoder_Track ) ;
            // //
            Autonomous_Control ( Drive, 0, 0, 0, 0, 0, 0, Wall_Goal, On, 0, 0, 3000, 0, 0, Lift_Ready ) ;
            Autonomous_Control ( Drive, 60, 60, 0, 0, 0, 0, 0, On, 0, 0, 100, 0, 0, 0 ) ;
            Autonomous_Control ( Wall_Track, 50, 50, 0, 0, Right, 38, Wall_Goal, On, 0, 0, 1000, 0, Coast, 0 ) ;
            Autonomous_Control ( Drive, 20, 20, 0, 0, 0, 0, Wall_Goal, On, Wall_Goal, 0, 2000, 0, Coast, Script_Ready ) ;
            Wait ( 250 ) ; // #6
            Autonomous_Control ( Drive, -63, -63, -100, -100, 0, 0, 0, 0, 0, 0, 1500, 0, 0, Encoder_Track ) ;
            Autonomous_Control ( Encoder_Track, -63, -63, -150, -150, 0, 0, Pickup, 0, 0, 0, 2000, 0, Brake, Encoder_Track ) ;
            Autonomous_Control ( Encoder_Track, -63, 15, -200, 0, 0, 0, Pickup, 0, 0, 0, 2000, 0, Brake, Left_Encoder_Track ) ;
            Autonomous_Control ( Drive, -55, -55, 0, 0, 0, 0, 15, 0, 0, 0, 1500, 0, 0, Line ) ;
            Autonomous_Control ( Encoder_Track, -55, -55, -60, -60, 0, 0, 15, 0, 0, 0, 1500, 0, Brake, Encoder_Track ) ;
            Autonomous_Control ( Drive, 60, -60, 0, 0, 0, 0, 0, 0, 0, 0, 1500, 0, Brake, Line ) ;
      }
      High_Hang ( ) ;
}

#include "Main.h"

void Script_Functions ( void )
{
      Timer4 = GetTimer ( 4 ) ;
      Gripper_Limit = GetAnalogInput ( 7 ) ;
      if ( Script == Wall_Goal && Stage != Off )
      {
            if ( Stage == 2 && Lift_Status == Ready )
            {
                  Gripper = Off ;
                  Stage = Off ;
                  Script = Off ;
                  if ( Secondary_Script == Off )
                  {
                        Descore_Armed = Descore_Wall_Goal ;
                  }
            }
            if ( Stage == 1 )
            {
                  if ( Secondary_Script == Off )
                  {
                        Lift_Setpoint = (Wall_Goal - 66) ;
                  }
                  if ( Secondary_Script == On )
                  {
                        Lift_Setpoint = (Wall_Goal - 36) ;
                  }
                  Stage = 2 ;
            }
      }
      if ( Script == Movable_Weighted_Base && Stage != Off )
      {
            if ( Stage == 2 && Lift_Status == Ready )
            {
                  Gripper = Off ;
                  Stage = Off ;
                  Script = Off ;
                  if ( Secondary_Script == Off )
                  {
                        Descore_Armed = Descore_Movable_Weighted_Base ;
                  }
            }
            if ( Stage == 1 )
            {
                  if ( Secondary_Script == Off && Preload == Off )
                  {
                        Lift_Setpoint = (Movable_Weighted_Base - 90) ;
                  }
                  if ( Secondary_Script == On )
                  {
                        Lift_Setpoint = (Movable_Weighted_Base - 50) ;
                  }
                  if ( Secondary_Script == Off && Preload == On )
                  {
                        Lift_Setpoint = (Movable_Weighted_Base - 102) ;
                        Preload = Off ;
                  }
                  Stage = 2 ;
            }
      }
      if ( Script == Pickup && Stage != Off )
      {
            if ( Stage == 4 && Timer4 > 200 )
            {
                  Lift_Setpoint = Pickup ;
                  Stage = Off ;
                  Script = Off ;
            }
            if ( Stage == 3 && Timer4 > 300 )
            {
                  if ( Gripper_Limit < 10 )
                  {
                        Stage = Off ;
                        Script = Off ;
                  }
                  if ( Gripper_Limit > 10 )
                  {
                        Lift_Setpoint = (Lift_Encoder + 5) ;
                        Lift_Status = Ready ;
                        Gripper = Off ;
                        Stage = 4 ;
                        PresetTimer ( 4 , 0 ) ;
                  }
            }
            if ( Stage == 2 && Timer4 > Gripper_Time )
            {
                  if ( Secondary_Script == Off )
                  {
                        Lift_Setpoint = Movable_Weighted_Base ;
                  }
                  if ( Secondary_Script == On )
                  {
                        Lift_Setpoint = Wall_Goal ;
                  }
                  Stage = 3 ;
                  PresetTimer ( 4 , 0 ) ;
            }
            if ( Stage == 1 )
            {
                  Gripper = On ;
                  Stage = 2 ;
            }
      }
      if ( Script == Descore_Wall_Goal && Stage != Off )
      {
            if ( Stage == 2 && Timer4 > Gripper_Time )
            {
                  Lift_Setpoint = Wall_Goal ;
                  Stage = Off ;
                  Script = Off ;
            }
            if ( Stage == 1 )
            {
                  PresetTimer ( 4 , 0 ) ;
                  Gripper = On ;
                  Stage = 2 ;
            }
      }
      if ( Script == Descore_Movable_Weighted_Base && Stage != Off )
      {
            if ( Stage == 2 && Timer4 > Gripper_Time )
            {
                  Lift_Setpoint = Movable_Weighted_Base ;
                  Stage = 2 ;
                  Stage = Off ;
                  Script = Off ;
            }
            if ( Stage == 1 )
            {
                  PresetTimer ( 4 , 0 ) ;
                  Gripper = On ;
                  Stage = 2 ;
            }
      }
      if ( Script == Ladder && Stage != Off )
      {
            if ( Stage == 3  )
            {
                  Lift_Setpoint = (Ladder - 38) ;
                  Stage = Off ;
                  Script = Off ;
            }
            if ( Stage == 2 && Lift_Status == Ready && Lift_Limit > 10 )
            {
                  Tilt = Back ;
                  Stage = 3 ;
            }
            if ( Stage == 1 )
            {
                  if ( (Secondary_Script == On && Timer4 > 150) || Secondary_Script == Off )
                  {
                        Lift_Setpoint = 15 ;
                        Stage = 2 ;
                  }
            }
            if ( Stage == -1 )
            {
                  Tilt = Forward ;
                  PresetTimer ( 4 , 0 ) ;
                  Stage = 1 ;
            }
      }
      if ( Script == Off )
      {
            Secondary_Script = Off ;
      }
}

#ifndef __API_H
#define __API_H

#include <stdio.h>

void IO_Initialization(void);
void DefineControllerIO(unsigned char ucP1, unsigned char ucP2, unsigned char ucP3, unsigned char ucP4,
                        unsigned char ucP5, unsigned char ucP6, unsigned char ucP7, unsigned char ucP8,
                        unsigned char ucP9, unsigned char ucP10, unsigned char ucP11, unsigned char ucP12);

void SetCompetitionMode(int nCompTime, int nOperTime);
void SetAutonomousMode(unsigned char ucMode);

unsigned char GetDigitalInput(unsigned char ucPort);
void SetDigitalOutput(unsigned char ucPort, unsigned char ucValue);
unsigned int GetAnalogInput(unsigned char ucPort);

void StartEncoder(unsigned char ucPort);
void StopEncoder(unsigned char ucPort);
long GetEncoder(unsigned char ucPort);
void PresetEncoder(unsigned char ucPort, long lPresetValue);

void StartQuadEncoder(unsigned char ucChannelA, unsigned char ucChannelB, unsigned char ucInvert);
void StopQuadEncoder(unsigned char ucChannelA, unsigned char ucChannelB);
long GetQuadEncoder(unsigned char ucChannelA, unsigned char ucChannelB);
void PresetQuadEncoder(unsigned char ucChannelA, unsigned char ucChannelB, long lPresetValue);

void StartInterruptWatcher(unsigned char port, unsigned char direction);
void StopInterruptWatcher(unsigned char port);
unsigned char GetInterruptWatcher(unsigned char port);

void SetMotor(unsigned char ucMotor, int iSpeed);
void SetServo(unsigned char ucMotor, int iSpeed);

void Arcade2(unsigned char ucJoystick,
                unsigned char ucMoveChannel, unsigned char ucRotateChannel,
                unsigned char ucLeftMotor, unsigned char ucRightMotor,
                unsigned char ucLeftInvert, unsigned char ucRightInvert);
void Arcade4(unsigned char ucJoystick,
            unsigned char ucMoveChannel, unsigned char ucRotateChannel,
            unsigned char ucLeftfrontMotor, unsigned char ucRightfrontMotor,
            unsigned char ucLeftrearMotor, unsigned char ucRightrearMotor,
            unsigned char ucLeftfrontInvert, unsigned char ucRightfrontInvert,
            unsigned char ucLeftrearInvert, unsigned char ucRightrearInvert);
void Tank2(unsigned char ucJoystick,
            unsigned char ucLeftChannel, unsigned char ucRightChannel,
            unsigned char ucLeftMotor, unsigned char ucRightMotor,
            unsigned char ucLeftInvert, unsigned char ucRightInvert);
void Tank4(unsigned char ucJoystick,
            unsigned char ucLeftChannel, unsigned char ucRightChannel,
            unsigned char ucLeftfrontMotor, unsigned char ucRightfrontMotor,
            unsigned char ucLeftrearMotor, unsigned char ucRightrearMotor,
            unsigned char ucLeftfrontInvert, unsigned char ucRightfrontInvert,
            unsigned char ucLeftrearInvert, unsigned char ucRightrearInvert);
void Holonomic(unsigned char ucJoystick,
        unsigned char ucMoveChannel1, unsigned char ucMoveChannel2, unsigned char ucRotateChannel,
            unsigned char ucLeftfrontMotor, unsigned char ucRightfrontMotor,
            unsigned char ucLeftrearMotor, unsigned char ucRightrearMotor,
            unsigned char ucLeftfrontInvert, unsigned char ucRightfrontInvert,
            unsigned char ucLeftrearInvert, unsigned char ucRightrearInvert);
void JoystickToMotor(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucMotor, unsigned char ucInv);
void JoystickToMotorAndLimit(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucMotor, unsigned char ucInv, unsigned char ucPositiveLimitSwitch, unsigned char ucNegativeLimitSwitch);
void JoystickToServo(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucMotor, unsigned char ucInv);
void JoystickDigitalToMotor(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucFirstButton, int nFirstButtonValue, unsigned char ucSecondButton, int nSecondButtonValue, unsigned char ucMotor);
void JoystickDigitalToServo(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucFirstButton, int nFirstButtonValue, unsigned char ucSecondButton, int nSecondButtonValue, unsigned char ucMotor);
void JoystickDigitalToMotorAndLimit(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucFirstButton, int nFirstButtonValue, unsigned char ucFirstLimitSwitch, unsigned char ucSecondButton, int nSecondButtonValue, unsigned char ucSecondLimitSwitch, unsigned char ucMotor);
void JoystickToDigitalOutput(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucButton, unsigned char ucDout);
void JoystickToDigitalLatch(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucButton, unsigned char ucDout);
int GetJoystickAnalog(unsigned char ucJoystick, unsigned char ucChannel);
unsigned char GetJoystickDigital(unsigned char ucJoystick, unsigned char ucChannel, unsigned char ucButton);
int GetJoystickAccelerometer(unsigned char ucJoystick, unsigned char ucAxis);
void GetJoystickAccelerometerEx(unsigned char ucJoystick, int *pnAxisX, int *pnAxisY);
void SetJoystickAnalogDeadband(unsigned char ucPort, unsigned char ucChannel, unsigned char ucPosValue, unsigned char ucNegValue);
void SetJoystickAccelDeadband(unsigned char ucPort, unsigned char ucAxis, unsigned char ucPosValue, unsigned char ucNegValue);

void PrintToScreen(const char *fmt, ...);

void Wait(unsigned long ulTime);
unsigned long GetMsClock(void);

void StartTimer(unsigned char ucTimerNumber);
void StopTimer(unsigned char ucTimerNumber);
void PresetTimer(unsigned char ucTimerNumber, unsigned long ulValue);
unsigned long GetTimer(unsigned char ucTimerNumber);

unsigned int GetUltrasonic(unsigned char ucEcho, unsigned char ucPing);
void StartUltrasonic(unsigned char ucEcho, unsigned char ucPing);
void StopUltrasonic(unsigned char ucEcho, unsigned char ucPing);

void ResetGD(void);
void ClearGD(unsigned char ucRow1, unsigned char ucCol1, unsigned char ucRow2, unsigned char ucCol2, unsigned char ucFrame);
void PrintTextToGD(unsigned char ucRow, unsigned char ucCol, unsigned long ulColor, const char *szText, ...);
void PrintFrameToGD(unsigned char ucRow1, unsigned char ucCol1, unsigned char ucRow2, unsigned char ucCol2, unsigned long ulColor);

float GetMainBattery();
float GetBackupBattery();

unsigned int GetRandomNumber(int nMin, int nMax);

void InitLCD(unsigned char ucPort);
unsigned char SetLCDText(unsigned char ucPort, unsigned char nLine, const char *szMsg, ...);
unsigned char SetLCDLight(unsigned char ucPort, unsigned char nLight);
void StartLCDButtonsWatcher(unsigned char ucPort);
void StopLCDButtonsWatcher(unsigned char ucPort);
void GetLCDButtonsWatcher(unsigned char ucPort, unsigned char *b1, unsigned char *b2, unsigned char *b3);

void InitAccelerometer(unsigned char ucPort);
void StartAccelerometer(unsigned char ucPort);
int GetAcceleration(unsigned char ucPort);
void StopAccelerometer(unsigned char ucPort);

void InitGyro(unsigned char ucPort);
void StartGyro(unsigned char ucPort);
void StopGyro(unsigned char ucPort);
int GetGyroAngle(unsigned char ucPort);
void SetGyroType(unsigned char ucPort, unsigned int nType);
void SetGyroDeadband(unsigned char ucPort, char cDeadband);
long GetGyroReal(unsigned char port);

double LogBase(double dX, double dBase);
double Log(double dX);
double Log10(double dX);
double Exp(double dX);
double Frexp(double dX, int *pExp);
double Ldexp(double dX, int nExp);
double Pow(double dX, double dY);
double Sqrt(double dX);
double Rad2Deg(double dRad);
double Deg2Rad(double dDeg);
double Sin(double dAngle, unsigned char ucUnits);
double Cos(double dAngle, unsigned char ucUnits);
double Tan(double dAngle, unsigned char ucUnits);
double Asin(double dX, unsigned char ucUnits);
double Acos(double dX, unsigned char ucUnits);
double Atan(double dX, unsigned char ucUnits);
unsigned int GetRandomNumber(int nMin, int nMax);
int Abs(int nX);
double Fabs(double dX);
double Floor(double dX);
double Ceil(double dX);
double Modf(double dX, double *pInt);
double Fmod(double dX, double dY);

void RegisterRepeatingTimer(unsigned long ulTime, void (*handler)(void));
void CancelTimer(void (*handler)(void));

void SetDebugInfo(unsigned char ucIsOn);

#endif
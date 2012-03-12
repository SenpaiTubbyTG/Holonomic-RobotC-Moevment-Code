Autonomous_Control 
#include "Main.h"
void Autonomous_Control ( int Navigation_Type, float Left_Motor_Setpoint, float Right_Motor_Setpoint, int Left_Encoder_Setpoint, int Right_Encoder_Setpoint, int Ultrasonic_Direction, int Ultrasonic_Set¬
point, int Lift_Height_Setpoint, int Gripper_Setpoint, int Script_Setpoint, int Tilt_Setpoint, int Max_Time, int Min_Time, int Stop, int Break_Option )
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
Autonomous_Control 2
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
      while ( IsEnabled(
) )
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
Autonomous_Control 3
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
Autonomous_Control 4
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
Autonomous_Control 5
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
Autonomous_Control 6
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
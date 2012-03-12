Driver_Control
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
                        if ( Lift_Setpoint == Wall_Goal || Lift_Setpoint == Movable_Weighted_Base || Lift_Setpoint == Descore_Wall_Goal ||  Lift_Setpoint == Descore_Wall_Goal2 || Lift_Setpoint == Descore_Mov¬
                        able_Weighted_Base )
                        {
                              Lift_Setpoint = (Lift_Setpoint + 1) ;
                        }
                        Lift_Status = Ready ;
                  }
                  if ( !(
(
(Script == Descore_Movable_Weighted_Base) || (Script == Descore_Wall_Goal)
) && Gripper_Limit < 10) )
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
Driver_Control 2
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
            Ch4 = (
(Ch4 * Angle) + Ch4) ;
            Ch3 = (
(Ch3 * Angle) + Ch3) ;
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
Driver_Control 3
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
Driver_Control 4
                  Armed1 = On ;
            }
            if ( (
(Gripper_Limit < 10) || (Ch6u == 1 && Ch6u_Armed == On) || (Ch6d == 1 && Ch6d_Armed == On)
) && Lift_Encoder > 75 && Lift_Encoder < 165 && Last_Goal == Descore_Wall_Goal && Lift_¬
            Status == Ready && Script == 0 && Gripper == Off )
            {
                  Script = Descore_Wall_Goal ;
                  Stage = 1 ;
                  Ch6d_Armed = Off ;
                  Ch6u_Armed = Off ;
                  Last_Goal = Pickup ;
                  Lift_Reset = On ;
            }
            if ( (
(Gripper_Limit < 10) || (Ch6u == 1 && Ch6u_Armed == On) || (Ch6d == 1 && Ch6d_Armed == On)
) && Lift_Encoder > 25 && Lift_Encoder < 125 &&  Last_Goal == Descore_Movable_Weighted¬
            _Base && Lift_Status == Ready && Script == 0 && Gripper == Off )
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
                  if ( Ch6d_Armed == On && Last_Goal == Wall_Goal && Lift_Setpoint <= (Wall_Goal + Lift_C) && Lift_Setpoint >= (Wall_Goal - Lift_C) && Lift_Status == Ready && Script == 0 && Gripper == O¬
                  n )
                  {
                        Script = Wall_Goal ;
                        Stage = 1 ;
                        Secondary_Script = On ;
                        Ch6d_Armed = Off ;
                  }
                  if ( Ch6d_Armed == On && Last_Goal == Movable_Weighted_Base && Lift_Setpoint <= (Movable_Weighted_Base + Lift_C) && Lift_Setpoint >= (Movable_Weighted_Base - Lift_C) && Lift_St¬
                  atus == Ready && Script == 0 && Gripper == On )
                  {
                        Script = Movable_Weighted_Base ;
                        Stage = 1 ;
                        Secondary_Script = On ;
                        Ch6d_Armed = Off ;
                  }
                  if ( Ch6d_Armed == On && Lift_Status == Ready && Script == Off && Tilt == Forward && Gripper == On && Lift_Setpoint <= (Last_Goal - Lift_C) && (
(Lift_Setpoint >= (Wall_Goal - 70) && Las¬
                  t_Goal == Wall_Goal) || (Lift_Setpoint >= (Movable_Weighted_Base - 105) && Last_Goal == Movable_Weighted_Base)
) )
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
                  if ( Ch6d_Armed == On &&  Gripper == Off && Gripper_Limit > 10 && Tilt == Forward && Lift_Setpoint != Descore_Wall_Goal && Lift_Setpoint != Descore_Movable_Weighted_Base && Lift_L¬
                  imit >= 10 && Script == Off && Lift_Setpoint != Pickup && Lift_Status == Ready )
                  {
                        Lift_Setpoint = Pickup ;
                        Gripper = Off ;
                        Ch6d_Armed = Off ;
                  }
            }
            if ( Ch6d == 0 && Ch6u == 1  )
            {
                  if ( Last_Goal == Wall_Goal && Lift_Setpoint <= (Wall_Goal + Lift_C) && Lift_Setpoint >= (Wall_Goal - 46) && Lift_Status == Ready && Script == 0 && Tilt == Forward && Gripper == On && C¬
                  h6u_Armed == On )
                  {
                        Script = Wall_Goal ;
                        Stage = 1 ;
                        Secondary_Script = Off ;
                        Ch6u_Armed = Off ;
                  }
                  if ( Last_Goal == Movable_Weighted_Base && Lift_Setpoint <= (Movable_Weighted_Base + Lift_C) && Lift_Setpoint >= (Movable_Weighted_Base - 75) && Lift_Status == Ready && Script ==¬
                   0 && Tilt == Forward && Gripper == On && Ch6u_Armed == On )
                  {
                        Script = Movable_Weighted_Base ;
                        Stage = 1 ;
                        Secondary_Script = Off ;
                        Ch6u_Armed = Off ;
                  }
                  if ( Ch6u_Armed == On && Lift_Status == Ready && Script == Off && Tilt == Forward && Gripper == On && Lift_Setpoint <= (Last_Goal - Lift_C) && (
(Lift_Setpoint >= (Wall_Goal - 70) && Las¬
                  t_Goal == Wall_Goal) || (Lift_Setpoint >= (Movable_Weighted_Base - 105) && Last_Goal == Movable_Weighted_Base)
) )
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
Driver_Control 5
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
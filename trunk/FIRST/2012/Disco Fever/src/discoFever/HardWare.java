/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package discoFever;

import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.camera.AxisCamera;

public class Hardware {
   
   //DriveTrain Hardware  
   private static Encoder m_flEncoder;
   private static Encoder m_frEncoder;
   private static Encoder m_blEncoder;
   private static Encoder m_brEncoder;
   private static Jaguar m_flJaguar;
   private static Jaguar m_frJaguar;
   private static Jaguar m_blJaguar;
   private static Jaguar m_brJaguar;
   //// more motors for banebaots and fisherprice
   public static DiscoFeverDrive m_drive;
   
   //collector 
   private static DiscoFeverCollector m_collector;
   private static DiscoFeverLauncher m_launcher;
   
}



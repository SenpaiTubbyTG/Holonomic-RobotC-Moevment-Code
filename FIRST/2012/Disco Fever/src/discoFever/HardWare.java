/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package discoFever;

import edu.wpi.first.wpilibj.DriverStationLCD;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.camera.AxisCamera;

public class HardWare {
   
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
   
   public static Joystick m_leftStick = new Joystick(1);
   public static Joystick m_rightStick = new Joystick(2); 
   
   //collector 
   public static DiscoFeverCollector m_collector;
   
   //launcher
   public static DiscoFeverLauncher m_launcher;
   
   //camera
   public static AxisCamera m_camera = AxisCamera.getInstance();
   
   
   public static void cameraToDriversStation(){
       m_camera.writeResolution(AxisCamera.ResolutionT.k320x240);
       m_camera.writeBrightness(0);
       DriverStationLCD.getInstance().updateLCD();
   }
   
}



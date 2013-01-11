/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.disco2013;
import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Relay;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.Victor;

/**
 *
 * @author Doris
 */
public class HW {
  //------------------------------------
//      Public Constants
//------------------------------------
//------------------------------------
//       Module Locations
//------------------------------------
    /** -------------------------------------------------------
    The slot where the default analog Module is located
    ------------------------------------------------------- */
    public static int kAnalogModuleSlot = 0;
    /** -------------------------------------------------------
    The slot where the second analog Module is located
    ------------------------------------------------------- */
    public static int kSecondAnalogModuleSlot = 0;
    /** -------------------------------------------------------
    The slot where the default Digital Module is located
    ------------------------------------------------------- */
    public static int kDigitalModuleSlot = 4;
    /** -------------------------------------------------------
    The slot where the second Digital Module is located
    ------------------------------------------------------- */
    public static int kSecondDigitalModuleSlot = 6;
    /** -------------------------------------------------------
    The slot where the default Solenoid Module is located
    ------------------------------------------------------- */
    public static int kSolenoidModuleSlot = 8;
    
    public static Victor LFM = new Victor(1);
    public static Victor LBM = new Victor(2);
    public static Victor RFM = new Victor(3);
    public static Victor RBM = new Victor(4);
    public static Victor Shooter1 = new Victor(5);
    public static Victor Shooter2 = new Victor(6);
    public static Victor Collect1 = new Victor(7);
    public static Victor Collect2 = new Victor(8);
    
    public static RobotDrive drive = new RobotDrive(LFM,LBM,RFM,RBM);
    
    public static Joystick Stick1 = new Joystick(1);
    public static Joystick Stick2 = new Joystick(2);
    
    public static Compressor compressor = new Compressor(1,1);
    public static Relay liftRelay = new Relay(2);
    
}

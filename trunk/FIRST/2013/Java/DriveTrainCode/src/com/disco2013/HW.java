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
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.Ultrasonic;

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
    
    public static Compressor compressor = new Compressor(1,1);
    public static Relay liftRelay = new Relay(2);
 
    public static Victor LBM = new Victor(1);
    public static Victor LFM = new Victor(2);
//    public static Victor Collect2 = new Victor(6);
    public static Victor RBM = new Victor(3);
//    public static Victor Collect1 = new Victor(5);
    public static Victor Shooter1 = new Victor(7);
    public static Victor RFM = new Victor(4);
    public static Victor Shooter2 = new Victor(8);
    public static GamePad Stick1 = new GamePad(1, GamePad.MODE_D);
    public static RobotDrive drive = new RobotDrive(LFM, LBM, RFM, RBM);
//    public static Encoder encoder1 = new Encoder(1,2);
//    public static Encoder encoder2 = new Encoder(3,4);
//    public static Ultrasonic ultra1 = new Ultrasonic(1,1,1,1);
//    public static Ultrasonic ultra2 = new Ultrasonic(2,2,2,2);
//    public static Ultrasonic ultra3 = new Ultrasonic(3,3,3,3);

   
    
    
}

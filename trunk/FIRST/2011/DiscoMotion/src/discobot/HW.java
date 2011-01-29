//====================================================================
// FILE NAME: HW.java (Team 2587 - Discobots)
//
// CREATED ON: Jan 23, 2010
// CREATED BY: Allen Gregory
// MODIFIED ON:
// MODIFIED BY:
// ABSTRACT:
//	 This file allows us to declare the hardware for the robot in one place
//
//====================================================================
package discobot;

import DriveControllers.DiscoDrive;
import Sensors.*;
import edu.wpi.first.wpilibj.*;
//import edu.wpi.first.addons.*;

/**
 * @purpose puts all of the hardware declarations into one
place.  In addition, it makes them available to
both autonomous and teleop.
 * @author Allen Gregory and pavchag
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
//------------------------------------
//         Jaguar class
//------------------------------------
//------------------------------------
//         Drive motors
//------------------------------------
    public static Jaguar frontLeftDM = new Jaguar(1);
    public static Jaguar frontRightDM = new Jaguar(2);
    public static Jaguar rearRightDM = new Jaguar(3);
    public static Jaguar rearLeftDM = new Jaguar(4);

    public static DiscoDrive drive = new DiscoDrive(frontLeftDM, frontRightDM, rearRightDM, rearLeftDM);

//------------------------------------
//          DriverStations class
//------------------------------------
    /**
     *  Get an instance of the driverstation to use in our code
     */
    public static DriverStation driverStation =
            DriverStation.getInstance();
    // public static TrackerDashboard trackerDash =
    //        new TrackerDashboard();
//------------------------------------
//              Joystick classes
//------------------------------------
    /**
     *  Defines Drive Joystick 1
     */
    public static Joystick driveStickLeft =
            new Joystick(1);
    /**
     *  Defines Drive Joystick 2
     */
    public static Joystick driveStickRight =
            new Joystick(2);
    /**
     *  Kicker Joystick
     */
    public static Joystick liftHandle =
            new Joystick(3);

//-------------------------------------
//          Digital classes
//-------------------------------------
    /**
     *  The Front Encoders
     */
    public static DiscoEncoder frontLeftEncoder =
            new DiscoEncoder(1, 2, false, Encoder.EncodingType.k2X);
    public static DiscoEncoder frontRightEncoder =
            new DiscoEncoder(3, 4, false, Encoder.EncodingType.k2X);
    /**
     *  The Rear Encoder
     */
    public static DiscoEncoder rearRightEncoder =
            new DiscoEncoder(5, 6, false, Encoder.EncodingType.k2X);
    public static DiscoEncoder rearLeftEncoder =
            new DiscoEncoder(7, 8, false, Encoder.EncodingType.k2X);

    //-------------------------------------
    //      LCD class
    //-------------------------------------
    /**
     *  The instance of the driverStationLCD that we will use
     */
    public static DriverStationLCD lcd =
            DriverStationLCD.getInstance();
}


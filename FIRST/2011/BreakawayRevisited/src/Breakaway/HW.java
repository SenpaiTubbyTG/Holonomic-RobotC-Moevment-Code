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
package Breakaway;

import DriveControllers.*;
import DriveControllers.DiscoDriveConverter.Output;
import Utils.*;
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
    public static Jaguar leftDriveMotor
            = new Jaguar(7);
    public static Jaguar rightDriveMotor
            = new Jaguar(8);
    public static Jaguar frontDriveMotor
            = new Jaguar(9);
    public static Jaguar rearDriveMotor
            = new Jaguar(6);
    public static Jaguar leftDribbler
            = new Jaguar(5);
    public static Jaguar rightDribbler
            = new Jaguar(4);
    public static Jaguar kickerMotor
            = new Jaguar(1);
    public static Jaguar kickerBar
            = new Jaguar(2);

//------------------------------------
//      Servo Class
//------------------------------------
    /*
     *  Servo that is used to Pan the Camera
     */
    public static Servo camPan =
            new Servo(6,9);
    /**
     *  Servo that is used to Tilt the Camera
     */
    public static Servo camTilt =
            new Servo(6,10);
//------------------------------------
//         Relay classes
//------------------------------------
    /**
     *  The Relay that is used with the Kicker
     */
/*    public static Relay kickerRelay =
            new Relay(4);
 */
//------------------------------------
//         Compressor class - runs the compressor
//            with a single relay
//------------------------------------
    /**
     *  The Compressor and Pressure Switch
     */
   /* public static Compressor compressor =
            new Compressor(14, //Presure Sensor
            1 ); //Compressor
    */
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
    public static Joystick kickhandle =
            new Joystick(3);
//------------------------------------
//             Analog classes
//------------------------------------
//------------------------------------
//                Gyro class
//------------------------------------
    /**
     *  Defines The Raw Gyro Channel
     * We declare a raw_gyro so that we can get at the
     * raw values of the gyro if we need them.
     */
    public static AnalogChannel rawGyro =
            new AnalogChannel(1);
    /**
     *  Assign the WPI gyro the rawGyro
     */
    public static Gyro gyro =
            new Gyro(rawGyro);

    /*
     * Turning PIDController and its used driveConverter
     */

    public static DiscoDriveConverter driveConverter =
            new DiscoDriveConverter(0.0, 0.0, 0.0, Output.kSpeed);
    public static PIDController gyroController =
            new PIDController(0.1, 0.0, 0.45, HW.gyro, driveConverter);

    /*
     * Gyro Datalogger
     */
    public static DataLogger gyroLog =
            new DataLogger("Gyro", "gyro angle");
//------------------------------------
//                Accelerometer class
//------------------------------------
    /**
     *  The accelerometer
     */
    public static ADXL345_I2C accel =
            new ADXL345_I2C(4, ADXL345_I2C.DataFormat_Range.k8G);
//-------------------------------------
//          Digital classes
//-------------------------------------
     /**
     *  The Front Encoder
     */
     public static DiscoEncoder EncoderLeft =
        new DiscoEncoder(11, 12, true, Encoder.EncodingType.k2X);
    /**
     *  The Rear Encoder
     */
     public static DiscoEncoder EncoderRight =
         new DiscoEncoder(9, 10, true, Encoder.EncodingType.k2X);

     public static DigitalInput limit1 =
            new DigitalInput(3);

    public static DigitalInput limit2 =
            new DigitalInput(4);

    public static DigitalInput limit3 =
            new DigitalInput(5);


    /*
    public static DigitalInput kickSwitch =
            new DigitalInput(3);

    public static DigitalInput loadSwitch =
            new DigitalInput(4);

    public static DigitalInput barUpSwitch =
            new DigitalInput(6,3);

    public static DigitalInput barDownSwitch =
            new DigitalInput(6,5);
    */
    
    //-------------------------------------
    //      LCD class
    //-------------------------------------
    /**
     *  The instance of the driverStationLCD that we will use
     */
    public static DriverStationLCD lcd =
            DriverStationLCD.getInstance();
//-------------------------------------
//                 Ancillary classes
//-------------------------------------

    /*public static DataLogger rightVCLog =
            new DataLogger("rightVC Log", "rightVCError");
    public static DataLogger leftVCLog =
            new DataLogger("leftVC Log", "leftVCError");*/

   /* public static VelocityController leftVC =
            new VelocityController(EncoderLeft, leftDriveMotor);

    public static VelocityController rightVC =
            new VelocityController(EncoderRight, rightDriveMotor);
*/
    //public static OrientationController turnController =
      //      new OrientationController(gyro, rightVC, leftVC);

    //public static VelocityController2 rightVC = new VelocityController2(0.003, 0.0, 0.0, EncoderRight, rightDriveMotor);
    //public static VelocityController2 leftVC = new VelocityController2(0.003, 0.0, 0.0, EncoderLeft, leftDriveMotor);
    //public static DataLogger vcDataLogger = new DataLogger("vc", "output");
//-------------------------------------
//                 Ultrasonic class
//-------------------------------------
    public static MaxbotixSonar sonar =
            new MaxbotixSonar(2);

    //public static DataLogger sonarLog =
      //      new DataLogger("Sonar Log", "range (in)");

    //public static SonarController sonarController =
      //      new SonarController(sonar, 0.065, 0.0, 0.102);

//-------------------------------------
//                 Autonomous class
//-------------------------------------
   public static RobotDrive drive = new RobotDrive(leftDriveMotor,rightDriveMotor);

   public static DigitalInput autonMode = new DigitalInput(6,8);
   //public static DigitalInput backZoneAuton = new DigitalInput(6,9);

} // end class



package disco;

import edu.wpi.first.wpilibj.Preferences;

/**
 * The HW is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
public class HW {

    /**
     * Hardware
     */

    //REGULAR 3CIM GEARBOXES. MUST UPDATE VALUES AFTER LSR
    public static final double wheelRadius=2.0;//in
    public static final double wheelSeparation=18.0;//in
    public static final double driveReduction=0.5;  //KNOWN INCORRECT
    public static final double maxFPS=9;    //KNOWN INCORRECT

    //CUSTOM 3CIM SHIFTING GEARBOXES. FIND VALUES.
//    public static final double wheelRadius=2.0;//in
//    public static final double wheelSeparation=18.0;//in
//    public static final double driveReduction=0.5;
//    public static final double maxFPS=9;    //TODO: Test

    //DON'T NEED TO CHANGE THESE
    public static final double encoderTicksPerRev=128/driveReduction;
    public static final double distancePerRev=2*Math.PI*wheelRadius;
    public static final double distancePerPulse=distancePerRev/encoderTicksPerRev;

    /*
     * User Variables
     */
    public static Preferences preferences=Preferences.getInstance();



    /** -------------------------------------------------------
    Motors
    ------------------------------------------------------- */
    public static final int LeftDrive1Channel=1,    LeftDrive1Slot=1,
			    LeftDrive2Channel=2,    LeftDrive2Slot=1,
			    RightDrive1Channel=3,   RightDrive1Slot=1,
			    RightDrive2Channel=4,   RightDrive2Slot=1,

			    ShooterFrontChannel=1,	    ShooterFrontSlot=2, // 6
			    ShooterBackChannel=2,	    ShooterBackSlot=2; // 4
    /** -------------------------------------------------------
    Relays
    ------------------------------------------------------- */
    public static final int compressorChannel = 2,      compressorSlot = 2;

    /** -------------------------------------------------------
    Solenoids
    ------------------------------------------------------- */
    public static final int shootPneumaticChannel=6,
                            clearSmallChannel=5,
                            encoder1PowerChannel=7,
                            encoder2PowerChannel=8,
			    leftShiftChannel=2,
			    rightShiftChannel=3;

    /** -------------------------------------------------------
    Sensors
    ------------------------------------------------------- */
    public static final int //Digital
                            leftEncoderAChannel=5,
			    leftEncoderBChannel=6,	leftEncoderSlot=1,
			    rightEncoderAChannel=4,
			    rightEncoderBChannel=3,	rightEncoderSlot=1,

			    shooterEncoderFrontChannel=1,	shooterEncoderFrontSlot=1,
                            shooterEncoderBackChannel=2,	shooterEncoderBackSlot=1,

                            pressureSwitchChannel=14,    pressureSwitchSlot=2,

                            limitSwitchLeftChannel = 7, limitSwitchLeftSlot = 1,
                            limitSwitchRightChannel =14, limitSwitchRightSlot = 1,


                            //Analog
                            gyroChannel = 1, gyroSlot = 1,
                            maxbotixsonar1Channel=4,    maxbotixsonar1Slot=1,
                            maxbotixsonar2Channel=5,    maxbotixsonar2Slot=1,
                            maxbotixsonar3Channel=6,    maxbotixsonar3Slot=1,

                            autonPotChannel=2,          autonPotSlot=1,

                            frisbeeLoadedChannel=3,     frisbeeLoadedSlot=1;


}
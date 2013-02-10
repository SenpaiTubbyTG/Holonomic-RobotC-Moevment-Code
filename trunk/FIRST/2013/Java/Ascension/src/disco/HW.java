package disco;

import edu.wpi.first.wpilibj.camera.AxisCamera;

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
    public static double wheelRadius=2.5;//in
    public static double wheelSeparation=18.5;//in
    public static int encoderTicks=128;
    
    /** -------------------------------------------------------
    Motors
    ------------------------------------------------------- */
    public static final int LeftDrive1Channel=1,    LeftDrive1Slot=1,
			    LeftDrive2Channel=2,    LeftDrive2Slot=1,
			    RightDrive1Channel=3,   RightDrive1Slot=1,
			    RightDrive2Channel=4,   RightDrive2Slot=1,
            
			    Collect1Channel=4,	    Collect1Slot=2,
			    Collect2Channel=9,	    Collect2Slot=2,
            
			    ShooterFrontChannel=1,	    ShooterFrontSlot=2,
			    ShooterBackChannel=3,	    ShooterBackSlot=2;
    /** -------------------------------------------------------
    Relays
    ------------------------------------------------------- */
    public static final int compressorChannel = 2,  compressorSlot = 2,
                            shootPneumaticChannel=1,    shootPneumaticSlot=2;
    /** -------------------------------------------------------
    Solenoids
    ------------------------------------------------------- */
            
    /** -------------------------------------------------------
    Sensors
    ------------------------------------------------------- */
    public static final int //Digital
                            leftEncoderAChannel=2,
			    leftEncoderBChannel=1,	leftEncoderSlot=1,
			    rightEncoderAChannel=2,
			    rightEncoderBChannel=1,	rightEncoderSlot=2,
            
			    shooterEncoderFrontChannel=3,	shooterEncoderFrontSlot=1,
                            shooterEncoderBackChannel=4,	shooterEncoderBackSlot=1,
            
                            pressureSwitchChannel=14,    pressureSwitchSlot=2,
                            
                            limitSwitchLeftChannel = 10, limitSwitchLeftSlot = 1,
                            limitSwitchRightChannel =10, limitSwitchRightSlot = 2,
                            //Analog
                            gyroChannel = 2, gyroSlot = 1,
                            maxbotixsonar1Channel=1,    maxbotixsonar1Slot=1,
                            maxbotixsonar2Channel=3,    maxbotixsonar2Slot=1,
                            maxbotixsonar3Channel=4,    maxbotixsonar3Slot=1;
    
                            
}

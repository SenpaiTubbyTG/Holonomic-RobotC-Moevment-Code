package disco;

/**
 * The HW is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
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
    public static int kDigitalModuleSlot = 4;	//Really?
    /** -------------------------------------------------------
    The slot where the second Digital Module is located
    ------------------------------------------------------- */
    public static int kSecondDigitalModuleSlot = 6;
    /** -------------------------------------------------------
    The slot where the default Solenoid Module is located
    ------------------------------------------------------- */
    public static int kSolenoidModuleSlot = 8;

//    public static Compressor compressor = new Compressor(1,1);
//    public static Relay liftRelay = new Relay(2);

    /** -------------------------------------------------------
    Motors
    ------------------------------------------------------- */
    public static final int LeftDrive1Channel=1,    LeftDrive1Slot=1,
			    LeftDrive2Channel=2,    LeftDrive2Slot=1,
			    RightDrive1Channel=3,   RightDrive1Slot=1,
			    RightDrive2Channel=4,   RightDrive2Slot=1,
            
			    Collect1Channel=4,	    Collect1Slot=2,
			    Collect2Channel=9,	    Collect2Slot=2,
            
			    Shooter1Channel=1,	    Shooter1Slot=2,
			    Shooter2Channel=3,	    Shooter2Slot=2;
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
                            leftEncoderAChannel=10,
			    leftEncoderBChannel=10,	leftEncoderSlot=1,
			    rightEncoderAChannel=10,
			    rightEncoderBChannel=10,	rightEncoderSlot=1,
            
			    shooterEncoderChannel=3,	shooterEncoderSlot=1,
                            shooterEncoder2Channel=4,	shooterEncoder2Slot=1,
            
                            pressureSwitchChannel=1,    pressureSwitchSlot=2,
                            
                            limitSwitchLeftChannel = 10, limitSwitchLeftSlot = 1,
                            limitSwitchRightChannel =10, limitSwitchRightSlot = 2,
                            //Analog
                            gyroChannel = 10, gyroSlot = 1,
                            maxbotixsonar1Channel=1,    maxbotixsonar1Slot=1,
                            maxbotixsonar2Channel=2,    maxbotixsonar2Slot=1,
                            maxbotixsonar3Channel=3,    maxbotixsonar3Slot=1;
    
                            
}

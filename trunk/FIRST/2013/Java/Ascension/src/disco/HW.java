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
            
			    Collect1Channel=7,	    Collect1Slot=1,
			    Collect2Channel=3,	    Collect2Slot=2,
            
			    Shooter1Channel=2,	    Shooter1Slot=2,
			    Shooter2Channel=4,	    Shooter2Slot=2;
    /** -------------------------------------------------------
    Relays
    ------------------------------------------------------- */
    public static final int compressorSlot = 3,
                            compressorChannel = 5;
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
            
			    shooterEncoderChannel=1,	shooterEncoderSlot=2,
            
			    ultrasonic1PingChannel=1,
			    ultrasonic1EchoChannel=2,	ultrasonic1Slot=1,
			    ultrasonic2PingChannel=7,
			    ultrasonic2EchoChannel=8,	ultrasonic2Slot=1,
			    ultrasonic3PingChannel=9,
			    ultrasonic3EchoChannel=10,	ultrasonic3Slot=1,
                            //Analog
                            maxbotixsonar1Channel=1,    maxbotixsonar1Slot=1,
            
                            pressureSwitchSlot = 2,
                            pressureSwitchChannel = 5;
}

package disco.practice;

/**
 * The HW is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
public class HW {

        public static final int
                     // motor port assignment
                     leftFrontDriveChannel   =9,   leftFrontDriveSlot  =1,	//12/24/12
                     leftBackDriveChannel    =10/*9*/,  leftBackDriveSlot   =1,	//""
                     rightFrontDriveChannel  =7,   rightFrontDriveSlot =1,	//""
                     rightBackDriveChannel   =8/*7*/,   rightBackDriveSlot  =1,	//""
                     mouthChannel            =2,   mouthSlot           =2,	//""
                     indexerChannel          =1,   indexerSlot         =2,	//""
                     shooter1Channel         =5,   shooter1Slot        =1,	//""
                     shooter2Channel         =6,   shooter2Slot        =1,	//""
                     tiltMotorChannel        =4,   tiltMotorSlot       =1,	//""
                     // Pneumatic Solenoids
                     lowerWhackerChannel     =5,   whackerSlot         =1,	//""
                     liftWhackerChannel      =6,					//""
                     liftBrakeChannel        =7,   brakeSlot           =2,	//UNPLUGGED
                     lowerBrakeChannel       =8,					//UNPLUGGED
                     // Digital inputs
                     chamberChannel          =3,   chamberSlot         =1,	//UNPLUGGED
                     bridgeChannel           =7,   bridgeSlot          =2,	//UNPLUGGED
                     encoderChannel          =9,   encoderSlot         =2,	//12/24/12
                     pressureSwitchChannel   =1,   pressureSwitchSlot  =1,	//""
		     hoodFarChannel	     =11,  hoodFarSlot=1,		//""
		     hoodKeyChannel	     =10,  hoodKeySlot=1,		//""
                     // analog inputs
                     potChannel              =3,   potSlot             =1,	//UNPLUGGED
                     // relay  output (spotlight and compressor)
                     spotlightChannel        =4,   spotlightSlot       =2,	//ACTUALLY CONNECTED TO INDEXER
                     indexerLEDChannel       =1,   indexerLEDSlot      =2,	//12/24/12
                     shooterLEDChannel       =2,   shooterLEDSlot      =2,	//UNPLUGGED
                     compressorChannel       =1,   compressorSlot      =1;	//12/24/12

        public static final String  cameraAddress = "10.25.87.11",
                                    coprocAddress = "";
}

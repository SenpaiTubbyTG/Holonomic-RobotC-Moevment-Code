package disco;

import disco.utils.GamePad;
import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.Relay;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.Victor;

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

    public static Compressor compressor = new Compressor(1,1);
    public static Relay liftRelay = new Relay(2);

    /** -------------------------------------------------------
    Motors
    ------------------------------------------------------- */
    public static final int LeftDrive1Channel=1,    LeftDrive1Slot=1,
			    LeftDrive2Channel=2,    LeftDrive2Slot=1,
			    RightDrive1Channel=3,   RightDrive1Slot=1,
			    RightDrive2Channel=4,   RightDrive2Slot=1,
			    Collect1Channel=5,	    Collect1Slot=1,
			    Collect2Channel=6,	    Collect2Slot=1,
			    Shooter1Channel=7,	    Shooter1Slot=1,
			    Shooter2Channel=8,	    Shooter2Slot=1,
                            DiscoEncoderChannel=1,  DiscoEncoderSlot=1;
  /** -------------------------------------------------------
    Relays
    ------------------------------------------------------- */

    /** -------------------------------------------------------
    Solenoids
    ------------------------------------------------------- */

    /** -------------------------------------------------------
    Sensors
    ------------------------------------------------------- */
}

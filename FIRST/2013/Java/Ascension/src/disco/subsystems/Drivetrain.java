/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.subsystems;

import disco.HW;
import disco.commands.drivetrain.JoyArcadeTwoSpeed;
import disco.utils.MaxbotixSonar;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.Ultrasonic;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.PIDSubsystem;
import edu.wpi.first.wpilibj.command.Subsystem;


/**README
 * This class is in the middle of being set up to use PID control for both distance with sonars and distance with encoders.
 * As you can see, this is unfinished.
 * I realized that we should investigate using commands that incorporate the PID control and that just give PWM values to the drivetrain.
 * We won't be able to use this nice PIDSubsystem stuff, but we will be able to do more complicated things.
 */
public class Drivetrain extends PIDSubsystem {
    private Victor leftDrive1;
    private Victor leftDrive2;
    private Victor RightDrive1;
    private Victor RightDrive2;
    private RobotDrive drive;

    private static double  kP_range=0.01,
		    kI_range=0,
		    kD_range=0;
    private static double  kP_distance=0,
		    kI_distance=0,
		    kD_distance=0;
    private DriveMode thismode;

    private MaxbotixSonar sonar1;
    private Ultrasonic ultra1;
    private Encoder leftEncoder;
    private Encoder rightEncoder;


    public static class DriveMode {

        /**
         * The integer value representing this enumeration
         */
        public final int value;
        static final int range_val = 0;
        static final int distance_val = 1;
        static final int driver_val = 2;
        /**
         * Drive with sonar
         */
        public static final DriveMode Range = new DriveMode(range_val);
        /**
         * Drive with encoders
         */
        public static final DriveMode Distance = new DriveMode(distance_val);
	/**
         * Drive with joysticks
         */
        public static final DriveMode Driver = new DriveMode(driver_val);

        private DriveMode(int value) {
            this.value = value;
        }
    }

    public Drivetrain(){
	super("Drivetrain",kP_range,kI_range,kD_range);
	disable();
	leftDrive1=new Victor(HW.LeftDrive1Slot,HW.LeftDrive1Channel);
	leftDrive2=new Victor(HW.LeftDrive2Slot,HW.LeftDrive2Channel);
	RightDrive1=new Victor(HW.RightDrive1Slot,HW.RightDrive1Channel);
	RightDrive2=new Victor(HW.RightDrive2Slot,HW.RightDrive2Channel);
	drive=new RobotDrive(leftDrive1,leftDrive2,RightDrive1,RightDrive2);
	//drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
	//drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
	drive.setSafetyEnabled(false);

        sonar1=new MaxbotixSonar(HW.maxbotixsonar1Slot,HW.maxbotixsonar1Channel,MaxbotixSonar.Unit.kInches);
        ultra1=new Ultrasonic(  HW.ultrasonic1Slot,HW.ultrasonic1PingChannel,
                                HW.ultrasonic1Slot,HW.ultrasonic1EchoChannel,Ultrasonic.Unit.kInches);
    }

    public void initDefaultCommand() {
        setDefaultCommand(new JoyArcadeTwoSpeed());
    }

    public void tankDrive(double left,double right){
	drive.tankDrive(left, right);
    }

    public void arcadeDrive(double move, double turn) {
	drive.arcadeDrive(move,turn,true);
    }

    public double getSonar(){
        return sonar1.getMedianRange();
    }

    public double getUltra1(){
        return ultra1.getRangeInches();
    }

    public double getEncoder() {
	return -1;  //not supported
    }


    public void setMode(DriveMode mode){
	switch(mode.value){
	    case DriveMode.range_val:
		enable();
		break;
	    case DriveMode.distance_val:
		enable();
		break;
	    case DriveMode.driver_val:
		disable();
		break;
	    default:
		disable();
		break;
	}
	thismode=mode;
    }

    protected double returnPIDInput() {
	switch(thismode.value){
	    case DriveMode.range_val:
		return getSonar();
	    case DriveMode.distance_val:
		return getEncoder();
	    case DriveMode.driver_val:
		return 0;
	    default:
		return 0;
	}
    }

    protected void usePIDOutput(double output) {
    }
}
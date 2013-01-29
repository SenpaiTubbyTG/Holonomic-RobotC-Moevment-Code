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
import edu.wpi.first.wpilibj.command.Subsystem;


public class Drivetrain extends Subsystem {
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

    private MaxbotixSonar sonar1;
    private Ultrasonic ultra1;
    private Encoder leftEncoder;
    private Encoder rightEncoder;

    public Drivetrain(){
	super("Drivetrain");
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

    public int getLeftEncoder() {
	return 0;  //not supported
    }
    public int getRightEncoder(){
	return 0;
    }
}
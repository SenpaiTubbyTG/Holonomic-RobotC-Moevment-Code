/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.subsystems;

import disco.HW;
import disco.commands.drivetrain.AssistedTank;
import disco.utils.BetterDrive;
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
    private BetterDrive drive;

    private MaxbotixSonar sonar1;
    private MaxbotixSonar sonar2;
    private MaxbotixSonar sonar3;
    private Encoder leftEncoder;
    private Encoder rightEncoder;

    public Drivetrain(){
	super("Drivetrain");
	leftDrive1=new Victor(HW.LeftDrive1Slot,HW.LeftDrive1Channel);
	leftDrive2=new Victor(HW.LeftDrive2Slot,HW.LeftDrive2Channel);
	RightDrive1=new Victor(HW.RightDrive1Slot,HW.RightDrive1Channel);
	RightDrive2=new Victor(HW.RightDrive2Slot,HW.RightDrive2Channel);
	drive=new BetterDrive(leftDrive1,leftDrive2,RightDrive1,RightDrive2);
	//drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
	//drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
	drive.setSafetyEnabled(false);

        sonar1=new MaxbotixSonar(HW.maxbotixsonar1Slot,HW.maxbotixsonar1Channel,MaxbotixSonar.Unit.kInches);
        sonar2=new MaxbotixSonar(HW.maxbotixsonar2Slot,HW.maxbotixsonar2Channel,MaxbotixSonar.Unit.kInches);
        sonar3=new MaxbotixSonar(HW.maxbotixsonar3Slot,HW.maxbotixsonar3Channel,MaxbotixSonar.Unit.kInches);
    }

    public void initDefaultCommand() {
        setDefaultCommand(new AssistedTank());
    }

    public void tankDrive(double left,double right){
	drive.tankDrive(left, right);
    }

    public void arcadeDrive(double move, double turn) {
	drive.arcadeDrive(move,turn);
    }

    public double getSonar(){
        return sonar1.getMedianRange();
    }

    public int getLeftEncoder() {
	return 0;  //not supported
    }
    public int getRightEncoder(){
	return 0;
    }
}
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.subsystems;

import disco.HW;
import disco.commands.drivetrain.RawJoyTank;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.Subsystem;

public class Drivetrain extends Subsystem {
    private Victor leftDrive1;
    private Victor leftDrive2;
    private Victor RightDrive1;
    private Victor RightDrive2;
    private RobotDrive drive;

    public Drivetrain(){
	super("Drivetrain");
	leftDrive1=new Victor(HW.LeftDrive1Slot,HW.LeftDrive1Channel);
	leftDrive2=new Victor(HW.LeftDrive2Slot,HW.LeftDrive2Channel);
	RightDrive1=new Victor(HW.RightDrive1Slot,HW.RightDrive1Channel);
	RightDrive2=new Victor(HW.RightDrive2Slot,HW.RightDrive2Channel);
	drive=new RobotDrive(leftDrive1,leftDrive2,RightDrive1,RightDrive2);
	drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
	drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
	drive.setSafetyEnabled(false);
    }

    public void initDefaultCommand() {
        setDefaultCommand(new RawJoyTank());
    }

    public void tankDrive(double left,double right){
	drive.tankDrive(left, right);
    }

    public void arcadeDrive(double move, double turn) {
	drive.arcadeDrive(move,turn);
    }
}
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.subsystems;

import disco.practice.HW;
import disco.practice.commands.Drivetrain.RawJoyTank;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.Subsystem;

public class Drivetrain extends Subsystem {
    private RobotDrive m_drive;
    private Victor leftFront, leftBack, rightFront, rightBack;

    public Drivetrain(){
	super("Drivetrain");
	leftFront=new Victor(HW.leftFrontDriveSlot,HW.leftFrontDriveChannel);
	leftBack=new Victor(HW.leftBackDriveSlot,HW.leftBackDriveChannel);
	rightFront=new Victor(HW.rightFrontDriveSlot,HW.rightFrontDriveChannel);
	rightBack=new Victor(HW.rightBackDriveSlot,HW.rightBackDriveChannel);
	m_drive= new RobotDrive(    leftFront,
				    leftBack,
				    rightFront,
				    rightBack);
        m_drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        m_drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
	m_drive.setSafetyEnabled(false);
    }

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        setDefaultCommand(new RawJoyTank());
    }

    public void driveArcade(double move, double turn){
	m_drive.arcadeDrive(move, turn, true);
    }

    public void driveTank(double left,double right){
	m_drive.tankDrive(left, right);
    }
}
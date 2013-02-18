/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.drivetrain;

import disco.HW;
import disco.commands.CommandBase;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.PIDSource;
import edu.wpi.first.wpilibj.networktables.NetworkTable;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;


public class DriveAngleEncoder extends CommandBase {
    private double  m_kP=0.0008,
		    m_kI=0.00002,
		    m_kD=0.008;
    private int m_setpoint = 0;
    protected double m_leftCorrection = 0;
    protected double m_rightCorrection = 0;
    boolean finished = false;
    private int m_leftInitial;
    private int m_rightInitial;
    private PIDController leftControl;
    private PIDController rightControl;

    private PIDOutput leftOutput = new PIDOutput() {

        public void pidWrite(double output) {
            useLeftOutput(output);
        }
    };
    private PIDSource leftSource = new PIDSource() {

        public double pidGet() {
            return offsetLeft();
        }
    };
    private PIDOutput rightOutput = new PIDOutput() {

        public void pidWrite(double output) {
            useRightOutput(output);
        }
    };
    private PIDSource rightSource = new PIDSource() {

        public double pidGet() {
            return offsetRight();
        }
    };
    
    private double left;
    private double right;


    public DriveAngleEncoder(double angleSetpoint) {
        requires(drivetrain);

	//gives difference in encoder counts we want to target
        m_setpoint = (int) (Math.toRadians(angleSetpoint) / HW.distancePerRev * HW.wheelSeparation * HW.encoderTicksPerRev);
        leftControl = new PIDController(m_kP, m_kI, m_kD, rightSource, leftOutput);
        rightControl = new PIDController(m_kP, m_kI, m_kD, leftSource, rightOutput);
    }

    protected void initialize() {
	m_leftInitial = drivetrain.getLeftEncoder();
	m_rightInitial = drivetrain.getRightEncoder();

	
	leftControl.enable();
	rightControl.enable();
	leftControl.setSetpoint(m_setpoint);
	rightControl.setSetpoint(m_setpoint);
        SmartDashboard.putData("angle control", leftControl);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        left = m_rightCorrection;
	right = -m_leftCorrection;
	double max = Math.max(Math.abs(left), Math.abs(right));
	if(max > 1){
            left = left / max;
            right = right / max;
	}
        drivetrain.tankDriveUnsmoothed(left, right);
//        if (turnControl.getError()<10) {
//            finished = true;
//        }
        SmartDashboard.putNumber("drive output",m_leftCorrection);
        SmartDashboard.putNumber("drive input",leftControl.getError());
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        double turnRate=drivetrain.getLeftRate()-drivetrain.getRightRate();
        return Math.abs(leftControl.getError())<20 && Math.abs(turnRate)<10;
    }
    
    
    
    protected void interrupted(){
        end();
    }
    
    private void useRightOutput(double output){
	m_rightCorrection=output;
    }
    private void useLeftOutput(double output){
	m_leftCorrection=output;
    }

    protected void end() {
        leftControl.disable();
        rightControl.disable();
        drivetrain.tankDrive(0,0);
    }
    
    protected int offsetLeft(){
	return drivetrain.getLeftEncoder()-m_leftInitial;
    }
    protected int offsetRight(){
	return drivetrain.getRightEncoder()-m_rightInitial;
    }
}

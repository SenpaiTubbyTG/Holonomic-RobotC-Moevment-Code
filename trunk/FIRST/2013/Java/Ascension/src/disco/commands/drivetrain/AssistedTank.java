/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.drivetrain;

import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.PIDSource;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;


public class AssistedTank extends RawJoyTank {
    private PIDController turnControl;
    private double  m_kP=0,
		    m_kI=0,
		    m_kD=0;
    //joystick differences below this are assumed to be intended to be identical.
    private double m_correctionThreshold=0.2;
    //protected double threshold=0.2;

    private double m_correction=0;
    private int m_leftInitial=0;
    private int m_rightInitial=0;

    private PIDOutput output = new PIDOutput() {

        public void pidWrite(double output) {
            usePIDOutput(output);
        }
    };
    private PIDSource source = new PIDSource() {

        public double pidGet() {
            return returnPIDInput();
        }
    };


    public AssistedTank() {
        requires(drivetrain);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
	super.initialize();
	m_leftInitial = drivetrain.getLeftEncoder();
	m_rightInitial = drivetrain.getRightEncoder();

	turnControl = new PIDController(m_kP, m_kI, m_kD, source, output);
	turnControl.enable();
	turnControl.setSetpoint(0); //minimize error
        SmartDashboard.putData("Encoder PID", turnControl);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
	calculateInput();
	if(Math.abs(left-right)<=m_correctionThreshold){
            //we should correct
	    if(!turnControl.isEnable()){
		turnControl.enable();
	    }
	    left -= m_correction;
	    right += m_correction;
	    //normalize if we are out of range (based on RobotDrive, which only does this for mecanum)
	    double max = Math.max(Math.abs(left), Math.abs(right));
	    if(max > 1){
                left = left / max;
                right = right / max;
	    }
	}
        else {
	    //driver is doing something else. start over.
	    if(turnControl.isEnable()){
		turnControl.disable();
	    }
	    m_leftInitial=drivetrain.getLeftEncoder();
	    m_rightInitial=drivetrain.getRightEncoder();
	}
        drivetrain.tankDrive(left, right);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
	turnControl.disable();
	turnControl.free();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
	end();
    }

    private double returnPIDInput(){
	return offsetLeft()-offsetRight();
    }

    private void usePIDOutput(double output){
	m_correction=output;
    }

    private int offsetLeft(){
	return drivetrain.getLeftEncoder()-m_leftInitial;
    }
    private int offsetRight(){
	return drivetrain.getRightEncoder()-m_rightInitial;
    }
    
    public PIDController getController(){
        return turnControl;
    }

}
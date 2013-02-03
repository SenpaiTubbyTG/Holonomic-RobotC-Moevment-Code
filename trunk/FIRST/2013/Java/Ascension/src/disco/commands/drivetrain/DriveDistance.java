/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.drivetrain;

import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.PIDSource;

/**
 *
 * @author Developer
 */
public class DriveDistance extends AssistedTank {
    private final double m_setpoint;
    private PIDController distControl;
    private double  m_kP=0,
		    m_kI=0,
		    m_kD=0;
    
    private double m_correction=0;
    private int m_leftInitial=0;
    private int m_rightInitial=0;
    
    private PIDOutput distOutput = new PIDOutput() {

        public void pidWrite(double output) {
            usePIDOutput(output);
        }
    };
    private PIDSource distSource = new PIDSource() {

        public double pidGet() {
            return returnPIDInput();
        }
    };
    
    public DriveDistance(double setpoint) {
        requires(drivetrain);
        m_setpoint=setpoint;
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        super.initialize();
        m_leftInitial = drivetrain.getLeftEncoder();
	m_rightInitial = drivetrain.getRightEncoder();

	distControl = new PIDController(m_kP, m_kI, m_kD, distSource, distOutput);
	distControl.setSetpoint(m_setpoint);
        distControl.enable();
        super.turnControl.enable();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        left=m_correction;
        right=m_correction;
        left-=super.m_correction;
        right+=super.m_correction;
        
        double max = Math.max(Math.abs(left), Math.abs(right));
        if(max > 1){
            left = left / max;
            right = right / max;
        }
        drivetrain.tankDrive(left, right);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
        drivetrain.tankDrive(0,0);
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
        end();
    }
    
    private double returnPIDInput(){
        //average current value
        return (offsetLeft()+offsetRight())/2.0;
    }
    
    private void usePIDOutput(double output) {
        m_correction=output;
    }
}

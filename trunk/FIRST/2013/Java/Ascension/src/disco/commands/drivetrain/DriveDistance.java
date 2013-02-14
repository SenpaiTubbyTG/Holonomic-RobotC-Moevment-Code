/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.drivetrain;

import disco.HW;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.PIDSource;

public class DriveDistance extends AssistedTank {
    private final double m_setpoint;
    private PIDController distControl;
    private boolean finished=false;
    private double  m_kP=0.0012,
		    m_kI=0.00003,
		    m_kD=0.005;
    
    private double m_distCorrection=0;
    
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
    
    //give this the distance in inches
    public DriveDistance(double setpoint) {
        requires(drivetrain);
        m_setpoint=setpoint/HW.distancePerPulse;
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
        //drive
        left=m_distCorrection;
        right=m_distCorrection;
        //but don't turn
        left += left>0 ? super.m_correction : -super.m_correction;
	right -= right>0 ? super.m_correction : -super.m_correction;
        
        double max = Math.max(Math.abs(left), Math.abs(right));
        if(max > 1){
            left = left / max;
            right = right / max;
        }
        drivetrain.tankDrive(left, right);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        double distRate=(drivetrain.getLeftRate()+drivetrain.getRightRate())/2;
        return Math.abs(distControl.getError())<10 && Math.abs(distRate)<10;
    }

    // Called once after isFinished returns true
    protected void end() {
        drivetrain.tankDrive(0,0);
        distControl.disable();
        super.turnControl.disable();
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
        m_distCorrection=output;
    }
}

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
    private PIDController leftDistControl;
    private PIDController rightDistControl;
    private boolean finished=false;
    private double  m_kP=0.009,
		    m_kI=0.00003,
		    m_kD=0.008;
    
    private double m_leftDistCorrection=0;
    private double m_rightDistCorrection=0;
    
    private PIDOutput distOutputL = new PIDOutput() {

        public void pidWrite(double output) {
            m_leftDistCorrection=output;
        }
    };
    private PIDSource distSourceL = new PIDSource() {

        public double pidGet() {
            return offsetLeft();
        }
    };
    private PIDOutput distOutputR = new PIDOutput() {

        public void pidWrite(double output) {
            m_rightDistCorrection=output;
        }
    };
    private PIDSource distSourceR = new PIDSource() {

        public double pidGet() {
            return offsetRight();
        }
    };
    
    //give this the distance in inches
    public DriveDistance(double setpoint) {
        requires(drivetrain);
        m_setpoint=setpoint/HW.distancePerPulse;
        leftDistControl = new PIDController(m_kP, m_kI, m_kD, distSourceL, distOutputL);
        rightDistControl = new PIDController(m_kP, m_kI, m_kD, distSourceR, distOutputR);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        super.initialize();
        m_leftInitial = drivetrain.getLeftEncoder();
	m_rightInitial = drivetrain.getRightEncoder();

	
	leftDistControl.setSetpoint(m_setpoint);
        leftDistControl.enable();
	rightDistControl.setSetpoint(m_setpoint);
        rightDistControl.enable();
        super.turnControl.disable();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        //drive
        left=m_leftDistCorrection;
        right=m_rightDistCorrection;
        //but don't turn
//        left += left>0 ? super.m_correction : -super.m_correction;
//	right -= right>0 ? super.m_correction : -super.m_correction;
        
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
        return Math.abs(leftDistControl.getError())<10 && Math.abs(rightDistControl.getError())<10 && Math.abs(distRate)<10;
    }

    // Called once after isFinished returns true
    protected void end() {
        super.end();
        drivetrain.tankDrive(0,0);
        leftDistControl.disable();
        rightDistControl.disable();
        super.turnControl.disable();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
        end();
    }
}

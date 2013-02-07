/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.drivetrain;

import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.PIDSource;
import edu.wpi.first.wpilibj.networktables.NetworkTable;


public class DriveAngle extends AssistedTank {
    private double  m_kP=0,
		    m_kI=0,
		    m_kD=0;
    private int m_leftInitial=0;
    private int m_rightInitial=0;
    private int m_setpoint = 0;
    boolean finished = false;

    private PIDOutput turnOutput = new PIDOutput() {

        public void pidWrite(double output) {
            usePIDOutput(output);
        }
    };
    private PIDSource turnSource = new PIDSource() {

        public double pidGet() {
            return returnPIDInput();
        }
    };

    public DriveAngle(double angleSetpoint) {
        requires(drivetrain);
        double wheelRadius = 0;
        double wheelSeperation = 0;
        int encoderTicks = 0;

	//gives difference in encoder counts we want to target
        m_setpoint = (int) (Math.toRadians(angleSetpoint) / (2 * Math.PI) * (wheelSeperation / wheelRadius) * encoderTicks);
    }

    protected void initialize() {
	super.initialize();
	m_leftInitial = drivetrain.getLeftEncoder();
	m_rightInitial = drivetrain.getRightEncoder();

	turnControl = new PIDController(m_kP, m_kI, m_kD, turnSource, turnOutput);
	turnControl.enable();
	turnControl.setSetpoint(m_setpoint);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        left -= m_correction;
	right += m_correction;
	double max = Math.max(Math.abs(left), Math.abs(right));
	if(max > 1){
            left = left / max;
            right = right / max;
	}
        drivetrain.tankDrive(left, right);
        if (turnControl.getError()<10) {
            finished = true;
        }
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return finished;
    }

    private double returnPIDInput(){
	return offsetLeft()-offsetRight();
    }

    private void usePIDOutput(double output){
	m_correction=output;
    }
    /*
     * TODO: TABLES NEED A NAME
     */
    public static double getTargetAngle() {
        return NetworkTable.getTable("").getNumber("mainTargetAngle");
    }
    public static double getTargetDistance() {
        return NetworkTable.getTable("").getNumber("mainTargetDistance");
    }
  /*  public static double[] getTargetAngles() {
       NetworkTable.getTable("").getValue("targetListAngles", );
    }*/
}

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.drivetrain;

import disco.HW;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.PIDSource;
import edu.wpi.first.wpilibj.networktables.NetworkTable;


public class DriveAngleGyro extends RawJoyTank {
    private double  m_kP=0.007,
		    m_kI=0.0005,
		    m_kD=0;
    private double m_setpoint = 0;
    private double m_correction=0;
    private double initialAngle=0;
    boolean finished = false;
    protected PIDController gyroControl;

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

    public DriveAngleGyro(double angleSetpoint) {
        requires(drivetrain);

	//gives difference in encoder counts we want to target
        m_setpoint =angleSetpoint;
    }

    protected void initialize() {
	super.initialize();
	gyroControl = new PIDController(m_kP, m_kI, m_kD, turnSource, turnOutput);
	gyroControl.setSetpoint(m_setpoint);
        gyroControl.enable();
        initialAngle=drivetrain.getGyroAngle();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        left= m_correction;
	right= -m_correction;
	double max = Math.max(Math.abs(left), Math.abs(right));
	if(max > 1){
            left = left / max;
            right = right / max;
	}
        drivetrain.tankDriveUnsmoothed(left, right);
        
        if (gyroControl.getError()<5) {
            finished = true;
        }
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    private double returnPIDInput(){
	return drivetrain.getGyroAngle()-initialAngle;
    }

    private void usePIDOutput(double output){
	m_correction=output;
        System.out.println(output);
    }
    
    public PIDController getController(){
        return gyroControl;
    }
    
    /*
     * TODO: TABLES NEED A NAME
     */
    public static double getTargetAngle() {
        return NetworkTable.getTable("Camera").getNumber("rotAng1");
    }
    public static double getTargetDistance() {
        return NetworkTable.getTable("Camera").getNumber("mainTargetDistance");
    }
  /*  public static double[] getTargetAngles() {
       NetworkTable.getTable("").getValue("targetListAngles", );
    }*/
}

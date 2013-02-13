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
    private double  m_kP=0.001,
		    m_kI=0.00005,
		    m_kD=0.0;
    private int m_setpoint = 0;
    protected double m_correction=0;
    boolean finished = false;
    private int m_leftInitial;
    private int m_rightInitial;
    private PIDController turnControl;

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
    private double left;
    private double right;


    public DriveAngleEncoder(double angleSetpoint) {
        requires(drivetrain);

	//gives difference in encoder counts we want to target
        m_setpoint = (int) (Math.toRadians(angleSetpoint) / HW.distancePerRev * HW.wheelSeparation * HW.encoderTicksPerRev);
    }

    protected void initialize() {
	m_leftInitial = drivetrain.getLeftEncoder();
	m_rightInitial = drivetrain.getRightEncoder();

	turnControl = new PIDController(m_kP, m_kI, m_kD, turnSource, turnOutput);
	turnControl.enable();
	turnControl.setSetpoint(m_setpoint);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        left = m_correction;
	right = -m_correction;
	double max = Math.max(Math.abs(left), Math.abs(right));
	if(max > 1){
            left = left / max;
            right = right / max;
	}
        drivetrain.tankDriveUnsmoothed(left, right);
//        if (turnControl.getError()<10) {
//            finished = true;
//        }
        SmartDashboard.putNumber("drive output",m_correction);
        SmartDashboard.putNumber("drive input",turnControl.getError());
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return finished;
    }
    
    
    
    protected void interrupted(){
        end();
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
        return NetworkTable.getTable("").getNumber("rotAng1");
    }
    public static double getTargetDistance() {
        return NetworkTable.getTable("").getNumber("mainTargetDistance");
    }
  /*  public static double[] getTargetAngles() {
       NetworkTable.getTable("").getValue("targetListAngles", );
    }*/

    protected void end() {
        turnControl.disable();
    }
    
    protected int offsetLeft(){
	return drivetrain.getLeftEncoder()-m_leftInitial;
    }
    protected int offsetRight(){
	return drivetrain.getRightEncoder()-m_rightInitial;
    }
}

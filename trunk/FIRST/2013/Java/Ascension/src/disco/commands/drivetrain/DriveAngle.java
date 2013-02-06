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
    final double startPosition = 0;
    private double  m_kP=0,
		    m_kI=0,
		    m_kD=0;
    
    private final double m_correctionThreshold = 0.2;
    private int m_leftInitial = 0, m_rightInitial = 0;
    final double angleSetpoint;
    final double angleStart;
    double angleChange = 0;
    
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
    

    public DriveAngle(double setpoint) {
        requires(drivetrain);
        this.angleSetpoint = setpoint;
        angleStart = 0;
    }

    protected void initialize() {
        super.initialize();

        m_leftInitial = drivetrain.getRightEncoder();
        m_rightInitial = drivetrain.getLeftEncoder();
        
	turnControl = new PIDController(m_kP, m_kI, m_kD, distSource, distOutput);
	turnControl.setSetpoint(angleSetpoint);
        turnControl.enable();
    }
    
    protected void execute() {
        if(Math.abs(left-right) <= m_correctionThreshold){
	    if(!turnControl.isEnable()){
		turnControl.enable();
	    }
	    left -= m_correction;
	    right += m_correction;
	    double max = Math.max(Math.abs(left), Math.abs(right));
	    if(max > 1){
                left = left / max;
                right = right / max;
	    }
	}
        else {
	    if(turnControl.isEnable()){
		turnControl.disable();
	    }
	} 
        drivetrain.tankDrive(left, right);
        if ((int) angleChange == (int) angleSetpoint) { // Fix degree of error
            finished = true;
        }
    }
    
    boolean finished = false;
    protected boolean isFinished() {
        return false;
    }
    
    private double returnPIDInput(){
        /*
         * TODO: REMEMBER TO SET THESE THREE VARIABLES!
         */
        double wheelRadius = 0;
        double wheelSeperation = 0;
        int encoderTicks = 0;
        angleChange = Math.toDegrees((2 * Math.PI) * (wheelRadius / wheelSeperation) * ((offsetRight()) - (offsetLeft()) / encoderTicks));
        return angleChange;
    }
    private void usePIDOutput(double output){
	m_correction=output;
    }
    /*
     * TODO: TABLES NEED A NAME or they will feel sad. :'(
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

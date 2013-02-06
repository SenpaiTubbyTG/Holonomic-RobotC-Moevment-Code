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
    private PIDController turnControl;
    private double  m_kP=0,
		    m_kI=0,
		    m_kD=0;
    
    private double m_correction=0;
    private int rightStartPos = 0, leftStartPos = 0;
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
        angleSetpoint = setpoint;
        angleStart = 0;
    }

    // Herp derp. This is run before anything else runs but after the const is run...
    // Once again... Herp derp.
    protected void initialize() {
        super.initialize();

        rightStartPos = drivetrain.getRightEncoder();
        leftStartPos = drivetrain.getLeftEncoder();
        
	turnControl = new PIDController(m_kP, m_kI, m_kD, distSource, distOutput);
	turnControl.setSetpoint(angleSetpoint);
        turnControl.enable();
    }
    
    protected void execute() {
        if(Math.abs(left-right) <= 0.2){
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
        if ((int) angleChange == (int) angleSetpoint) {
            finished = true;
        }
    }
    
    boolean finished = false;
    protected boolean isFinished() {
        return false;
    }

    // Called once finished equals true... Herp derp.
    protected void end() {
        drivetrain.tankDrive(0,0);
    }

    // Called when command is interrupted by another command that uses same subsystem.
    protected void interrupted() {
        end();
    }
    
    private double returnPIDInput(){
        /*
         * TODO: REMEMBER TO SET THESE THREE VARIABLES!
         * Herp derp.
         */
        double wheelRadius = 0;
        double wheelSeperation = 0;
        int encoderTicks = 0;
        angleChange = Math.toDegrees((2 * Math.PI) * (wheelRadius / wheelSeperation) * (((leftStartPos - drivetrain.getLeftEncoder()) - (rightStartPos - drivetrain.getRightEncoder())) / encoderTicks));
        return angleChange;
    }
    
    private void usePIDOutput(double output) {
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

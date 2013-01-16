package disco.practice.subsystems;

import com.sun.squawk.util.Arrays;
import disco.practice.HW;
import disco.utils.DiscoCounterEncoder;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.PIDSubsystem;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
/*
 * Code based of LaserDragon and Ultraviolet code.
 */
public class Shooter extends Subsystem/*extends PIDSubsystem*/ {
    private Victor m_shooter1;
    private Victor m_shooter2;
    private DiscoCounterEncoder m_shooterEncoder;

    private double[] samplingValues = new double[40];
    private double avgSpeed = 0;
    private static double shooter_kP=0.001;
    private static double shooter_kI=0.001;
    private static double shooter_kD=0.0;

    //public final double defaultSetpoint=1600;
    private double PWMSetpoint=0.5;

    public Shooter() {
        super("Shooter");
        m_shooterEncoder = new DiscoCounterEncoder(HW.encoderSlot, HW.encoderChannel,1);
        m_shooterEncoder.start();
        m_shooter1 = new Victor(HW.shooter1Slot, HW.shooter1Channel);
        m_shooter2 = new Victor(HW.shooter2Slot, HW.shooter2Channel);
	//getController().setSetpointRange(100, 3500);
    }

    protected void initDefaultCommand() {
	//Do nothing
    }
    

    public void setShooter(double speed) {
        PWMSetpoint=speed;
        m_shooter1.set(PWMSetpoint);
        m_shooter2.set(PWMSetpoint);
    }

    protected double returnPIDInput() {
        //LOOP THROUGH AND SHIFT ALL VALUES TO THE RIGHT BY ONE, REMOVING THE LAST VALUE
        for(int i = samplingValues.length-1; i > 0; i--){
            samplingValues[i] = samplingValues[i-1];
        }
        //PUSH IN A NEW VALUE BASED ON RATE
        samplingValues[0] = m_shooterEncoder.getRPM();

        //TEMP ARRAY FOR PERFORMING MEDIAN OPERATION
        double[] median = Arrays.copy(samplingValues, 0, 40, 0, 40);
        Arrays.sort(median);

        //RETURNS THE MIDDLE OF THE SORTED MEDIAN ARRAY
        avgSpeed = median[median.length/2];
        return avgSpeed;
    }

    protected void usePIDOutput(double output) {

        double pwm = -1*m_shooter1.get();
        double speed = output + pwm;
        setShooter(-1*speed);

        SmartDashboard.putDouble("PID OUTPUT",output);
    }

    public double getRPM(){
	return m_shooterEncoder.getRPM();
    }

    public double getFilteredRate(){
     return avgSpeed;
    }
    

//    public void setRPM(double rpm){
//        this.setSetpoint(rpm);
//    }
//
//    public boolean isEnabled(){
//	PIDController controller=this.getPIDController();
//	return controller.isEnable();
//    }
//
//    public PIDController getController(){
//	return getPIDController();
//    }
    
    public double getSetpoint(){
        return PWMSetpoint;
    }

}
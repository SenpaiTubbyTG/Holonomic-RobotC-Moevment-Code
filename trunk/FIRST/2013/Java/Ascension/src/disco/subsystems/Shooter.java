/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.subsystems;

import disco.HW;
import disco.utils.DiscoCounterEncoder;
import edu.wpi.first.wpilibj.Counter;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.PIDSubsystem;

//This is what we have now. This will eventually become a PIDSubsystem (maybe)
public class Shooter extends PIDSubsystem {
    // Put methods for controlling this subsystem
    // here. Call these from Commands.
    private Talon m_shooter1;
    private Talon m_shooter2;
    private Counter m_encoder;
    private static double   kP=0,
			    kI=0,
			    kD=0,
			    kF=0.1;

    public Shooter(){
	super("shooter",kP,kI,kD,kF);
	m_shooter1=new Talon(HW.Shooter1Slot,HW.Shooter1Channel);
	m_shooter2=new Talon(HW.Shooter2Slot,HW.Shooter2Channel);
	m_encoder=new Counter(HW.shooterEncoderSlot,HW.shooterEncoderChannel);
    }

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }

    public void setPower(double power){
	setPower1(power);
	setPower2(power);
    }

    public void setPower1(double power){
	m_shooter1.set(power);
    }

    public void setPower2(double power){
	m_shooter2.set(power);
    }

    public double getPower1(){
	return m_shooter1.get();
    }

    public double getPower2(){
	return m_shooter2.get();
    }

    protected double returnPIDInput() {
	return m_encoder.get();
    }

    protected void usePIDOutput(double output) {
	setPower(output);
    }

    public double getRPM() {
	return m_encoder.get();
    }
}
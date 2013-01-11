/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.subsystems;

import disco.practice.HW;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.Subsystem;

public class Intake extends Subsystem {
    private Victor m_mouthMotor;
    public static final double IN=1.0;
    public static final double OUT=-1.0;
    public static final double STOP=0.0;

    public Intake(){
	super("Intake");
	m_mouthMotor=new Victor(HW.mouthSlot, HW.mouthChannel);
    }

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
	//This subsystem should do nothing, in general.
    }

    public void setMouth(double power){
	m_mouthMotor.set(power);
    }

}
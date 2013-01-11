/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.subsystems;

import disco.practice.HW;
import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.DoubleSolenoid.Value;
import edu.wpi.first.wpilibj.command.Subsystem;


public class Whacker extends Subsystem {
    // Put methods for controlling this subsystem
    // here. Call these from Commands.
    private DoubleSolenoid m_whacker;
    public static final int UP=DoubleSolenoid.Value.kReverse_val;
    public static final int DOWN=DoubleSolenoid.Value.kForward_val;

    public Whacker(){
	super("Whacker");
	m_whacker=new DoubleSolenoid(HW.whackerSlot,HW.lowerWhackerChannel,HW.liftWhackerChannel);
    }

    public void initDefaultCommand() {
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
	//Don't do anything
    }

    public void setPosition(int position){
	if(position==UP){
	    m_whacker.set(DoubleSolenoid.Value.kReverse);
	}
	else if(position==DOWN){
	    m_whacker.set(DoubleSolenoid.Value.kForward);
	}
    }

    public Value getPosition(){
	return m_whacker.get();
    }
}

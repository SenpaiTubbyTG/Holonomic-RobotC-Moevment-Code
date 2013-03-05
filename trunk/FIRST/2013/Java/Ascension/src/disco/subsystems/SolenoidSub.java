/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.subsystems;

import disco.HW;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.Solenoid;
/**
 *
 * @author Developer
 */
public class SolenoidSub extends Subsystem {
    // Put methods for controlling this subsystem
    // here. Call these from Commands.
    Solenoid m_relay;
    public SolenoidSub(){
	super("Solenoid");
	m_relay=new Solenoid(1,8);
    }

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }
    
    public boolean get(){
	return m_relay.get();
    }
    
    
    public void set(boolean val){
	if(val) {
	    m_relay.set(true);
	}
	else {
	    m_relay.set(false);
	}
    }
}

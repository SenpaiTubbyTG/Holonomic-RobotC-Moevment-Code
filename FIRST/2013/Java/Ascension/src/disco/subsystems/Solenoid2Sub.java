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
public class Solenoid2Sub extends Subsystem {
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

    Solenoid m_relay2;
    public Solenoid2Sub(){
	super("Solenoid2");
	m_relay2=new Solenoid(1,7);
    }

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }
    
    public boolean get(){
	return m_relay2.get();
    }
    
    public void set(boolean val){
	if(val) {
	    m_relay2.set(true);
	}
	else {
	    m_relay2.set(false);
	}
    }
}

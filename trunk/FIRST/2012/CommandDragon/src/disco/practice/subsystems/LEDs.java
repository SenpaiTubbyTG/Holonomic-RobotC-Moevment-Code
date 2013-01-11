/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.subsystems;

import edu.wpi.first.wpilibj.command.Subsystem;
import disco.practice.HW;
import edu.wpi.first.wpilibj.Relay;


public class LEDs extends Subsystem {
    Relay m_SpotlightLED;
    Relay m_indexerLED;
    Relay m_shooterLED;

    public LEDs(){
	super("LEDs");
	m_SpotlightLED	= new Relay(HW.spotlightSlot, HW.spotlightChannel, Relay.Direction.kForward);
        m_indexerLED	= new Relay(HW.indexerLEDSlot, HW.indexerLEDChannel, Relay.Direction.kForward);
        m_shooterLED	= new Relay(HW.shooterLEDSlot, HW.shooterLEDChannel, Relay.Direction.kForward);
    }

    public void initDefaultCommand() {
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
	//The lights should do nothing in general
    }

    public void allOff(){
	setSpotlight(false);
	setIndexerLED(false);
	setShooterLED(false);
    }

    public void allOn(){
	setSpotlight(true);
	setIndexerLED(true);
	setShooterLED(true);

    }

    public void setSpotlight(boolean state){
	if(state){
	    m_SpotlightLED.set(Relay.Value.kOn);
	}
	else{
	    m_SpotlightLED.set(Relay.Value.kOff);
	}
    }

    public void setIndexerLED(boolean state){
	if(state){
	    m_indexerLED.set(Relay.Value.kOn);
	}
	else{
	    m_indexerLED.set(Relay.Value.kOff);
	}
    }

    public void setShooterLED(boolean state){
	if(state){
	    m_shooterLED.set(Relay.Value.kOn);
	}
	else{
	    m_shooterLED.set(Relay.Value.kOff);
	}
    }
}

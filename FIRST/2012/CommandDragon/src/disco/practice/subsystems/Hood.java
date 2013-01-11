/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.subsystems;

import disco.practice.HW;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.Subsystem;


public class Hood extends Subsystem {
    private Victor m_tiltMotor;
    public static final double POWER=0.3;
    private DigitalInput keyLimit;
    private DigitalInput farLimit;

    public static final int POS_KEY=1,
			    POS_FAR=2,
			    POS_MOVING=3;

    public Hood(){
	super("Hood");
	m_tiltMotor=new Victor(HW.tiltMotorSlot,HW.tiltMotorChannel);
	keyLimit=new DigitalInput(HW.hoodKeySlot,HW.hoodKeyChannel);
	farLimit=new DigitalInput(HW.hoodFarSlot,HW.hoodFarChannel);
    }

    public void initDefaultCommand() {
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
	//do nothing.
    }

    public void setHoodPower(double power){
	m_tiltMotor.set(power);
    }

    public boolean getKeyLimit(){
	return keyLimit.get();
    }

    public boolean getFarLimit(){
	return farLimit.get();
    }

    public int getPosition(){
	//false is closed switch
	if(!getKeyLimit()){
	    return POS_KEY;
	}
	if(!getFarLimit()){
	    return POS_FAR;
	}
	else{
	    return POS_MOVING;
	}
    }
}

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.subsystems;

import disco.HW;
import disco.commands.pneumatics.AutoShift;
import edu.wpi.first.wpilibj.Solenoid;
import edu.wpi.first.wpilibj.command.Subsystem;

public class Shifter extends Subsystem {
    Solenoid leftShift;
    Solenoid rightShift;

    public static final int GEAR_LOW=1;
    public static final int GEAR_HIGH=2;

    public Shifter(){
	leftShift=new Solenoid(HW.leftShiftChannel);
	rightShift=new Solenoid(HW.rightShiftChannel);
    }

    public void initDefaultCommand() {
        setDefaultCommand(new AutoShift());
    }


    public void setLeftShifter(int gear){
	switch(gear){
	    case GEAR_LOW:
		leftShift.set(false);
		break;
	    case GEAR_HIGH:
		leftShift.set(true);
		break;
	    default:
		leftShift.set(true);
	}
    }

    public void setRightShifter(int gear){
	switch(gear){
	    case GEAR_LOW:
		rightShift.set(true);
		break;
	    case GEAR_HIGH:
		rightShift.set(false);
		break;
	    default:
		rightShift.set(false);
	}
    }
}
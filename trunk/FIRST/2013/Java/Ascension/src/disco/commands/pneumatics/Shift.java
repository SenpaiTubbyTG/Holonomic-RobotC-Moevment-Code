/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.pneumatics;

import disco.commands.CommandBase;
import disco.subsystems.Shifter;


    // Make this return true when this Command no longer needs to run execute()
public class Shift extends CommandBase {
    private static long lastShift = System.currentTimeMillis() - 500;
    
    public Shift() {
        requires(shifter);
    }
    
    protected void initialize() {
        if (lastShift < System.currentTimeMillis()) {
        if(shifter.getShiftMode() == Shifter.GEAR_LOW) {
               shifter.setLeftShifter(Shifter.GEAR_HIGH);
               shifter.setRightShifter(Shifter.GEAR_HIGH);
            } else {
               shifter.setLeftShifter(Shifter.GEAR_LOW);
               shifter.setRightShifter(Shifter.GEAR_LOW);
            }
            lastShift = System.currentTimeMillis() - 500;
        }
    }
    
    protected void execute() {
    }

    protected boolean isFinished() {
        return true;
    }

    protected void end() {
    }

    protected void interrupted() {
    }
}

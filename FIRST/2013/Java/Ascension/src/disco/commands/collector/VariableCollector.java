/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.collector;

import disco.commands.CommandBase;
import disco.utils.GamePad;
import edu.wpi.first.wpilibj.Joystick;


public class VariableCollector extends CommandBase {
    protected Joystick joy1;
    protected GamePad gp;
    protected double threshold=0.15;
    private double power=0;

    public VariableCollector() {
        // Use requires() here to declare subsystem dependencies
        requires(collector);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
	joy1=oi.getJoy1();
	if(joy1 instanceof GamePad){
	    gp=(GamePad) joy1;
	}
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
	if(gp!=null){
	    if(gp.getRawButton(gp.BUMPER_R)){
		power+=0.01;
	    }
	    else if(gp.getRawButton(gp.TRIGGER_R)){
		power-=0.01;
	    }
	    if(gp.getRawButton(gp.BUMPER_R) && gp.getRawButton(gp.TRIGGER_R)){
		power=0;
	    }
	}
	collector.setPower(Math.abs(power)>threshold ? power : 0);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
	collector.setPower(0);
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
	end();
    }
}
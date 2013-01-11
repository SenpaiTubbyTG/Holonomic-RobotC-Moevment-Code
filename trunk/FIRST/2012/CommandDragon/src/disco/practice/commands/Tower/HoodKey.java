/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.commands.Tower;

import disco.practice.commands.CommandBase;
import disco.practice.subsystems.Hood;

public class HoodKey extends CommandBase {
    private static double timeout=2;

    public HoodKey() {
	// Use requires() here to declare subsystem dependencies
	requires(hood);
	setTimeout(timeout);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
	hood.setHoodPower(-Hood.POWER);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
	return hood.getKeyLimit() || isTimedOut();
    }

    // Called once after isFinished returns true
    protected void end() {
	hood.setHoodPower(0);
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
	end();
    }
}

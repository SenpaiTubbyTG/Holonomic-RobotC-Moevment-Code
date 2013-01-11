/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.commands.Pneumatics;

import disco.practice.commands.CommandBase;
import disco.practice.subsystems.Whacker;


public class WhacksOn extends CommandBase {
    private boolean done=false;

    public WhacksOn() {
	// Use requires() here to declare subsystem dependencies
	requires(whacker);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
	whacker.setPosition(Whacker.DOWN);
	done=true;
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
	return done;
    }

    // Called once after isFinished returns true
    protected void end() {
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
	end();
    }
}

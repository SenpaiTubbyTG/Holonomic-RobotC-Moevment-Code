/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.commands.Tower;

import disco.practice.commands.CommandBase;


public class ShooterDec extends CommandBase {
    boolean done=false;

    public ShooterDec() {
	// Use requires() here to declare subsystem dependencies
	//requires(shooter); I don't think this is necessary

    }

    // Called just before this Command runs the first time
    protected void initialize() {
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
	shooter.setShooter(shooter.getSetpoint()-.1);
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

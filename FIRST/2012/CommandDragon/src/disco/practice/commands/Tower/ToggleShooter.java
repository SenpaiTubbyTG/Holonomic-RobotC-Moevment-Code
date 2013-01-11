/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.commands.Tower;

import disco.practice.commands.CommandBase;
import disco.practice.commands.Pneumatics.CompressorStart;
import disco.practice.commands.Pneumatics.CompressorStop;
import edu.wpi.first.wpilibj.command.Scheduler;


public class ToggleShooter extends CommandBase {
    boolean shooterEnabled;
    boolean done=false;

    public ToggleShooter() {
	// Use requires() here to declare subsystem dependencies
	requires(shooter);
	requires(compressor);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
	shooterEnabled=shooter.isEnabled();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
	if(shooterEnabled){
	    shooter.disable();
	    Scheduler.getInstance().add(new CompressorStart());
	}
	else{
	    shooter.enable();
	    Scheduler.getInstance().add(new CompressorStop());
	}
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

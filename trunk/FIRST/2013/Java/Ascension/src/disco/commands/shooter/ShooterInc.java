/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.shooter;

import disco.commands.CommandBase;


public class ShooterInc extends CommandBase {
    private boolean done;

    public ShooterInc() {
        requires(shooter);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        done=false;
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        double set=shooter.getSetpoint();
	if(set<10000){
            shooter.setSetpoint(set+100);
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
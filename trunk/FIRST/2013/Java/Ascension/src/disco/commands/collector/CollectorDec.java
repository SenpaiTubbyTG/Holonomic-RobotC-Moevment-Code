/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.collector;

import disco.commands.CommandBase;


public class CollectorDec extends CommandBase {
    private boolean done=false;

    public CollectorDec() {
        requires(collector);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
	double power=collector.getPower();

	if(power>=0){
	    power-=0.1;
	}
	else{
	    power=0;
	}
	collector.setPower(power);
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
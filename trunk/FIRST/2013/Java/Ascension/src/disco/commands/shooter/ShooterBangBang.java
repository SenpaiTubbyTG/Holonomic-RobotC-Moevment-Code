/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.shooter;

import disco.commands.CommandBase;


public class ShooterBangBang extends CommandBase {
    private boolean done;

    public ShooterBangBang() {
        // Use requires() here to declare subsystem dependencies
        requires(shooter);
        requires(compressor);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
	done=false;
	shooter.disable();
	compressor.set(false);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
	if(shooter.getRPM1()>shooter.getSetpoint()){
	    shooter.setPower1(0);
	}
	else{
	    shooter.setPower1(1);
	}
	if(shooter.getRPM2()>shooter.getSetpoint()){
	    shooter.setPower2(0);
	}
	else{
	    shooter.setPower2(1);
	}
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
	shooter.setPower(0);
	compressor.set(true);
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
	end();
    }
}
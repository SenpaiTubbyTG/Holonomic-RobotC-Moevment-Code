/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.shooter;

import disco.commands.CommandBase;


public class ShooterReset extends CommandBase {
    private boolean done;
    
    long initTime;
    boolean firstRun = true;
    boolean isEnabling;
    
    public ShooterReset() {
        requires(shooter);
        // Use requires() here to declare subsystem dependencies
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        if (!shooter.isEnabled()) {
            compressor.set(false);
        } else {
            shooter.disable();
            compressor.set(true);
            return;
        }
        initTime = System.currentTimeMillis();
        done=false;
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        if (System.currentTimeMillis() < initTime + 400) {
          //System.out.println("im a potato");
            shooter.setPower(-1);
        } else {
            done = true;
        }
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return done;
    }

    // Called once after isFinished returns true
    protected void end() {
        if (isEnabling) {
            shooter.setPower(0);
            shooter.enable();
        }
    } 

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
	end();
    }
}
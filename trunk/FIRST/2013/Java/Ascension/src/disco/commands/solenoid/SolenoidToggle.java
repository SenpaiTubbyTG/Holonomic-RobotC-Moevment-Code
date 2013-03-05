/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.solenoid;

import disco.commands.CommandBase;
/**
 *
 * @author Developer
 */
public class SolenoidToggle extends CommandBase {
    boolean done=false;
    boolean prevState;
    public SolenoidToggle() {
        // Use requires() here to declare subsystem dependencies
        requires(solenoid);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        prevState=solenoid.get();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        solenoid.set(true);
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

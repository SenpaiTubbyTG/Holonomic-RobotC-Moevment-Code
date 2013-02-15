/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands;

import disco.commands.drivetrain.*;;
import disco.utils.Modes;
import edu.wpi.first.wpilibj.command.CommandGroup;
import disco.utils.Modes;

/**
 *
 * @author Nolan
 */
public class CycleDrivePIDMode extends CommandGroup {
    
    public CycleDrivePIDMode() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        if (Modes.modeDrivePID == true) {
            if (Modes.modeDriveTank == true) {
                this.addParallel(new RawJoyTank());
            } else {
                this.addParallel(new JoyArcadeTwoSpeed());
            }
            Modes.modeDrivePID = false;
        } else {
            if (Modes.modeDriveTank == true) {
                this.addParallel(new AssistedTank());
            } else {
               this.addParallel(new RawJoyArcade());
            }
            Modes.modeDrivePID = true;
        }
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    }
}

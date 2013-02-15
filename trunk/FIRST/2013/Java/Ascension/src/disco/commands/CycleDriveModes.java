/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands;

import disco.commands.drivetrain.*;;
import disco.commands.shooter.*;
import disco.utils.Modes;
import edu.wpi.first.wpilibj.command.*;

public class CycleDriveModes extends CommandGroup {
    public CycleDriveModes() {
        
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        if (Modes.modeDriveTank == true) {
            if (Modes.modeDrivePID == true) {
                this.addParallel(new JoyArcadeTwoSpeed());
            } else {
                this.addParallel(new RawJoyArcade());
            }
            Modes.modeDriveTank = false;
        } else {
            if (Modes.modeDrivePID == true) {
                this.addParallel(new AssistedTank());
            } else {
                this.addParallel(new RawJoyTank());
            }
            Modes.modeDriveTank = true;
        }
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return true;
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

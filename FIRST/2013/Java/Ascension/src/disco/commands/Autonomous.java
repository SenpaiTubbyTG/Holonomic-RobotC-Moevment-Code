/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands;

import disco.commands.shooter.Shoot;
import disco.commands.shooter.ShooterToggle;
import edu.wpi.first.wpilibj.command.CommandGroup;
import edu.wpi.first.wpilibj.command.WaitCommand;

/**
 *
 * @author Doris
 */
public class Autonomous extends CommandGroup {
    
    public Autonomous() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
        addSequential(new ShooterToggle());
        addSequential(new WaitCommand(2));
        addSequential(new Shoot());
        addSequential(new WaitCommand(1));
        addSequential(new Shoot());
        addSequential(new WaitCommand(1));
        addSequential(new Shoot());
        addSequential(new WaitCommand(1));
        addSequential(new Shoot());
        addSequential(new WaitCommand(1));
        addSequential(new Shoot());
        addSequential(new ShooterToggle());
    }

    // Called just before this Command runs the first time
    protected void initialize() {

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
        end();
    }
}

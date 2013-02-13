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
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        addSequential(new ShooterToggle());
        addSequential(new WaitCommand(0.5));
        addSequential(new Shoot());
        addSequential(new WaitCommand(0.5));
        addSequential(new Shoot());
        addSequential(new WaitCommand(0.5));
        addSequential(new Shoot());
        addSequential(new WaitCommand(0.5));
        addSequential(new Shoot());
        addSequential(new WaitCommand(0.5));
        addSequential(new Shoot());
        addSequential(new WaitCommand(0.5));
        addSequential(new ShooterToggle());
        addSequential(new WaitCommand(12.0));
        
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

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands;

import disco.commands.drivetrain.DriveAngle;
import disco.commands.drivetrain.DriveDistance;
import disco.commands.shooter.ShootIn;
import disco.commands.shooter.ShootOut;
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
        addSequential(new DriveAngle(DriveAngle.getTargetAngle()));
        /*addSequential(new ShootIn());
        addSequential(new WaitCommand(0.5));
        addSequential(new ShootOut());
        addSequential(new WaitCommand(0.5));*/
        /*12.566 in. circumference
        128 pulses
        10.1859 pulses/in.*/
        
        

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

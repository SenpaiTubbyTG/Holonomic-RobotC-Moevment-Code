/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands;

import disco.commands.drivetrain.DriveAngleEncoder;
import disco.commands.drivetrain.DriveDistance;
import disco.commands.shooter.AutoShoot;
import disco.commands.shooter.Shoot;
import disco.commands.shooter.ShooterToggle;
import edu.wpi.first.wpilibj.command.CommandGroup;
import edu.wpi.first.wpilibj.command.WaitCommand;

/**
 *
 * @author Doris
 */
public class Autonomous extends CommandGroup {
    public static final int MODE_SAFE = 0;
    public static final int MODE_RISKY = 1;
    public static final int MODE_DANGEROUS = 2;
    
    public Autonomous(int mode) {
        switch (mode) {
            case Autonomous.MODE_RISKY:
                break;
            case Autonomous.MODE_DANGEROUS:
                addSequential(new ShooterToggle());
                addSequential(new AutoShoot(5));
                addSequential(new ShooterToggle());
                addSequential(new DriveDistance(-90));
            default:
                addSequential(new ShooterToggle());
                addSequential(new AutoShoot(5));
                addSequential(new ShooterToggle());
                break;
        }
            

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

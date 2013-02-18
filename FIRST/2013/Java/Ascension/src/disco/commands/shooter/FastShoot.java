/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.shooter;

import disco.commands.CommandBase;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.CommandGroup;
import java.util.Timer;

public class FastShoot extends CommandGroup {
    private int number;
    private int count;

    
    public FastShoot(int number) {
        this.number=number;
        setTimeout(0);
        count=0;
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        count=0;
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        if(CommandBase.shooter.isOnTarget() && isTimedOut() && count<number){
            new Shoot().start();
            setTimeout(timeSinceInitialized()+0.5);
            count++;
        }
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return count==number;
    }

    // Called once after isFinished returns true
    protected void end() {
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    }
}
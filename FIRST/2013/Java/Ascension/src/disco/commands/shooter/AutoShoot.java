/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.shooter;

import disco.commands.CommandBase;
import disco.commands.pneumatics.Shoot;
import edu.wpi.first.wpilibj.command.CommandGroup;

public class AutoShoot extends CommandGroup {
    private int number;
    private int number2 = 1;
    private double delay;
    private int count;

    
    public AutoShoot(int number, double delay) {
        this.number=number;
        this.delay=delay;
        setTimeout(delay);
        count=0;
    }

    // Called just before this Command runs the first time
    protected void initialize() {
        count=0;
        setTimeout(timeSinceInitialized()+delay);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        if(count==0 && !isTimedOut()){
            //wait
        }
//        if((CommandBase.shooter.isOnTarget() && this.isTimedOut()) && count<number2){
//            new Shoot().start();
//            setTimeout(timeSinceInitialized()+delay+5);
//            count++;
//        }
        else if((CommandBase.shooter.isOnTarget() && this.isTimedOut()) && count<number){
            new Shoot().start();
            setTimeout(timeSinceInitialized()+delay);
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
        end();
    }
}

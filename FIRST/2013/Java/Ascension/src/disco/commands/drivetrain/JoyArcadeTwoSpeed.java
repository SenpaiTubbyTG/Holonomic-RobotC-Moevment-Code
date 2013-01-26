/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.drivetrain;

import disco.commands.CommandBase;
import disco.utils.GamePad;
import edu.wpi.first.wpilibj.Joystick;


/**
 * Allows fine control with the right joystick
 */
public class JoyArcadeTwoSpeed extends CommandBase {
    private double move=0;
    private double turn=0;
    private Joystick joy1;
    private GamePad gp;
    private double threshold=0.2;

    public JoyArcadeTwoSpeed() {
        // Use requires() here to declare subsystem dependencies
        requires(drivetrain);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
	joy1=oi.getJoy();
	if(joy1 instanceof GamePad){
	    gp=(GamePad) joy1;
	}
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute(){
	if(gp != null){
	    move=gp.getLY();
	    move=Math.abs(move)>threshold ? move : 0;
	    turn=-1*gp.getLX();
	    turn=Math.abs(turn)>threshold ? turn : 0;
            
            move+=gp.getRY()/2;
            turn+= -1*gp.getRX()/2;
	}
	else{
	    throw new IllegalStateException("JoyArcadeTwoSpeed only works with gamepads for now.");
	}
	drivetrain.arcadeDrive(move,turn);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
	drivetrain.arcadeDrive(0, 0);
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
	end();
    }
}
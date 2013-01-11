/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.commands.Drivetrain;

import disco.practice.commands.CommandBase;
import disco.utils.GamePad;
import edu.wpi.first.wpilibj.Joystick;



public class RawJoyArcade extends CommandBase {
    private double move=0;
    private double turn=0;
    private Joystick joy1;
    private GamePad gp;
    private double threshold=0.2;

    public RawJoyArcade() {
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
	    turn=gp.getLX();
	    turn=Math.abs(turn)>threshold ? turn : 0;
	}
	else{
	    move=joy1.getAxis(Joystick.AxisType.kY);
	    move=Math.abs(move)>threshold ? move : 0;
	    turn=joy1.getAxis(Joystick.AxisType.kX);
	    turn=Math.abs(turn)>threshold ? turn : 0;
	}
	drivetrain.driveArcade(move,turn);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
	drivetrain.driveArcade(0, 0);
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
	end();
    }
}
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.commands.Drivetrain;

import disco.practice.commands.CommandBase;
import disco.utils.GamePad;
import edu.wpi.first.wpilibj.Joystick;



public class RawJoyTank extends CommandBase {
    private double left=0;
    private double right=0;
    private Joystick joy1;
    private GamePad gp;
    private double threshold=0.2;

    public RawJoyTank() {
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
	    left=gp.getLY();
	    left=Math.abs(left)>threshold ? left : 0;
	    right=gp.getRY();
	    right=Math.abs(right)>threshold ? right : 0;
	    drivetrain.driveTank(left, right);
	}
	else{
	    //left=joy1.getAxis(Joystick.AxisType.kY);
	    //right=joy1.getAxis(Joystick.AxisType.kX);
	    throw new IllegalStateException("Tank drive only works with game pads for now. Sorry");
	    //drivetrain.driveArcade(left,right);
	}
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
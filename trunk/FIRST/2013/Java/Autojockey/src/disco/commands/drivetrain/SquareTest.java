/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.drivetrain;

import disco.commands.CommandBase;
import lejos.robotics.localization.OdometryPoseProvider;
import lejos.robotics.navigation.DifferentialPilot;

public class SquareTest extends CommandBase {

    DifferentialPilot p;
    OdometryPoseProvider o;
    int direction = 1;
    int length = 36;
    boolean finished = false;

    public SquareTest() {
	// Use requires() here to declare subsystem dependencies
	requires(drivetrain);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
	p = drivetrain.pilot;
	o = drivetrain.op;
	Thread t = new Thread() {
	    public void run() {
		for (int i = 0; i < 4; i++) {
		    drawSquare(direction * length);
		    if (i == 1) {
			p.rotate(90);
			direction = -1;
		    }
		}
		finished = true;
	    }
	};
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
	System.out.println(o.getPose().getX() + " , " + o.getPose().getY());
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
	return finished;
    }

    // Called once after isFinished returns true
    protected void end() {
	p.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
	end();
    }

    public void drawSquare(float length) {
	byte direction = 1;
	if (length < 0) {
	    direction = -1;
	    length = -length;
	}
	for (int i = 0; i < 4; i++) {
	    p.travel(length, true);
	    p.rotate(direction * 90, true);
	}
    }
}
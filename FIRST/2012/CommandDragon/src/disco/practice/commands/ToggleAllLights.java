/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.commands;

/**
 *
 * @author sam
 */
public class ToggleAllLights extends CommandBase {
    private static boolean m_areLightsOn=false;
    private boolean done=false;

    public ToggleAllLights() {
	// Use requires() here to declare subsystem dependencies
	requires(lights);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
	if(m_areLightsOn){
	    lights.allOff();
	}
	else{
	    lights.allOn();
	}
	m_areLightsOn=!m_areLightsOn;
	done=true;
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
	return done;
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

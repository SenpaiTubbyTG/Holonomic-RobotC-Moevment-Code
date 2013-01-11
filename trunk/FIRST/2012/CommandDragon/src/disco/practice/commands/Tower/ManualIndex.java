/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.commands.Tower;

import disco.practice.commands.CommandBase;
import disco.practice.subsystems.Indexer;


public class ManualIndex extends CommandBase {
    private boolean done=false;
    private double m_value;

    public ManualIndex(double value) {
	// Use requires() here to declare subsystem dependencies
	requires(indexer);
	m_value=value;
    }

    protected ManualIndex(){
	throw new IllegalArgumentException("You must specify a direction for the mouth");
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
	if(m_value==Indexer.UP){
	    indexer.setIndexer(Indexer.UP);
	}
	else if(m_value==Indexer.DOWN){
	    indexer.setIndexer(Indexer.DOWN);
	}
	done=true;
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
	return false;
    }

    // Called once after isFinished returns true
    protected void end() {
	indexer.setIndexer(Indexer.STOP);
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
	end();
    }
}

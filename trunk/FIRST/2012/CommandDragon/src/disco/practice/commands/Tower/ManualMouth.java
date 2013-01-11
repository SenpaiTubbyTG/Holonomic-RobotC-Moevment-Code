/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.commands.Tower;

import disco.practice.commands.CommandBase;
import disco.practice.subsystems.Intake;


public class ManualMouth extends CommandBase {

    private boolean done = false;
    private double m_value;

    public ManualMouth(double value) {
        // Use requires() here to declare subsystem dependencies
        requires(intake);
        m_value = value;
    }

    protected ManualMouth() {
        throw new IllegalArgumentException("You must specify a direction for the mouth");
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
        if (m_value == Intake.IN) {
            intake.setMouth(Intake.IN);
        } else if (m_value == Intake.OUT) {
            intake.setMouth(Intake.OUT);
        }
        done = true;
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
        intake.setMouth(Intake.STOP);
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
        end();
    }
}
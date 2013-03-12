package disco.commands.shooter;

import disco.commands.CommandBase;

public class AutoSetRPM extends CommandBase {
    boolean done;
    public AutoSetRPM() {
    }
    protected void initialize() {
        done = false;
    }

    protected void execute() {
	if (shooter.getSetpoint() == 5000 && shooter.difference == 500) {
            shooter.setSetpoint(5500);
            shooter.difference = 500;
        }
	else {
            shooter.setSetpoint(shooter.m_defaultSetpoint);
            shooter.difference = 500;
        }
        done = true;
    }

    protected boolean isFinished() {
        return done;
    }

    protected void end() {
    }

    protected void interrupted() {
        end();
    }
}

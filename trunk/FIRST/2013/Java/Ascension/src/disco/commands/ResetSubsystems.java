package disco.commands;

import disco.utils.Dashboard;
//WHY WHY WHY WHY WHY
public class ResetSubsystems extends CommandBase {
    
    boolean done;
    
    public ResetSubsystems() {
    }

    protected void initialize() {
        requires(drivetrain);
        requires(shooter);
        requires(collector);
        requires(compressor);
        // Make sure all other commmands have a valid interrupted() methods.
        done = false;
    }

    protected void execute() {
        System.out.println("====================================================");
        System.out.println("Resetting subsystems and OI!");
        System.out.println("This is potentionally suicidial!");
        CommandBase.init();
        Dashboard.init();
        // This assumes that the robot is NOT multi-threaded! (Except for the Thread sam created)
        System.out.println("====================================================");
        done = true;
    }

    protected boolean isFinished() {
        return done;
    }

    protected void end() {
    }

    protected void interrupted() {
    }
}

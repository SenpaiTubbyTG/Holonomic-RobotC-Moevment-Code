package disco.practice.commands;

import disco.practice.OI;
import disco.practice.subsystems.DiscoCompressor;
import disco.practice.subsystems.Drivetrain;
import disco.practice.subsystems.Hood;
import disco.practice.subsystems.Indexer;
import disco.practice.subsystems.Intake;
import disco.practice.subsystems.LEDs;
import disco.practice.subsystems.Shooter;
//import disco.practice.subsystems.Vision;
import disco.practice.subsystems.Whacker;
import edu.wpi.first.wpilibj.command.Command;

/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.exampleSubsystem
 */
public abstract class CommandBase extends Command {

    public static OI oi;
    // Create a single static instance of all of your subsystems
    public static Drivetrain drivetrain = new Drivetrain();
    public static LEDs lights=new LEDs();
    public static Intake intake=new Intake();
    public static Shooter shooter=new Shooter();
    public static Indexer indexer=new Indexer();
    public static DiscoCompressor compressor=new DiscoCompressor();
    public static Whacker whacker=new Whacker();
    public static Hood hood=new Hood();
//    public static Vision vision=new Vision();

    public static void init() {
        // This MUST be here. If the OI creates Commands (which it very likely
        // will), constructing it during the construction of CommandBase (from
        // which commands extend), subsystems are not guaranteed to be
        // yet. Thus, their requires() statements may grab null pointers. Bad
        // news. Don't move it.
        oi = new OI();
    }

    public CommandBase(String name) {
        super(name);
    }

    public CommandBase() {
        super();
    }
}

/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package disco;

import disco.commands.CommandBase;
import disco.utils.Dashboard;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.Scheduler;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class MainAscent extends IterativeRobot {

    Command autonomousCommand;

    public MainAscent() {
	super();
    }

    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit() {
	// instantiate the command used for the autonomous period
	//autonomousCommand = new ExampleCommand();

	// Initialize all subsystems
	CommandBase.init();
	getWatchdog().setEnabled(false);
	Dashboard.init();
	Dashboard.putStuff();
    }

    public void disabledInit() {
    }

    public void disabledPeriodic() {
	Scheduler.getInstance().run();
    }

    public void autonomousInit() {
	// schedule the autonomous command (example)
	autonomousCommand.start();
    }

    public void autonomousPeriodic() {
	Scheduler.getInstance().run();
    }

    public void teleopInit() {
	autonomousCommand.cancel();
    }

    public void teleopPeriodic() {
	Scheduler.getInstance().run();
    }

    public void testPeriodic() {
	LiveWindow.run();
    }
}

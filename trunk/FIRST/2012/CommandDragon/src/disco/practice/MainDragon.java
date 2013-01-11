/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package disco.practice;


import disco.practice.commands.CommandBase;
import disco.practice.commands.Pneumatics.CompressorStart;
import disco.practice.commands.Pneumatics.CompressorStop;
import disco.practice.commands.Pneumatics.WhacksOff;
import disco.utils.Dashboard;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.command.Scheduler;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class MainDragon extends IterativeRobot {


    public MainDragon(){
	super();
	//what goes here?
    }
    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit() {
        // Initialize all subsystems
        CommandBase.init();
	getWatchdog().setEnabled(false);
	Dashboard.init();
        Dashboard.putStuff();
    }

    public void disabledInit(){
	//End motion here
	Scheduler.getInstance().add(new WhacksOff());
	Scheduler.getInstance().add(new CompressorStop());
	Dashboard.putStuff();
    }
    public void disabledPeriodic(){
	Scheduler.getInstance().run();
//	Dashboard.putStuff();
    }
    public void disabledContinuous(){
	Thread.yield();
    }



    public void autonomousInit() {
        // schedule the autonomous command
    }
    public void autonomousPeriodic() {
        Scheduler.getInstance().run();
//	Dashboard.putStuff();
    }
    public void autonomousContinuous(){
	Thread.yield();
    }



    public void teleopInit() {
	//Stop auton commmand
	Scheduler.getInstance().add(new CompressorStart());
    }
    public void teleopPeriodic() {
        Scheduler.getInstance().run();
//	Dashboard.putStuff();
    }
    public void teleopContinuous(){
	// Scheduler.getInstance().run();
	Thread.yield();
    }
}
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.utils;

import disco.commands.CommandBase;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Dashboard {

    public static void init() {
        putStuff();
    }

    public static void putStuff() {
        putSubsystems();
        putSensors();
    }

    public static void putSubsystems() {
        SmartDashboard.putData(CommandBase.drivetrain);
        SmartDashboard.putData(CommandBase.shooter);
        // Show what command your subsystem is running on the SmartDashboard
    }

    public static void putSensors() {
//	SmartDashboard.putData("Shooter PID",CommandBase.shooter.getController()); //don't need this?
	SmartDashboard.putNumber("Shooter RPM", CommandBase.shooter.getRPM());
	SmartDashboard.putNumber("Left joy", ((GamePad)(CommandBase.oi.getJoy())).getLY());
        SmartDashboard.putNumber("RIght joy", ((GamePad)(CommandBase.oi.getJoy())).getRY());
    }
}

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.utils;

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
        // Show what command your subsystem is running on the SmartDashboard
//        SmartDashboard.putData(CommandBase.drivetrain);
    }

    public static void putSensors() {
//	SmartDashboard.putData("Shooter PID",CommandBase.shooter.getController()); //don't need this?
//	SmartDashboard.putNumber("Shooter RPM", CommandBase.shooter.getRPM());
    }
}

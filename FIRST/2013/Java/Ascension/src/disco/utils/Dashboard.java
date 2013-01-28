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

    //Only call this once or we overflow the memory. Bad day.
    public static void putSubsystems() {
        SmartDashboard.putData(CommandBase.drivetrain);
        SmartDashboard.putData(CommandBase.shooter);
        SmartDashboard.putData(CommandBase.collector);
        // Show what command your subsystem is running on the SmartDashboard
    }

    //Repeatedly call this to update dashboard values.
    public static void putSensors() {
//	SmartDashboard.putData("Shooter PID",CommandBase.shooter.getController()); //don't need this?
	SmartDashboard.putNumber("Shooter RPM", CommandBase.shooter.getRPM());
	SmartDashboard.putNumber("Left joy Y", ((GamePad)(CommandBase.oi.getJoy())).getLY());
        SmartDashboard.putNumber("Left joy X", ((GamePad)(CommandBase.oi.getJoy())).getLX());
        SmartDashboard.putNumber("Collector Power", CommandBase.collector.getPower());
        SmartDashboard.putNumber("Sonar", CommandBase.drivetrain.getSonar());
        SmartDashboard.putNumber("Ultrasonic1", CommandBase.drivetrain.getUltra1());
    }
}

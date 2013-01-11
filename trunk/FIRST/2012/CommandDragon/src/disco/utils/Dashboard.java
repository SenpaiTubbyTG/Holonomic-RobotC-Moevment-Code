/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.utils;

import disco.practice.commands.CommandBase;
import disco.practice.subsystems.Hood;
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
        SmartDashboard.putData(CommandBase.drivetrain);
        SmartDashboard.putData(CommandBase.lights);
        SmartDashboard.putData(CommandBase.intake);
        SmartDashboard.putData(CommandBase.shooter);
        SmartDashboard.putData(CommandBase.indexer);
        SmartDashboard.putData(CommandBase.compressor);
        SmartDashboard.putData(CommandBase.whacker);
        SmartDashboard.putData(CommandBase.hood);
    }

    public static void putSensors() {
        SmartDashboard.putBoolean("Air Full", CommandBase.compressor.getPressureSwitch());

        String position = "";
        switch (CommandBase.hood.getPosition()) {
            case Hood.POS_FAR:
                position = "Far";
                break;
            case Hood.POS_KEY:
                position = "Key";
                break;
            case Hood.POS_MOVING:
                position = "Moving";
                break;
        }
        SmartDashboard.putString("Hood position", position);

//	SmartDashboard.putData("Shooter PID",CommandBase.shooter.getController()); //don't need this?
//	SmartDashboard.putNumber("Shooter RPM", CommandBase.shooter.getRPM());
    }
}

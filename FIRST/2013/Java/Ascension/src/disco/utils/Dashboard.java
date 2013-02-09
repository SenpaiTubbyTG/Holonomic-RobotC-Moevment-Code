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
        SmartDashboard.putData(CommandBase.compressor);
        //put other PID and stuff
    }

    //Repeatedly call this to update dashboard values.
    public static void putSensors() {
//	SmartDashboard.putData("Shooter PID",CommandBase.shooter.getController()); //don't need this?
	SmartDashboard.putNumber("Forward Shooter RPM", CommandBase.shooter.getRPM1());
	SmartDashboard.putNumber("Forward Shooter PWM", CommandBase.shooter.getPower1());
	SmartDashboard.putNumber("Back Shooter RPM", CommandBase.shooter.getRPM2());
	SmartDashboard.putNumber("Back Shooter PWM", CommandBase.shooter.getPower2());
        
        SmartDashboard.putNumber("Shooter Setpoint", CommandBase.shooter.getSetpoint());
        SmartDashboard.putBoolean("Shooter On target", CommandBase.shooter.isOnTarget());
        
        
	SmartDashboard.putNumber("Left joy Y", ((GamePad)(CommandBase.oi.getJoy())).getLY());
        SmartDashboard.putNumber("Right joy Y", ((GamePad)(CommandBase.oi.getJoy())).getRY());
        SmartDashboard.putNumber("Front sonar 1", CommandBase.drivetrain.getFrontSonar1());
        SmartDashboard.putNumber("Gyro angle", CommandBase.drivetrain.getGyroAngle());
        
        SmartDashboard.putNumber("Collector Power", CommandBase.collector.getPower());
        
        SmartDashboard.putBoolean("Air Full", CommandBase.compressor.getPressureSwitch());
        SmartDashboard.putString("Compressor State", CommandBase.compressor.getEnabled() ? "ON" : "OFF");
    }
}

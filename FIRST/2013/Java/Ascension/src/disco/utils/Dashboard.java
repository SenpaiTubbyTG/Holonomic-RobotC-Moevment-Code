/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.utils;

import disco.MainAscent;
import disco.commands.Autonomous;
import disco.commands.CommandBase;
import disco.commands.shooter.ShooterBangBang;
import disco.commands.shooter.ShooterControlled;
import disco.subsystems.Shooter;
import edu.wpi.first.wpilibj.smartdashboard.SendableChooser;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Dashboard {

    public static SendableChooser autonChooser;
    public static double autonSetpoint = 5400;
    
    public static void init() {
        autonChooser = new SendableChooser();
        autonChooser.addDefault("Safe", new Autonomous(Autonomous.MODE_SAFE));
        autonChooser.addObject("Risky", new Autonomous(Autonomous.MODE_RISKY));
        autonChooser.addObject("Dangerous", new Autonomous(Autonomous.MODE_DANGEROUS));
        putStuff();
    }

    public static void putStuff() {
        putSubsystems();
        putSensors();
        SmartDashboard.putNumber("Shooter Auton Setpoint", autonSetpoint);
        SmartDashboard.putData("Autonomous Chooser", autonChooser);
    }

    //Only call this once or we overflow the memory. Bad day.
    public static void putSubsystems() {
        SmartDashboard.putData(CommandBase.drivetrain);
        SmartDashboard.putData(CommandBase.shooter);
        SmartDashboard.putData(CommandBase.collector);
        SmartDashboard.putData(CommandBase.compressor);
        //SmartDashboard.putData("Gyro PID",DriveAngleGyro.getController());
    }

    //Repeatedly call this to update dashboard values.
    public static void putSensors() {
         SmartDashboard.putNumber("Execution loop time", MainAscent.getExecutionTime());

	 //SHOOTER
	SmartDashboard.putNumber("Forward Shooter RPM", CommandBase.shooter.getFrontRPM());
	SmartDashboard.putNumber("Forward Shooter PWM", CommandBase.shooter.getFrontPower());
	SmartDashboard.putNumber("Back Shooter RPM", CommandBase.shooter.getBackRPM());
	SmartDashboard.putNumber("Back Shooter PWM", CommandBase.shooter.getBackPower());
        SmartDashboard.putNumber("Shooter difference", CommandBase.shooter.difference);
        SmartDashboard.putNumber("Shooter Setpoint", CommandBase.shooter.getSetpoint());
        SmartDashboard.putBoolean("Shooter On target", CommandBase.shooter.isOnTarget());
        SmartDashboard.putNumber("kP", ShooterControlled.kP);
        SmartDashboard.putNumber("kI", ShooterControlled.kI);
        SmartDashboard.putNumber("kD", ShooterControlled.kD);
        SmartDashboard.putNumber("load sensor", CommandBase.shooter.isLoaded());

        //DRIVETRAIN
	//SmartDashboard.putNumber("Left joy Y", ((GamePad)(CommandBase.oi.getJoy())).getLY());
        //SmartDashboard.putNumber("Right joy Y", ((GamePad)(CommandBase.oi.getJoy())).getRY());
        //SmartDashboard.putNumber("Front sonar 1", CommandBase.drivetrain.getFrontSonar1());
        //SmartDashboard.putNumber("Gyro angle", CommandBase.drivetrain.getGyroAngle());
        SmartDashboard.putBoolean("Touching Left Pyramid", CommandBase.drivetrain.getLeftPyramid());
        SmartDashboard.putBoolean("Touching Right Pyramid", CommandBase.drivetrain.getRightPyramid());
        SmartDashboard.putNumber("Left Encoder", CommandBase.drivetrain.getLeftEncoder());
        SmartDashboard.putNumber("Right Encoder", CommandBase.drivetrain.getRightEncoder());
        SmartDashboard.putNumber("Left Rate", CommandBase.drivetrain.getLeftRate()/12.0);
        SmartDashboard.putNumber("Right Rate", CommandBase.drivetrain.getRightRate()/12.0);

	//COLLECTOR
        SmartDashboard.putNumber("Collector Power", CommandBase.collector.getPower());

	//COMPRESSOR
        SmartDashboard.putBoolean("Air Full", CommandBase.compressor.getPressureSwitch());
        SmartDashboard.putString("Compressor State", CommandBase.compressor.getEnabled() ? "ON" : "OFF");
        
        //SHOOTER AUTON SETPOINT
        SmartDashboard.getNumber("Shooter Auton Setpoint", autonSetpoint);
    }
}

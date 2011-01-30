/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package Breakaway;

import Utils.*;
import edu.wpi.first.wpilibj.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Main extends IterativeRobot {

    Tuple driveOutput;
    double leftVelocity;
    double rightVelocity;
    boolean dataLogged = false;
    int i = 0;

    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit() {

        HW.gyro.reset();
        HW.EncoderLeft.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.EncoderLeft.init();
        HW.EncoderRight.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.EncoderRight.init();

    }

    /**
     * This function is called once every time the robot is disabled
     */
    public void disabledInit() {
        HW.EncoderLeft.stop();
        HW.EncoderLeft.reset();
        HW.EncoderRight.stop();
        HW.EncoderRight.reset();

        if (!dataLogged) {
            HW.vcDataLogger.writeData();
            DiscoUtils.debugPrintln("log write complete");
            dataLogged = true;
        }
    }

    /**
     * Periodic code for disabled mode should go here.
     */
    public void disabledPeriodic() {
    }

    /**
     * This function is called once before Autonomous
     */
    public void autonomousInit() {
    }

    /**
     * This function is called periodically during autonomous
     */
    public void autonomousPeriodic() {
    }

    /**
     * This function is called periodically during operator control
     */
    public void teleopInit() {
        HW.gyro.reset();
        HW.EncoderLeft.start();
        HW.EncoderRight.start();
        HW.leftVC.setReversed(true);

        HW.leftVC.init();
        HW.rightVC.init();

        /*leftVC.enable();
        rightVC.enable();
        leftVC.setSetpoint(0);
        rightVC.setSetpoint(0);*/
        //HW.turnController.initialize();
        //HW.ultra.setDistanceUnits(Ultrasonic.Unit.kInches);
    }
    double goal = 0.0;
    //double testSpeed = 120.0;

    public void teleopPeriodic() {
        goal = HW.driveStickLeft.getY() * 130.0;
        if (HW.driveStickLeft.getRawButton(8)) {
            HW.leftVC.setGoalVelocity(goal);
            HW.rightVC.setGoalVelocity(goal);
            HW.leftVC.controller();
            HW.rightVC.controller();
        } else if (HW.driveStickLeft.getTrigger()) {
            HW.leftVC.enable();
            HW.rightVC.enable();
        } else if (HW.driveStickLeft.getRawButton(2)) {
            HW.leftVC.disable();
            HW.rightVC.disable();
        }

        DiscoUtils.debugPrintln("\n\nleftVel: " + HW.EncoderLeft.getRate());
        DiscoUtils.debugPrintln("rightVe: " + HW.EncoderRight.getRate());
        DiscoUtils.debugPrintln("leftOut: " + HW.leftDriveMotor.get());
        DiscoUtils.debugPrintln("rightOut: " + HW.rightDriveMotor.get());
        //DiscoUtils.debugPrintln("error: " + HW.rightVC.error);
        //DiscoUtils.debugPrintln("iterm: " + HW.rightVC.iterm);
        //HW.rightVC.setGoalVelocity(goal);
        //HW.drive.tankDrive(HW.leftVC.controller(), HW.rightVC.controller());

        //DiscoUtils.debugPrintln("GOAL: " + goal);
        /*DiscoUtils.debugPrintln(
        "leftOutput: " + HW.leftDriveMotor.get());
        DiscoUtils.debugPrintln(
        "rightOutput: " + HW.rightDriveMotor.get());
        DiscoUtils.debugPrintln(
        "leftVelocity: " + HW.EncoderLeft.getRate());
        DiscoUtils.debugPrintln(
        "rightVelocity: " + HW.EncoderRight.getRate());*/
        // DATALOGGER
        //HW.vcDataLogger.addEntry(HW.gyro.getAngle());

    }
}

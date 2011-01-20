/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package Breakaway;

import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Main extends IterativeRobot {

    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit() {
        HW.drive.setInvertedMotor(DiscoDrive.kLeftMotor, true); //Invert Left
        HW.drive.setInvertedMotor(DiscoDrive.kRightMotor, true); //Invert Right
        HW.drive.setInvertedMotor(DiscoDrive.kFrontMotor, false); //Don't Invert Front
        HW.drive.setInvertedMotor(DiscoDrive.kRearMotor, false); //Don't Invert Rear
    }

    /**
     * This function is called once everytime the robot is disabled
     */
    public void disabledInit() {
        HW.leftEncoder.reset();
        HW.leftEncoder.stop();
        HW.rightEncoder.reset();
        HW.rightEncoder.stop();
    }

    /**
     * Periodic code for disabled mode should go here.
     */
    public void disabledPeriodic() {
        HW.leftEncoder.reset();
        HW.leftEncoder.stop();
        HW.rightEncoder.stop();
        HW.rightEncoder.reset();
    }

    /**
     * This function is called once befor Autonomous
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
        HW.leftEncoder.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.leftEncoder.start();
        HW.leftEncoder.reset();
        HW.rightEncoder.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.rightEncoder.start();
        HW.rightEncoder.reset();
        //HW.ultra.setEnabled(true);
        //HW.ultra.setAutomaticMode(true);
        HW.leftVelocityController.initialize();
        //HW.rightVelocityController.initialize();
    }

    public void teleopPeriodic() {
        //HW.drive.basicDrive(0.0, 0.0, HW.driveStick1.getY(), HW.driveStick2.getY());
        //DiscoUtils.debugPrintln("isValid: " + HW.ultra.isRangeValid());
        //DiscoUtils.debugPrintln("Ultrasonic Rangefinder: " + Double.toString(HW.ultra.getRangeInches()));
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser6, 1, "8:34pm");
        DriverStationLCD.getInstance().updateLCD();
        if(HW.driveStick1.getTrigger())
            HW.leftVelocityController.setGoalVelocity(0.0);
        if(HW.driveStick1.getRawButton(8))
            HW.leftVelocityController.setGoalVelocity(-50.0);
        if(HW.driveStick1.getRawButton(9))
            HW.leftVelocityController.setGoalVelocity(50.0);

        if(HW.leftVelocityController.controller()) {
            DiscoUtils.debugPrintln("getRate(mine): " + HW.leftEncoder.getRate(0.01));
            DiscoUtils.debugPrintln("getRate(wpi) : " + HW.leftEncoder.getRate());
            DiscoUtils.debugPrintln("");
        }
        //HW.rightVelocityController.controller(0.0, 1000.0);
        /*if (HW.driveStick1.getTrigger()) {
            //HW.leftEncoder.reset();
            //HW.rightEncoder.reset();
            DiscoUtils.debugPrintln("Testing Right");
            HW.rightVelocityController.initOutputData();
        }
        if (HW.driveStick2.getTrigger()) {
            //HW.leftEncoder.reset();
            //HW.rightEncoder.reset();
            DiscoUtils.debugPrintln("Testing Left");
            HW.leftVelocityController.initOutputData();
        }*/
        /*DiscoUtils.debugPrintln("\n\n");
        DiscoUtils.debugPrintln("Actual Left Rate:   " + HW.leftEncoder.getRate());
        DiscoUtils.debugPrintln("Left Encoder Rate:  " + HW.leftEncoder.getRate(0.01));
        DiscoUtils.debugPrintln("Right Encoder Rate: " + HW.rightEncoder.getRate(0.01) + "\n");
        DiscoUtils.debugPrintln("Left Encoder Test Distance:    " + HW.leftEncoder.getTestDistance());
        DiscoUtils.debugPrintln("Left Encoder Actual Distance:  " + HW.leftEncoder.getDistance());
        DiscoUtils.debugPrintln("Right Encoder Test Distance:   " + HW.rightEncoder.getTestDistance());
        DiscoUtils.debugPrintln("Right Encoder Actual Distance: " + HW.rightEncoder.getDistance());
         */
    }
}

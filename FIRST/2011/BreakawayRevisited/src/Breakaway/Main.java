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
    }

    /**
     * This function is called once every time the robot is disabled
     */
    public void disabledInit() {
        HW.frontEncoder.reset();
        HW.frontEncoder.stop();
        HW.rearEncoder.reset();
        HW.rearEncoder.stop();
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
        HW.frontEncoder.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.frontEncoder.start();
        HW.frontEncoder.reset();
        HW.rearEncoder.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.rearEncoder.start();
        HW.rearEncoder.reset();
        HW.rearVelocityController.initialize();
        HW.frontVelocityController.initialize();
        //HW.ultra.setDistanceUnits(Ultrasonic.Unit.kInches);
    }

    public void teleopPeriodic() {
        //Teleop tank drive using VelocityController
        HW.rearVelocityController.setGoalVelocity(HW.driveStick1.getY() * 1.3);
        HW.frontVelocityController.setGoalVelocity(HW.driveStick2.getY() * 1.3);
        HW.drive.basicDrive(0.0, 0.0, HW.frontVelocityController.controller(), HW.frontVelocityController.controller());
        HW.gyro.getAngle();

        /*
        if(HW.driveStick1.getTrigger()) {
            HW.rearVelocityController.setGoalVelocity(0.0);
            HW.frontVelocityController.setGoalVelocity(0.0);
        }
        if(HW.driveStick1.getRawButton(8)) {
            HW.rearVelocityController.setGoalVelocity(-50.0);
            HW.frontVelocityController.setGoalVelocity(-50.0);
        }
        if(HW.driveStick1.getRawButton(9)) {
            HW.rearVelocityController.setGoalVelocity(50.0);
            HW.frontVelocityController.setGoalVelocity(50.0);
        }*/

        /* Ultrasonic Test
        HW.ultra.setAutomaticMode(true);
        DiscoUtils.debugPrintln("isValid: " + HW.ultra.isRangeValid());
        DiscoUtils.debugPrintln("Ultrasonic Rangefinder: " + HW.ultra.getRangeInches());
        */

        /*if(HW.leftVelocityController.controller()) {
            DiscoUtils.debugPrintln("getRate(mine): " + HW.leftEncoder.getRate(0.01));
            DiscoUtils.debugPrintln("getRate(wpi) : " + HW.leftEncoder.getRate());
            DiscoUtils.debugPrintln("");
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

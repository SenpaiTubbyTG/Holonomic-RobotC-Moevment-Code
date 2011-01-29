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
    boolean done = false;
    boolean dataLogged = false;
    int i = 0;

    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit() {

        HW.gyro.reset();
        HW.EncoderLeft.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.EncoderLeft.setReverseDirection(true);
        HW.EncoderLeft.init();
        HW.EncoderRight.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.EncoderRight.setReverseDirection(true);
        HW.EncoderRight.init();

        HW.leftVC.setInverted(true);
    }

    /**
     * This function is called once every time the robot is disabled
     */
    public void disabledInit() {
        HW.EncoderLeft.stop();
        HW.EncoderLeft.reset();
        HW.EncoderRight.stop();
        HW.EncoderRight.reset();

        HW.rightVC.disable();
        HW.leftVC.disable();
        HW.rightVC.reset();
        HW.leftVC.reset();
        if (!dataLogged) {
            HW.vcDataLogger.writeData();
            DiscoUtils.debugPrintln("log write complete");
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

        //HW.leftVC.init();
        //HW.rightVC.init();

        /*leftVC.enable();
        rightVC.enable();
        leftVC.setSetpoint(0);
        rightVC.setSetpoint(0);*/
        //HW.turnController.initialize();
        //HW.ultra.setDistanceUnits(Ultrasonic.Unit.kInches);
    }

    public void teleopPeriodic() {

        if (HW.kickhandle.getTrigger()) {
            HW.leftVC.enable();
            HW.rightVC.enable();
            HW.leftVC.setSetpoint(0.0);
            HW.rightVC.setSetpoint(0.0);

        } else if (HW.kickhandle.getRawButton(7)) {
            HW.leftDriveMotor.set(-HW.driveStickRight.getY());
            HW.rightDriveMotor.set(HW.driveStickRight.getY());

            if (i > 10) {
                DiscoUtils.debugPrintln("leftOutput: " + HW.leftDriveMotor.get());
                DiscoUtils.debugPrintln("rightOutput: " + HW.rightDriveMotor.get());

                DiscoUtils.debugPrintln("left pidGet: " + HW.EncoderLeft.pidGet() + " ft/s");
                DiscoUtils.debugPrintln("right pidGet: " + HW.EncoderRight.pidGet() + " ft/s");
                i = 0;
            } else {
                i++;
            }

        } else if (HW.kickhandle.getRawButton(8)) {
            HW.leftVC.enable();
            HW.rightVC.enable();
            HW.leftVC.setSetpoint(2);
            HW.rightVC.setSetpoint(2);
            HW.vcDataLogger.addEntry(HW.rightVC.get());
            dataLogged = false;
            
            /*DiscoUtils.debugPrintln("leftError: " + leftVC.getError());
            DiscoUtils.debugPrintln("rightError: " + rightVC.getError());*/

            if (i > 5) {
                DiscoUtils.debugPrintln("leftOutput: " + HW.leftDriveMotor.get());
                DiscoUtils.debugPrintln("rightOutput: " + HW.rightDriveMotor.get());

                DiscoUtils.debugPrintln("leftError: " + HW.leftVC.getError());
                DiscoUtils.debugPrintln("rightError: " + HW.rightVC.getError());


                DiscoUtils.debugPrintln("left pidGet: " + HW.EncoderLeft.pidGet() + "ft/s");
                DiscoUtils.debugPrintln("right pidGet: " + HW.EncoderRight.pidGet() + "ft/s");

                i = 0;
            } else {
                i++;
            }
        } else {
            HW.rightVC.disable();
            HW.leftVC.disable();
            HW.rightVC.reset();
            HW.leftVC.reset();
            HW.drive.drive(HW.driveStickLeft.getY(), HW.driveStickRight.getX());


            if (i > 10) {
                DiscoUtils.debugPrintln("left output: " + HW.leftDriveMotor.get());
                DiscoUtils.debugPrintln("right output: " + HW.rightDriveMotor.get());

                DiscoUtils.debugPrintln("left pidGet: " + HW.EncoderLeft.pidGet() + "ft/s");
                DiscoUtils.debugPrintln("right pidGet: " + HW.EncoderRight.pidGet() + "ft/s");

                DiscoUtils.debugPrintln("left distance: " + HW.EncoderLeft.getDistance() + "ins");
                DiscoUtils.debugPrintln("right distance: " + HW.EncoderRight.getDistance() + "ins");

                DiscoUtils.debugPrintln("left integrated distance: " + HW.EncoderLeft.getIntDistance() + "ins");
                DiscoUtils.debugPrintln("right integrated distance: " + HW.EncoderRight.getIntDistance() + "ins");
                i = 0;
            } else {
                i++;
            }

        }

        /* DATALOGGER
        HW.gyroLog.addEntry(HW.gyro.getAngle());
        done = true;
         */

    }
}

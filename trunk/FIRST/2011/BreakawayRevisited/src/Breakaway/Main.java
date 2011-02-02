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

    /*double leftVelocity;
    double rightVelocity;
    boolean dataLogged = false;
    int i = 0;*/
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
        HW.sonarLog.init();
    }

    /**
     * This function is called once every time the robot is disabled
     */
    public void disabledInit() {
        HW.EncoderLeft.stop();
        HW.EncoderLeft.reset();
        HW.EncoderRight.stop();
        HW.EncoderRight.reset();
        HW.sonarController.enable();
        //HW.rightVC.disable();
        //HW.leftVC.disable();
        HW.sonarLog.disable();
        HW.sonarLog.writeData();
        DiscoUtils.debugPrintln("log write complete");
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
        //HW.gyro.reset();

        HW.EncoderLeft.start();
        HW.EncoderRight.start();
        //HW.rightVC.reset();
        //HW.leftVC.reset();
        //HW.leftVC.setInverted(true);
        //HW.leftVC.enable();
        //HW.rightVC.enable();
        HW.sonarController.setOutputRange(-0.5, 0.5);
        HW.sonarController.enable();
        HW.sonarLog.enable();
    }
    //double goal = 0.0;
    double testSpeed = 5.0;
    int i = 0;
    //PIDController gyroController = new PIDController(0.2, 0.0, 0.0, Gyro, new DiscoDriveConverter(0.0, 0.0, 0.0, Output.kSpeed));

    public void teleopPeriodic() {
        HW.sonarController.setDistance(24.0);
        testSpeed = -HW.sonarController.getSpeed();
        HW.leftDriveMotor.set(-testSpeed);
        HW.rightDriveMotor.set(testSpeed);
        //HW.leftVC.setSetpoint(testSpeed);
        //HW.rightVC.setSetpoint(testSpeed);
        //HW.sonarController.setDistance();
        HW.sonarController.enable();
        HW.sonarLog.setEntryValue(HW.sonar.getRangeInches());
        if (i > 10) {
            DiscoUtils.debugPrintln("Sonar range: " + HW.sonar.getRangeInches());
            DiscoUtils.debugPrintln("SonarCtl Speed: " + HW.sonarController.getSpeed());
            DiscoUtils.debugPrintln("SonarCtl Error: " + HW.sonarController.getError());
            DiscoUtils.debugPrintln("SonarCtlResult: " + HW.sonarController.getResult());
            i = 0;
        } else {
            i++;
        }

        //goal = HW.driveStickLeft.getY() * 130.0;
        /*
         * Velocity Controller Test code
        if (HW.driveStickLeft.getTrigger()) {// || HW..getRawButton(7)) {
        HW.sonarController.setDistance();
        HW.sonarLog.setEntryValue(HW.sonar.getRangeInches()/12);

        HW.rightVC.enable();
        HW.leftVC.enable();
        HW.sonarLog.enable();
        HW.rightVC.setSetpoint(testSpeed);
        HW.leftVC.setSetpoint(testSpeed);

        } else {
        HW.sonarLog.disable();
        HW.drive.drive(HW.driveStickLeft.getY(), HW.driveStickRight.getX());
        HW.rightVC.disable();
        HW.leftVC.disable();
        }*/

        /*if (HW.driveStickLeft.getTrigger()) {
        //HW.leftVC.enable();
        HW.rightVC.enable();
        //HW.leftVC.setSetpoint(0.0);
        HW.rightVC.setSetpoint(0.0);

        } else if (HW.kickhandle.getRawButton(8)) {
        //HW.leftVC.enable();
        HW.rightVCLog.enable();
        HW.rightVC.enable();
        //HW.leftVC.setSetpoint(testSpeed);

        HW.rightVCLog.setEntryValue(HW.rightVC.get());
         *
         */

        /*DiscoUtils.debugPrintln("leftError: " + leftVC.getError());
        DiscoUtils.debugPrintln("rightError: " + rightVC.getError());*/

        /*if (i > 5) {
        DiscoUtils.debugPrintln("leftOutput: " + HW.leftDriveMotor.get());
        DiscoUtils.debugPrintln("rightOutput: " + HW.rightDriveMotor.get());

        DiscoUtils.debugPrintln("left pidGet: " + HW.EncoderLeft.pidGet() + "ft/s");
        DiscoUtils.debugPrintln("right pidGet: " + HW.EncoderRight.pidGet() + "ft/s");

        //DiscoUtils.debugPrintln("leftError: " + HW.leftVC.getError());
        DiscoUtils.debugPrintln("rightError: " + HW.rightVC.getError());

        //DiscoUtils.debugPrintln("leftVCoutput: " + HW.leftVC.get());
        DiscoUtils.debugPrintln("rightVCoutput: " + HW.rightVC.get());

        i = 0;
        } else {
        i++;
        }
        }*/

        /*else if (HW.kickhandle.getRawButton(7)) {
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
        
        }*/
    }
}

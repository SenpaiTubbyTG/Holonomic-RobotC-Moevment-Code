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
    boolean stopped = true;
    boolean joystickDrive = true;
    double leftVelocity;
    double rightVelocity;
    boolean done = false;
    boolean dataLogged = false;

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
        HW.EncoderLeft.reset();
        HW.EncoderLeft.stop();
        HW.EncoderRight.reset();
        HW.EncoderRight.stop();
    }

    /**
     * Periodic code for disabled mode should go here.
     */
    public void disabledPeriodic() {
        if (done && !dataLogged) {
            DiscoUtils.debugPrintln("log write complete");
            dataLogged = true;
        }
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
        HW.EncoderLeft.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.EncoderLeft.init();
        HW.EncoderRight.setDistancePerPulse((8 * Math.PI) / 47 / 3);
        HW.EncoderRight.init();
        HW.rightVelocityController.setReversed(true);
        HW.gyro.reset();

        HW.leftVelocityController.init();
        HW.rightVelocityController.init();
        //HW.turnController.initialize();
        //HW.ultra.setDistanceUnits(Ultrasonic.Unit.kInches);
    }

    public void teleopPeriodic() {
        //Teleop tank drive using VelocityController
        HW.leftVelocityController.setGoalVelocity(
                (HW.driveStickLeft.getY() + HW.driveStickRight.getX()) * 130);
        HW.rightVelocityController.setGoalVelocity(
                (HW.driveStickLeft.getY() - HW.driveStickRight.getX()) * 130);
        
        //DiscoUtils.debugPrintln("leftEncoderVelocity: " + HW.EncoderLeft.getRate());
        //DiscoUtils.debugPrintln("rightEncoderVelocity: " + HW.EncoderRight.getRate());
        
        /*if (joystickDrive) {
        HW.rearVelocityController.setGoalVelocity(HW.driveStick1.getY() * 130);
        HW.frontVelocityController.setGoalVelocity(HW.driveStick2.getY() * 130);
        }
        if (HW.driveStick1.getRawButton(3) || HW.driveStick2.getRawButton(3)) {
        joystickDrive = false;
        HW.rearVelocityController.setGoalVelocity(60);
        HW.frontVelocityController.setGoalVelocity(60);
        } else if (HW.driveStick1.getTrigger()) {
        joystickDrive = true;
        }*/

        //HW.drive.basicDrive(0.0, 0.0, HW.frontVelocityController.controller(),
          //      HW.rearVelocityController.controller());


        /* DATALOGGER
        HW.gyroLog.addEntry(HW.gyro.getAngle());
        done = true;
         */


        /*if (HW.driveStick1.getTrigger()) {
            //HW.rearDriveMotor.set(0.0);
            //HW.frontDriveMotor.set(0.0);
            HW.leftDriveMotor.set(0.0);
            HW.rightDriveMotor.set(0.0);
            stopped = true;
        } else if (HW.driveStick1.getRawButton(8)) {
            HW.turnController.setVelocity(-45.0, -45.0);
            stopped = false;
        } else if (!stopped) {
            HW.turnController.controller();
        }*/
    }
}

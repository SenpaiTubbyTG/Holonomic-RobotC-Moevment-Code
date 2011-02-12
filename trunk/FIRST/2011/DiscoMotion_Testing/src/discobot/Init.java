/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package discobot;

import edu.wpi.first.wpilibj.*;
import Utils.*;

/**
 *
 * @author Nelson
 */
public class Init {

    public static void robotInit() {
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);

        //DataLogger.dataLogger.init();

        HW.encoderFrontLeft.init();
        HW.encoderFrontRight.init();
        HW.encoderRearRight.init();
        HW.encoderRearLeft.init();
    }

    public static void disabledInit() {
        //DataLogger.dataLogger.disable();
        //DataLogger.dataLogger.writeData();
        HW.turnController.disable();
    }

    public static void autonomousInit() {
        HW.sonarControllerLeft.enable();
        setPIDs();
        HW.turnController.enable();
        HW.turnController.setSetpoint(0.0);
        //HW.sonarControllerFrontLeft.enable();
        //HW.sonarControllerFrontRight.enable();
    }

    public static void setPIDs() {
        HW.gyro.reset();
        HW.sonarControllerLeft.setPID(HW.PIDConstants[0][0],
                                      HW.PIDConstants[0][1],
                                      HW.PIDConstants[0][2]);
    }

    public static void teleopInit() {
        String[] header = {"FL","FR","RR","RL"};
        DataLogger.dataLogger.setHeader(header);
        DataLogger.dataLogger.setTimeOffset(Timer.getFPGATimestamp());

        setPIDs();
        //DataLogger.dataLogger.enable();

        HW.turnController.reset();
        HW.turnController.enable();

        HW.encoderFrontLeft.reset();
        HW.encoderFrontRight.reset();
        HW.encoderRearRight.reset();
        HW.encoderRearLeft.reset();
    }
}

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

    public static final double k_frontDist = 40.0;
    public static final double k_leftDist = 33.0;

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
        HW.sonarControllerLeft.disable();
        setPIDs();
        DiscoUtils.debugPrintln("PID Values Set");
    }

    public static void autonomousInit() {
        HW.sonarControllerLeft.setDistance(k_leftDist);
        HW.sonarControllerLeft.setOutputRange(-0.6, 0.6);
        HW.sonarControllerLeft.enable();
        setPIDs();
        HW.turnController.reset();
        HW.turnController.enable();
        HW.turnController.setSetpoint(0.0);
        DiscoUtils.debugPrintln("P: " + HW.sonarControllerLeft.getP()
                + "I: " + HW.sonarControllerLeft.getI()
                + "D: " + HW.sonarControllerLeft.getD());
        //HW.sonarControllerFrontLeft.enable();
        //HW.sonarControllerFrontRight.enable();
    }

    public static void setPIDs() {
        //HW.gyro.reset();
        HW.PIDConstants = PIDTuner.readFile();
        HW.sonarControllerLeft.setPID(
                HW.PIDConstants[0][0],
                HW.PIDConstants[0][1],
                HW.PIDConstants[0][2]);
        HW.sonarControllerFrontLeft.setPID(
                HW.PIDConstants[1][0],
                HW.PIDConstants[1][1],
                HW.PIDConstants[1][2]);
        ;
    }

    public static void teleopInit() {
        String[] header = {"FL", "FR", "RR", "RL"};
        DataLogger.dataLogger.setHeader(header);
        DataLogger.dataLogger.setTimeOffset(Timer.getFPGATimestamp());
        //DataLogger.dataLogger.enable();

        HW.turnController.reset();
        HW.turnController.enable();

        HW.encoderFrontLeft.reset();
        HW.encoderFrontRight.reset();
        HW.encoderRearRight.reset();
        HW.encoderRearLeft.reset();

        HW.sonarControllerLeft.setDistance(k_leftDist);
        HW.sonarControllerLeft.setOutputRange(-0.6, 0.6);
        HW.sonarControllerFrontLeft.setDistance(k_frontDist);
        HW.sonarControllerFrontLeft.setOutputRange(-0.6, 0.6);
    }
}

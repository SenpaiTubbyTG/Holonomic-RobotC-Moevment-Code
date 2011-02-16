package discobot;

import edu.wpi.first.wpilibj.*;
import Utils.*;

/**
 * @author Nelson
 */
public class Init {

    public static final String[] k_DataLoggerHeader = {"FL", "FR", "RR", "RL"};
    public static final double k_frontDist = 40.0;
    public static final double k_leftDist = 33.0;

    public static void robotInit() {
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
        //DataLogger.dataLogger.init();
        /*HW.encoderFrontLeft.init();
        HW.encoderFrontRight.init();
        HW.encoderRearRight.init();
        HW.encoderRearLeft.init();*/
    }

    public static void disabledInit() {
        //dataLoggerWrite();
        disablePIDs();
    }

    public static void autonomousInit() {
        initPIDs();
    }

    public static void teleopInit() {
        initPIDs();
        /*HW.encoderFrontLeft.reset();
        HW.encoderFrontRight.reset();
        HW.encoderRearRight.reset();
        HW.encoderRearLeft.reset();*/
    }

    public static void disablePIDs() {
        HW.turnController.disable();
        HW.sonarControllerLeft.disable();
        HW.sonarControllerFrontLeft.disable();
    }

    public static void initPIDs() {
        HW.gyro.reset();
        HW.turnController.reset();
        HW.sonarControllerLeft.setDistance(k_leftDist);
        HW.sonarControllerLeft.setOutputRange(-0.6, 0.6);
        HW.sonarControllerFrontLeft.setDistance(k_frontDist);
        HW.sonarControllerFrontLeft.setOutputRange(-0.6, 0.6);
        HW.sonarControllerLeft.enable();
        HW.sonarControllerFrontLeft.enable();
        HW.turnController.enable();
        //setPIDs();
    }

    public static void setPIDs() {
        HW.PIDConstants = PIDTuner.readFile();
        HW.sonarControllerLeft.setPID(
                HW.PIDConstants[0][0],
                HW.PIDConstants[0][1],
                HW.PIDConstants[0][2]);
        HW.sonarControllerFrontLeft.setPID(
                HW.PIDConstants[1][0],
                HW.PIDConstants[1][1],
                HW.PIDConstants[1][2]);
        DiscoUtils.debugPrintln("PID Values Set");
    }

    public static void dataLoggerInit() {
        DataLogger.dataLogger.setHeader(k_DataLoggerHeader);
        DataLogger.dataLogger.setTimeOffset(Timer.getFPGATimestamp());
        DataLogger.dataLogger.enable();
    }

    public static void dataLoggerWrite() {
        DataLogger.dataLogger.disable();
        DataLogger.dataLogger.writeData();
    }
}

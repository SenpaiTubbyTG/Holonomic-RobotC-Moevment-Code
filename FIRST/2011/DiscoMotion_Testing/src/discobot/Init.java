package discobot;

import edu.wpi.first.wpilibj.*;
import Utils.*;

/**
 * @author Nelson
 */
public class Init {

    public static final String[] k_DataLoggerHeader = {"FL", "FR", "RR", "RL"};
    public static final double k_frontDist = 50.0;
    public static final double k_leftDist = 50.0;
    //tolerance in inches
    public static final double k_sonarTolerance = 3.0;

    public static void robotInit() {
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);

        //DataLogger.dataLogger.updateArmSpeed();
        /*HW.encoderFrontLeft.updateArmSpeed();
        HW.encoderFrontRight.updateArmSpeed();
        HW.encoderRearRight.updateArmSpeed();
        HW.encoderRearLeft.updateArmSpeed();*/
    }

    public static void disabledInit() {
        //dataLoggerWrite();
        disablePIDs();
        initEncoders();
    }

    public static void autonomousInit() {
        initPIDs();
        initEncoders();
        HW.arm.updateArmSpeed();
        Autonomous.tubeHung = false;
        Autonomous.currentMode = Autonomous.k_sonarPositionMode;
    }

    public static void teleopInit() {
        initPIDs();
        initEncoders();
        HW.liftEncoder.init();
        HW.arm.updateArmSpeed();
    }

    public static void disablePIDs() {
        HW.turnController.disable();
        HW.sonarControllerLeft.disable();
        HW.sonarControllerFrontLeft.disable();
    }

    public static void initPIDs() {
        HW.gyro.reset();
        HW.turnController.reset();//also enables
        HW.sonarControllerLeft.setDistance(k_leftDist);
        HW.sonarControllerLeft.setOutputRange(-0.5, 0.5);
        HW.sonarControllerLeft.enable();
        HW.sonarControllerFrontLeft.setDistance(k_frontDist);
        HW.sonarControllerFrontLeft.setOutputRange(-0.6, 0.6);
        HW.sonarControllerFrontLeft.enable();
        HW.lift.enablePIDControl();
        HW.lift.setSetpoint(HW.lift.kLiftD);
        setPIDs();
        DiscoUtils.debugPrintln("L  PIDs: P="+HW.sonarControllerLeft.getP()+"\tD="+HW.sonarControllerLeft.getD());
        DiscoUtils.debugPrintln("FL PIDs: P="+HW.sonarControllerFrontLeft.getP()+"\tD="+HW.sonarControllerFrontLeft.getD());
        DiscoUtils.debugPrintln("lift PIDs: P=" + HW.lift.getP() + "\tD=" + HW.lift.getD());
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
        HW.lift.setPID(
                HW.PIDConstants[2][0],
                HW.PIDConstants[2][1],
                HW.PIDConstants[2][2]);
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

    public static void initEncoders() {
        HW.encoderFrontLeft.setCodesPerRev(HW.FrontLeftEncoderTicks);
        HW.encoderFrontRight.setCodesPerRev(HW.FrontRightEncoderTicks);
        HW.encoderRearRight.setCodesPerRev(HW.RearRightEncoderTicks);
        HW.encoderRearLeft.setCodesPerRev(HW.RearLeftEncoderTicks);
        HW.encoderFrontLeft.init();
        HW.encoderFrontRight.init();
        HW.encoderRearRight.init();
        HW.encoderRearLeft.init();
        HW.liftEncoder.init();
    }
}

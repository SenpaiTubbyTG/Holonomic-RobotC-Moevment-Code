package discobot;

import edu.wpi.first.wpilibj.*;
import Utils.*;

/**
 *
 * @author Nelson Chen
 */
public class Disabled {

    private static int i = 0;
    private static int printPeriod = 10000;
    public static final String[] k_DataLoggerHeader = {"FL", "FR", "RR", "RL"};

    public static void robotInit() {
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
        //HW.LEDminibot.setDirection(Relay.Direction.kBoth);
        //DataLogger.dataLogger.updateArmSpeed();
        /*HW.encoderFrontLeft.updateArmSpeed();
        HW.encoderFrontRight.updateArmSpeed();
        HW.encoderRearRight.updateArmSpeed();
        HW.encoderRearLeft.updateArmSpeed();*/
        //PIDTuner.setPIDs();
    }

    public static void init() {
        //dataLoggerWrite();
        //disablePIDs();
        Autonomous.currentMode = Autonomous.k_approachGridMode;
        DiscoUtils.debugPrintln("DISABLED INIT COMPLETE");
    }

    public static void periodic() {
        Autonomous.currentMode = Autonomous.k_approachGridMode;
    }

    public static void continuous() {
        if (i > printPeriod) {
            //debugEncoders();
            //debugDistanceControllers();
            debugSonars();
            //debugLimits();
            //debugLift();
            //debugTurnController();
            i = 0;
        } else {
            i++;
        }
        if(HW.liftHandle.getRawButton(1) && HW.liftHandle.getRawButton(8)) {
            Autonomous.currentMode = Autonomous.k_finishAutonMode;
        }
    }

    public static void disablePIDs() {
        HW.turnController.disable();
        HW.sonarControllerLeft.disable();
        //HW.sonarControllerFrontRight.disable();
        HW.sonarControllerFrontRight.disable();
        HW.lift.disablePIDControl();
        DiscoUtils.debugPrintln("PIDS DISABLED");
    }

    public static void dataLoggerWrite() {
        DataLogger.dataLogger.disable();
        DataLogger.dataLogger.writeData();
    }

    public static void dataLoggerInit() {
        DataLogger.dataLogger.setHeader(k_DataLoggerHeader);
        DataLogger.dataLogger.setTimeOffset(Timer.getFPGATimestamp());
        DataLogger.dataLogger.enable();
    }

    public static void debugSonars() {
        DiscoUtils.debugPrintln("SONARS:  "
                + "L=" + HW.sonarLeft.getRangeInches()
                + " / FL=" + HW.sonarFrontLeft.getRangeInches()
                + " / FR=" + HW.sonarFrontRight.getRangeInches()
                + " / R=" + HW.sonarRight.getRangeInches());
    }

    public static void debugTurnController() {
        DiscoUtils.debugPrintln("TurnController:  "
                + "Gyro=" + HW.gyro.getAngle()
                + " / Setpt=" + HW.turnController.getSetpoint()
                + " / Error=" + HW.turnController.getError()
                + " / Rotat=" + HW.turnController.getRotation());
    }

    public static void debugEncoders() {
        DiscoUtils.debugPrintln("ENCODER DISTANCES:  "
                + "FL=" + HW.encoderFrontLeft.getDistance()
                + " / FR=" + HW.encoderFrontRight.getDistance()
                + " / RR=" + HW.encoderRearRight.getDistance()
                + " / RL=" + HW.encoderRearLeft.getDistance());
        /*DiscoUtils.debugPrintln("ENCODERS RATE:  "
                + "FL=" + HW.encoderFrontLeft.getRate()
                + " / FR=" + HW.encoderFrontRight.getRate()
                + " / RR=" + HW.encoderRearRight.getRate()
                + " / RL=" + HW.encoderRearLeft.getRate());*/
    }

    static void debugLimits() {
        DiscoUtils.debugPrintln("ARM:  " + "ISUP:" + HW.arm.isUp() + " / ISDOWN: " + HW.arm.isDown());
        DiscoUtils.debugPrintln("LIFT:  "
                + "MD:" + HW.liftLimitMiddleDown.get()
                + " / ID:" + HW.liftLimitInnerDown.get()
                + " / MU:" + HW.liftLimitMiddleUp.get()
                + " / IU:" + HW.liftLimitInnerUp.get());
    }

    public static void debugLift() {
        DiscoUtils.debugPrintln("LIFT LIMITS:  "
                + "DOWN:" + HW.lift.isLiftDown()
                + " / MIDDLE:" + HW.lift.isLiftMiddle()
                + " / UP:" + HW.lift.isLiftUp());
        DiscoUtils.debugPrintln("LIFT MOTOR:  " + "SPEED:" + HW.liftMotor.getSpeed());
        DiscoUtils.debugPrintln("LIFT CONTROLLER:  "
                + "POSITION:" + HW.lift.getPosition()
                + " / SETPOINT:" + HW.lift.getSetpoint()
                + " / ERROR:" + HW.lift.getError()
                + " / OUTPUT:" + HW.lift.getOutput());
    }

    public static void debugDistanceControllers() {
        DiscoUtils.debugPrintln("\nFL:  SETPOINT = " + HW.distanceControllerFrontLeft.getSetpoint()
                + " / POSITION = " + HW.distanceControllerFrontLeft.pidGet()
                + " / ERROR = " + HW.distanceControllerFrontLeft.getError()
                + " / OUTPUT = " + HW.distanceControllerFrontLeft.getOutput());
        DiscoUtils.debugPrintln("FR:  SETPOINT = " + HW.distanceControllerFrontRight.getSetpoint()
                + " / POSITION = " + HW.distanceControllerFrontRight.pidGet()
                + " / ERROR = " + HW.distanceControllerFrontRight.getError()
                + " / OUTPUT = " + HW.distanceControllerFrontRight.getOutput());
        DiscoUtils.debugPrintln("RR:  SETPOINT = " + HW.distanceControllerRearRight.getSetpoint()
                + " / POSITION = " + HW.distanceControllerRearRight.pidGet()
                + " / ERROR = " + HW.distanceControllerRearRight.getError()
                + " / OUTPUT = " + HW.distanceControllerRearRight.getOutput());
        DiscoUtils.debugPrintln("RL:  SETPOINT = " + HW.distanceControllerRearLeft.getSetpoint()
                + " / POSITION = " + HW.distanceControllerRearLeft.pidGet()
                + " / ERROR = " + HW.distanceControllerRearLeft.getError()
                + " / OUTPUT = " + HW.distanceControllerRearLeft.getOutput());
    }
}

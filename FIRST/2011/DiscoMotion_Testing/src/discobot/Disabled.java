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

        //DataLogger.dataLogger.updateArmSpeed();
        /*HW.encoderFrontLeft.updateArmSpeed();
        HW.encoderFrontRight.updateArmSpeed();
        HW.encoderRearRight.updateArmSpeed();
        HW.encoderRearLeft.updateArmSpeed();*/
    }

    public static void init() {
        //dataLoggerWrite();
        disablePIDs();
        DiscoUtils.debugPrintln("DISABLED INIT COMPLETE");
    }

    public static void periodic() {
    }

    public static void continuous() {
        if (i > printPeriod) {
             //debugSonars();
             //debugEncoders();
             //debugLimits();
             //debugLift();
            /*DiscoUtils.debugPrintln("FL Range: " + HW.sonarFrontLeft.getRangeInches());
            DiscoUtils.debugPrintln("L  Range: " + HW.sonarLeft.getRangeInches());
            DiscoUtils.debugPrintln("FL Range: " + HW.sonarFrontLeft.getRangeInches());
            DiscoUtils.debugPrintln("FL Error: " + HW.sonarControllerFrontLeft.getError());
            DiscoUtils.debugPrintln("FL Setpt: " + HW.sonarControllerFrontLeft.getSetpoint());
            */
            //DiscoUtils.debugPrintln("FL: " + HW.encoderFrontLeft.getRawPosition());
            //DiscoUtils.debugPrintln("liftGet: " + HW.lift.pidGet());
            //DiscoUtils.debugPrintln("RR: " + HW.encoderRearRight.getRawPosition());
            //DiscoUtils.debugPrintln("RL: " + HW.encoderRearLeft.getRawPosition());
            /*DiscoUtils.debugPrintln("Arm up: " + HW.arm.isUp());
            DiscoUtils.debugPrintln("Arm down: " + HW.arm.isDown());*/
            /*DiscoUtils.debugPrintln("\nisLiftUp: " + HW.lift.isLiftUp());
            DiscoUtils.debugPrintln("isLiftMiddle: " + HW.lift.isLiftMiddle());
            DiscoUtils.debugPrintln("isLiftDown: " + HW.lift.isLiftDown());
            DiscoUtils.debugPrintln("\nInnerDown: " + HW.liftLimitInnerDown.get());
            DiscoUtils.debugPrintln("InnerUp: " + HW.liftLimitInnerUp.get());
            DiscoUtils.debugPrintln("MiddleDown: " + HW.liftLimitMiddleDown.get());
            DiscoUtils.debugPrintln("MiddleUp: " + HW.liftLimitMiddleUp.get());*/
            //DiscoUtils.debugPrintln("Arm Up: " + HW.armSwitchUp.get());
            //DiscoUtils.debugPrintln("Arm Down: " + HW.armSwitchDown.get());
            i = 0;
        } else {
            i++;
        }
    }

    public static void disablePIDs() {
        HW.turnController.disable();
        HW.sonarControllerLeft.disable();
        HW.sonarControllerFrontLeft.disable();

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

    public static void debugEncoders(){
        DiscoUtils.debugPrintln("ENCODERS POS:  "
                    + "FL=" + HW.encoderFrontLeft.getRawPosition()
                    + " / FR=" + HW.encoderFrontRight.getRawPosition()
                    + " / RR=" + HW.encoderRearRight.getRawPosition()
                    + " / RL=" + HW.encoderRearLeft.getRawPosition());
        DiscoUtils.debugPrintln("ENCODERS RATE:  "
                    + "FL=" + HW.encoderFrontLeft.getRate()
                    + " / FR=" + HW.encoderFrontRight.getRate()
                    + " / RR=" + HW.encoderRearRight.getRate()
                    + " / RL=" + HW.encoderRearLeft.getRate());
    }

    static void debugLimits(){
        DiscoUtils.debugPrintln("ARM:  " + "UP:" + HW.armSwitchUp.get() + " / DOWN: " + HW.armSwitchDown.get());
        DiscoUtils.debugPrintln("LIFT:  "
                + "MD:" + HW.liftLimitMiddleDown.get()
                + " / ID:" + HW.liftLimitInnerDown.get()
                + " / MU:" + HW.liftLimitMiddleUp.get()
                + " / IU:" + HW.liftLimitInnerUp.get());
    }

    public static void debugLift(){
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
}


package discobot;

import Utils.*;
import com.sun.squawk.util.MathUtils;
import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson
 */
public class Autonomous {

    /**
     * Distance constants; need to be changed to reflect actual distances
     */
    private static final double k_scoringDistance = 10.0;
    private static final double k_approachDistance = 30.0;
    private static final double k_leftDistance = 33.0;
    private static double k_maxSonarError = 3.0;
    private static final double k_maxLiftError = 15.0;
    private static final double k_scoreHeight = HW.lift.kLiftM1;
    /**
     * Scoring modes
     */
    private static final int k_approachGridMode = 0;
    private static final int k_liftRaisingMode = 1;
    private static final int k_creepToGridMode = 2;
    private static final int k_hangTubeP1Mode = 3;
    private static final int k_hangTubeP2Mode = 4;
    private static final int k_liftDropMode = 5;
    private static final int k_takeItBackMode = 7;
    private static final int k_reverseMode = 9;
    private static final int k_finishAutonMode = 10;
    private static int currentMode = k_approachGridMode;
    private static boolean tubeHung = false;
    private static double modeStartTime = 0.0;

    public static void init() {
        currentMode = k_approachGridMode;
        initEncoders();
        initPIDs();
        HW.arm.updateArmSpeed();
        DiscoUtils.debugPrintln("AUTONOMOUS INIT COMPLETE");
        modeStartTime = Timer.getFPGATimestamp();
    }

    public static void periodic() {
        switch (currentMode) {
            case k_approachGridMode:
                sonarPositionFar();
                if (inPosition() && (Timer.getFPGATimestamp() - modeStartTime > 1.0)) {
                    //disableSonarPositioning();
                    HW.drive.HolonomicDrive(0.0, 0.0, 0.0);
                    currentMode = k_liftRaisingMode;
                    Timer.delay(1.0);
                }
                DiscoUtils.debugPrintln("Sonar pos mode");
                break;
            case k_liftRaisingMode:
                HW.lift.setSetpoint(k_scoreHeight);
                if (Math.abs(HW.lift.pidGet()) > k_scoreHeight - k_maxLiftError) {
                    //enableSonarPositioning();
                    setDistanceFromGrid(k_scoringDistance);
                    HW.sonarControllerLeft.setOutputRange(-0.4, 0.4);
                    HW.sonarControllerFrontLeft.setOutputRange(-0.4, 0.4);
                    //HW.sonarControllerFrontRight.setOutputRange(-0.4, 0.4);
                    currentMode = k_creepToGridMode;
                    Timer.delay(1.0);
                }
                DiscoUtils.debugPrintln("Lift raise");
                break;
            case k_creepToGridMode:
                setDistanceFromGrid(k_scoringDistance);
                sonarPositionClose();
                if (inPosition()) {
                    HW.drive.HolonomicDrive(0.0, 0.0, 0.0);
                    currentMode = k_hangTubeP1Mode;
                    Timer.delay(1.0);
                }
                DiscoUtils.debugPrintln("creeping to grid");
                break;
            case k_hangTubeP1Mode:
                disableSonarPositioning();
                HW.lift.setSetpoint(k_scoreHeight - 50);
                if (HW.lift.pidGet() < (k_scoreHeight - 40)) {
                    currentMode = k_hangTubeP2Mode;
                }
                DiscoUtils.debugPrintln("Tube hang P1 mode");
                break;
            case k_hangTubeP2Mode:
                disableSonarPositioning();
                hangTube2();
                if (tubeHung) {
                    setDistanceFromGrid(50.0);
                    currentMode = k_takeItBackMode;
                    Timer.delay(1.0);
                    k_maxSonarError = 7.77;
                }
                DiscoUtils.debugPrintln("Tube hang P2 mode");
                break;
            case k_takeItBackMode:
                setDistanceFromGrid(70.0);
                sonarPositionFar();
                if (inPosition()) {
                    HW.drive.HolonomicDrive(0.0, 0.0, 0.0);
                    currentMode = k_liftDropMode;
                    Timer.delay(1.0);
                }
                DiscoUtils.debugPrintln("Take it back now y'all");
                break;
            case k_liftDropMode:
                HW.lift.setSetpoint(HW.lift.kLiftD);
                if (HW.lift.isLiftDown()) {
                    currentMode = k_reverseMode;
                    Timer.delay(1.0);
                }
                DiscoUtils.debugPrintln("Lift down mode");
                break;
            case k_reverseMode:
                HW.turnController.turnToOrientation(0.0);
                HW.drive.HolonomicDrive(0.0, 0.0, HW.turnController.getRotation());
                if (HW.turnController.getError() < 5) {
                    currentMode = k_finishAutonMode;
                    Timer.delay(1.0);
                }
                DiscoUtils.debugPrintln("Reverse! Reverse");
                break;
            case k_finishAutonMode:
                Disabled.disablePIDs();
                stopAllMotors();
                break;
        }
        HW.arm.up();
    }

    public static void stopAllMotors() {
        HW.liftMotor.set(0.0);
        HW.DMFrontLeft.set(0.0);
        HW.DMFrontRight.set(0.0);
        HW.DMRearRight.set(0.0);
        HW.DMRearLeft.set(0.0);
    }

    public static void continuous() {
        Disabled.continuous();
    }

    public static void disableSonarPositioning() {
        HW.sonarControllerFrontLeft.disable();
        //HW.sonarControllerFrontRight.disable();
        HW.sonarControllerLeft.disable();
    }

    public static void enableSonarPositioning() {
        HW.sonarControllerFrontLeft.enable();
        //HW.sonarControllerFrontRight.enable();
        HW.sonarControllerLeft.enable();
        HW.turnController.enable();
        HW.turnController.setSetpoint(180);
    }

    public static void setDistanceFromGrid(double dist) {
        HW.sonarControllerFrontLeft.setDistance(dist);
        //HW.sonarControllerFrontRight.setDistance(dist);
        enableSonarPositioning();
    }

    public static void sonarPositionFar() {
        double x;
        if (HW.sonarFrontLeft.getRangeInches() < 65) {
            x = HW.sonarControllerLeft.getSpeed();
        } else {
            x = 0;
        }
        double y = HW.sonarControllerFrontLeft.getSpeed();
                //+ HW.sonarControllerFrontRight.getSpeed())
                /// 2;
        HW.drive.HolonomicDrive(x, y, HW.turnController.getRotation());
        //DiscoUtils.debugPrintln("X: " + x);
        //DiscoUtils.debugPrintln("Y: " + y);
    }

    public static void sonarPositionClose() {
        /*HW.turnController.setAngle(
        MathUtils.atan(HW.sonarFrontLeft.getRangeInches() - HW.sonarFrontRight.getRangeInches() / 21.625));
        HW.turnController.setSetpoint(180.0);*/
        double x = HW.sonarControllerLeft.getSpeed();
        double y = HW.sonarControllerFrontLeft.getSpeed();
                //+ HW.sonarControllerFrontRight.getSpeed())
                /// 2;
        HW.drive.HolonomicDrive(x, y, HW.turnController.getRotation());
        //DiscoUtils.debugPrintln("X: " + x);
        //DiscoUtils.debugPrintln("Y: " + y);
    }

    public static boolean inPosition() {
        if (Math.abs(HW.sonarControllerLeft.getError()) < k_maxSonarError
                && Math.abs(HW.sonarControllerFrontLeft.getError()) < k_maxSonarError) {
                //&& Math.abs(HW.sonarControllerFrontRight.getError()) < k_maxSonarError) {
            return true;
        } else {
            return false;
        }
    }

    public static void hangTube1() {
    }

    public static void hangTube2() {
        HW.arm.tubeOut();
        HW.lift.setSetpoint(k_scoreHeight - 100);
        if (HW.lift.pidGet() < (k_scoreHeight - 90)) {
            HW.arm.stopCollector();
            tubeHung = true;
        }
    }

    public static void initPIDs() {
        HW.turnController.reset(180.0);//also enables
        HW.turnController.setOutputRange(-0.5, 0.5);
        HW.turnController.setSetpoint(180.0);
        HW.sonarControllerLeft.setDistance(k_leftDistance);
        HW.sonarControllerLeft.setOutputRange(-0.5, 0.5);
        HW.sonarControllerLeft.enable();
        HW.sonarControllerFrontLeft.setDistance(k_approachDistance);
        HW.sonarControllerFrontLeft.setOutputRange(-0.5, 0.5);
        HW.sonarControllerFrontLeft.enable();
        //HW.sonarControllerFrontRight.setDistance(k_approachDistance);
        //HW.sonarControllerFrontRight.setOutputRange(-0.5, 0.5);
        //HW.sonarControllerFrontRight.enable();
        HW.lift.enablePIDControl();
        HW.lift.setOutputRange(-0.2, 0.75);
        PIDTuner.setPIDs();
        HW.lift.setSetpoint(HW.lift.kLiftD);
        DiscoUtils.debugPrintln("PIDS ENABLED");
        DiscoUtils.debugPrintln("L  PIDs: P=" + HW.sonarControllerLeft.getP() + "\tD=" + HW.sonarControllerLeft.getD());
        DiscoUtils.debugPrintln("FL PIDs: P=" + HW.sonarControllerFrontLeft.getP() + "\tD=" + HW.sonarControllerFrontLeft.getD());
        //DiscoUtils.debugPrintln("FR PIDs: P=" + HW.sonarControllerFrontRight.getP() + "\tD=" + HW.sonarControllerFrontRight.getD());
        DiscoUtils.debugPrintln("lift PIDs: P=" + HW.lift.getP() + "\tD=" + HW.lift.getD());
        DiscoUtils.debugPrintln("turnC PIDs: P=" + HW.turnController.getP() + "\tD=" + HW.turnController.getD());
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

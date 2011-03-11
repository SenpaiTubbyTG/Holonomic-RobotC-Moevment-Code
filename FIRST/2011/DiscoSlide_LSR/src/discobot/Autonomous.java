package discobot;

import Utils.*;
import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson
 *       
 */
public class Autonomous {

    /**
     * Distance constants
     */
    public static final double k_frontDistanceToTube = 20.0;//TBD: distance to collected tube
    public static final double k_scoringDistance = 13.0;
    //private static final double k_approachDistance = 50.0;
    public static final double k_leftDistanceToLane = 35.0;
    public static final double k_leftDistanceToWall = k_leftDistanceToLane + 51.0;
    public static double leftDistanceToLane = k_leftDistanceToLane;
    public static double leftDistanceToWall = k_leftDistanceToWall;
    public static final double k_distanceBetweenColumns = 30.0; //columns are 30 in. ctr-to-ctr
    public static double k_maxSonarError = 2.5;
    public static double k_maxHeadingError = 5.0;
    public static double k_maxLiftError = 15.0;
    public static double scoreHeight = HW.lift.kLiftTopCircle;
    /**
     * Scoring modes
     */
    public static final int k_approachGridMode = 0;
    public static final int k_pullTubeDownMode = 2;
    public static final int k_hangTubeMode = 3;
    public static final int k_takeItBackMode = 5;
    public static final int k_collectTubeMode = 7;
    public static final int k_returnToGridMode = 8;
    public static final int k_finishAutonMode = 10;
    public static int currentMode = k_approachGridMode;
    public static boolean tubeHung = false;
    private static double modeStartTime = 0.0;
    private static double k_startDistance;

    public static void init() {
        //currentMode = k_approachGridMode;
        initEncoders();
        initPIDs();
        HW.arm.updateArmSpeed();
        DiscoUtils.debugPrintln("AUTONOMOUS INIT COMPLETE");
        k_startDistance = HW.sonarFrontRight.getRangeInches();
        modeStartTime = Timer.getFPGATimestamp();
    }

    public static void periodic() {
        switch (currentMode) {
            case k_approachGridMode:
                HW.lift.setSetpoint(scoreHeight);
                //sonarPosition(0.1);
                sonarPosition();
                if (HW.sonarLeft.getRangeInches() <= (leftDistanceToLane + leftDistanceToWall) / 2
                        && HW.sonarControllerLeft.getSetpoint() != leftDistanceToLane) {
                    HW.sonarControllerLeft.setDistance(leftDistanceToLane);
                }
                if (inPosition()
                        && Math.abs(HW.lift.pidGet()) > (scoreHeight - k_maxLiftError)
                        && (Timer.getFPGATimestamp() - modeStartTime > 1.0)) {
                    //disableSonarPositioning();
                    HW.drive.HolonomicDrive(0.0, 0.0, 0.0);
                    currentMode = k_pullTubeDownMode;
                    //Timer.delay(1.0);
                    modeStartTime = Timer.getFPGATimestamp();
                }
                break;
            case k_pullTubeDownMode:
                HW.lift.setSetpoint(scoreHeight - 100);
                if (HW.lift.pidGet() < (scoreHeight - 90)) {
                    currentMode = k_hangTubeMode;
                }
                break;
            case k_hangTubeMode:
                //disableSonarPositioning();
                hangTube();
                if (tubeHung) {
                    setFrontDistance(k_startDistance);
                    //limitSonarControllers(0.75);
                    k_maxSonarError = 3.0;
                    currentMode = k_takeItBackMode;
                    modeStartTime = Timer.getFPGATimestamp();
                }
                break;
            case k_takeItBackMode:
                //sonarPosition(-0.1);

                //if far enough from grid that lowering the lift is safe
                if (HW.sonarFrontRight.getRangeInches() >= 25.0
                        && HW.lift.getSetpoint() != HW.lift.kLiftD) {
                    HW.lift.setSetpoint(HW.lift.kLiftD);
                    HW.turnController.setSetpoint(270);
                }
                if (HW.turnController.getSetpoint() == 270.0) {
                    if (HW.turnController.getError() < k_maxHeadingError) {
                        setLeftDistance(k_startDistance);
                        if (HW.sonarLeft.getRangeInches() > (k_startDistance - k_maxSonarError)
                                && HW.lift.isLiftDown()) {
                            k_maxSonarError = 2.0;
                            setFrontDistance(k_frontDistanceToTube);
                            currentMode = k_collectTubeMode;
                        }
                    } else {
                        //TODO: use old speeds based on rotateVector
                    }

                } else {
                    sonarPosition();
                }
                break;
            case k_collectTubeMode:
                HW.arm.collect();
                sonarPosition();
                if (HW.sonarFrontRight.getRangeInches() < k_frontDistanceToTube - k_maxSonarError) {
                    HW.turnController.setSetpoint(180.0);
                    currentMode = k_returnToGridMode;
                    setFrontDistance(k_scoringDistance);
                    leftDistanceToWall += k_distanceBetweenColumns;
                    leftDistanceToLane += k_distanceBetweenColumns;
                    setLeftDistance(leftDistanceToWall);
                    scoreHeight = HW.lift.kLiftTopSquare;
                }
                break;
            case k_returnToGridMode:
                if (HW.sonarLeft.getRangeInches() <= (leftDistanceToLane + leftDistanceToWall) / 2
                        && HW.sonarControllerLeft.getSetpoint() != leftDistanceToLane) {
                    HW.sonarControllerLeft.setDistance(leftDistanceToLane);
                }
                if (HW.arm.isArmUp() && HW.turnController.getSetpoint() != 180.0) {
                    HW.turnController.setSetpoint(180.0);
                }
                if (HW.turnController.getSetpoint() == 180.0) {
                    if (HW.turnController.getError() < k_maxHeadingError) {
                        setLeftDistance(k_leftDistanceToWall);
                        setFrontDistance(k_scoringDistance);
                        if (HW.sonarLeft.getRangeInches() < (k_scoringDistance + k_maxSonarError)
                                && HW.lift.isLiftUp()) {
                            tubeHung = false;
                            currentMode = k_pullTubeDownMode;
                        }
                    } else {
                        //TODO: use old speeds based on rotateVector
                    }

                } else {
                    sonarPosition();
                }
                HW.lift.setSetpoint(scoreHeight);
                //WORK PAUSED HERE
                break;

            case k_finishAutonMode:
                Disabled.disablePIDs();
                stopAllMotors();
                break;
        }
        if (currentMode != k_collectTubeMode) {
            HW.arm.up();
        }
    }

    public static void limitSonarControllers(double limit) {
        HW.sonarControllerFrontRight.setOutputRange(-limit, limit);
        HW.sonarControllerLeft.setOutputRange(-limit, limit);
    }

    public static void stopAllMotors() {
        HW.liftMotor.set(0.0);
        HW.DMFrontLeft.set(0.0);
        HW.DMFrontRight.set(0.0);
        HW.DMRearRight.set(0.0);
        HW.DMRearLeft.set(0.0);
    }

    public static void continuous() {
        //Disabled.continuous();
    }

    public static void disableSonarPositioning() {
        HW.sonarControllerFrontRight.disable();
        HW.sonarControllerLeft.disable();
        HW.drive.HolonomicDrive(0.0, 0.0, 0.0);
    }

    public static void enableSonarPositioning() {
        HW.sonarControllerFrontRight.enable();
        //HW.sonarControllerFrontRight.enable();
        HW.sonarControllerLeft.enable();
        //HW.turnController.enable();
        //HW.turnController.setSetpoint(180);
    }

    public static void setFrontDistance(double dist) {
        HW.sonarControllerFrontRight.setDistance(dist);
        //HW.sonarControllerFrontRight.setDistance(dist);
        enableSonarPositioning();
    }

    public static void setLeftDistance(double dist) {
        HW.sonarControllerLeft.setDistance(dist);
        //HW.sonarControllerFrontRight.setDistance(dist);
        enableSonarPositioning();
    }

    /**
     * @deprecated sonarPositioningFar based on a hard-coded offset
     * to correct mechanical imbalance in drive train
     */
    public static void sonarPositionFar(double offset) {
        if (HW.lift.getPosition() > HW.lift.kLiftTopCircle - 100) {
            limitSonarControllers(0.5);
        } else {
            limitSonarControllers(0.75);
        }
        //limitSonarControllers(HW.lift.getPosition());
        double x;
        if (HW.sonarFrontRight.getRangeInches() < 65) {
            x = HW.sonarControllerLeft.getSpeed();
        } else {
            x = offset; //trying to correct drive train deficiency
        }
        double y = HW.sonarControllerFrontRight.getSpeed();
        //+ HW.sonarControllerFrontRight.getSpeed())
        /// 2;
        HW.drive.HolonomicDrive(x, y, HW.turnController.getRotation());
        //DiscoUtils.debugPrintln("X: " + x);
        //DiscoUtils.debugPrintln("Y: " + y);
    }

    public static void sonarPosition() {
        if (HW.lift.getPosition() > HW.lift.kLiftTopCircle - 150) {
            limitSonarControllers(0.6);
        } else {
            limitSonarControllers(1.0);
        }
        //OR limitSonarControllers(HW.lift.getPosition());
        HW.drive.HolonomicDrive(HW.sonarControllerLeft.getSpeed(),
                HW.sonarControllerFrontRight.getSpeed(),
                HW.turnController.getRotation());
        //DiscoUtils.debugPrintln("X: " + x);
        //DiscoUtils.debugPrintln("Y: " + y);
    }

    public static void sonarPositionClose() {
        /*HW.turnController.setAngle(
        MathUtils.atan(HW.sonarFrontLeft.getRangeInches() - HW.sonarFrontRight.getRangeInches() / 21.625));
        HW.turnController.setSetpoint(180.0);*/
        double x = HW.sonarControllerLeft.getSpeed();
        double y = HW.sonarControllerFrontRight.getSpeed();
        //+ HW.sonarControllerFrontRight.getSpeed())
        /// 2;
        HW.drive.HolonomicDrive(x, y, HW.turnController.getRotation());
        //DiscoUtils.debugPrintln("X: " + x);
        //DiscoUtils.debugPrintln("Y: " + y);
    }

    public static boolean inPosition() {
        if (Math.abs(HW.sonarControllerLeft.getError()) < k_maxSonarError
                && Math.abs(HW.sonarControllerFrontRight.getError()) < k_maxSonarError) {
            //&& Math.abs(HW.sonarControllerFrontRight.getError()) < k_maxSonarError) {
            return true;
        } else {
            return false;
        }
    }

    public static void hangTube() {
        HW.lift.setSetpoint(scoreHeight - 110);
        if (HW.lift.pidGet() < (scoreHeight - 100)) {
            HW.arm.stopCollector();
            HW.lift.setSetpoint(HW.lift.pidGet());
            tubeHung = true;
        } else {
            HW.arm.tubeOut();
        }
    }

    public static void initPIDs() {
        HW.turnController.reset(180.0);//also enables
        HW.turnController.setOutputRange(-0.75, 0.75);
        HW.turnController.setSetpoint(180.0);
        HW.sonarControllerLeft.setDistance(leftDistanceToWall);
        HW.sonarControllerFrontRight.setDistance(k_scoringDistance);
        limitSonarControllers(1.0);
        enableSonarPositioning();
        HW.lift.enablePIDControl();
        HW.lift.setOutputRange(-0.2, 1.0);
        //HW.lift.setSetpoint(HW.lift.kLiftD);
        //PIDTuner.setPIDs();
        /*DiscoUtils.debugPrintln("PIDS ENABLED");
        DiscoUtils.debugPrintln("L  PIDs: P=" + HW.sonarControllerLeft.getP() + "\tD=" + HW.sonarControllerLeft.getD());
        DiscoUtils.debugPrintln("FL PIDs: P=" + HW.sonarControllerFrontRight.getP() + "\tD=" + HW.sonarControllerFrontRight.getD());
        //DiscoUtils.debugPrintln("FR PIDs: P=" + HW.sonarControllerFrontRight.getP() + "\tD=" + HW.sonarControllerFrontRight.getD());
        DiscoUtils.debugPrintln("lift PIDs: P=" + HW.lift.getP() + "\tD=" + HW.lift.getD());
        DiscoUtils.debugPrintln("turnC PIDs: P=" + HW.turnController.getP() + "\tD=" + HW.turnController.getD());*/
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

package discobot;

import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author Nelson
 */
public class EncoderAutonomous {

    //public static final double k_componentVelocity = Math.sin(Math.PI/4);s
    public static final double k_distanceToZone = 50.0;
    public static final double k_distanceToGrid = 20.0;
    public static final double k_maxHeadingError = 5.0;
    public static final double k_maxPositionError = 3.0;
    public static final double k_maxLiftError = 15.0;
    public static final double k_scoreHeight = HW.lift.kLiftM1;
    public static final int k_turnToAngleMode = 1;
    public static final int k_driveToZoneMode = 2;
    public static final int k_revertAngleMode = 3;
    public static final int k_liftRaiseMode = 4;
    public static final int k_driveToGridMode = 5;
    public static final int k_lowerLiftMode = 6;
    public static final int k_hangTubeMode = 7;
    public static final int k_backUpZoneMode = 8;
    public static final int k_liftDropMode = 9;
    public static final int k_backUpFarMode = 10;
    public static final int k_turnHalfMode = 11;
    public static final int k_finishAutonMode = 12;
    public static int currentMode = k_turnToAngleMode;
    public static boolean tubeHung = false;
    public static double modeStartTime = 0.0;

    public static void init() {
        HW.turnController.enable();
        HW.turnController.turnToOrientation(45);
        HW.lift.enablePIDControl();
        HW.lift.setSetpoint(HW.lift.kLiftD);
        currentMode = k_turnToAngleMode;
        modeStartTime = Timer.getFPGATimestamp();
    }

    public static void periodic() {
        switch (currentMode) {
            case k_turnToAngleMode:
                HW.drive.HolonomicDrive(0.0, 0.0, HW.turnController.getRotation());
                if (Math.abs(HW.turnController.getError()) < k_maxHeadingError
                        && (Timer.getFPGATimestamp() - modeStartTime) > 0.1) {
                    //HW.drive.setMotorSpeeds(0.0, 0.0, 0.0, 0.0);
                    HW.distanceControllerFrontLeft.init();
                    HW.distanceControllerFrontRight.init();
                    HW.distanceControllerRearRight.init();
                    HW.distanceControllerRearLeft.init();
                    currentMode = k_driveToZoneMode;
                    HW.distanceControllerFrontLeft.setDistance(0.0);
                    HW.distanceControllerFrontRight.setDistance(k_distanceToZone);
                    HW.distanceControllerRearRight.setDistance(0.0);
                    HW.distanceControllerRearLeft.setDistance(k_distanceToZone);
                    modeStartTime = Timer.getFPGATimestamp();
                }
                DiscoUtils.debugPrintln("turnToAngleMode");
                break;
            case k_driveToZoneMode:
                HW.drive.holonomicDrive(
                        (HW.distanceControllerFrontRight.getOutput() + HW.distanceControllerFrontLeft.getOutput()) / 2 ,
                        45, HW.turnController.getRotation());
                //HW.drive.setMotorSpeeds();//HW.distanceControllerRearRight.getOutput());
                if (Math.abs(HW.distanceControllerFrontRight.getError()) < k_maxPositionError
                        && Math.abs(HW.distanceControllerRearLeft.getError()) < k_maxPositionError
                        && (Timer.getFPGATimestamp() - modeStartTime) > 1.0) {
                    //HW.drive.setMotorSpeeds(0.0, 0.0, 0.0, 0.0);
                    currentMode = k_revertAngleMode;
                }
                DiscoUtils.debugPrintln("driveToZoneMode");
                break;
            case k_revertAngleMode:
                HW.drive.HolonomicDrive(0.0, 0.0, HW.turnController.getRotation());
                if (HW.turnController.getError() < k_maxHeadingError) {
                    HW.drive.setMotorSpeeds(0.0, 0.0, 0.0, 0.0);
                    currentMode = k_liftRaiseMode;
                }
                DiscoUtils.debugPrintln("revertAngleMode");
                break;
            case k_liftRaiseMode:
                HW.lift.setSetpoint(k_scoreHeight);
                if (Math.abs(HW.lift.pidGet()) > k_scoreHeight - k_maxLiftError) {
                    setDistanceToGrid(k_distanceToGrid);
                    //HW.drive.setMotorSpeeds(0.0, 0.0, 0.0, 0.0);
                    currentMode = k_driveToGridMode;
                }
                DiscoUtils.debugPrintln("liftRaiseMode");
                break;
            case k_driveToGridMode:
                HW.drive.setMotorSpeeds(HW.distanceControllerFrontLeft.getOutput(),
                        HW.distanceControllerFrontRight.getOutput(),
                        HW.distanceControllerRearLeft.getOutput(),
                        HW.distanceControllerRearRight.getOutput());
                if (inPosition()) {
                    HW.drive.setMotorSpeeds(0.0, 0.0, 0.0, 0.0);
                    currentMode = k_revertAngleMode;
                }
                DiscoUtils.debugPrintln("driveToGridMode");
                break;
            case k_lowerLiftMode:
                HW.lift.setSetpoint(k_scoreHeight - 50);
                if (HW.lift.pidGet() < (k_scoreHeight - 40)) {
                    currentMode = k_hangTubeMode;
                }
                DiscoUtils.debugPrintln("Lower lift Mode");
                break;
            case k_hangTubeMode:
                hangTube();
                if (tubeHung) {
                    currentMode = k_backUpZoneMode;
                    setDistanceToGrid(-60);
                    //Timer.delay(1.0);
                }
                DiscoUtils.debugPrintln("Tube hang mode");
                break;
            case k_backUpZoneMode:
                HW.drive.setMotorSpeeds(HW.distanceControllerFrontLeft.getOutput(),
                        HW.distanceControllerFrontRight.getOutput(),
                        HW.distanceControllerRearLeft.getOutput(),
                        HW.distanceControllerRearRight.getOutput());
                if (inPosition()) {
                    HW.drive.HolonomicDrive(0.0, 0.0, 0.0);
                    currentMode = k_liftDropMode;
                    Timer.delay(1.0);
                }
                DiscoUtils.debugPrintln("backUpZoneMode");
                break;
            case k_liftDropMode:
                HW.lift.setSetpoint(HW.lift.kLiftD);
                if (HW.lift.isLiftDown()) {
                    currentMode = k_backUpFarMode;
                    Timer.delay(1.0);
                    setDistanceToGrid(-100.0);
                }
                DiscoUtils.debugPrintln("liftDropMode");
                break;
            case k_backUpFarMode:
                HW.drive.setMotorSpeeds(HW.distanceControllerFrontLeft.getOutput(),
                        HW.distanceControllerFrontRight.getOutput(),
                        HW.distanceControllerRearLeft.getOutput(),
                        HW.distanceControllerRearRight.getOutput());
                if (inPosition()) {
                    HW.drive.HolonomicDrive(0.0, 0.0, 0.0);
                    Timer.delay(1.0);
                    HW.turnController.setSetpoint(0.0);
                    //HW.turnController.turnToOrientation(0.0);
                    //the speed of turnToOrientation is probably unecessary
                    currentMode = k_turnHalfMode;
                }
                DiscoUtils.debugPrintln("backUpFarMode");
                break;
            case k_turnHalfMode:
                HW.drive.HolonomicDrive(0.0, 0.0, HW.turnController.getRotation());
                if (HW.turnController.getError() < k_maxHeadingError) {
                    currentMode = k_finishAutonMode;
                    Timer.delay(1.0);
                }
                DiscoUtils.debugPrintln("turnHalfMode");
                break;
            case k_finishAutonMode:
                Disabled.disablePIDs();
                stopAllMotors();
                DiscoUtils.debugPrintln("Autonomous finished!");
                break;
        }
        HW.arm.up();
    }

    public static void setDistanceToGrid(double dist) {
        HW.distanceControllerFrontLeft.setDistance(dist);
        HW.distanceControllerFrontRight.setDistance(dist);
        HW.distanceControllerRearRight.setDistance(dist);
        HW.distanceControllerRearLeft.setDistance(dist);
    }

    public static boolean inPosition() {
        return (Math.abs(HW.distanceControllerFrontLeft.getError()) < k_maxPositionError
                && Math.abs(HW.distanceControllerFrontRight.getError()) < k_maxPositionError
                && Math.abs(HW.distanceControllerRearRight.getError()) < k_maxPositionError
                && Math.abs(HW.distanceControllerRearLeft.getError()) < k_maxPositionError);
    }

    public static void stopAllMotors() {
        HW.liftMotor.set(0.0);
        HW.DMFrontLeft.set(0.0);
        HW.DMFrontRight.set(0.0);
        HW.DMRearRight.set(0.0);
        HW.DMRearLeft.set(0.0);
    }

    public static void hangTube() {
        HW.arm.tubeOut();
        HW.lift.setSetpoint(k_scoreHeight - 100);
        if (HW.lift.pidGet() < (k_scoreHeight - 90)) {
            HW.arm.stopCollector();
            tubeHung = true;
        }
    }

    public static void continuous() {
        Disabled.continuous();
    }
}

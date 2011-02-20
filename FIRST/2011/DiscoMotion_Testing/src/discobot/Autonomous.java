package discobot;

import Utils.DiscoUtils;

/**
 * @author Nelson
 */
public class Autonomous {

    public static final double k_scoringDistance = 30.0;
    public static final double k_maxSonarError = 3.0;
    public static final double k_maxLiftError = 15.0;
    public static final double k_scoreHeight = HW.lift.kLiftM1;
    public static boolean tubeHung = false;
    private static int i = 0;
    public static final int k_approachGridMode = 0;
    private static final int k_liftRaisingMode = 1;
    private static final int k_creepToGridMode = 2;
    private static final int k_hangTubeMode = 3;
    private static final int k_liftDropMode = 4;
    private static final int k_takeItBackMode = 5;
    private static final int k_reverseMode = 6;
    private static final int k_finishAutonMode = 7;
    public static int currentMode = k_approachGridMode;

    public static void periodic() {
        switch (currentMode) {
            case k_approachGridMode:
                sonarPosition();
                if (inPosition()) {
                    currentMode = k_liftRaisingMode;
                }
                DiscoUtils.debugPrintln("Sonar pos mode");
                break;
            case k_liftRaisingMode:
                disableSonarPositioning();
                HW.lift.setSetpoint(k_scoreHeight);
                if (Math.abs(HW.lift.pidGet()) > k_scoreHeight - k_maxLiftError) {
                    currentMode = k_creepToGridMode;
                }
                DiscoUtils.debugPrintln("Lift raise");
                break;
            case k_creepToGridMode:
                enableSonarPositioning();
                setDistanceFromGrid(k_scoringDistance);
                sonarPosition();
                if (HW.sonarFrontLeft.getRangeInches() < k_scoringDistance + k_maxSonarError) {
                    currentMode = k_hangTubeMode;
                }
                DiscoUtils.debugPrintln("creeping to grid");
                break;
            case k_hangTubeMode:
                disableSonarPositioning();
                hangTube();
                if (tubeHung) {
                    currentMode = k_liftDropMode;
                }
                DiscoUtils.debugPrintln("Tube hang mode");
                break;
            case k_liftDropMode:
                HW.lift.downToSwitch();
                if (HW.lift.isLiftDown()) {
                    currentMode = k_takeItBackMode;
                }
                DiscoUtils.debugPrintln("Lift down mode");
                break;
            case k_takeItBackMode:
                enableSonarPositioning();
                setDistanceFromGrid(100);
                sonarPosition();
                if(inPosition()) {
                    currentMode = k_reverseMode;
                }
                DiscoUtils.debugPrintln("Take it back now y'all");
                break;
            case k_reverseMode:
                HW.turnController.turnToOrientation(180);
                if(HW.turnController.getError() < 5) {
                    currentMode = k_finishAutonMode;
                }
                DiscoUtils.debugPrintln("Reverse! Reverse");
                break;
            case k_finishAutonMode:
                DiscoUtils.debugPrintln("PRETEND LIKE IM FLASHING PRETTY LIGHTS");
                //FLASH PRETTY LIGHTS HERE!!!
                break;
        }
        HW.arm.up();
    }

    public static void continuous() {
        if (i > 10000) {

            /*DiscoUtils.debugPrintln("Lift Error: " + HW.lift.getError());
            DiscoUtils.debugPrintln("Lift Speed: " + HW.lift.getLiftSpeed());
            DiscoUtils.debugPrintln("Lift Set Point: " + HW.lift.getSetpoint());
            DiscoUtils.debugPrintln("FL Setpt: " + HW.sonarControllerFrontLeft.getSetpoint());*/
            //DiscoUtils.debugPrintln("inPosition: " + inPosition());
            DiscoUtils.debugPrintln("FL Range: " + HW.sonarFrontLeft.getRangeInches());
            DiscoUtils.debugPrintln("L Range: " + HW.sonarLeft.getRangeInches());
            DiscoUtils.debugPrintln("FL Error: " + HW.sonarControllerFrontLeft.getError());
            DiscoUtils.debugPrintln("L Error: " + HW.sonarControllerLeft.getError());
            i = 0;
        } else {
            i++;
        }
    }

    public static void disableSonarPositioning() {
        HW.sonarControllerFrontLeft.disable();
        HW.sonarControllerLeft.disable();
    }

    public static void enableSonarPositioning() {
        HW.sonarControllerFrontLeft.enable();
        HW.sonarControllerLeft.enable();
    }

    public static void setDistanceFromGrid(double dist) {
        HW.sonarControllerFrontLeft.setDistance(dist);
        enableSonarPositioning();
    }

    public static void sonarPosition() {
        double x;
        if (!inPosition()) {
            if (HW.sonarFrontLeft.getRangeInches() < 60) {
                x = HW.sonarControllerLeft.getSpeed();
            } else {
                x = 0;
            }
            double y = HW.sonarControllerFrontLeft.getSpeed();
            HW.drive.HolonomicDrive(x, y, HW.turnController.getRotation());
            DiscoUtils.debugPrintln("X: " + x);
            DiscoUtils.debugPrintln("Y: " + y);
        } else {
            HW.drive.holonomicDrive(0.0, 0.0, HW.turnController.getRotation());
        }
    }

    public static boolean inPosition() {
        if (Math.abs(HW.sonarControllerLeft.getError()) < k_maxSonarError
                && Math.abs(HW.sonarControllerFrontLeft.getError()) < k_maxSonarError) {
            return true;
        } else {
            return false;
        }
    }

    public static void hangTube() {
        HW.lift.setSetpoint(k_scoreHeight - 40);
        HW.arm.tubeOut();
        if (HW.lift.pidGet() < (k_scoreHeight - 30)) {
            HW.arm.stopCollector();
            tubeHung = true;
        }
    }
}

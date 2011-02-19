package discobot;

import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson
 */
public class Autonomous {

    public static final double k_scoringDistance = 30.0;
    public static final double k_maxDistanceError = 3.0;
    public static final double k_maxLiftError = 20.0;
    public static boolean tubeHung = false;
    private static int i = 0;
    public static final int k_sonarPositionMode = 0;
    private static final int k_liftRaisingMode = 1;
    private static final int k_hangTubeMode = 2;
    private static final int k_liftDropMode = 3;
    public static int currentMode = k_sonarPositionMode;

    public static void periodic() {
        switch (currentMode) {
            case k_sonarPositionMode:
                sonarPosition();
                if (inPosition()) {
                    currentMode = k_liftRaisingMode;
                }
                break;
            case k_liftRaisingMode:
                liftUp();
                if (Math.abs(HW.lift.getError()) < k_maxLiftError) {
                    if (HW.sonarControllerFrontLeft.getSetpoint() == k_scoringDistance) {
                        currentMode = k_hangTubeMode;
                    } else if(HW.lift.getPosition() > HW.lift.kLiftH1 - 20){
                        setDistanceFromGrid(k_scoringDistance);
                        currentMode = k_sonarPositionMode;
                    }
                }
                break;
            case k_hangTubeMode:
                hangTube();
                if(tubeHung) {
                    currentMode = k_liftDropMode;
                }
                break;
            case k_liftDropMode:
                liftDown();
                break;
        }
        //HW.arm.up();
    }

    public static void continuous() {
        if (i > 10000) {

            /*DiscoUtils.debugPrintln("Lift Error: " + HW.lift.getError());
            DiscoUtils.debugPrintln("Lift Speed: " + HW.lift.getLiftSpeed());
            DiscoUtils.debugPrintln("Lift Set Point: " + HW.lift.getSetpoint());
            DiscoUtils.debugPrintln("FL Setpt: " + HW.sonarControllerFrontLeft.getSetpoint());*/
            //DiscoUtils.debugPrintln("inPosition: " + inPosition());
            /*DiscoUtils.debugPrintln("FL Range: " + HW.sonarFrontLeft.getRangeInches());
            DiscoUtils.debugPrintln("L Range: " + HW.sonarLeft.getRangeInches());
            DiscoUtils.debugPrintln("FL Error: " + HW.sonarControllerFrontLeft.getError());
            DiscoUtils.debugPrintln("L Error: " + HW.sonarControllerLeft.getError());*/
            i = 0;
        } else {
            i++;
        }
    }

    public static void setDistanceFromGrid(double dist) {
        HW.sonarControllerFrontLeft.setDistance(dist);
        HW.sonarControllerFrontLeft.enable();
    }

    public static void sonarPosition() {
        double x;
        if (!inPosition()) {
            if (HW.sonarFrontLeft.getRangeInches() < 70) {
                HW.sonarControllerFrontLeft.setOutputRange(-0.4, 0.4);
                HW.sonarControllerLeft.setOutputRange(-0.4, 0.4);
                x = HW.sonarControllerLeft.getSpeed();
            } else {
                x = 0;
            }
            double y = HW.sonarControllerFrontLeft.getSpeed();
            HW.drive.HolonomicDrive(x, y, HW.turnController.getRotation());
            /*DiscoUtils.debugPrintln("X: " + x);
            DiscoUtils.debugPrintln("Y: " + y);*/
        } else {
            HW.drive.holonomicDrive(0.0, 0.0, HW.turnController.getRotation());
        }
    }

    public static boolean inPosition() {
        if (Math.abs(HW.sonarControllerLeft.getError()) < k_maxDistanceError
                && Math.abs(HW.sonarControllerFrontLeft.getError()) < k_maxDistanceError) {
            return true;
        } else {
            return false;
        }
    }

    public static void liftUp() {
        HW.lift.setSetpoint(HW.lift.kLiftH1);
        HW.lift.enablePIDControl();
    }

    public static void liftDown() {
        HW.lift.setSetpoint(HW.lift.kLiftD);
        HW.lift.enablePIDControl();
    }

    public static void hangTube() {
        HW.lift.setSetpoint(HW.lift.kLiftH1 - 50);
        HW.arm.tubeOut();
        if (HW.lift.getError() < k_maxLiftError) {
            Timer.delay(2.0);
            HW.arm.stopCollector();
            tubeHung = true;
        }
        DiscoUtils.debugPrintln("Tube hung!");
    }
}

package discobot;

import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson
 */
public class Autonomous {

    public static final double k_scoringDistance = 30.0;
    public static final double k_maxError = 3.0;
    public static boolean tubeHung = false;
    private static int i = 0;

    public static void periodic() {
        HW.lift.enablePIDControl();
        sonarPosition();
        HW.arm.up();
        if (inPosition()) {
            if (!HW.lift.isLiftUp() && !tubeHung) {
                liftUp();
            } else {
                setPositionFromWall(k_scoringDistance);
                if (!tubeHung && inPosition()) {
                    hangTube();
                }
            }
        }
        if (tubeHung) {
            liftDown();
            setPositionFromWall(70.0);
        }
        /*if(tubeHung && inPosition()) {
        HW.turnController.turnToOrientation(180.0);
        }*/
    }

    public static void continuous() {
    }

    public static void setPositionFromWall(double dist) {
        HW.sonarControllerFrontLeft.setDistance(dist);
        HW.sonarControllerFrontLeft.enable();
    }

    public static void sonarPosition() {
        double x;
        if (!inPosition()) {
            if (HW.sonarFrontLeft.getRangeInches() < 70) {
                x = HW.sonarControllerLeft.getSpeed();
            } else {
                x = 0;
            }
            double y = HW.sonarControllerFrontLeft.getSpeed();
            HW.drive.HolonomicDrive(x, y, HW.turnController.getRotation());
        } else {
            HW.drive.holonomicDrive(0.0, 0.0, HW.turnController.getRotation());
        }
    }

    public static boolean inPosition() {
        if (HW.sonarControllerLeft.getError() < k_maxError
                && HW.sonarControllerFrontLeft.getError() < k_maxError) {
            return true;
        } else {
            return false;
        }
    }

    public static void liftUp() {
        HW.lift.setSetpoint(HW.lift.kLiftH1);
    }

    public static void liftDown() {
        HW.lift.setSetpoint(HW.lift.kLiftD);
    }

    public static void hangTube() {
        HW.lift.setSetpoint(HW.lift.kLiftH1 - 50);
        HW.arm.tubeOut();
        if (HW.lift.getError() < 5) {
            HW.arm.stopCollector();
            tubeHung = true;
        }
    }
}

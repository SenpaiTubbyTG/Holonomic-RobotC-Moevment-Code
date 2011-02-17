package discobot;

import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson
 */
public class Autonomous {

    public static final double scoringDistance = 30.0;
    public static boolean tubeHung = false;
    private static int i = 0;

    public static void periodic() {
        HW.lift.enablePIDControl();
        sonarPosition();
        //HW.arm.up();
        if (inPosition()) {
            if (!HW.lift.isLiftUp() && !tubeHung) {
                liftUp();
            } else {
                setPositionFromWall(scoringDistance);
                if (!tubeHung && inPosition()) {
                    hangTube();
                    tubeHung = true;
                }
            }
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
        if (HW.sonarControllerLeft.onTarget()
                && HW.sonarControllerFrontLeft.onTarget()) {
            return true;
        } else {
            return false;
        }
    }

    public static void liftUp() {
        HW.lift.setSetpoint(HW.lift.kLiftUp);
    }

    public static void liftDown() {
        HW.lift.setSetpoint(HW.lift.kLiftDown);
    }

    public static void hangTube() {
        HW.lift.setLiftSpeed(0.3);
        Timer.delay(0.3);
        HW.arm.tubeOut();
        Timer.delay(1.0);
        HW.arm.stopCollector();
        setPositionFromWall(100.0);
        liftDown();
    }
}

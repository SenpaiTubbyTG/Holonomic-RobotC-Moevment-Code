package discobot;

import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson
 */
public class AutoScore {

    public static final double k_maxError = 3.0;
    //distances from left wall
    //Left grid, left column
    public static final double k_LeftGrid_LeftColumn = 33.0;
    //Left grid, center column
    public static final double k_LeftGrid_CenterColumn = 57.0;
    //Left grid, right column
    public static final double k_LeftGrid_RightColumn = 81.0;
    //Right grid, left column
    public static final double k_RightGrid_LeftColumn = 255.0;
    //Right grid, center column
    public static final double k_RightGrid_CenterColumn = 279.0;
    //Right grid, right column
    public static final double k_RightGrid_RightColumn = 303.0;

    public static void setXPosition(double Xdist) {
        HW.sonarControllerLeft.setDistance(Xdist);
        HW.sonarControllerLeft.enable();
    }

    public static void setPositionFromGrid(double dist) {
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
        }
    }
}

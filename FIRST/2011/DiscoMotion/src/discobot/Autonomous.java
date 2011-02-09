package discobot;

import Utils.*;
import com.sun.squawk.util.MathUtils;
import DriveControllers.*;
/**
 * @author Nelson
 */
public class Autonomous {

    public static final double k_frontDist = 24.0;
    public static final double k_leftDist = 120.0;

    private static double x;
    private static double y;

    public static void periodic() {
        x = HW.sonarControllerLeft.getSpeed();
        y = (HW.sonarControllerFrontLeft.getSpeed() + HW.sonarControllerFrontRight.getSpeed())/2;
        HW.drive.holonomicDrive(getMagnitude(), getDirection(), getRotation());
    }

    public static void driveToWall() {
        HW.sonarControllerLeft.setDistance(k_leftDist);
        HW.sonarControllerFrontRight.setDistance(k_frontDist);
        HW.sonarControllerFrontLeft.setDistance(k_frontDist);
    }

    public static double getDirection() {
        return MathUtils.atan2(y, x);
    }

    public static double getMagnitude() {
        return Math.sqrt(x*x + y*y);
    }

    public static double getRotation() {
        //TODO: change drive class first to use a PIDController for orientation
        return 0.0;
    }
}

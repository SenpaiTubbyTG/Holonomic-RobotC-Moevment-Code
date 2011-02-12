package discobot;

import Utils.*;
import com.sun.squawk.util.MathUtils;
import DriveControllers.*;

/**
 * @author Nelson
 */
public class Autonomous {

    public static final double k_frontDist = 54.0;
    public static final double k_leftDist = 137.16;
    private static double x;
    private static double yl;
    private static double yr;

    public static void periodic() {
        x = HW.sonarControllerLeft.getSpeed();
        HW.turnController.setSetpoint(0.0);

        HW.drive.HolonomicDrive(x, 0.0, HW.turnController.getRotation());

        DiscoUtils.debugPrintln("L  sonar: " + HW.sonarLeft.getRangeCM());
        DiscoUtils.debugPrintln("gyro: " + HW.gyro.getAngle());

        /*yl = HW.sonarControllerFrontLeft.getSpeed();
        //yr = HW.sonarControllerFrontRight.getSpeed();
        HW.drive.setNormalizeMotorSpeeds(yl + x, yr - x, yr + x, yl - x);*/
        //y = (HW.sonarControllerFrontLeft.getSpeed() + HW.sonarControllerFrontRight.getSpeed())/2;
        //HW.drive.holonomicDrive(x, y, );
    }

    public static void driveToWall() {
        HW.sonarControllerLeft.setDistance(k_leftDist);
        HW.sonarControllerFrontRight.setDistance(k_frontDist);
        HW.sonarControllerFrontLeft.setDistance(k_frontDist);
    }
}

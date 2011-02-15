package discobot;

import Utils.*;
import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson
 */
public class Autonomous {

    public static final double k_maxError = 1.0;
    private static double x;
    private static double y;
    //private static int i = 0;

    public static void periodic() {
        if(HW.sonarControllerLeft.getError() > k_maxError) {
            x = HW.sonarControllerLeft.getSpeed();
        } else {
            x = 0;
        }

        if(HW.sonarControllerFrontLeft.getError() > k_maxError) {
            y = HW.sonarControllerFrontLeft.getSpeed();
        } else {
            y = 0;
        }
        HW.drive.HolonomicDrive(x, y, HW.turnController.getRotation());
    }
}

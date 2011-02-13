package discobot;

import Utils.*;
import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson
 */
public class Autonomous {

    private static double x;
    private static double yl;
    private static double yr;
    private static int i = 0;

    public static void periodic() {
        x = HW.sonarControllerLeft.getSpeed();
        HW.drive.HolonomicDrive(x, 0.0, HW.turnController.getRotation());
        if (i > 50) {
            DiscoUtils.debugPrintln("L sonar: " + HW.sonarLeft.pidGet());
            DiscoUtils.debugPrintln("x: " + x);
            i = 0;
        } else {
            i++;
        }

        if(Math.abs(HW.sonarControllerLeft.getError()) < 2.0) {
            Timer.delay(5.0);
            HW.turnController.turnToOrientation(180.0);
        }

        /*yl = HW.sonarControllerFrontLeft.getSpeed();
        //yr = HW.sonarControllerFrontRight.getSpeed();
        HW.drive.setNormalizeMotorSpeeds(yl + x, yr - x, yr + x, yl - x);*/
        //y = (HW.sonarControllerFrontLeft.getSpeed() + HW.sonarControllerFrontRight.getSpeed())/2;
    }
}

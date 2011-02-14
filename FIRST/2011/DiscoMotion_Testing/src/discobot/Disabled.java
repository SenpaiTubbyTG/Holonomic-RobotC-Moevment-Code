package discobot;

import edu.wpi.first.wpilibj.*;
import Utils.*;

/**
 *
 * @author Nelson Chen
 */
public class Disabled {

    private static int i = 0;

    public static void periodic() {
    }

    public static void continuous() {
        if (i > 100) {
            /*DiscoUtils.debugPrintln("X accel: )" + HW.accelerometer.getAccelerations().XAxis);
            DiscoUtils.debugPrintln("Y accel: )" + HW.accelerometer.getAccelerations().YAxis);
            */
            i = 0;
        } else {
            i++;
        }

        //HW.accelerometer.calculateIntialAccel();

    }
}

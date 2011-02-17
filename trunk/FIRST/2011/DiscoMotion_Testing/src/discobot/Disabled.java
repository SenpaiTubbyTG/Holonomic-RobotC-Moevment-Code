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
        if (i > 10000) {
            i = 0;
        } else {
            i++;
        }
    }
}

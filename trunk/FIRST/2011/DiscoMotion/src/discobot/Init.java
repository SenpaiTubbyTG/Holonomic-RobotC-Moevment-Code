/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package discobot;

import edu.wpi.first.wpilibj.*;
import Utils.*;

/**
 *
 * @author Nelson
 */
public class Init {

    public static void robotInit() {
    }

    public static void disabledInit() {
        DataLogger.dataLogger.disable();
        DataLogger.dataLogger.writeData();
    }

    public static void autonomousInit() {
        HW.sonarControllerLeft.enable();
        HW.sonarControllerFrontLeft.enable();
        HW.sonarControllerFrontRight.enable();
    }

    public static void teleopInit() {
        String[] header = {""};
        DataLogger.dataLogger.setHeader(header);
        DataLogger.dataLogger.setTimeOffset(Timer.getFPGATimestamp());
        DataLogger.dataLogger.enable();
    }
}

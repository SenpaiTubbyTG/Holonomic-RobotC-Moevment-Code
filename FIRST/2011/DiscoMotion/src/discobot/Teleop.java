package discobot;

import Utils.*;
import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Nelson Chen
 */
public class Teleop {

    static final double k_armSpeed = 0.3;
    static boolean enabled = false;
    static double currentX = 0.0;
    static double currentY = 0.0;
    static double offset = 0.0;
    static double currentTime;
    static boolean[] driveStickLeftButtons = new boolean[12];
    static double[] lastPressed = new double[12];

    public static void periodic() {
        updateButtons();

        if (driveStickLeftButtons[2] || driveStickLeftButtons[3] || driveStickLeftButtons[4] || driveStickLeftButtons[5]) {
            enabled = true;
            if (driveStickLeftButtons[2]) {
                currentY = -0.5;
                currentX = 0.0;
            } else if (driveStickLeftButtons[3]) {
                currentY = 0.5;
                currentX = 0.0;
            } else if (driveStickLeftButtons[4]) {
                currentY = 0.0;
                currentX = -0.5;
            } else if (driveStickLeftButtons[5]) {
                currentY = 0.0;
                currentX = 0.5;
            }
        } else {
            enabled = false;
        }

        if (HW.driveStickRight.getRawButton(3)) { //arm up
            HW.arm.set(-k_armSpeed);
        } else if (HW.driveStickRight.getRawButton(2)) { // arm down
            HW.arm.set(k_armSpeed);
        } else {
            HW.arm.set(0.0);
        }

        HW.collector.set(HW.driveStickRight.getY());
        HW.lift.set(-HW.liftHandle.getY());

        if ((currentTime - lastPressed[8]) > 0.25 && driveStickLeftButtons[8]) {
            offset -= 0.1;
            lastPressed[8] = currentTime;
            DiscoUtils.debugPrintln("Offset decreased to: " + offset);
        } else if ((currentTime - lastPressed[9]) > 0.25 && driveStickLeftButtons[9]) {
            offset += 0.1;
            lastPressed[9] = currentTime;
            DiscoUtils.debugPrintln("Offset increased to: " + offset);
        }

        if (enabled) {
            HW.drive.HolonomicDrive(currentX, currentY, 0.0, offset);
        } else {
            HW.drive.HolonomicDrive(0.0, 0.0, 0.0, 0.0);
        }

    }

    public static void continuous() {
    }

    private static void updateButtons() {
        for (int b = 1; b < 12; b++) {
            driveStickLeftButtons[b] = HW.driveStickLeft.getRawButton(b);
        }
        currentTime = Timer.getFPGATimestamp();
    }
}

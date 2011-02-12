package discobot;

import Utils.*;
import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Nelson Chen
 */
public class Teleop {

    static boolean enabled = false;
    static final double k_armSpeed = 0.3;
    static double currentX = 0.0;
    static double currentY = 0.0;
    static double offset = 0.0;
    static double currentTime;
    static boolean[] driveStickLeftButtons = new boolean[12];
    static boolean[] driveStickRightButtons = new boolean[12];
    static boolean[] liftHandleButtons = new boolean[12];
    static double[] lastPressed = new double[12];
    static int i = 0;

    //static double[] encoder = new double[4];

    public static void periodic() {
        /*encoder[0] = HW.encoderFrontLeft.getDistance();
        encoder[1] = HW.encoderFrontRight.getDistance();
        encoder[2] = HW.encoderRearRight.getDistance();
        encoder[3] = HW.encoderRearLeft.getDistance();
        DataLogger.dataLogger.setEntryValue(encoder);*/
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

        if (enabled) {
            HW.drive.HolonomicDrive(currentX, currentY, HW.driveStickRight.getX(), offset);
        } else {
            HW.drive.HolonomicDrive(HW.driveStickLeft.getX(),
                                HW.driveStickLeft.getY(),
                                HW.driveStickRight.getX());
        }

        if (HW.driveStickRight.getRawButton(3)) { //arm up
            HW.armMotor.set(-k_armSpeed);
        } else if (HW.driveStickRight.getRawButton(2)) { // arm down
            HW.armMotor.set(k_armSpeed);
        } else {
            HW.armMotor.set(0.0);
        }

        HW.lift.set(-HW.liftHandle.getY());
        //HW.collector.periodic(liftHandleButtons);
        //HW.arm.periodic(liftHandleButtons);s
        if(liftHandleButtons[2]) {
            HW.collectorMotor.set(0.5);
        }
        else if(liftHandleButtons[3]) {
            HW.collectorMotor.set(-0.5);
        }

        /*if ((currentTime - lastPressed[8]) > 0.25 && driveStickLeftButtons[8]) {
            offset -= 0.1;
            lastPressed[8] = currentTime;
            DiscoUtils.debugPrintln("Offset decreased to: " + offset);
        } else if ((currentTime - lastPressed[9]) > 0.25 && driveStickLeftButtons[9]) {
            offset += 0.1;
            lastPressed[9] = currentTime;
            DiscoUtils.debugPrintln("Offset increased to: " + offset);
        }*/

        if (i > 10) {
            DiscoUtils.debugPrintln("Gyro: " + HW.gyro.getAngle());
            DiscoUtils.debugPrintln("L  sonar: " + HW.sonarLeft.getRangeCM());
            //DiscoUtils.debugPrintln("FL sonar: " + HW.sonarFrontLeft.getRangeInches());
            //DiscoUtils.debugPrintln("FR sonar: " + HW.sonarFrontRight.getRangeInches());
            i = 0;
        } else {
            i++;
        }

    }

    public static void continuous() {
    }

    private static void updateButtons() {
        for (int b = 1; b < 12; b++) {
            driveStickLeftButtons[b] = HW.driveStickLeft.getRawButton(b);
        }
        for (int b = 1; b < 12; b++) {
            liftHandleButtons[b] = HW.liftHandle.getRawButton(b);
        }
        currentTime = Timer.getFPGATimestamp();
    }
}

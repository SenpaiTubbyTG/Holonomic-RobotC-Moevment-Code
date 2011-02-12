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

        //Drive Code
        //Button Drive
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

        if (HW.driveStickLeft.getRawButton(11)) {
            HW.turnController.reset(0);
        } else if (HW.driveStickLeft.getRawButton(10)) {
            HW.turnController.reset(90);
        } else if (HW.driveStickLeft.getRawButton(7)) {
            HW.turnController.reset(180);
        } else if (HW.driveStickLeft.getRawButton(6)) {
            HW.turnController.reset(270);
        } else if (HW.driveStickRight.getRawButton(11)) {
            HW.turnController.turnToOrientation(0);
        } else if (HW.driveStickRight.getRawButton(10)) {
            HW.turnController.turnToOrientation(90);
        } else if (HW.driveStickRight.getRawButton(7)) {
            HW.turnController.turnToOrientation(180);
        } else if (HW.driveStickRight.getRawButton(6)) {
            HW.turnController.turnToOrientation(270);
        } else {
            HW.turnController.incrementSetpoint(HW.driveStickRight.getX());
        }


        //Joystick Drive
        if (enabled) {
            HW.drive.HolonomicDrive(currentX, currentY, HW.turnController.getRotation(), offset);
        } else {
            double out[] = rotateVector(HW.driveStickLeft.getX(),HW.driveStickLeft.getY(), -1 * HW.gyro.getAngle());
            HW.drive.HolonomicDrive(out[0], out[1], HW.turnController.getRotation());
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
        if (liftHandleButtons[2]) {
            HW.collectorMotor.set(0.5);
        } else if (liftHandleButtons[3]) {
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
            //DiscoUtils.debugPrintln("Gyro: " + HW.gyro.getAngle());
            //DiscoUtils.debugPrintln("L  sonar: " + HW.sonarLeft.getRangeCM());
            //DiscoUtils.debugPrintln("FL sonar: " + HW.sonarFrontLeft.getRangeInches());
            //DiscoUtils.debugPrintln("FR sonar: " + HW.sonarFrontRight.getRangeInches());
            DiscoUtils.debugPrintln("Angle Setpoint: " + HW.turnController.getSetpoint());
            i = 0;
        } else {
            i++;
        }

    }

    public static void continuous() {
    }
    /**
     * Rotate a vector in Cartesian space.
     */
    protected static double[] rotateVector(double x, double y, double angle) {
        double cosA = Math.cos(angle * (3.14159 / 180.0));
        double sinA = Math.sin(angle * (3.14159 / 180.0));
        double out[] = new double[2];
        out[0] = x * cosA - y * sinA;
        out[1] = x * sinA + y * cosA;
        return out;
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

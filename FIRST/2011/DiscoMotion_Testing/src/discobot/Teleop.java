package discobot;

import Utils.*;

/**
 *
 * @author Nelson Chen
 */
public class Teleop {

    public static final int k_collectorInButton = 2;//on lift joystick
    public static final int k_collectorOutButton = 3;//on lift joystick
    private static final int k_collectButton = 1; //on left-hand driver joystick
    private static final int k_armDownButton = 7;//on lift joystick
    static final double k_rotationDeadZone = 0.1;
    static final double k_driveRotationThreshold = 0.5;
    static final double k_gyroRotationThreshold = 1.0;
    static boolean sonarControlEnabled = false;
    static boolean fieldCentricEnabled = true;
    static double currentX = 0.0;
    static double currentY = 0.0;
    static double oldAngle = 0.0;
    static double liftSpeed = 0.0;
    static double rotation;
    static int i = 0;
    static boolean[] leftButtons = new boolean[12];
    static boolean[] rightButtons = new boolean[12];
    static boolean[] liftButtons = new boolean[12];

    public static void periodic() {
        updateButtons();
        drive();
        lift();
    }

    public static void drive() {
        //Turn Controller Reset and Orientation
        if (leftButtons[11]) {
            HW.turnController.reset(0);
        } else if (leftButtons[10]) {
            HW.turnController.reset(90);
        } else if (leftButtons[7]) {
            HW.turnController.reset(180);
        } else if (leftButtons[6]) {
            HW.turnController.reset(270);
        } else if (rightButtons[3]) {
            HW.turnController.turnToOrientation(0);
        } else if (rightButtons[5]) {
            HW.turnController.turnToOrientation(90);
        } else if (rightButtons[2]) {
            HW.turnController.turnToOrientation(180);
        } else if (rightButtons[4]) {
            HW.turnController.turnToOrientation(270);
        } else {
            if (Math.abs(HW.driveStickRight.getX()) < k_rotationDeadZone) {
                HW.turnController.setSetpoint(HW.gyro.getAngle());
            } else {
                HW.turnController.incrementSetpoint(HW.driveStickRight.getX());
            }
        }

        //Field-centric "HALO" control
        rotation = HW.turnController.getRotation();
        double out[] = rotateVector(HW.driveStickLeft.getX(), HW.driveStickLeft.getY(), -1 * HW.gyro.getAngle());
        if (leftButtons[5]) {
            HW.sonarControllerFrontLeft.enable();
            currentY = HW.sonarControllerFrontLeft.getSpeed();
            if (HW.sonarFrontLeft.getRangeInches() < 70) {
                HW.sonarControllerLeft.enable();
                currentX = HW.sonarControllerLeft.getSpeed();
            } else {
                currentX = 0;
            }
            HW.drive.HolonomicDrive(currentX, currentY, rotation);
            DiscoUtils.debugPrintln("Sonar Positioning Active");

        } else {
            HW.drive.HolonomicDrive(out[0], out[1], rotation);
        }
    }

    public static void lift() {
        //Lift control
        liftSpeed = -HW.liftHandle.getY();
        if (liftSpeed > 0 && !HW.liftLimitInnerUp.get() && !HW.liftLimitMiddleUp.get()) {
            HW.lift.set(0.0);
        } else if ((liftSpeed < 0 && !HW.liftLimitInnerDown.get() && !HW.liftLimitMiddleDown.get())) {
            HW.lift.set(0.0);
        } else {
            HW.lift.set(liftSpeed);
        }

        //Arm control for driver and lift operator
        //arm raises automatically unless ordered downards
        if (leftButtons[k_collectButton]) {
            HW.arm.collect();
        } else if (liftButtons[k_armDownButton]) {
            HW.arm.down();
        } else {
            HW.arm.up();
        }

        //Manual Collector control by lift operator
        if (liftButtons[k_collectorInButton]) {
            HW.arm.tubeIn();
        } else if (liftButtons[k_collectorOutButton]) {
            HW.arm.tubeOut();
        }
    }

    public static void continuous() {
        //verifyGyro(HW.gyro.getAngle());
        if (i > 10000) {
            //DataLogger.dataLogger.setEntryValue(INSERT ARRAY HERE);
            //DiscoUtils.debugPrintln("\nLift INNER-UP switch: " + HW.liftLimitInnerUp.get());
            i = 0;
        } else {
            i++;
        }
    }

    /**
     * Rotate a vector tubeIn Cartesian space.
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
        for (int b = 1; b
                < 12; b++) {
            leftButtons[b] = HW.driveStickLeft.getRawButton(b);
            rightButtons[b] = HW.driveStickRight.getRawButton(b);
            liftButtons[b] = HW.liftHandle.getRawButton(b);
        }
    }

    public static void verifyGyro(double currentAngle) {
        double angleChange = currentAngle - oldAngle;
        if (Math.abs(rotation) > k_driveRotationThreshold
                && Math.abs(angleChange) < k_gyroRotationThreshold) {
            fieldCentricEnabled = false;
        } else {
            fieldCentricEnabled = true;
        }
        oldAngle = currentAngle;
    }
}

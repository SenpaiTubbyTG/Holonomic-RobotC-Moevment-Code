package discobot;

import Utils.*;
import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson Chen
 */
public class Teleop {

    static final double k_scoringDistance = 30.0;
    private static final int k_collectButton = 1; //on left-hand driver joystick
    public static final int k_collectorInButton = 2;//on liftMotor joystick
    public static final int k_collectorOutButton = 3;//on liftMotor joystick
    private static final int k_armDownButton = 1;//on liftMotor joystick
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
    static double startTime = 0.0;
    static boolean raisingArm = false;
    static int i = 0;
    static boolean[] leftButtons = new boolean[12];
    static boolean[] rightButtons = new boolean[12];
    static boolean[] liftButtons = new boolean[12];

    public static void init() {
        initPIDs();
        initEncoders();
        HW.arm.updateArmSpeed();
        Teleop.startTime = Timer.getFPGATimestamp();
        HW.lift.downToSwitch();
        DiscoUtils.debugPrintln("TELEOP INIT COMPLETE");
    }

    public static void disablePIDs() {
        HW.turnController.disable();
        HW.sonarControllerLeft.disable();
        HW.sonarControllerFrontLeft.disable();

        DiscoUtils.debugPrintln("PIDS DISABLED");
    }

    public static void periodic() {
        //setControlModes();
        updateButtons();
        limitDrive();
        drive();
        lift();

        /*if(leftButtons[1]) {// && (Timer.getFPGATimestamp() - startTime) > 110) {
        //deploy minibot here... I hope
        }*/
        /*if (leftButtons[8]) {
        HW.turnController.disable();
        } else if (leftButtons[9]) {
        HW.turnController.enable();
        }*/
    }

    public static void continuous() {
        //verifyGyro(HW.gyro.getAngle());
        Disabled.continuous();
    }

    //Used for making switches that will disable control loops
    public static void setControlModes(){
        boolean liftOpenLoop = false;
        if (liftOpenLoop){
            HW.lift.disablePIDControl();
        } else {
            HW.lift.enablePIDControl();
        }

        boolean driveOpenLoop = false;
        if (driveOpenLoop){
            HW.turnController.disable();
        } else {
            HW.turnController.reset(0.0);
        }
    }

    public static void limitDrive(){
        if (HW.lift.getPosition() > HW.lift.kLiftM1){
            //HW.turnController.setOutputRange(-.5, .5);
            HW.drive.setMaxOutput(.75);
        } else {
            //HW.turnController.setDefaultOutputRange();
            HW.drive.setMaxOutput(1);
        }
    }
    public static void drive() {
        //Turn Controller Reset and Orientation
        if (leftButtons[3]) {
            HW.turnController.reset(0);
        } else if (leftButtons[5]) {
            HW.turnController.reset(90);
        } else if (leftButtons[2]) {
            HW.turnController.reset(180);
        } else if (leftButtons[4]) {
            HW.turnController.reset(270);
        } else if (rightButtons[3]) {
            HW.turnController.turnToOrientation(0);
        } else if (rightButtons[5]) {
            HW.turnController.turnToOrientation(90);
        } else if (rightButtons[2]) {
            HW.turnController.turnToOrientation(180);
        } else if (rightButtons[4]) {
            HW.turnController.turnToOrientation(270);
        }
        HW.turnController.incrementSetpoint(HW.driveStickRight.getX());

        //Field-centric "HALO" control
        HW.turnController.enable();
        rotation = HW.turnController.getRotation();
        double out[] = rotateVector(HW.driveStickLeft.getX(), HW.driveStickLeft.getY(), -1 * HW.gyro.getAngle());
        if (leftButtons[9]) {
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
            //DiscoUtils.debugPrintln("out[0]: " + out[0] + "\tout[1]: " + out[1] + "\trotation: " + rotation);
            HW.drive.HolonomicDrive(out[0], out[1], rotation);
        }
    }

    public static void lift() {
        //Lift control
        if (liftButtons[6]) {
            HW.lift.setSetpoint(HW.lift.kLiftH2);
        } else if (liftButtons[7]) {
            HW.lift.setSetpoint(HW.lift.kLiftM2);
        } else if (liftButtons[8]) {
            HW.lift.setSetpoint(HW.lift.kLiftD);
        } else if (liftButtons[2]) {
            HW.lift.setSetpoint(HW.lift.getPosition() - 10);
        } /*else if(liftButtons[9]) {
        HW.lift.downToSwitchPeriodic();
        }*/
        if (Math.abs(HW.liftHandle.getY()) > 0.15) {
            HW.lift.setLiftSpeed(-HW.liftHandle.getY());
        }


        //Arm control for driver and liftMotor operator
        //arm raises automatically unless ordered downards
        HW.arm.updateArmSpeed();
        if (leftButtons[k_collectButton]) { //driver collect overrides liftMotor operator
            HW.arm.collect();
            raisingArm = true;
        } else {
            if (liftButtons[k_armDownButton]) {
                HW.arm.down();
                //Manual Collector control by liftMotor operator
                if (liftButtons[k_collectorInButton]) {
                    HW.arm.tubeIn();
                } else if (liftButtons[k_collectorOutButton]) {
                    HW.arm.tubeOut();
                } else {
                    HW.arm.stopCollector();
                }
            } else {
                HW.arm.up();
                //Manual Collector control by liftMotor operator
                if (liftButtons[k_collectorInButton] || raisingArm) {
                    if (!raisingArm) {
                        HW.arm.tubeIn();
                    } else {
                        HW.arm.tubeIn();
                        HW.arm.up();
                    }
                } else if (liftButtons[k_collectorOutButton]) {
                    HW.arm.tubeOut();
                } else {
                    HW.arm.stopCollector();
                    if (raisingArm) {
                        HW.arm.tubeIn();
                        HW.arm.up();
                    }
                }
            }
        }
        if (raisingArm && HW.arm.isUp()) {
            raisingArm = false;
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
        for (int b = 1; b < 12; b++) {
            leftButtons[b] = HW.driveStickLeft.getRawButton(b);
            rightButtons[b] = HW.driveStickRight.getRawButton(b);
            liftButtons[b] = HW.liftHandle.getRawButton(b);
        }
    }

    public static void initPIDs() {
        HW.turnController.reset(0);//also enables
        HW.sonarControllerLeft.setOutputRange(-0.5, 0.5);
        HW.sonarControllerLeft.enable();
        HW.sonarControllerFrontLeft.setDistance(k_scoringDistance);
        HW.sonarControllerFrontRight.setDistance(k_scoringDistance);
        HW.sonarControllerFrontLeft.setOutputRange(-0.5, 0.5);
        HW.sonarControllerFrontRight.setOutputRange(-0.5, 0.5);
        HW.sonarControllerFrontLeft.enable();
        HW.sonarControllerFrontRight.enable();
        HW.lift.enablePIDControl();
        HW.lift.setSetpoint(HW.lift.kLiftD);
        PIDTuner.setPIDs();
        DiscoUtils.debugPrintln("PIDS ENABLED");
        DiscoUtils.debugPrintln("L  PIDs: P=" + HW.sonarControllerLeft.getP() + "\tD=" + HW.sonarControllerLeft.getD());
        DiscoUtils.debugPrintln("FL PIDs: P=" + HW.sonarControllerFrontLeft.getP() + "\tD=" + HW.sonarControllerFrontLeft.getD());
        DiscoUtils.debugPrintln("lift PIDs: P=" + HW.lift.getP() + "\tD=" + HW.lift.getD());
        DiscoUtils.debugPrintln("turnC PIDs: P=" + HW.turnController.getP() + "\tD=" + HW.turnController.getD());
        HW.sonarControllerFrontLeft.setOutputRange(-0.4, 0.4);
        HW.sonarControllerLeft.setOutputRange(-0.4, 0.4);
    }

    public static void initEncoders() {
        HW.encoderFrontLeft.setCodesPerRev(HW.FrontLeftEncoderTicks);
        HW.encoderFrontRight.setCodesPerRev(HW.FrontRightEncoderTicks);
        HW.encoderRearRight.setCodesPerRev(HW.RearRightEncoderTicks);
        HW.encoderRearLeft.setCodesPerRev(HW.RearLeftEncoderTicks);
        HW.encoderFrontLeft.init();
        HW.encoderFrontRight.init();
        HW.encoderRearRight.init();
        HW.encoderRearLeft.init();
        HW.liftEncoder.init();
    }

    /* UNTESTED
     public static void verifyGyro(double currentAngle) {
        double angleChange = currentAngle - oldAngle;
        if (Math.abs(rotation) > k_driveRotationThreshold
                && Math.abs(angleChange) < k_gyroRotationThreshold) {
            fieldCentricEnabled = false;
        } else {
            fieldCentricEnabled = true;
        }
        oldAngle = currentAngle;
    }*/
}

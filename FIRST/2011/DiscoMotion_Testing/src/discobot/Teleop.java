package discobot;

import Utils.*;
import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson Chen
 */
public class Teleop {

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

    public static void periodic() {
        setControlModes();
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
            HW.turnController.setOutputRange(-.5, .5);
            HW.drive.setMaxOutput(.75);
        } else {
            HW.turnController.setDefaultOutputRange();
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

        } else if(leftButtons[7]){
            HW.drive.setMotorSpeeds(1, 1, 1, 1);
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

    public static void continuous() {
        //verifyGyro(HW.gyro.getAngle());
        debugPrint();
    }

    public static void debugPrint() {
        if (i > 1000) {
            Disabled.debugLift();
            DiscoUtils.debugPrintln("Lift HANDLE: " + HW.liftHandle.getY());
            
            DiscoUtils.debugPrintln("Drive Left: " + HW.driveStickLeft.getY());
            /*DiscoUtils.debugPrintln("arm DOWN speed: " + HW.arm.k_armDownSpeed);
            DiscoUtils.debugPrintln("arm  UP  speed: " + HW.arm.k_armUpSpeed);*/
            //DiscoUtils.debugPrintln("Lift Error: " + HW.lift.getError());
            //DiscoUtils.debugPrintln("\nLift Speed: " + HW.lift.getLiftSpeed());
            //DiscoUtils.debugPrintln("\nLift Motor: " + HW.liftMotor.get());
            //DiscoUtils.debugPrintln("Arm Motor: " + HW.armMotor.get());
            //DiscoUtils.debugPrintln("FL: " + HW.DMFrontLeft.get());
            //DiscoUtils.debugPrintln("FR: " + HW.DMFrontRight.get());
            //DiscoUtils.debugPrintln("RR: " + HW.DMRearRight.get());
            //DiscoUtils.debugPrintln("RL: " + HW.DMRearLeft.get());
            //DiscoUtils.debugPrintln("Lift Set Point: " + HW.lift.getSetpoint());
            //DiscoUtils.debugPrintln("Lift Position: " + HW.lift.pidGet());
            //DiscoUtils.debugPrintln("Lift Inner Down: " + HW.liftLimitInnerDown.get());
            //DiscoUtils.debugPrintln("Lift Middle Down: " + HW.liftLimitMiddleDown.get());
            //DiscoUtils.debugPrintln("isLiftDown: " + HW.lift.isLiftDown());
            //DiscoUtils.debugPrintln("Lift Middle Up: " + HW.liftLimitMiddleUp.get());
            //DiscoUtils.debugPrintln("Lift Inner Up: " + HW.liftLimitInnerUp.get());
            /*DiscoUtils.debugPrintln("FR: " + HW.encoderFrontRight.getRate());
            DiscoUtils.debugPrintln("RR: " + HW.encoderRearRight.getRate());
            DiscoUtils.debugPrintln("RL: " + HW.encoderRearLeft.getRate());*/
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
        for (int b = 1; b < 12; b++) {
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

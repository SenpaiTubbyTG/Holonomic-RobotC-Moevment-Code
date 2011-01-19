package Breakaway;

import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.*;
import com.sun.squawk.util.MathUtils;

/** -------------------------------------------------------
 * @class DiscoDrive
 * @purpose  Utility class for handling Robot drive based on
 * a definition of the motor configuration. The disco
 * drive class handles basic driving for a robot.
 * This is a 6 wheel holonomic drive setup. With a normal standard 4 wheel drive
 * and two wheels place perpendicular between each set of the front and rear drive wheels
 * In this diagram
 * The Front Wheel fwd = left
 * The Right Wheel fwd = up
 * The Rear Wheel fwd = right
 * The Left Wheel fwd = down
0---<>---0
|        |
|        |
0---<>---0
@author Allen Gregory
@written Jan 22,2010
------------------------------------------------------- */
public class DiscoDrive {

    private SpeedController rearMotor;
    private double leftSpeed;
    private SpeedController frontMotor;
    private double rightSpeed;
    private SpeedController leftMotor;
    private double frontSpeed;
    private SpeedController rightMotor;
    private double rearSpeed;
    /**
     * kLeftMotor - used by invert motors to tell it what motor to invert
     */
    public static final int kLeftMotor = 1;
    /**
     * kFrontMotor - used by invert motors to tell it what motor to invert
     */
    public static final int kFrontMotor = 2;
    /**
     * kRightMotor - used by invert motors to tell it what motor to invert
     */
    public static final int kRightMotor = 3;
    /**
     * kReftMotor - used by invert motors to tell it what motor to invert
     */
    public static final int kRearMotor = 4;
    private int[] invertedMotors = {1, 1, 1, 1, 1};
    //Gyro Variables
    private boolean isGyro;
    private Gyro discoGyro;
    private AnalogChannel rawDiscoGyro;
    private PIDController turnController;

    /** -------------------------------------------------------
    @method DiscoDrive Constructor
    @param leftMotor - The left SpeedController object used to drive the robot.
    @param rightMotor - The right SpeedController object used to drive the robot.
    @param frontMotor - The front center SpeedController object used to drive the robot.
    @param rearMotor -The rear center SpeedController object used to drive the robot.
    @purpose constructor - used if 4 motors used in this drive configuration and there is not a gyro
    @author Allen Gregory
    @written Jan 25, 2010
    ------------------------------------------------------- */
    public DiscoDrive(final int leftMotor,
            final int rightMotor,
            final int frontMotor,
            final int rearMotor) {

        this.rearMotor = new Jaguar(rearMotor);
        this.frontMotor = new Jaguar(frontMotor);
        this.leftMotor = new Jaguar(rightMotor);
        this.rightMotor = new Jaguar(leftMotor);

        isGyro = false;
        initiateTurnController();

    }

    /** -------------------------------------------------------
    @method DiscoDrive Constructor
    @param leftMotor - The left SpeedController object used to drive the robot.
    @param rightMotor - The right SpeedController object used to drive the robot.
    @param frontMotor - The front center SpeedController object used to drive the robot.
    @param rearMotor -The rear center SpeedController object used to drive the robot.
    @purpose constructor - used if there 4 motors used in this drive configuration and there is not a gyro present
    @author Allen Gregory
    @written Jan 22, 2010
    ------------------------------------------------------- */
    public DiscoDrive(SpeedController leftMotor,
            SpeedController rightMotor,
            SpeedController frontMotor,
            SpeedController rearMotor) {

        this.rearMotor = leftMotor;
        this.frontMotor = rightMotor;
        this.leftMotor = frontMotor;
        this.rightMotor = rearMotor;

        isGyro = false;
        initiateTurnController();
    }

    /** -------------------------------------------------------
    @method DiscoDrive Constructor
    @param leftMotor - The left SpeedController object used to drive the robot.
    @param rightMotor - The right SpeedController object used to drive the robot.
    @param frontMotor - The front center SpeedController object used to drive the robot.
    @param rearMotor -The rear center SpeedController object used to drive the robot.
    @param gyro - the gyro object to use for DiscoDrive
    @param rawGyro - the analog channel of the gyro, used to the raw rate information
    @purpose constructor - used if there are only 4 motors used in this drive configuration
    @author Allen Gregory
    @written Jan 22, 2010
    ------------------------------------------------------- */
    public DiscoDrive(SpeedController leftMotor,
            SpeedController rightMotor,
            SpeedController frontMotor,
            SpeedController rearMotor,
            Gyro gyro,
            AnalogChannel rawGyro) {

        this.rearMotor = leftMotor;
        this.frontMotor = rightMotor;
        this.leftMotor = frontMotor;
        this.rightMotor = rearMotor;

        isGyro = true;
        discoGyro = gyro;
        rawDiscoGyro = rawGyro;
        initiateTurnController();
    }

    /** -------------------------------------------------------
    @method DiscoDrive Constructor
    @param leftMotor - The left SpeedController object used to drive the robot.
    @param rightMotor - The right SpeedController object used to drive the robot.
    @param frontMotor - The front center SpeedController object used to drive the robot.
    @param rearMotor -The rear center SpeedController object used to drive the robot.
    @param gyro - the gyro object to use for DiscoDrive
    @param rawGyro - the analog channel of the gyro so that we can use the rate if need by
    @purpose constructor - used if there are only 4 motors used in this drive configuration
    @author Allen Gregory
    @written Jan 22, 2010
    ------------------------------------------------------- */
    public DiscoDrive(final int leftMotor,
            final int rightMotor,
            final int frontMotor,
            final int rearMotor,
            Gyro gyro,
            AnalogChannel rawGyro) {

        this.rearMotor = new Jaguar(leftMotor);
        this.frontMotor = new Jaguar(rightMotor);
        this.leftMotor = new Jaguar(frontMotor);
        this.rightMotor = new Jaguar(rearMotor);

        isGyro = true;
        discoGyro = gyro;
        rawDiscoGyro = rawGyro;
        initiateTurnController();

    }

    /**
     * initiateTurnController initiates the PID turncontroller for the DiscoDrive when it is using the gyro to drive
     */
    public void initiateTurnController() {
        discoGyro.setSensitivity(.007);
        turnController = new PIDController(.08, 0.0, 0.5, discoGyro, new PIDOutput() {

            public void pidWrite(double output) {
                addRotation(output);
            }
        }, .005);
        turnController.setInputRange(-360.0, 360.0);
        turnController.setTolerance(1 / 90. * 100);
        turnController.disable();
    }

    /**
     * basicDrive the motors all with a different values of a joystick.
     *
     * The Left Motor is controlled by speed1
     * The Right Motor is constrolled by speed2
     * The Front Motor is controlled by speed3
     * The Rear Motor is controlled by speed4
     *
     * @param leftSpeedTemp - the speed to set the left motor to
     * @param rightSpeedTemp - the speed to set the right motor to
     * @param frontSpeedTemp - the speed to set the front motor to
     * @param rearSpeedTemp - the speed to set the rear motor to
     */
    public void basicDrive(double leftSpeedTemp, double rightSpeedTemp,
            double frontSpeedTemp, double rearSpeedTemp) {

        /*DiscoUtils.debugPrintln("Basic Drive Calculated Values");
        DiscoUtils.debugPrintln("Magnatude: " + getMagnitude()
                + " Direction: " + getDirection()
                + " Spin: " + getSpin());*/

        leftSpeed = DiscoUtils.limit(leftSpeedTemp * invertedMotors[1]);
        rightSpeed = DiscoUtils.limit(rightSpeedTemp * invertedMotors[2]);
        frontSpeed = DiscoUtils.limit(frontSpeedTemp * invertedMotors[3]);
        rearSpeed = DiscoUtils.limit(rearSpeedTemp * invertedMotors[4]);

        rearMotor.set(rearSpeed);
        frontMotor.set(frontSpeed);
        leftMotor.set(leftSpeed);
        rightMotor.set(rightSpeed);

        /*DiscoUtils.debugPrintln("Basic Drive Outputed Values");
        DiscoUtils.debugPrintln("Left: " + leftSpeed
                + " Right: " + rightSpeed
                + " Front: " + frontSpeed
                + " Rear: " + rearSpeed);
        System.out.println("Left: " + leftSpeed
                + " Right: " + rightSpeed
                + " Front: " + frontSpeed
                + " Rear: " + rearSpeed);*/
    }

    public void autonDrive(double leftSpeed, double rightSpeed,
            double frontSpeed, double rearSpeed) {

        rearMotor.set(rearSpeed);
        frontMotor.set(frontSpeed/1.5);
        leftMotor.set(leftSpeed);
        rightMotor.set(rightSpeed);

        /*DiscoUtils.debugPrintln("Basic Drive Outputed Values");
        DiscoUtils.debugPrintln("Left: " + leftSpeed
                + " Right: " + rightSpeed
                + " Front: " + frontSpeed
                + " Rear: " + rearSpeed);
        System.out.println("Left: " + leftSpeed
                + " Right: " + rightSpeed
                + " Front: " + frontSpeed
                + " Rear: " + rearSpeed);*/
    }

    /**
     * holonomicDrive the motors at "magnitude", "direction", and "rotation".
     *
     *
     * @param magnitude The speed component of the velocity to send to the motors.
     * @param direction The direction component of the velocity to send to the motors.
     * @param rotation  The rotation that you want to add to the robots movement.
     */
    public void holonomicDrive(double magnitude, double direction, double rotation) {
        //DiscoUtils.debugPrintln("Holonomic Drive Code Debug");
        //DiscoUtils.debugPrintln("magnitude = " + magnitude + ", direction = " + direction + ", rotation = " + rotation);

        double cosD = Math.cos((double) (direction) * 3.14159 / 180.0);
        double sinD = Math.cos((double) (direction - 90.0) * 3.14159 / 180.0);
        double leftSpeedTemp = DiscoUtils.limit((double) (cosD * (double) magnitude + rotation));
        double frontSpeedTemp = DiscoUtils.limit((double) (sinD * (double) magnitude + rotation));
        double rightSpeedTemp = DiscoUtils.limit((double) (cosD * (double) magnitude - rotation));
        double rearSpeedTemp = DiscoUtils.limit((double) (sinD * (double) magnitude - rotation));

        basicDrive(leftSpeedTemp, rightSpeedTemp, frontSpeedTemp, rearSpeedTemp); //Changed so that it uses the basicDrive function
    }

    /**
     * GetDirection give the direction value that the drive is currently going
     */
    /**
     * Hold the Orientation of the robot to a specific angle
     * Uses the gyro
     *
     * @param angle - the angle you wish the robot to turn towards
     */
    public void orienentOn(double angle) {
        if (isGyro) {
            turnController.setSetpoint(angle);
            turnController.enable();
        } else {
            //DiscoUtils.errorPrintln("DiscoDrive.orienentOn Error: Gyro not enbabled for DiscoDrive");
        }
    }

    /**
     * Turn off the hold orientation mode
     * Uses the gyro
     */
    public void orientOff() {
        if (isGyro) {
            turnController.disable();
        } else {
            //DiscoUtils.errorPrintln("DiscoDrive.orienentOff Error: Gyro not enbabled for DiscoDrive");
        }
    }

    /**
     * Adds a rotation to the robot as it translates
     *
     * @param speed - the speed of rotation to add to the robot.
     */
    public void addRotation(double speed) {
        basicDrive(rearMotor.get() + speed,
                frontMotor.get() + speed,
                leftMotor.get() + speed,
                rightMotor.get() + speed);
        //DiscoUtils.debugPrintln(speed + " rotation addded to the Drive");
    }

    /**
     * Invert a motor direction.
     * This is used when a motor should run in the opposite direction as the drive
     * code would normally run it. Motors that are direct drive would be inverted, the
     * Drive code assumes that the motors are geared with one reversal.
     * 1 = Left Motor
     * 2 = Right Motor
     * 3 = Front Motor
     * 4 = Rear Motor
     * @param motor The motor index to invert.
     * @param isInverted True if the motor should be inverted when operated.
     */
    public void setInvertedMotor(final int motor, final boolean isInverted) {
        if (motor >= 1 && motor <= 4) {
            invertedMotors[motor] = isInverted ? -1 : 1;
        } else {
            //DiscoUtils.errorPrintln("Invert Drive Motor Error: Motor value out of range");
        }
    }


    /**
     * getMagnitude
     * Calculate the Magnitude of the Drive Train
     */
    public double getMagnitude() {
        double x = ((((-1) * frontSpeed) + rearSpeed) / 2);
        double y = ((((-1) * leftSpeed) + rightSpeed) / 2);
        double magnatude = Math.sqrt(MathUtils.pow(y, 2)
                + MathUtils.pow(x, 2));
        //DiscoUtils.debugPrintln("getMagnatude: " + magnatude);
        return magnatude;
}

    void targetAlign() {
        orienentOn(HW.gyro.getAngle() + DiscoUtils.rawToAngle(HW.camPan.getRaw()));

    }

    /**
     * getDirection
     * calculate the direction of the Drive Train
     * Returns direction in Degrees with 0 the robot driving strait
     */
    public double getDirection() {
        double x = ((((-1) * frontSpeed) + rearSpeed) / 2);
        double y = ((((-1) * leftSpeed) + rightSpeed) / 2);
        double direction = Math.toDegrees(MathUtils.atan2(y, x));
        //DiscoUtils.debugPrintln("getDirection: " + direction);

        return direction;
    }

    /**
     * getSpin
     * Calculate the spin of the drive train
     */
    public double getSpin() {
        double spin = ((rearSpeed - ((-1) * frontSpeed)) + (leftSpeed - ((-1) * rightSpeed))) / 2;
        //DiscoUtils.debugPrintln("getSpin: " + spin);
        return spin;
       
    }
}

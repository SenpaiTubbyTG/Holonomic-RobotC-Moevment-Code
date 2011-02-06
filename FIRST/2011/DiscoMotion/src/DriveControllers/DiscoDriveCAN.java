package DriveControllers;

import Utils.DiscoUtils;
import com.sun.squawk.util.MathUtils;
import discobot.HW;
import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.can.*;

/** -------------------------------------------------------
 * @class DiscoDriveCAN
 * @purpose  Class for handling Robot drive The disco
 * drive class handles basic driving for a robot.
 * This is a 4 wheel holonomic drive setup. Each wheel is mounted
 * on a corner of the robot. This configuration allows to both
 * translate in the x and y direction and rotate at the same time.

@author Allen Gregory
@written Jan 22,2010
------------------------------------------------------- */
public class DiscoDriveCAN {

    /**
     * The location of a motor on the robot for the purpose of driving
     */
    public static class MotorType {

        /**
         * The integer value representing this enumeration
         */
        public final int value;
        static final int kFrontLeft_val = 0;
        static final int kFrontRight_val = 1;
        static final int kRearRight_val = 2;
        static final int kRearLeft_val = 3;
        /**
         * motortype: front left
         */
        public static final MotorType kFrontLeft = new MotorType(kFrontLeft_val);
        /**
         * motortype: front right
         */
        public static final MotorType kFrontRight = new MotorType(kFrontRight_val);
        /**
         * motortype: rear right
         */
        public static final MotorType kRearRight = new MotorType(kRearRight_val);
        /**
         * motortype: rear left
         */
        public static final MotorType kRearLeft = new MotorType(kRearLeft_val);

        private MotorType(int value) {
            this.value = value;
        }
    }
    public static final int kNumberOfWheels = 4;
    protected final int m_invertedMotors[] = new int[4];
    private double m_maxOutputPercent = 1.0; //Used to limit the motors to a smaller value, if you only want to go 50% make this .5
    private CANJaguar.ControlMode m_controlMode = CANJaguar.ControlMode.kSpeed;
    public static final DiscoDriveCAN drive = new DiscoDriveCAN();

    /**
     *  set up all the CANJaguars used in DiscoDriveCAN
     */
    private DiscoDriveCAN() {
        try {
           /* //Intialize each Jaguar
            HW.frontLeftCAN = new CANJaguar(HW.frontLeftDMAddress, m_controlMode);
            HW.frontRightCAN = new CANJaguar(HW.frontRightDMAddress, m_controlMode);
            HW.rearRightCAN = new CANJaguar(HW.rearRightDMAddress, m_controlMode);
            HW.rearLeftCAN = new CANJaguar(HW.rearLeftDMAddress, m_controlMode);

            //Set Encoder Counts to Turn
            HW.frontLeftCAN.configEncoderCodesPerRev(HW.encoderCodesPerRev);
            HW.frontRightCAN.configEncoderCodesPerRev(HW.encoderCodesPerRev);
            HW.rearRightCAN.configEncoderCodesPerRev(HW.encoderCodesPerRev);
            HW.rearLeftCAN.configEncoderCodesPerRev(HW.encoderCodesPerRev);

            //Set Up Pid Controls
            HW.frontLeftCAN.setPID(0.1, 0.0, 0.0001);
            HW.frontRightCAN.setPID(0.1, 0.0, 0.0001);
            HW.rearRightCAN.setPID(0.1, 0.0, 0.0001);
            HW.rearLeftCAN.setPID(0.1, 0.0, 0.0001);

            //Set all Jaguars to Brake
            HW.frontLeftCAN.configNeutralMode(CANJaguar.NeutralMode.kBrake);
            HW.frontRightCAN.configNeutralMode(CANJaguar.NeutralMode.kBrake);
            HW.rearRightCAN.configNeutralMode(CANJaguar.NeutralMode.kBrake);
            HW.rearLeftCAN.configNeutralMode(CANJaguar.NeutralMode.kBrake);

            //Enable closed loop control
            HW.frontLeftCAN.enableControl();
            HW.frontRightCAN.enableControl();
            HW.rearRightCAN.enableControl();
            HW.rearLeftCAN.enableControl();
*/

        } catch (Exception e) {
            DiscoUtils.debugPrintln("CAN Timeout: " + e);
        }
    }

    public void writeFirmwareVersions(){
        try {
            DiscoUtils.debugPrintln("Front Left FirmWare Version: " + HW.frontLeftCAN.getFirmwareVersion());
            DiscoUtils.debugPrintln("Front Left FirmWare Version: " + HW.frontRightCAN.getFirmwareVersion());
            DiscoUtils.debugPrintln("Front Left FirmWare Version: " + HW.rearRightCAN.getFirmwareVersion());
            DiscoUtils.debugPrintln("Front Left FirmWare Version: " + HW.rearLeftCAN.getFirmwareVersion());
        } catch (Exception e){
            DiscoUtils.debugPrintln("Error in Firmware writeFirmwareVersions: " + e);
        }
    }

    /**
     * Holonomic Drive method for omni wheel robots
     *
     * This is a modified version of the WPILIB Mecannum code.
     * @param magnitude The speed that the robot should drive in a given direction.  [-1.0..1.0]
     * @param direction The direction the robot should drive. The direction and maginitute are
     * independent of the rotation rate.
     * @param rotation The rate of rotation for the robot that is completely independent of
     * the magnitude or direction.  [-1.0..1.0]
     */
    public void HolonomicDrive(double x, double y, double rotation) {
        // Normalized for full power along the Cartesian axes.
        y = limitToPercent(y);
        x = limitToPercent(x);

        double direction = MathUtils.atan2(x, y); //Return direction in radians
        double magnitude = Math.sqrt(MathUtils.pow(x, 2) + MathUtils.pow(y, 2));

        // Rotate direction 1/8 of a turn (45 degrees) for foward to be foward
        double dirInRad = (direction + (Math.PI / 4));
        double cosD = Math.cos(dirInRad);
        double sinD = Math.cos(dirInRad);

        double wheelSpeeds[] = new double[kNumberOfWheels];
        wheelSpeeds[MotorType.kFrontLeft.value] = (sinD * magnitude + rotation);
        wheelSpeeds[MotorType.kRearRight.value] = (sinD * magnitude - rotation);
        wheelSpeeds[MotorType.kFrontRight.value] = (cosD * magnitude + rotation);
        wheelSpeeds[MotorType.kRearLeft.value] = (cosD * magnitude - rotation);

        normalize(wheelSpeeds);

        if (m_controlMode == CANJaguar.ControlMode.kPercentVbus) {
            setMotorsPercentVbus(wheelSpeeds[MotorType.kFrontLeft.value], wheelSpeeds[MotorType.kRearRight.value],
                    wheelSpeeds[MotorType.kFrontRight.value], wheelSpeeds[MotorType.kRearLeft.value]);
        } else if (m_controlMode == CANJaguar.ControlMode.kSpeed) {
            setMotorsSpeed(wheelSpeeds[MotorType.kFrontLeft.value], wheelSpeeds[MotorType.kRearRight.value],
                    wheelSpeeds[MotorType.kFrontRight.value], wheelSpeeds[MotorType.kRearLeft.value]);
        }

    }

    /**
     * Sets individual motor speeds to certain percentages of the voltage, just like PWM control
     * Will invert the motors properly and limit them with setMaxOutput(double)
     * @param frontLeftSpeed
     * @param frontRightSpeed
     * @param rearLeftSpeed
     * @param rearRightSpeed
     */
    public void setMotorsPercentVbus(double frontLeftSpeed, double frontRightSpeed, double rearLeftSpeed, double rearRightSpeed) {
        if (m_controlMode != CANJaguar.ControlMode.kPercentVbus) {
            updateControlMode(CANJaguar.ControlMode.kPercentVbus);
        }

        byte syncGroup = (byte) 0x80;

        try {
            HW.frontLeftCAN.setX(frontLeftSpeed * m_invertedMotors[MotorType.kFrontLeft.value] * m_maxOutputPercent, syncGroup);
            HW.frontRightCAN.setX(frontRightSpeed * m_invertedMotors[MotorType.kFrontRight.value] * m_maxOutputPercent, syncGroup);
            HW.rearRightCAN.setX(rearRightSpeed * m_invertedMotors[MotorType.kRearRight.value] * m_maxOutputPercent, syncGroup);
            HW.rearLeftCAN.setX(rearLeftSpeed * m_invertedMotors[MotorType.kRearLeft.value] * m_maxOutputPercent, syncGroup);
        } catch (Exception e) {
        }

        try {
            CANJaguar.updateSyncGroup(syncGroup);
        } catch (CANNotInitializedException e) {
        } catch (CANTimeoutException e) {
        }
    }

    /**
     * Used when in closed loop control sends RPMs to the wheels
     * @param frontLeftSpeed
     * @param frontRightSpeed
     * @param rearLeftSpeed
     * @param rearRightSpeed
     */
    public void setMotorsSpeed(double frontLeftSpeed, double frontRightSpeed, double rearLeftSpeed, double rearRightSpeed) {
        if (m_controlMode != CANJaguar.ControlMode.kSpeed) {
            updateControlMode(CANJaguar.ControlMode.kSpeed);
        }

        byte syncGroup = (byte) 0x80;

        double scaleOutput = m_maxOutputPercent * HW.maxWheelVelocity;
        try {
            HW.frontLeftCAN.setX(frontLeftSpeed * m_invertedMotors[MotorType.kFrontLeft.value] * scaleOutput, syncGroup);
            HW.frontRightCAN.setX(frontRightSpeed * m_invertedMotors[MotorType.kFrontRight.value] * scaleOutput, syncGroup);
            HW.rearRightCAN.setX(rearRightSpeed * m_invertedMotors[MotorType.kRearRight.value] * scaleOutput, syncGroup);
            HW.rearLeftCAN.setX(rearLeftSpeed * m_invertedMotors[MotorType.kRearLeft.value] * scaleOutput, syncGroup);
        } catch (Exception e) {
        }

        try {
            CANJaguar.updateSyncGroup(syncGroup);
        } catch (CANNotInitializedException e) {
        } catch (CANTimeoutException e) {
        }
    }

    /**
     * Normalize all wheel speeds if the magnitude of any wheel is greater than 1
     */
    protected static void normalize(double wheelSpeeds[]) {
        double maxMagnitude = Math.abs(wheelSpeeds[0]);
        int i;
        for (i = 1; i < kNumberOfWheels; i++) {
            double temp = Math.abs(wheelSpeeds[i]);
            if (maxMagnitude < temp) {
                maxMagnitude = temp;
            }
        }
        if (maxMagnitude > 1) {
            for (i = 0; i < kNumberOfWheels; i++) {
                wheelSpeeds[i] = wheelSpeeds[i] / maxMagnitude;
            }
        }
    }

    /**
     * Limit motor values to the m_maxWheelVelocity and -m_maxWheelVelocity
     */
    protected static double limitToPercent(double num) {
        if (num > 1) {
            return 1;
        }
        if (num < (-1)) {
            return (-1);
        }
        return num;
    }

    /**
     * Limit motor values to the m_maxWheelVelocity and -m_maxWheelVelocity
     */
    protected static double limitToMaxVelocity(double num) {
        if (num > HW.maxWheelVelocity) {
            return HW.maxWheelVelocity;
        }
        if (num < (-1 * HW.maxWheelVelocity)) {
            return (-1 * HW.maxWheelVelocity);
        }
        return num;
    }

    public void updateControlMode(CANJaguar.ControlMode controlMode) {
        try {
            HW.frontLeftCAN.changeControlMode(controlMode);
            HW.frontRightCAN.changeControlMode(controlMode);
            HW.rearRightCAN.changeControlMode(controlMode);
            HW.rearLeftCAN.changeControlMode(controlMode);
        } catch (Exception e) {
            DiscoUtils.debugPrintln("Exception during control Mode Switch: " + e);
        }

        m_controlMode = controlMode;
    }

    /**
     * Invert a motor direction.
     * This is used when a motor should run in the opposite direction as the drive
     * code would normally run it. Motors that are direct drive would be inverted, the
     * drive code assumes that the motors are geared with one reversal.
     * @param motor The motor index to invert.
     * @param isInverted True if the motor should be inverted when operated.
     */
    public void setInvertedMotor(MotorType motor, boolean isInverted) {
        m_invertedMotors[motor.value] = isInverted ? -1 : 1;
    }

    /**
     * set the maximum wheel velocity, will be used by the method that determines max wheel velocity later.
     */
    public void setMaxWheelVelocity(double maxVelocity) {
        HW.maxWheelVelocity = maxVelocity;
    }
}

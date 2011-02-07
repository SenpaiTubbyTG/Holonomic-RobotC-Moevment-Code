package DriveControllers;

import Utils.DiscoUtils;
import com.sun.squawk.util.MathUtils;
import discobot.HW;
import discobot.PWMJaguar;

/** -------------------------------------------------------
 * @class DiscoDrivePWM
 * @purpose  Class for handling Robot drive The disco
 * drive class handles basic driving for a robot.
 * This is a 4 wheel holonomic drive setup. Each wheel is mounted
 * on a corner of the robot. This configuration allows to both
 * translate in the x and y direction and rotate at the same time.

@author Allen Gregory
@written Jan 22,2010
------------------------------------------------------- */
public class DiscoDrivePWM {

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
    private PWMJaguar.ControlMode m_controlMode = PWMJaguar.ControlMode.kPercentVbus;
    public static final DiscoDrivePWM drive = new DiscoDrivePWM();

    /**
     *  set up all the PWMJaguars used in DiscoDrivePWM
     */
    private DiscoDrivePWM() {
        try {
            //Intialize each Jaguar
            HW.frontLeftPWM = new PWMJaguar(HW.frontLeftDMAddress, m_controlMode);
            HW.frontRightPWM = new PWMJaguar(HW.frontRightDMAddress, m_controlMode);
            HW.rearRightPWM = new PWMJaguar(HW.rearRightDMAddress, m_controlMode);
            HW.rearLeftPWM = new PWMJaguar(HW.rearLeftDMAddress, m_controlMode);

            //Used only by PWMCan
            HW.frontLeftPWM.setEncoderChannels(1, 2, false);
            HW.frontRightPWM.setEncoderChannels(3, 4, false);
            HW.rearRightPWM.setEncoderChannels(5, 6, false);
            HW.rearLeftPWM.setEncoderChannels(7, 8, false);

            //Set Encoder Counts to Turn
            HW.frontLeftPWM.configEncoderCodesPerRev(HW.encoderCodesPerRev);
            HW.frontRightPWM.configEncoderCodesPerRev(HW.encoderCodesPerRev);
            HW.rearRightPWM.configEncoderCodesPerRev(HW.encoderCodesPerRev);
            HW.rearLeftPWM.configEncoderCodesPerRev(HW.encoderCodesPerRev);

            //Set Up Pid Controls
            HW.frontLeftPWM.setPID(0.1, 0.0, 0.0001);
            HW.frontRightPWM.setPID(0.1, 0.0, 0.0001);
            HW.rearRightPWM.setPID(0.1, 0.0, 0.0001);
            HW.rearLeftPWM.setPID(0.1, 0.0, 0.0001);

            //Set all Jaguars to Brake
            HW.frontLeftPWM.configNeutralMode(PWMJaguar.NeutralMode.kBrake);
            HW.frontRightPWM.configNeutralMode(PWMJaguar.NeutralMode.kBrake);
            HW.rearRightPWM.configNeutralMode(PWMJaguar.NeutralMode.kBrake);
            HW.rearLeftPWM.configNeutralMode(PWMJaguar.NeutralMode.kBrake);

            //Enable closed loop control
            HW.frontLeftPWM.enableControl();
            HW.frontRightPWM.enableControl();
            HW.rearRightPWM.enableControl();
            HW.rearLeftPWM.enableControl();


        } catch (Exception e) {
            DiscoUtils.debugPrintln("PWM Timeout: " + e);
        }
    }

    public void writeFirmwareVersions(){
        try {
            DiscoUtils.debugPrintln("Front Left FirmWare Version: " + HW.frontLeftPWM.getFirmwareVersion());
            DiscoUtils.debugPrintln("Front Left FirmWare Version: " + HW.frontRightPWM.getFirmwareVersion());
            DiscoUtils.debugPrintln("Front Left FirmWare Version: " + HW.rearRightPWM.getFirmwareVersion());
            DiscoUtils.debugPrintln("Front Left FirmWare Version: " + HW.rearLeftPWM.getFirmwareVersion());
        } catch (Exception e){
            DiscoUtils.debugPrintln("Error in Firmware writeFirmwareVersions: " + e);
        }
    }

    /**
     * Holonomic Drive method for omni wheel robots
     *
     * This is a modified version of the WPILIB code.
     * @param magnitude The speed that the robot should drive in a given direction.  [-1.0..1.0]
     * @param direction The direction the robot should drive. The direction and maginitute are
     * independent of the rotation rate.
     * @param rotation The rate of rotation for the robot that is completely independent of
     * the magnitude or direction.  [-1.0..1.0]
     */
    public void HolonomicDrive(double x, double y, double rotation) {
        double xIn = limitToPercent(x);
        double yIn = limitToPercent(y);
        // Negate y for the joystick.
        yIn = -yIn;

        double wheelSpeeds[] = new double[kNumberOfWheels];
        wheelSpeeds[MotorType.kFrontLeft_val] = xIn + yIn + rotation;
        wheelSpeeds[MotorType.kFrontRight_val] = -xIn + yIn - rotation;
        wheelSpeeds[MotorType.kRearRight_val] = xIn + yIn - rotation;
        wheelSpeeds[MotorType.kRearLeft_val] = -xIn + yIn + rotation;


        normalize(wheelSpeeds);

        if (m_controlMode == PWMJaguar.ControlMode.kPercentVbus) {
            setMotorsPercentVbus(wheelSpeeds[MotorType.kFrontLeft.value], wheelSpeeds[MotorType.kRearRight.value],
                    wheelSpeeds[MotorType.kFrontRight.value], wheelSpeeds[MotorType.kRearLeft.value]);
        } else if (m_controlMode == PWMJaguar.ControlMode.kSpeed) {
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
        if (m_controlMode != PWMJaguar.ControlMode.kPercentVbus) {
            updateControlMode(PWMJaguar.ControlMode.kPercentVbus);
        }

        byte syncGroup = (byte) 0x80;

        try {
            HW.frontLeftPWM.setX(frontLeftSpeed * m_invertedMotors[MotorType.kFrontLeft.value] * m_maxOutputPercent, syncGroup);
            HW.frontRightPWM.setX(frontRightSpeed * m_invertedMotors[MotorType.kFrontRight.value] * m_maxOutputPercent, syncGroup);
            HW.rearRightPWM.setX(rearRightSpeed * m_invertedMotors[MotorType.kRearRight.value] * m_maxOutputPercent, syncGroup);
            HW.rearLeftPWM.setX(rearLeftSpeed * m_invertedMotors[MotorType.kRearLeft.value] * m_maxOutputPercent, syncGroup);
        } catch (Exception e) {
        }

        try {
            PWMJaguar.updateSyncGroup(syncGroup);
        } catch (Exception e){
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
        if (m_controlMode != PWMJaguar.ControlMode.kSpeed) {
            updateControlMode(PWMJaguar.ControlMode.kSpeed);
        }

        byte syncGroup = (byte) 0x80;

        double scaleOutput = m_maxOutputPercent * HW.maxWheelVelocity;
        try {
            HW.frontLeftPWM.setX(frontLeftSpeed * m_invertedMotors[MotorType.kFrontLeft.value] * scaleOutput, syncGroup);
            HW.frontRightPWM.setX(frontRightSpeed * m_invertedMotors[MotorType.kFrontRight.value] * scaleOutput, syncGroup);
            HW.rearRightPWM.setX(rearRightSpeed * m_invertedMotors[MotorType.kRearRight.value] * scaleOutput, syncGroup);
            HW.rearLeftPWM.setX(rearLeftSpeed * m_invertedMotors[MotorType.kRearLeft.value] * scaleOutput, syncGroup);
        } catch (Exception e) {
        }

        try {
            PWMJaguar.updateSyncGroup(syncGroup);
        } catch (Exception e){
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

    public void updateControlMode(PWMJaguar.ControlMode controlMode) {
        try {
            HW.frontLeftPWM.changeControlMode(controlMode);
            HW.frontRightPWM.changeControlMode(controlMode);
            HW.rearRightPWM.changeControlMode(controlMode);
            HW.rearLeftPWM.changeControlMode(controlMode);
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

    public void setControlMode(PWMJaguar.ControlMode controlMode){
        m_controlMode = controlMode;
    }
}

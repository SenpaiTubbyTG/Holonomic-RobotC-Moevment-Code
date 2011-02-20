/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package discobot;

import Utils.DiscoUtils;
import DriveControllers.*;
import Sensors.DiscoEncoder;
import edu.wpi.first.wpilibj.*;

/**
 *
 * @author JAG
 */
public class PWMJaguar extends Jaguar{

    /**
     * Imitates the ControlMode class in CANJaguar
     * Current and Voltage modes are not possible
     */
    public static class ControlMode {

        public final int value;
        static final int kPercentVbus_val = 0;
        static final int kSpeed_val = 2;
        static final int kPosition_val = 3;
        public static final ControlMode kPercentVbus = new ControlMode(kPercentVbus_val);
        public static final ControlMode kSpeed = new ControlMode(kSpeed_val);
        public static final ControlMode kPosition = new ControlMode(kPosition_val);

        private ControlMode(int value) {
            this.value = value;
        }
    }

    /**
     * Limit switch masks
     */
    public static class Limits {

        public final int value;
        static final int kForwardLimit_val = 1;
        static final int kReverseLimit_val = 2;
        public static final Limits kForwardLimit = new Limits(kForwardLimit_val);
        public static final Limits kReverseLimit = new Limits(kReverseLimit_val);

        private Limits(int value) {
            this.value = value;
        }
    }

    /**
     * Determines which sensor to use for position reference.
     * Only implementing quad encoder as of now
     */
    public static class PositionReference {

        public final byte value;
        static final byte kQuadEncoder_val = 0;
        static final byte kPotentiometer_val = 1;
        static final byte kNone_val = (byte) 0xFF;
        public static final PositionReference kQuadEncoder = new PositionReference(kQuadEncoder_val);
        public static final PositionReference kPotentiometer = new PositionReference(kPotentiometer_val);
        public static final PositionReference kNone = new PositionReference(kNone_val);

        private PositionReference(byte value) {
            this.value = value;
        }
    }

    /**
     * Determines which sensor to use for speed reference.
     * Only implementing quad encoder as of now
     */
    public static class SpeedReference {

        public final byte value;
        static final byte kEncoder_val = 0;
        static final byte kInvEncoder_val = 2;
        static final byte kQuadEncoder_val = 3;
        static final byte kNone_val = (byte) 0xFF;
        public static final SpeedReference kEncoder = new SpeedReference(kEncoder_val);
        public static final SpeedReference kInvEncoder = new SpeedReference(kInvEncoder_val);
        public static final SpeedReference kQuadEncoder = new SpeedReference(kQuadEncoder_val);
        public static final SpeedReference kNone = new SpeedReference(kNone_val);

        private SpeedReference(byte value) {
            this.value = value;
        }
    }

    /**
     * NeutralMode is set by the Jumper when using PWM but need if for 
     * compatibility with CANJagura
     */
    public static class NeutralMode {

        public final byte value;
        static final byte kJumper_val = 0;
        static final byte kBrake_val = 1;
        static final byte kCoast_val = 2;
        public static final NeutralMode kJumper = new NeutralMode(kJumper_val);
        public static final NeutralMode kBrake = new NeutralMode(kBrake_val);
        public static final NeutralMode kCoast = new NeutralMode(kCoast_val);

        private NeutralMode(byte value) {
            this.value = value;
        }
    }

    /**
     * Determines which sensor to use for position reference.
     */
    public static class LimitMode {

        public final byte value;
        static final byte kSwitchInputsOnly_val = 0;
        static final byte kSoftPositionLimit_val = 1;
        public static final LimitMode kSwitchInputsOnly = new LimitMode(kSwitchInputsOnly_val);
        public static final LimitMode kSoftPostionLimits = new LimitMode(kSoftPositionLimit_val);

        private LimitMode(byte value) {
            this.value = value;
        }
    }
    private static final double kControllerPeriod = .01;
    private ControlMode m_controlMode;
    private double m_maxOutputVoltage = 1.0;
    private PositionReference m_positionReference;
    private SpeedReference m_speedReference;
    private int m_encoderCodesPerRev;
    private double m_X;
    private double m_output;
    private AbstractPID m_PIDController;
    private DiscoEncoder m_encoder;
    private DigitalInput m_reverseLimit;
    private DigitalInput m_forwardLimit;
    private double m_reverseSoftLimit = -1000000000;
    private double m_forwardSoftLimit = 1000000000;

    public PWMJaguar(final int channel) {
       super(channel);
        m_controlMode = ControlMode.kPercentVbus;
    }

    public PWMJaguar(final int channel, ControlMode controlMode) {
        this(channel);
        m_controlMode = controlMode;
    }

    /**
     * Functions that are not in CANJaguar
     */
    /**
     * Used to set up the encoder for use with the position and speed control modes
     * Note this is not in CANJaguar because the encoders are plugged directly into the Jaguars
     * @param aChannel
     * @param bChannel
     * @param reversed
     */
    public void setEncoderChannels(DigitalInput  aChannel, DigitalInput  bChannel, boolean reversed) {
        setEncoderChannels(aChannel, bChannel, reversed, CounterBase.EncodingType.k2X);
    }

    public void setEncoderChannels(DigitalInput aChannel, DigitalInput bChannel, boolean reversed,
            CounterBase.EncodingType x) {
        m_encoder = new DiscoEncoder(aChannel, bChannel, reversed, x);
        switch (m_controlMode.value) {
            case ControlMode.kPercentVbus_val:

                break;
            case ControlMode.kSpeed_val:
                m_PIDController = new VelocityController3(0.0, 0.0, 0.0, m_encoder, this, kControllerPeriod, false);
                break;
            case ControlMode.kPosition_val:
                m_PIDController = new PositionController(0.0, 0.0, 0.0, m_encoder, this, kControllerPeriod, false);
                break;
            default:
                DiscoUtils.debugPrintln("Control Mode is invalid for PWMJaguar");
        }

    }

    /**
     * Functions that are in CANJaguar
     */
    /**
     * Set the output set-point value.
     *
     * The scale and the units depend on the mode the Jaguar is in.
     * In PercentVbus Mode, the outputValue is from -1.0 to 1.0 (same as PWM Jaguar).
     * In Speed Mode, the outputValue is in Rotations/Minute.
     * In Position Mode, the outputValue is in Rotations.
     *
     * @param outputValue The set-point to sent to the motor controller.
     */
    public void setX(double outputValue) {
        setX(outputValue, (byte) 0);
    }

    /**
     * Set the output set-point value.
     *
     * The scale and the units depend on the mode the Jaguar is in.
     * In PercentVbus Mode, the outputValue is from -1.0 to 1.0 (same as PWM Jaguar).
     * In Speed Mode, the outputValue is in Rotations/Minute.
     * In Position Mode, the outputValue is in Rotations.
     *
     * NOTE: Limits are not enabled right now, except for soft limits.
     *
     * @param outputValue The set-point to sent to the motor controller.
     * @param syncGroup The update group to add this set() to, pending updateSyncGroup().  If 0, update immediately.
     */
    public void setX(double outputValue, byte syncGroup) {

        m_X = outputValue;
        switch (m_controlMode.value) {
            case ControlMode.kPercentVbus_val:
                if (m_X > m_maxOutputVoltage) {
                    m_X = m_maxOutputVoltage;
                }
                if (m_X < -m_maxOutputVoltage) {
                    m_X = -m_maxOutputVoltage;
                }
                super.set(m_X);
                break;
            case ControlMode.kSpeed_val: {
                if (m_PIDController != null) {
                    m_PIDController.setOutputRange(-m_maxOutputVoltage, m_maxOutputVoltage);
                    m_PIDController.setSetpoint(m_X);
                }
            }
            break;
            case ControlMode.kPosition_val: {
                if (m_PIDController != null) {
                    m_PIDController.setOutputRange(-m_maxOutputVoltage, m_maxOutputVoltage);
                    m_PIDController.setSetpoint(m_X);
                }
            }
            break;
            default:
                DiscoUtils.debugPrintln("Control Mode is invalid for PWMJaguar");
                return;
        }
    }

    /**
     * Get the recently set outputValue setpoint.
     *
     * The scale and the units depend on the mode the Jaguar is in.
     * In PercentVbus Mode, the outputValue is from -1.0 to 1.0 (same as PWM Jaguar).
     * In Speed Mode, the outputValue is in Rotations/Minute.
     * In Position Mode, the outputValue is in Rotations.
     *
     * @return The most recently set outputValue setpoint.
     */
    public double getX() {
        return m_X;
    }

    /**
     * Set the reference source device for speed controller mode.
     *
     * Choose encoder as the source of speed feedback when in speed control mode.
     *
     * @param reference Specify a SpeedReference.
     */
    public void setSpeedReference(SpeedReference reference) {
        if (reference.value == SpeedReference.kQuadEncoder_val) {
            m_speedReference = reference;
        } else {
            DiscoUtils.debugPrintln("Only Quad Encoder Enabled right now");
        }
    }

    /**
     * Get the reference source device for speed controller mode.
     *
     * @return A SpeedReference indicating the currently selected reference device for speed controller mode.
     */
    public SpeedReference getSpeedReference() {
        return m_speedReference;
    }

    /**
     * Set the reference source device for position controller mode.
     *
     * Choose between using and encoder and using a potentiometer
     * as the source of position feedback when in position control mode.
     *
     * NOTE: Quad Encoder is the only thing enable right now
     *
     * @param reference Specify a PositionReference.
     */
    public void setPositionReference(PositionReference reference) {
        if (reference.value == PositionReference.kQuadEncoder_val) {
            m_positionReference = reference;
        } else {
            DiscoUtils.debugPrintln("Only Quad Encoder Enabled right now");
        }
    }

    /**
     * Get the reference source device for position controller mode.
     *
     * @return A PositionReference indicating the currently selected reference device for position controller mode.
     */
    public PositionReference getPositionReference() {
        return m_positionReference;
    }

    /**
     * Set the P, I, and D constants for the closed loop modes.
     *
     * @param p The proportional gain of the Jaguar's PID controller.
     * @param i The integral gain of the Jaguar's PID controller.
     * @param d The differential gain of the Jaguar's PID controller.
     */
    public void setPID(double p, double i, double d) {

        if (m_PIDController != null) {
            switch (m_controlMode.value) {
                case ControlMode.kPercentVbus_val:
                    break;
                case ControlMode.kSpeed_val:
                    m_PIDController.setPID(p, i, d);
                    break;
                case ControlMode.kPosition_val:
                    m_PIDController.setPID(p, i, d);
                    break;
                default:
                    DiscoUtils.debugPrintln("Control Mode is invalid for PWMJaguar");
            }
        } else {
             DiscoUtils.debugPrintln("PID controller has not been intialized PID values not set");
        }
    }

    /**
     * Get the Proportional gain of the controller.
     *
     * @return The proportional gain.
     */
    public double getP() {
        if (m_PIDController != null) {
            return m_PIDController.getP();
        }
        return 0.0;
    }

    /**
     * Get the Intregral gain of the controller.
     *
     * @return The integral gain.
     */
    public double getI() {
        if (m_PIDController != null) {
            return m_PIDController.getI();
        }
        return 0.0;
    }

    /**
     * Get the Differential gain of the controller.
     *
     * @return The differential gain.
     */
    public double getD() {
        if (m_PIDController != null) {
            return m_PIDController.getD();
        }
        return 0.0;
    }

    /**
     * Enable the closed loop controller.
     *
     * Start actually controlling the output based on the feedback.
     */
    public void enableControl() {
        enableControl(0.0);
    }

    /**
     * Enable the closed loop controller.
     *
     * Start actually controlling the output based on the feedback.
     * If starting a position controller with an encoder reference,
     * use the encoderInitialPosition parameter to initialize the
     * encoder state.
     * @param encoderInitialPosition Encoder position to set if position with encoder reference.  Ignored otherwise.
     */
    public void enableControl(double encoderInitialPosition) {
        switch (m_controlMode.value) {
            case ControlMode.kPercentVbus_val:

                break;
            case ControlMode.kSpeed_val:
                if (m_PIDController != null) {
                    m_encoder.setPIDSourceParameter(DiscoEncoder.PIDSourceParameter.kRate);
                    m_PIDController.reset();
                    m_PIDController.enable();
                }
                break;
            case ControlMode.kPosition_val:
                if (m_PIDController != null) {
                    m_encoder.setPIDSourceParameter(DiscoEncoder.PIDSourceParameter.kDistance);
                    m_PIDController.reset();
                    m_encoder.setPosition(encoderInitialPosition);
                    m_PIDController.enable();
                }
                break;
            default:
                DiscoUtils.debugPrintln("Control Mode is invalid for PWMJaguar");
        }
    }

    /**
     * Disable the closed loop controller.
     *
     * Stop driving the output based on the feedback.
     */
    public void disableControl() {
        switch (m_controlMode.value) {
            case ControlMode.kPercentVbus_val:
                super.stopMotor();
                break;
            case ControlMode.kSpeed_val:
                m_PIDController.disable();
                super.stopMotor();
                break;
            case ControlMode.kPosition_val:
                m_PIDController.disable();
                super.stopMotor();
                break;
            default:
                DiscoUtils.debugPrintln("Control Mode is invalid for PWMJaguar");
        }
    }

    /**
     * Change the control mode of this Jaguar object.
     *
     * After changing modes, configure any PID constants or other settings needed
     * and then enableControl() to actually change the mode on the Jaguar.
     *
     * @param controlMode The new mode.
     */
    public void changeControlMode(ControlMode controlMode) {
        // Disable the previous mode
        disableControl();

        // Update the local mode
        m_controlMode = controlMode;
        switch (m_controlMode.value) {
            case ControlMode.kPercentVbus_val:
                break;
            case ControlMode.kSpeed_val:
                if (m_encoder != null) {
                    m_PIDController = new VelocityController3(0.0, 0.0, 0.0, m_encoder, this, kControllerPeriod, false);
                }
                break;
            case ControlMode.kPosition_val:
                if (m_encoder != null) {
                    m_PIDController = new PositionController(0.0, 0.0, 0.0, m_encoder, this, kControllerPeriod, false);
                }
                break;
            default:
                DiscoUtils.debugPrintln("Control Mode is invalid for PWMJaguar");
        }
    }

    /**
     * Get the active control mode from the Jaguar.
     *
     * @return ControlMode that the Jag is in.
     */
    public ControlMode getControlMode() {
        return m_controlMode;
    }

    /**
     * Get the voltage at the battery input terminals of the Jaguar.
     * Just gets the BusVoltage from the analogBumper, not actually what is at
     * the Jaguar
     * @return The bus voltage in Volts.
     */
    public double getBusVoltage() {
        AnalogChannel battery = new AnalogChannel(8);
        return battery.getAverageVoltage() * (1680.0 / 1000.0);
    }

    /**
     * Get the voltage being output from the motor terminals of the Jaguar.
     * Not able to do this with PWMJagur
     * @return The output voltage in Volts.
     */
    public double getOutputVoltage() {
        return m_output * getBusVoltage();
    }

    /**
     * Get the current through the motor terminals of the Jaguar.
     *
     * @return The output current in Amps.
     */
    public double getOutputCurrent() {
        DiscoUtils.debugPrintln("Unable to get current in PWMJaguar outputtin 0.0");
        return 0.0;
    }

    /**
     * Get the internal temperature of the Jaguar.
     *
     * @return The temperature of the Jaguar in degrees Celsius.
     */
    public double getTemperature() {
        DiscoUtils.debugPrintln("Unable to get temperature in PWMJaguar outputtin 0.0");
        return 0.0;
    }

    /**
     * Get the position of the encoder or potentiometer.
     *
     * @return The position of the motor based on the configured feedback.
     */
    public double getPosition() {
        if (m_encoder != null) {
            return m_encoder.getRawPosition();
        } else {
            return 0.0;
        }
    }

    /**
     * Get the speed of the encoder.
     *
     * @return The speed of the motor in RPM based on the configured feedback.
     */
    public double getSpeed() {
        if (m_encoder != null) {
            return m_encoder.getRate();
        } else {
            return 0.0;
        }
    }

    /**
     * Get the status of the forward limit switch.

     * @return The motor is allowed to turn in the forward direction when true.
     */
    public boolean getForwardLimitOK() {
        if (m_forwardLimit != null) {
            return !m_forwardLimit.get();
        } else {
            return true;
        }
    }

    /**
     * Get the status of the reverse limit switch.
     *
     * @return The motor is allowed to turn in the reverse direction when true.
     */
    public boolean getReverseLimitOK() {
        if (m_reverseLimit != null) {
            return !m_reverseLimit.get();
        } else {
            return true;
        }
    }

    /**
     * Get the status of any faults the Jaguar has detected.
     *
     * @return A bit-mask of faults defined by the "Faults" enum class.
     */
    public short getFaults() {
        DiscoUtils.debugPrintln("Unable to get Faults in PWMJaguar returning 0");
        return 0;
    }

    /**
     * Check if the Jaguar's power has been cycled since this was last called.
     *
     * This should return true the first time called after a Jaguar power up,
     * and false after that.
     *
     * @return The Jaguar was power cycled since the last call to this function.
     */
    public boolean getPowerCycled() {
        DiscoUtils.debugPrintln("Unable to get Power Cycled in PWMJaguar returning false");
        return false;
    }

    /**
     * Set the maximum voltage change rate.
     *
     * When in percent voltage output mode, the rate at which the voltage changes can
     * be limited to reduce current spikes.  Set this to 0.0 to disable rate limiting.
     *
     * @param rampRate The maximum rate of voltage change in Percent Voltage mode in V/s.
     */
    public void setVoltageRampRate(double rampRate) {

        switch (m_controlMode.value) {
            case ControlMode.kPercentVbus_val:
                break;
            default:
                return;
        }
    }

    /**
     * Get the version of the firmware running on the Jaguar.
     *
     * @return The firmware version.  0 if the device did not respond.
     */
    public int getFirmwareVersion() {
        DiscoUtils.debugPrintln("Unable to get Firmware Version in PWMJaguar");
        return 0;
    }

    /**
     * Get the version of the Jaguar hardware.
     *
     * @return The hardware version. 1: Jaguar,  2: Black Jaguar
     */
    public byte getHardwareVersion() {
        DiscoUtils.debugPrintln("Unable to get Hardware Version in PWMJaguar");
        return 0;
    }

    /**
     * Configure what the controller does to the H-Bridge when neutral (not driving the output).
     *
     * This allows you to override the jumper configuration for brake or coast.
     *
     * @param mode Select to use the jumper setting or to override it to coast or brake.
     */
    public void configNeutralMode(NeutralMode mode) {
        //Unable to set NeutralMode in PWMJaguar use Jumper instead
    }

    /**
     * Configure how many codes per revolution are generated by your encoder.
     *
     * @param codesPerRev The number of counts per revolution in 1X mode.
     */
    public void configEncoderCodesPerRev(int codesPerRev) {
        m_encoderCodesPerRev = codesPerRev;
        if (m_encoder != null) {
            //This will make it return Rate in RPM
            m_encoder.setDistancePerPulse((1 / m_encoderCodesPerRev));
        }
    }

    /**
     * Configure the number of turns on the potentiometer.
     *
     * There is no special support for continuous turn potentiometers.
     * Only integer numbers of turns are supported.
     *
     * @param turns The number of turns of the potentiometer
     */
    public void configPotentiometerTurns(int turns) {
        DiscoUtils.debugPrintln("Potentiometer not implemented for PWMJaguar");
    }

    /**
     * Configure Soft Position Limits when in Position Controller mode.
     *
     * When controlling position, you can add additional limits on top of the limit switch inputs
     * that are based on the position feedback.  If the position limit is reached or the
     * switch is opened, that direction will be disabled.
     *
     * @param forwardLimitPosition The position that if exceeded will disable the forward direction.
     * @param reverseLimitPosition The position that if exceeded will disable the reverse direction.
     */
    public void configSoftPositionLimits(double forwardLimitPosition, double reverseLimitPosition) {
        if (m_controlMode.value == ControlMode.kPosition_val) {
            m_reverseSoftLimit = reverseLimitPosition;
            m_forwardSoftLimit = forwardLimitPosition;
            m_PIDController.setInputRange(m_reverseSoftLimit, m_forwardSoftLimit);
        }
    }

    /**
     * Disable Soft Position Limits if previously enabled.
     *
     * Soft Position Limits are disabled by default.
     */
    public void disableSoftPositionLimits() {
        if (m_controlMode.value == ControlMode.kPosition_val) {
            m_reverseSoftLimit = -1000000000;
            m_forwardSoftLimit = 1000000000;
            m_PIDController.setInputRange(m_reverseSoftLimit, m_forwardSoftLimit);
        }
    }

    /**
     * Configure the maximum voltage that the Jaguar will ever output.
     *
     * This can be used to limit the maximum output voltage in all modes so that
     * motors which cannot withstand full bus voltage can be used safely.
     *
     * @param voltage The maximum voltage output by the Jaguar.
     */
    public void configMaxOutputVoltage(double voltage) {
        double percentVoltage = voltage / getBusVoltage();
        m_maxOutputVoltage = percentVoltage;
    }

    /**
     * Update all the motors that have pending sets in the syncGroup.
     * 
     * @param syncGroup A bitmask of groups to generate synchronous output.
     */
    public static void updateSyncGroup(byte syncGroup) {
        DiscoUtils.debugPrintln("Unable to update Sync Group in PWMJaguar");
    }
}

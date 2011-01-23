/*
 * MaxbotixSonar class for reading values from the Maxbotix Sonars.
 * Will have functions for running them in daisy chain mode which will require
 * a digital output.
 *
 * Remember that Maxbotix sensors get connected to Analog inputs not digital
 * inputs like other ultrasonic sensors.
 */

package Sensors;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.parsing.ISensor;

/**
 * 
 * @author JAG
 */
public class MaxbotixSonar extends SensorBase implements PIDSource, ISensor{
    /**
     * The units to return when PIDGet is called
     */
    public static class Unit {

        /**
         * The integer value representing this enumeration
         */
        public final int value;
        static final int kInches_val = 0;
        static final int kMillimeters_val = 1;
        /**
         * Use inches for PIDGet
         */
        public static final Unit kInches = new Unit(kInches_val);
        /**
         * Use millimeters for PIDGet
         */
        public static final Unit kMillimeter = new Unit(kMillimeters_val);

        private Unit(int value) {
            this.value = value;
        }
    }
    private static final double kPingTime = 20 * 1e-6;	///< Time (sec) for the ping trigger pulse.
    private static final double kMaxUltrasonicTime = 0.1;	///< Max time (ms) between readings.
    private static final double kCMToIn = 0.3937;
    private static final double kMinVoltage = 0.02;	  //Minimum voltage the ultrasonic sensor can return
    private AnalogChannel m_inputChannel = null;
    private DigitalOutput m_pingChannel = null;
    private boolean m_allocatedChannels;
    private boolean m_enabled = false;
    private Unit m_units;

    /**
     * Initialize the a daisy chain of MaxbotixSonar Sensors.
     * This is the code that initializes the Maxbotix Sensor if it is the first
     * sensor and it has to be triggered by a digital out to start the daisy
     * chain
     *
     * Should pulse high for 20us and then switch to high impedance,
     * If I can't figure out how to do this we will trigger the pulse
     * every 100ms * number of sensors
     */
    private synchronized void initializeDaisyChain() {
      if (m_pingChannel != null) {
        this.m_pingChannel.pulse(kPingTime);
      }
    }

    /**
     * Create an instance of the MaxbotixSonar Sensor using the default modules.
     * This is designed to support the Maxbotix-XL  ultrasonic sonar sensors. This
     * constructor is for the first module that is the start of a daisy chain. This
     * constructor assumes the analog I/O channel is in the default analog module
     * and that the ping channel is in the default digital module.
     * @param pingChannel The digital output channel that sends the pulse to initiate the
     * daisy chain of Maxbotix sonars
     * @param inputChannel The analog input channel has the analog voltage of the distance.
     * @param units The units returned in either kInches or kMilliMeters
     */
    public MaxbotixSonar(final int pingChannel, final int inputChannel, Unit units) {
        m_pingChannel = new DigitalOutput(pingChannel);
        m_inputChannel = new AnalogChannel(inputChannel);
        m_allocatedChannels = true;
        m_units = units;
        initializeDaisyChain();
    }

    /**
     * Create an instance of the MaxbotixSonar Sensor using the default modules.
     * This is designed to support the Maxbotix-XL  ultrasonic sonar sensors. This
     * constructor is for the first module that is the start of a daisy chain. This
     * constructor assumes the analog I/O channel is in the default analog module
     * and that the ping channel is in the default digital module.
     * Defualts to Inches
     * @param pingChannel The digital output channel that sends the pulse to initiate the
     * daisy chain of Maxbotix sonars
     * @param inputChannel The analog input channel has the analog voltage of the distance.
     */
    public MaxbotixSonar(final int pingChannel, final int inputChannel) {
        this(pingChannel, inputChannel, Unit.kInches);
    }

    /**
     * Create an instance of the MaxbotixSonar Sensor from a AnalogChannel for the input channel and a DigitalOutput
     * for the ping channel.
     * @param pingChannel The digital output object that starts the sensor daisy chain doing a ping. Requires a 20uS pulse to start.
     * @param inputChannel The AnalogChannel object that times the return pulse to determine the range.
     * @param units The units returned in either kInches or kMilliMeters
     */
    public MaxbotixSonar(DigitalOutput pingChannel, AnalogChannel inputChannel, Unit units) {
        if (pingChannel == null || inputChannel == null) {
            throw new NullPointerException("Null Channel Provided");
        }
        m_allocatedChannels = false;
        m_pingChannel = pingChannel;
        m_inputChannel = inputChannel;
        m_units = units;
        initializeDaisyChain();
    }

    /**
     * Create an instance of the MaxbotixSonar Sensor from a AnalogChannel for the input channel and a DigitalOutput
     * for the ping channel.
     * Defaults to Inches
     * @param pingChannel The digital output object that starts the sensor daisy chain doing a ping. Requires a 20uS pulse to start.
     * @param inputChannel The AnalogChannel object that times the return pulse to determine the range.
     * @param units The units returned in either kInches or kMilliMeters
     */
    public MaxbotixSonar(DigitalOutput pingChannel, AnalogChannel inputChannel) {
       this(pingChannel,inputChannel,Unit.kInches);
    }

    /**
     * Create an instance of the MaxbotixSonar sensor using specified modules.
     * This constructors takes the channel and module slot for each of the required
     * digital and analog I/O channels.
     * @param pingSlot The digital module that the pingChannel is in.
     * @param pingChannel The digital output channel that sends the pulse to initiate the sensor
     * sending the ping.
     * @param inputSlot The analog module that the inputChannel is in.
     * @param inputChannel The analog input channel that receives the voltage representing
     * the distance.
     * @param units The units returned in either kInches or kMilliMeters
     */
    public MaxbotixSonar(final int pingSlot, final int pingChannel,
            final int inputSlot, final int inputChannel, Unit units) {
        m_pingChannel = new DigitalOutput(pingSlot, pingChannel);
        m_inputChannel = new AnalogChannel(inputSlot, inputChannel);
        m_allocatedChannels = true;
        m_units = units;
        initializeDaisyChain();
    }

    /**
     * Create an instance of the MaxbotixSonar Sensor using the default modules.
     * This is designed to support the Maxbotix-XL  ultrasonic sonar sensors. This
     * constructor is for all sensors that are not the first sensor in a daisy chain. This
     * constructor assumes the analog I/O channel is in the default analog module
     * @param inputChannel The analog input channel has the analog voltage of the distance.
     * @param units The units returned in either kInches or kMilliMeters
     */
    public MaxbotixSonar(final int inputChannel, Unit units) {
        m_inputChannel = new AnalogChannel(inputChannel);
        m_allocatedChannels = true;
        m_units = units;
    }

    /**
     * Create an instance of the MaxbotixSonar Sensor using the default modules.
     * This is designed to support the Maxbotix-XL  ultrasonic sonar sensors. This
     * constructor is for all sensors that are not the first sensor in a daisy chain. This
     * constructor assumes the analog I/O channel is in the default analog module
     * Defaults to using inches
     * @param inputChannel The analog input channel has the analog voltage of the distance.
     * @param units The units returned in either kInches or kMilliMeters
     */
    public MaxbotixSonar(final int inputChannel) {
        this(inputChannel, Unit.kInches);
    }

    /**
     * Create an instance of the MaxbotixSonar Sensor from a AnalogChannel for the input channel
     * Used when not the first in a daisy chain.
     * @param inputChannel The AnalogChannel object that times the return pulse to determine the range.
     * @param units The units returned in either kInches or kMilliMeters
     */
    public MaxbotixSonar(AnalogChannel inputChannel, Unit units) {
        if (inputChannel == null) {
            throw new NullPointerException("Null Channel Provided");
        }
        m_allocatedChannels = false;
        m_inputChannel = inputChannel;
        m_units = units;
    }

    /**
     * Create an instance of the MaxbotixSonar Sensor from a AnalogChannel for the input channel.
     * Used when not the first in a daisy chain.
     * Defaults to inches
     * @param inputChannel The AnalogChannel object that times the return pulse to determine the range.
     * @param units The units returned in either kInches or kMilliMeters
     */
    public MaxbotixSonar(AnalogChannel inputChannel) {
        this(inputChannel, Unit.kInches);
    }

    /**
     * Check if this is a valid range reading
     */

    public boolean isRangeValid() {
        if (getVoltage() < kMinVoltage) {
            return false;
        }
        else {
            return true;
        }
    }

    /**
     * Return the Voltage reading directly form the analog module
     */
    public double getVoltage () {
        return m_inputChannel.getVoltage();
    }

    /**
     * Get the range in centimeters from the ultrasonic sensor, only if the range is valid.
     * @return double Range in millimeters of the target returned from the MaxbotixSonarsensor. If there is
     * no valid value yet then return 0.
     */
    public double getRangeCM() {
        if (isRangeValid()) {
            return getVoltage() / 1024;
        } else {
            return 0;
        }
    }
     /**
     * Get the range in millimeters from the MaxbotixSonarsensor.
     * @return double Range in millimeters of the target returned from the MaxbotixSonarsensor. If there is
     * no valid value yet then return 0.
     */
    public double getRangeMM() {
        return getRangeCM() * 10;
    }

    /**
     * Get the range in inches from the MaxbotixSonar sensor.
     * @return double Range in inches of the target returned from the MaxbotixSonarsensor. If there is
     * no valid value yet then return 0.
     */
    public double getRangeInches() {
        return getRangeCM() * kCMToIn;
    }

     /**
     * Get the range in the current DistanceUnit for the PIDSource base object.
     *
     * @return The range in DistanceUnit
     */
    public double pidGet() {
        switch (m_units.value) {
            case Unit.kInches_val:
                return getRangeInches();
            case Unit.kMillimeters_val:
                return getRangeMM();
            default:
                return 0.0;
        }
    }

    /**
     * Set the current DistanceUnit that should be used for the PIDSource base object.
     *
     * @param units The DistanceUnit that should be used.
     */
    public void setDistanceUnits(Unit units) {
        m_units = units;
    }

     /**
     * Get the current DistanceUnit that is used for the PIDSource base object.
     *
     * @return The type of DistanceUnit that is being used.
     */
    public Unit getDistanceUnits() {
        return m_units;
    }

    /**
     * Is the ultrasonic enabled
     * @return true if the ultrasonic is enabled
     */
    public boolean isEnabled() {
        return m_enabled;
    }

    /**
     * Set if the ultrasonic is enabled
     * @param enable set to true to enable the ultrasonic
     */
    public void setEnabled(boolean enable) {
        m_enabled = enable;
    }
}

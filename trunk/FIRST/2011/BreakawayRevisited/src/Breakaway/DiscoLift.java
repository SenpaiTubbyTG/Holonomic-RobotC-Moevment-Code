/*
 * Class to control the lift on the 2011 Discobots LogoMotion Robot
 */

package Breakaway;

import edu.wpi.first.wpilibj.*;
import Utils.DiscoUtils;


/**
 *
 * @author JAG
 */
public class DiscoLift {
    private SpeedController m_liftMotor = null;
    private double m_liftSpeed = 0;
    private double m_defaultLiftSpeedUp = 0;
    private double m_defaultLiftSpeedDown = 0;
    private Encoder m_encoder = null;
    private boolean m_autoLiftControl = false;
    private int m_limitSwitches = 0;
    private DigitalInput m_lowerLimit;
    private DigitalInput m_upperLimit;

    public static class Position {

        /**
         * The integer value representing this enumeration
         */
        public final int value;
        public DigitalInput limitSwitch;
        public int encoderCount;
        static final int k0_val = 0;
        static final int k1_val = 1;
        static final int k2_val = 2;
        static final int k3_val = 3;
        static final int k4_val = 4;
        static final int k5_val = 5;
        static final int k6_val = 6;

        /**
         *  the lowest value for the lift
         */
        public static final Position k0 = new Position(k0_val);

        /**
         *  the lowest peg of the scoring grid value for the lift
         */
        public static final Position k1 = new Position(k1_val);

        /**
         *  the second lowest peg of the scoring grid value for the lift
         */
        public static final Position k2 = new Position(k2_val);
        /**
         *  the 3rd lowest peg of the scoring grid value for the lift
         */
        public static final Position k3 = new Position(k2_val);
        /**
         *  the 4th lowest peg of the scoring grid value for the lift
         */
        public static final Position k4 = new Position(k4_val);
        /**
         *  the 2nd highest peg of the scoring grid value for the lift
         */
        public static final Position k5 = new Position(k5_val);
        /**
         *  the highest peg of the scoring grid value for the lift
         */
        public static final Position k6 = new Position(k6_val);

        private Position(int value) {
            this.value = value;
        }

        public void setLimitSwitch(DigitalInput input) {
            limitSwitch = input;
        }

        public void setEncoderCount (int count) {
            encoderCount = count;
        }


    }

    /**
     * Constructor for a simple lift that doesn't use sensors
     * @param liftMotor
     */
    public DiscoLift (SpeedController liftMotor) {
        m_liftMotor = liftMotor;
        m_limitSwitches = 0;
    }

    /**
     * Constructor that includes using the encoder
     */
    public DiscoLift (SpeedController liftMotor, Encoder encoder) {
        m_liftMotor = liftMotor;
        m_encoder = encoder;
        m_limitSwitches = 0;
    }

    public DiscoLift (SpeedController liftMotor, DigitalInput lowerLimit, DigitalInput upperLimit) {
        m_liftMotor = liftMotor;
        m_limitSwitches = 2;
        m_lowerLimit = lowerLimit;
        m_upperLimit = upperLimit;

    }

    /**
     * Set the encoder count for a certain position on the lift
     * @param pos
     * @param encoderCount
     */
    public void setEncoderCount (Position pos, int encoderCount) {
        if (m_encoder != null) {
            pos.setEncoderCount(encoderCount);
        } else {
            DiscoUtils.debugPrintln("DiscoLift Error: Enocder not defined for lift.");
        }
    }

    /**
     * Associate a Digital Input with a certain position on the lift
     * @param pos
     * @param limitSwitch
     */
    public void setLimitSwitch (Position pos, DigitalInput limitSwitch){
        pos.setLimitSwitch(limitSwitch);
        m_limitSwitches++;
    }

    /**
     * Associate a position with an encoder count and a Digital input for a limit switch
     * @param pos
     * @param encoderCount
     * @param limitSwitch
     */
    public void setPosition (Position pos, int encoderCount, DigitalInput limitSwitch) {
        setEncoderCount(pos, encoderCount);
        setLimitSwitch(pos, limitSwitch);
    }

    /**
     * Set the default speed up and down for the lift
     * @param speedUp
     * @param speedDown
     */
    public void setDefaultSpeed (double speedUp, double speedDown){
        m_defaultLiftSpeedUp = speedUp;
        m_defaultLiftSpeedDown = speedDown;
    }

    /**
     * Sets the default speed used in liftUp and liftDown
     * Makes the down speed the negative of the up speed
     * @param speed
     */
    public void setDefaultSpeed (double speed) {
        setDefaultSpeed(speed, -speed);
    }

    /**
     * Manually Set the speed of the lift motor if you are in manual
     * Will not allow the motor to go past the limit switches if they are setup
     * @param speed
     */
    public void setSpeed (double speed){
        m_autoLiftControl = false;
        m_liftSpeed = speed;
        if (m_liftSpeed < 0 && (m_lowerLimit == null || m_lowerLimit.get() == false)) {
            m_liftMotor.set(m_liftSpeed);
        } else if (m_liftSpeed > 0 && (m_upperLimit == null || m_upperLimit.get() == false)){
            m_liftMotor.set(m_liftSpeed);
        } else {
            m_liftMotor.set(0);
            m_liftSpeed = 0;
        }

    }

    /**
     * Make the lift move up at the default lift up speed
     * useful for button activation
     */
    public void liftUp(){
        setSpeed(m_defaultLiftSpeedUp);
    }

    /**
     * Make the lift move down at the default lift down speed
     * Useful for button activation
     */
    public void liftDown() {
        setSpeed(m_defaultLiftSpeedDown);
    }

    /**
     * Check the current speed of the lift
     * @return the current lift speed
     */
    public double getLiftSpeed() {
        return m_liftSpeed;
    }

    /**
     * check the value of the lower limit
     * @return
     */
    public boolean getLowerLimit() {
        return m_lowerLimit.get();
    }

    /**
     * check the value of the upper limit
     * @return
     */
    public boolean getUpperLimit() {
        return m_upperLimit.get();
    }
}

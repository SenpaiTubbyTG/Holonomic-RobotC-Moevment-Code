/*
 * Class to control the lift on the 2011 Discobots LogoMotion Robot
 */

package DiscoLift;

import edu.wpi.first.wpilibj.*;
import Utils.DiscoUtils;


/**
 *
 * @author JAG
 */
public class DiscoLift {

    /**
     * Default values used for the lift
     */
    private SpeedController m_liftMotor = null;
    private double m_liftSpeed = 0;
    private double m_defaultLiftSpeedUp = 0;
    private double m_defaultLiftSpeedDown = 0;
    private DigitalInput m_lowerLimit = null;
    private DigitalInput m_upperLimit = null;

    /**
     * Constructor for a simple lift that doesn't have limit switches
     * @param liftMotor
     */
    public DiscoLift (SpeedController liftMotor) {
        m_liftMotor = liftMotor;
    }


    /**
     * Create a DiscoLift with lowerLimit and upperLimit
     * @param liftMotor
     * @param lowerLimit
     * @param upperLimit
     */
    public DiscoLift (SpeedController liftMotor, DigitalInput lowerLimit, DigitalInput upperLimit) {
        m_liftMotor = liftMotor;
        m_lowerLimit = lowerLimit;
        m_upperLimit = upperLimit;
        //if (Position.FullDown.isLimit()){

        //}
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
    public synchronized void set (double speed){
        m_liftSpeed = speed;
        if (m_liftSpeed < 0 && isLowerLimit() == false) {
            m_liftMotor.set(m_liftSpeed);
        } else if (m_liftSpeed > 0 && isUpperLimit() == false){
            m_liftMotor.set(m_liftSpeed);
        } else {
            m_liftSpeed = 0;
            m_liftMotor.set(0);   
        }
    }

    /**
     * Make the lift move up at the default lift up speed
     * useful for button activation
     */
    public void liftUp(){
        set(m_defaultLiftSpeedUp);
    }

    /**
     * Make the lift move down at the default lift down speed
     * Useful for button activation
     */
    public void liftDown() {
        set(m_defaultLiftSpeedDown);
    }

    /**
     * Check the current speed of the lift
     * @return the current lift speed
     */
    public synchronized double get() {
        return m_liftSpeed;
    }

    /**
     * check the value of the lower limit
     * @return
     */
    public boolean isLowerLimit() {
        if (m_lowerLimit != null) {
            return m_lowerLimit.get();
        } else {
            DiscoUtils.debugPrintln("Attempting to Check Lower Limit but Limit Switch Undefined");
            return false;
        }
    }

    /**
     * check the value of the upper limit
     * @return
     */
    public boolean isUpperLimit() {
        if (m_upperLimit != null) {
            return m_upperLimit.get();
        } else {
            DiscoUtils.debugPrintln("Attempting to Check Upper Limit but Limit Switch Undefined");
            return false;
        }
    }

    /**
     * Write out the PID value as seen in the PIDOutput base object.
     *
     * @param output Write out the PWM value as was found in the PIDController
     */
    public void pidWrite(double output) {
        set(output);
    }
}

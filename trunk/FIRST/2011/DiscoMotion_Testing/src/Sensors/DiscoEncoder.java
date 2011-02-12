/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Sensors;

import edu.wpi.first.wpilibj.*;
import java.util.TimerTask;

/**
 *
 * @author Nelson
 */
public class DiscoEncoder extends Encoder implements PIDSource {

    public static final double kDefaultPeriod = .005;
    private double m_period = kDefaultPeriod;
    //private double oldTime = 0.0;
    private boolean m_enabled = false;
    private double m_oldPosition = 0.0;
    private double m_velocity = 0.0;
    private double m_integratedDistance = 0.0;
    private PIDSourceParameter m_pidSource = PIDSourceParameter.kRate;
    private double m_intialPosition = 0.0;
    private CounterBase.EncodingType m_encodingType;
    java.util.Timer m_controlLoop;

    private class EncoderRateTask extends TimerTask {

        private DiscoEncoder m_encoder;

        public EncoderRateTask(DiscoEncoder encoder) {
            if (encoder == null) {
                throw new NullPointerException("Given DiscoEncoder was null");
            }
            m_encoder = encoder;
        }

        public void run() {
            m_encoder.calculateRate();
        }
    }

    public void init() {
        start();
        reset();
        m_enabled = true;
        m_controlLoop = new java.util.Timer();
        m_controlLoop.schedule(new EncoderRateTask(this), 0L, (long) (m_period * 1000));
    }

    public DiscoEncoder(final int aChannel, final int bChannel, boolean reversed,
            CounterBase.EncodingType x) {
        super(aChannel, bChannel, reversed, x);
        m_encodingType = x;
        m_oldPosition = getDistance();
    }

    private void calculateRate() {   //delay in seconds
        /*double newTime = Timer.getFPGATimestamp();
        double timeDiff = newTime - oldTime;*/
        boolean enabled = m_enabled;

        if (enabled) {
            synchronized (this) {
                double newPosition = getDistance();
                m_velocity = (newPosition - m_oldPosition) / m_period;//timeDiff;
                m_oldPosition = newPosition;
                m_integratedDistance += m_velocity * m_period;
                //oldTime = newTime;
            }
        }
    }

    /**
     * Free the EncoderRateTask
     */
    protected void free() {
        m_controlLoop.cancel();
        m_controlLoop = null;
    }

    /**
     * Return the velocity in inches per sec
     * @return
     */
    public synchronized double pidGet() {
        //return feet per sec

        switch (m_pidSource.value) {
        case 0:
            return getRawPosition();
        case 1:
            return m_velocity;
        default:
            return 0.0;
        }
    }

    /**
     * returns the velocity in inches per sec
     * @return
     */
    public synchronized double getRate() {
        return m_velocity;
    }

    /**
     * Get the integrated distance from the calculated velocity
     * @return
     */
    public synchronized double getIntegratedDistance() {
        return m_integratedDistance;
    }

    /**
     * Return the position in encoder ticks, used to mimic CANJaguar in PWMJaguar
     */
    public double getRawPosition() {
        switch (m_encodingType.value) {
            case 0:
                return super.getRaw() * 1.0 + m_intialPosition;
            case 1:
                return super.getRaw() * 0.5 + m_intialPosition;
            case 2:
                return super.getRaw() * 0.25 + m_intialPosition;
            default:
                //This is never reached, EncodingType enum limits values
                return 0.0;
        }
    }

    public void setPosition(double position){
        reset();
        m_intialPosition = position;
    }

    /**
     * Start the encoder and velocity calculations
     */
    public void start() {
        m_enabled = true;
        super.start();
    }

    /**
     * Stop the encoder and velocity calculations
     */
    public void stop() {
        m_enabled = false;
        super.stop();
    }

    /**
     * Reset the encoder and velocity calculations
     */
    public void reset() {
        m_oldPosition = 0.0;
        m_integratedDistance = 0.0;
        super.reset();
    }

    /**
     * Set which parameter of the encoder you are using as a process control variable.
     *
     * @param pidSource An enum to select the parameter.
     */
    public void setPIDSourceParameter(PIDSourceParameter pidSource) {
	m_pidSource = pidSource;
    }
}

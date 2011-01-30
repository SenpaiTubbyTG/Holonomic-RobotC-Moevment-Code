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

    public static final double kDefaultPeriod = .05;
    private double m_period = kDefaultPeriod;
    //private double oldTime = 0.0;
    private boolean m_enabled = false;
    private double m_oldPosition = 0.0;
    private double m_velocity = 0.0;
    private double m_integratedDistance = 0.0;
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

    public DiscoEncoder(final int aSlot, final int bSlot, boolean reversed,
            CounterBase.EncodingType x) {
        super(aSlot, bSlot, reversed, x);
        //oldTime = Timer.getFPGATimestamp();
        m_oldPosition = getDistance();
    }

    public DiscoEncoder(final int aSlot, final int aChannel,
            final int bSlot, final int bChannel, final int indexSlot,
            final int indexChannel,
            boolean reverseDirection) {
        super(aSlot, aChannel, bSlot, bChannel, indexSlot, indexChannel, reverseDirection);
        //oldTime = Timer.getFPGATimestamp();
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
     * Return the velocity /12 for ft per sec
     * @return
     */
    public synchronized double pidGet() {
        //return feet per sec
        return m_velocity;
    }

    /**
     * returns the velocity /12 for ft per sec
     * @return
     */
    public synchronized double getRate() {
        return m_velocity;
    }

    /**
     * Get the integrated distance from the calculated velocity
     * @return
     */
    public synchronized double getIntDistance() {
        return m_integratedDistance;
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

}

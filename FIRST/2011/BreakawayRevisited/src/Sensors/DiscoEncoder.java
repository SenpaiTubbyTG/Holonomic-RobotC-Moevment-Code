/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package Sensors;

import edu.wpi.first.wpilibj.*;
import java.util.TimerTask;
import Utils.DiscoUtils;

/**
 *
 * @author Nelson
 */
public class DiscoEncoder extends Encoder {

    public static final double kDefaultPeriod = .05;
    private double m_period = kDefaultPeriod;
    double oldTime = 0.0;
    double oldPosition = 0.0;
    double velocity = 0.0;
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
            Timer.delay(0.01);
        }
    }

    public void init() {
        start();
        reset();
        m_controlLoop = new java.util.Timer();
        m_controlLoop.schedule(new EncoderRateTask(this), 0L, (long) (m_period * 1000));
    }

    public DiscoEncoder(final int aSlot, final int bSlot, boolean reversed,
            CounterBase.EncodingType x) {
        super(aSlot, bSlot, reversed, x);
        oldTime = Timer.getFPGATimestamp();
        oldPosition = getDistance();
    }

    public DiscoEncoder(final int aSlot, final int aChannel,
            final int bSlot, final int bChannel, final int indexSlot,
            final int indexChannel,
            boolean reverseDirection) {
        super(aSlot, aChannel, bSlot, bChannel, indexSlot, indexChannel, reverseDirection);
        oldTime = Timer.getFPGATimestamp();
        oldPosition = getDistance();
    }

    public void calculateRate() {   //delay in seconds
        double newTime = Timer.getFPGATimestamp();
        double timeDiff = newTime - oldTime;
        double newPosition = getDistance();
        synchronized (this) {
            double velocity = (newPosition - oldPosition) / timeDiff;
            oldPosition = newPosition;
            oldTime = newTime;
        }
    }

    /**
     * Free the EncoderRateTask
     */
    protected void free() {
        m_controlLoop.cancel();
        m_controlLoop = null;
    }

    public synchronized double getRate() {
        return velocity;
    }
}

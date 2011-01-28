/*
 * 2011 Team 2587 Discobots - DiscoLift Class to control the lift in LogoMotion
 */

package DiscoLift;

import edu.wpi.first.wpilibj.*;

/**
 * Defines the LiftController Class
 * @author JAG
 */
public class LiftController {

    private Lift m_lift = null;
    private Encoder m_encoder = null;
    private int m_liftHeight = 0;
    private int m_maxHeight = 100;

    /**
     *
     * @param lift
     * @param encoder
     */
    public LiftController(Lift lift, Encoder encoder) {
        m_lift = lift;
        m_encoder = encoder;

    }

    /**
     * Reset the encoder used for the lift controller
     */
    private void resetEncoder(){
        m_encoder.reset();
        m_liftHeight = 0;
    }

    /**
     * Set the height of the encoder
     */
    private void setEncoderToMax(){
        m_encoder.reset();
        m_liftHeight = m_maxHeight;
    }

}

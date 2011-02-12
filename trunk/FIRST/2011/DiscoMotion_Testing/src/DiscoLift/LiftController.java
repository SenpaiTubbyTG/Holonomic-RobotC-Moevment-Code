/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DiscoLift;

import Sensors.DiscoEncoder;

/**
 *
 * @author JAG
 */
public class LiftController {

    private DiscoLift m_discoLift = null;
    private DiscoEncoder m_encoder = null;

    public LiftController(DiscoLift lift, DiscoEncoder encoder) {
        m_discoLift = lift;
        m_encoder = encoder;
    }





}

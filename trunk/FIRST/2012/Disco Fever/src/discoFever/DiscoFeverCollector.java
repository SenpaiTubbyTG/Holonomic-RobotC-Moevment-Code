/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package discoFever;

import edu.wpi.first.wpilibj.Jaguar;

/**
 *
 * @author mdouglass101
 */
public class DiscoFeverCollector {
    Jaguar m_bfCollector;
    Jaguar m_bbCollector;
    Jaguar m_tfCollector;
    Jaguar m_tbCollector;
    
    public DiscoFeverCollector(Jaguar m_lfCol, Jaguar m_lbCol, Jaguar m_rfCol, Jaguar m_rbCol){
        m_bfCollector = m_lfCol;
        m_bbCollector = m_lbCol;
        m_tfCollector = m_rfCol;
        m_tbCollector = m_rbCol;
    }
    
    
}

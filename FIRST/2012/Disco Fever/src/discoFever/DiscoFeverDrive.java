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
public class DiscoFeverDrive {
    
    public static Jaguar m_flDrive;
    public static Jaguar m_frDrive;
    public static Jaguar m_blDrive;
    public static Jaguar m_brDrive;
    
    public DiscoFeverDrive(Jaguar m_flDrive, Jaguar m_frDrive, Jaguar m_blDrive, Jaguar m_brDrive){
        this.m_flDrive = m_flDrive;
        this.m_frDrive = m_frDrive;
        this.m_blDrive = m_blDrive;
        this.m_brDrive = m_brDrive;
    }
}


/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package discoFever;

import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.Joystick.AxisType;

/**
 *
 * @author mdouglass101
 */
public class DiscoFeverDrive {
    
    private Jaguar m_frontLeft, m_frontRight, m_backLeft, m_backRight;
    
    public DiscoFeverDrive(Jaguar fr, Jaguar fl, Jaguar bl, Jaguar br){
        m_frontLeft = fl;
        m_frontLeft = fr;
        m_backLeft = bl;
        m_backRight = br;
    }
    
    public void tankDrive(){
        m_frontLeft.set(Hardware.m_leftStick.getY());
        m_backLeft.set(Hardware.m_leftStick.getY());
        
        m_frontRight.set(Hardware.m_rightStick.getY());
        m_backRight.set(Hardware.m_rightStick.getY());
    }
    
    public void drive(int speed){
        m_frontLeft.set(speed);
        m_backLeft.set(speed);
        m_frontRight.set(speed);
        m_backRight.set(speed);
    }
}


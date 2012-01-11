/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package discoFever;

import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.RobotDrive;

/**
 *
 * @author mdouglass101
 */
public class DiscoFeverDrive {
    
    public static RobotDrive m_front;
    public static RobotDrive m_back;
    
    public DiscoFeverDrive(int flChannel, int frChannel, int blChannel, int brChannel){
        m_front = new RobotDrive(flChannel, frChannel);
        m_back  = new RobotDrive(blChannel, brChannel);
    }
    
    public void tankDrive(){
        m_front.tankDrive(HardWare.m_leftStick, HardWare.m_rightStick);
    }
}


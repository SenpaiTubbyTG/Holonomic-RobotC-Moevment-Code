package org.discobots.laserDragon;

import edu.wpi.first.wpilibj.Joystick;

/**
 *
 * @author mrdouglass
 */
public class ThreeJoystickControl implements RobotControlSystem{

    private Joystick m_leftStick, m_rightStick, m_shootStick;
    
    public ThreeJoystickControl(int left, int right, int shoot){
        m_leftStick = new Joystick(left);
        m_rightStick = new Joystick(right);
        m_shootStick = new Joystick(shoot);
    }
    
    public int mouthInput(){
        if(m_shootStick.getRawButton(2)){
            return FORWARD;
        } else if(m_shootStick.getRawButton(3)){
            return BACKWARD;
        } else {
            return NONE;
        }
    }

    public int indexerInput(){
        if(m_shootStick.getRawButton(1) && m_shootStick.getRawButton(4)){
            return SEND;
        } else if(m_shootStick.getRawButton(4)){
            return FORWARD;
        } else if(m_shootStick.getRawButton(1)){
            return BACKWARD;
        } else {
            return NONE;
        }
    }

    public int shooterEnableInput(){
        if(m_shootStick.getRawButton(5)){
            return SHOOTER_ENABLE;
        } else {
            return NONE;
        }
    }

    public int shooterSpeedInput(){
        if(m_shootStick.getRawButton(8)){
            return SHOOTER_DEC;
        } else if(m_shootStick.getRawButton(9)){
            return SHOOTER_INC;
        } else {
            return NONE;
        }
    }

    public int hoodTiltInput(){
        if(m_shootStick.getRawButton(10)){
            return FORWARD;
        } else if(m_shootStick.getRawButton(11)){
            return BACKWARD;
        } else {
            return NONE;
        }
    }

    public int whackerInput(){
        if(m_rightStick.getRawButton(1)){
            return FORWARD;
        } else if(m_leftStick.getRawButton(1)){
            return BACKWARD;
        } else {
            return NONE;
        }
    }
    
    public double rightDriveInput(){
        return -m_rightStick.getRawAxis(2);
    }
    
    public double leftDriveInput(){
        return -m_leftStick.getRawAxis(2);
    }
}
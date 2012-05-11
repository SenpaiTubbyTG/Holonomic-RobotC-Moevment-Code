/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package edu.wpi.first.wpilibj.templates;


import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.SimpleRobot;

public class LaserDragon extends SimpleRobot {
    
    Joystick m_leftStick, m_rightStick;
    RobotDrive drive;
    
    
    public LaserDragon(){
        m_leftStick = new Joystick(1);
        m_rightStick = new Joystick(2);
        drive = new RobotDrive(9,10,7,8); // these values need to be checked
    }
    
    public void autonomous() {
        
    }

    public void operatorControl() {
        while(isEnabled()){
            drive.tankDrive(m_leftStick, m_rightStick);
        }
    }
}

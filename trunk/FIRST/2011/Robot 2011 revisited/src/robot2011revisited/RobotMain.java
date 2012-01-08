/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package robot2011revisited;
import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Gyro;


/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class RobotMain extends SimpleRobot {

    Jaguar m_frontLeft, m_frontRight, m_backLeft, m_backRight; // motors
    Joystick m_leftStick, m_rightStick, m_armStick;
    HolonomicDrive m_holonomicDrive;
    Gyro m_gyro;

    public RobotMain(){
        super();
        m_frontLeft = new Jaguar(1);
        m_frontRight = new Jaguar(2);
        m_backLeft = new Jaguar(3);
        m_backRight = new Jaguar(4);
        m_leftStick = new Joystick(1);
        m_rightStick = new Joystick(2);
        m_armStick = new Joystick(3);
        m_gyro = new Gyro(1);
        
        m_holonomicDrive = new HolonomicDrive(m_frontLeft, m_frontRight,
                                              m_backLeft, m_backRight,
                                              m_leftStick, m_rightStick,
                                              m_gyro);


        getWatchdog().kill();
    }

    // This function is called once each time the robot enters autonomous mode.
    public void autonomous() {
        
    }

    // This function is called when robot enters autonomous
    public void operatorControl() {
        while(isOperatorControl() && isEnabled()){
            m_holonomicDrive.drive();
        }
    }
}
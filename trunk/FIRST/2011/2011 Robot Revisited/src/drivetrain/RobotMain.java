
package drivetrain;
import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Gyro;
import utilities.RobotUtil;

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
    }

    // This function is called once each time the robot enters autonomous mode.
    /*
     * The autonomous will perform a square without turning
     */
    public void autonomous() {
        getWatchdog().setEnabled(false);
        RobotUtil.setTaskDuration(2000);
        while(!RobotUtil.taskDurationElapsed())
            m_holonomicDrive.holonomicDrive(Math.PI/2.0, 1.0, 0, 0);
        RobotUtil.setTaskDuration(2000);
        while(!RobotUtil.taskDurationElapsed())
            m_holonomicDrive.holonomicDrive(Math.PI, 1.0, 0, 0);
        RobotUtil.setTaskDuration(2000);
        while(!RobotUtil.taskDurationElapsed())
            m_holonomicDrive.holonomicDrive(3.0*Math.PI/2.0, 1.0, 0, 0);
        RobotUtil.setTaskDuration(2000);
        while(!RobotUtil.taskDurationElapsed())
            m_holonomicDrive.holonomicDrive(0, 1.0, 0, 0);
        m_holonomicDrive.holonomicDrive(0,0,0,0);
        getWatchdog().setEnabled(true);
    }

    // This function is called when robot enters autonomous
    public void operatorControl() {
        while(isOperatorControl() && isEnabled()){
            m_holonomicDrive.operatorDrive();
            getWatchdog().feed();
        }
    }
}

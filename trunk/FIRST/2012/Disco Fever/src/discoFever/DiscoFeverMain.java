package discoFever;


import edu.wpi.first.wpilibj.IterativeRobot;

public class DiscoFeverMain extends IterativeRobot {
    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    private static TargetTracker m_tracker;
    
    public void robotInit() {
        m_tracker = new TargetTracker(Hardware.m_camera);
        Hardware.cameraToDriversStation();
    }

    /**
     * This function is called periodically during autonomous
     */
    
    public void autonomousContinuous(){
        
    }

    /**
     * This function is called periodically during operator control
     */
    public void teleopContinuos() {
        
    }
}

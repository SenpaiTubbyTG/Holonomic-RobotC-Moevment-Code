/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DriveControllers;

import DriveControllers.DiscoDriveConverter.Output;
import Sensors.MaxbotixSonar;

/**
 *
 * @author JAG
 */
public class SonarController {

    private DiscoDriveConverter m_driveConverter = null;
    private MaxbotixSonar m_sonar = null;
    private SonarPositionPID m_pid = null;

     public SonarController(DiscoDriveConverter driveConverter, MaxbotixSonar sonar, double p, double i, double d) {

        m_driveConverter = driveConverter;
        m_sonar = sonar;
        m_pid = new SonarPositionPID(p, i, d, m_sonar, m_driveConverter, .1);
    }

    public SonarController(MaxbotixSonar sonar, double p, double i, double d) {
        this(new DiscoDriveConverter(0.0, 0.0, 0.0, Output.kSpeed, -1, 1), sonar, p, i, d);
    }

    public void setDistance(double distance) {
        m_pid.setSetpoint(distance);
    }
    
    public void setPID(double p, double i, double d){
        m_pid.setPID(p, i, d);
    }
    
    public double getSpeed(){
       return m_driveConverter.getSpeed();
    }

}

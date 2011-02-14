/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DriveControllers;

import Sensors.MaxbotixSonar;
import edu.wpi.first.wpilibj.PIDOutput;

/**
 *
 * @author JAG
 */
public class SonarController implements PIDOutput{

    private MaxbotixSonar m_sonar = null;
    private SonarPositionPID m_pid = null;
    private double output = 0.0;

    public SonarController(MaxbotixSonar sonar, double p, double i, double d) {
        m_sonar = sonar;
        m_pid = new SonarPositionPID(p, i, d, m_sonar, this, .1);
    }

    public void pidWrite(double pidIn){
        output = pidIn;
    }

    public void setOutputRange(double min, double max) {
        m_pid.setOutputRange(min, max);
    }

    public void setDistance(double distance) {
        m_pid.setSetpoint(distance);
    }
    
    public void setPID(double p, double i, double d){
        m_pid.setPID(p, i, d);
    }
    
    public double getSpeed(){
       return output;
    }

    public void enable() {
        m_pid.enable();
    }

    public void disable() {
        m_pid.disable();
    }

    public double getError() {
        return m_pid.m_error;
    }

    public double getResult() {
        return m_pid.m_result;
    }

    public double getP() {
        return m_pid.m_P;
    }
    public double getI() {
        return m_pid.m_I;
    }
    public double getD() {
        return m_pid.m_D;
    }
}

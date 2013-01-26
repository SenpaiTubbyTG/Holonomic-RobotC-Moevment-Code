/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.subsystems;

import disco.HW;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 * @author Developer
 */
public class Collector extends Subsystem {
    private Victor m_motor1;
    private Victor m_motor2;
    private boolean inverted=false;
    
    public Collector(){
        super("Collector");
        m_motor1=new Victor(HW.Collect1Slot,HW.Collect1Channel);
        m_motor2=new Victor(HW.Collect2Slot,HW.Collect2Channel);
        
    }

    public void initDefaultCommand() {
       //do nothing
    }
    
    public double getPower(){
        return inverted ? -1*m_motor1.get() : m_motor1.get();
    }
    
    public void setPower(double power){
        power= inverted ? -1*power : power;
        m_motor1.set(power);
        m_motor2.set(-1*power);
    }
}

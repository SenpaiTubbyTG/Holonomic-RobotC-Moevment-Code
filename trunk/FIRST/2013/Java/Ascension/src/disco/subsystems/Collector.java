/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.subsystems;

import disco.HW;
import disco.commands.collector.VariableCollector;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 * @author Developer
 */
public class Collector extends Subsystem {
    private Talon m_motor1;
    private Talon m_motor2;
    private Talon m_motor3;
    private Talon m_motor4;
    private boolean inverted=false;

    public Collector(){
        super("Collector");
        m_motor1=new Talon(HW.Collect1Slot,HW.Collect1Channel);
        m_motor2=new Talon(HW.Collect2Slot,HW.Collect2Channel);
        m_motor3=new Talon(HW.Collect3Slot,HW.Collect3Channel);
        m_motor4=new Talon(HW.Collect4Slot,HW.Collect4Channel);

    }

    public void initDefaultCommand() {
       setDefaultCommand(new VariableCollector());
    }

    public double getPower(){
        return inverted ? -1*m_motor1.get() : m_motor1.get();
    }

    public void setPower(double power){
        power= inverted ? -1*power : power;
        m_motor1.set(power);
        m_motor3.set(power);
        m_motor2.set(-1*power);
        m_motor4.set(-1*power);
    }
}

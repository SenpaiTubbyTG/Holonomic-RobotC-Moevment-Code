/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.subsystems;

import disco.practice.HW;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.Subsystem;


public class Indexer extends Subsystem {
    private Victor m_indexerMotor;
    public static final double UP=0.5;
    public static final double DOWN=-0.5;
    public static final double STOP=0.0;

    public Indexer(){
	super("Indexer");
	m_indexerMotor=new Victor(HW.indexerSlot,HW.indexerChannel);
    }


    public void initDefaultCommand() {
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
	//This subsystem should do nothing in general.
    }

    public void setIndexer(double power){
	m_indexerMotor.set(power);
    }
}

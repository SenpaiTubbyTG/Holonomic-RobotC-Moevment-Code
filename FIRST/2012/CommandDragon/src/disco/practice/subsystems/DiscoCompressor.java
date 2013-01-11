/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.practice.subsystems;

import disco.practice.HW;
import disco.practice.commands.Pneumatics.CompressorStart;
import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.command.Subsystem;


public class DiscoCompressor extends Subsystem {
    Compressor m_compressor;

    public DiscoCompressor(){
	super("Compressor");
	m_compressor=new Compressor(	HW.pressureSwitchSlot,HW.pressureSwitchChannel,
					HW.compressorSlot,HW.compressorChannel);
    }

    public void initDefaultCommand() {
	// Set the default command for a subsystem here.
	//nothing
    }

    public boolean getEnabled(){
	return m_compressor.enabled();
    }

    public void set(boolean val){
	if(val) {
	    m_compressor.start();
	}
	else {
	    m_compressor.stop();
	}
    }

    public boolean getPressureSwitch(){
	return m_compressor.getPressureSwitchValue();
    }


}
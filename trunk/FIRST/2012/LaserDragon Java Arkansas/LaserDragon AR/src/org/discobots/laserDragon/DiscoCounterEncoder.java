package org.discobots.laserDragon;

import edu.wpi.first.wpilibj.Counter;
import edu.wpi.first.wpilibj.PIDSource;

/**
 *
 * @author mrdouglass
 */
public class DiscoCounterEncoder extends Counter implements PIDSource{
    
    private double cyclesPerRev;
    
    public DiscoCounterEncoder(int slot, int channel, double a){
        super(slot, channel);
        cyclesPerRev = a;
    }
    
    public double pidGet(){
        return getRPM();
    }
    
    public double getRPM(){
        return 60.0/getPeriod()/cyclesPerRev;
    }
}

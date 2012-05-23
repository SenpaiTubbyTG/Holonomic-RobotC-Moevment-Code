
package org.discobots.laserDragon;

import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.PIDSource;
import edu.wpi.first.wpilibj.Victor;

class ShooterDrive implements PIDOutput{
    Victor m_shooter1, m_shooter2;
    public ShooterDrive(Victor one, Victor two){
        m_shooter1 = one;
        m_shooter2 = two;
    }
    public void pidWrite(double output) {
        m_shooter1.set(output);
        m_shooter2.set(output);
    }
}

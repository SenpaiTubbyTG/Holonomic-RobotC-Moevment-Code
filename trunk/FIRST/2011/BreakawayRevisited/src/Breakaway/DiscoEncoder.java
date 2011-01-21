/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Breakaway;

import edu.wpi.first.wpilibj.*;
/**
 *
 * @author Nelson
 */
public class DiscoEncoder extends Encoder {

    double oldTime = 0.0;
    double oldPosition = 0.0;
    double testDistance = 0.0;
    double integratedDistance = 0.0;

    public DiscoEncoder(final int aSlot, final int bSlot, boolean reversed,
                                            CounterBase.EncodingType x) {
        super(aSlot, bSlot, reversed, x);
        oldTime = Timer.getFPGATimestamp();
        oldPosition = getDistance();
    }

    public double getRate(double delay) {   //delay in seconds
        if((Timer.getFPGATimestamp() - oldTime) > delay) {
            double newTime = Timer.getFPGATimestamp();
            double timeDiff = newTime - oldTime;
            double newPosition = getDistance();
            double velocity = (newPosition - oldPosition) / timeDiff;
            testDistance += velocity * timeDiff;
            integratedDistance += getRate() * timeDiff;
            oldPosition = newPosition;
            oldTime = newTime;
            return velocity;
        }
        else
            return 0.0;
    }

    public double getTestDistance() {
        return testDistance;
    }

    public double getIntegratedDistance() {
        return integratedDistance;
    }
}

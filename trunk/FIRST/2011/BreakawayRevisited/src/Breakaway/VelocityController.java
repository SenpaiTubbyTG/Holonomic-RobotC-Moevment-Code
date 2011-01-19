package Breakaway;

import Utils.Tuple;
import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Nelson
 */
public class VelocityController {

    double ki;
    double iterm;
    double[] velocityOutput;   //index will not be used for greater readibility
    int resolution;
    Encoder encoder;
    Jaguar motor;

    public VelocityController(Encoder e, Jaguar m, double k, int res) {
        encoder = e;
        motor = m;
        ki = k;
        resolution = res;
        velocityOutput = new double[res + 1];
    }

    public void initOutputData() {
        for (int x = 1; x <= resolution; x++) {
            velocityOutput[x] = test(x * 200.0 / resolution);
        }
    }

    private double test(double speed) {
        double initDist = encoder.getDistance();
        motor.set(speed);
        Timer.delay(1000);
        double finalDist = encoder.getDistance();
        motor.set(0.0);
        double distance = (finalDist - initDist) / 94;  //94 = scaling facto ticks-->inches
        return distance;    //also velocity in inches/sec because sampling period was 1 sec
    }

    private double velocityToOutput(double velocity) {
        double output = 0.0;
        //TODO, dependent on experimental data from velocityOutput
        return output;
    }

    private Tuple adjustVelocity(double goalVelocity, double oldDist, double oldTime) {
        double newDist = encoder.getDistance();
        double newTime = Timer.getFPGATimestamp();

        double distDiff = newDist - oldDist;
        double timeDiff = newTime - oldTime;

        double velocity = distDiff / timeDiff;
        double error = goalVelocity - velocity;

        iterm += timeDiff * error;

        double ffterm = velocityToOutput(goalVelocity);
        double output = ffterm + (ki * iterm);

        motor.set(DiscoUtils.limit(output));

        return new Tuple(distDiff, Timer.getFPGATimestamp());
    }

    public void controller(double goalVelocity, double goalDistance) {  //distance in inches
        double encoderCount = goalDistance * 94;
        iterm = 0;
        double distTraveled = 0;

        double ffterm = velocityToOutput(goalVelocity);

        double oldDist = encoder.getDistance();
        double oldTime = Timer.getFPGATimestamp();

        motor.set(ffterm);

        Tuple currentData;

        while (distTraveled <= goalDistance) {
            Timer.delay(30);
            currentData = adjustVelocity(goalVelocity, oldDist, oldTime);
            distTraveled += currentData.dist;
            oldTime = currentData.time;
        }
        motor.set(0.0);
    }
}

package Breakaway;

import Utils.Tuple;
import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Nelson
 */
public class VelocityController {

    final double ki = 0.02;
    double iterm = 0.0;
    final double itermMax = 20;
    public double goalVelocity;
    //final double[] velocityOutput =
    //int resolution = 20;
    Encoder encoder;
    Jaguar motor;
    double oldDist;
    double oldTime;

    double avgDistStart;
    double avgTimeStart;

    boolean avgInit = false;

    public VelocityController(Encoder e, Jaguar m) {
        encoder = e;
        motor = m;
    }

    /*the following two methods are for collecting data for setting up velocityToOutput
    public void initOutputData() {
    for (int x = 0; x <= resolution; x++) {
    velocityOutput[x] = test((x * 200.0 / resolution) - 100.0);
    }
    }

    private double test(double speed) {
    double initDist = encoder.getDistance();
    motor.set(speed / 200);
    Timer.delay(1.0);
    double finalDist = encoder.getDistance();
    motor.set(0.0);
    double distance = finalDist - initDist;  //94 = scaling facto ticks-->inches
    DiscoUtils.debugPrintln((speed) + "\t-->\t" + distance);
    return distance;    //also velocity in inches/sec because sampling period was 1 sec
    }*/
    private double velocityToOutput(double velocity) {
        double ffterm = 0.0;
        if (velocity <= -100) {
            ffterm = -0.80;
        } else if (velocity <= -75) {
            ffterm = -0.60;
        } else if (velocity <= -40) {
            ffterm = -0.40;
        } else if (velocity <= -10) {
            ffterm = -0.20;
        } else if (velocity == 0.0) {
            ffterm = 0.0;
        } else if (velocity <= 8) {
            ffterm = 0.20;
        } else if (velocity <= 40) {
            ffterm = 0.40;
        } else if (velocity <= 75) {
            ffterm = 0.60;
        } else if (velocity <= 100) {
            ffterm = 0.80;
        }
        //DiscoUtils.debugPrintln("velocityToOutput result: " + ffterm);
        return ffterm;
    }

    private void adjustVelocity(double goalVelocity, double oldDist, double oldTime) {
        double newDist = encoder.getDistance();
        double newTime = Timer.getFPGATimestamp();

        double distDiff = newDist - oldDist;
        double timeDiff = newTime - oldTime;

        double velocity = distDiff / timeDiff;
        DiscoUtils.debugPrintln("adjustVelocity velocity: " + velocity);
        double error = goalVelocity - velocity;
        DiscoUtils.debugPrintln("error: " + error);
        if (Math.abs(iterm) < itermMax) {
            iterm += (timeDiff * error);
        }
        /* for average rate; not working at present
         if(Math.abs(error) < 1.0 && !avgInit) {
            avgTimeStart = Timer.getFPGATimestamp();
            avgDistStart = encoder.getDistance();
            avgInit = true;
        }*/
            
        DiscoUtils.debugPrintln("iterm: " + iterm);
        double ffterm = velocityToOutput(goalVelocity);
        double output = ffterm + (ki * iterm);
        motor.set(DiscoUtils.limit(output));
        DiscoUtils.debugPrintln("Final Output: " + output);
    }

    public boolean controller() {  //distance in inches
        //returns true if it ran adjustVelocity, false if it does nothing
        //double distTraveled = 0;
        if ((Timer.getFPGATimestamp() - oldTime) > 0.03) {
            adjustVelocity(goalVelocity, oldDist, oldTime);
            //distTraveled += currentData.dist;
            oldTime = Timer.getFPGATimestamp();
            oldDist = encoder.getDistance();
            DiscoUtils.debugPrintln("Average Rate: " + (oldDist - avgDistStart)/(oldTime - avgTimeStart));
            return true;
        }
        else
            return false;
    }

    public void setGoalVelocity(double newVelocity) {
        goalVelocity = newVelocity;
    }

    public void initialize() {
        oldDist = encoder.getDistance();
        oldTime = Timer.getFPGATimestamp();
    }
}

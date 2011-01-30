package DriveControllers;

import Utils.DiscoUtils;
import Sensors.*;
import edu.wpi.first.wpilibj.*;
import java.util.TimerTask;

/**
 *
 * @author Nelson
 */
public class VelocityController {

    final double ki = 0.06;
    public double iterm = 0.0;
    final double itermMax = 15.0;
    public double goalVelocity;
    //final double[] velocityOutput =
    //int resolution = 20;
    DiscoEncoder encoder;
    Jaguar motor;
    //double oldDist;
    double oldTime;
    boolean reversed = false;
    double output = 0.0;
    //double distTraveled;
    //double goalDistance = 0.0;
    boolean enabled = false;

    //boolean avgInit = false;
    public VelocityController(DiscoEncoder e, Jaguar m) {
        encoder = e;
        motor = m;
    }

    public VelocityController(DiscoEncoder e, Jaguar m, boolean r) {
        encoder = e;
        motor = m;
        reversed = r;
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
        //DiscoUtils.debugPrintln("Feed-forward term: " + ffterm);
        return ffterm;
    }
    public double velocity;
    public double error;

    private double adjustVelocity(double goalVelocity, double oldTime) {
        double timeDiff = (Timer.getFPGATimestamp() - oldTime);
        velocity = encoder.getRate();
        //DiscoUtils.debugPrintln("getRate: " + velocity);
        error = goalVelocity - velocity;
        if (iterm + (timeDiff * error) < itermMax) {
            iterm += (timeDiff * error);
        }
        //DiscoUtils.debugPrintln("error: " + error);
        //DiscoUtils.debugPrintln("iterm: " + iterm);
        //distTraveled += distDiff;
        //double distDiff = (encoder.getDistance() - oldDist);
        double result;
        if (reversed) {
            result = (velocityToOutput(goalVelocity) + (ki * iterm)) * -1;
        } else {
            result = (velocityToOutput(goalVelocity) + (ki * iterm));
        }
        motor.set(result);
        return result;
    }

    public void controller() {  //distance in inches
        if (enabled) {
            if ((Timer.getFPGATimestamp() - oldTime) > 0.1) {
                output = adjustVelocity(goalVelocity, oldTime);
                oldTime = Timer.getFPGATimestamp();
                //oldDist = encoder.getDistance();
            }
        }
    }

    public void setGoalVelocity(double newVelocity) {
        goalVelocity = newVelocity;
    }

    /*public void setGoalDistance(double newGoalDistance) {
    goalDistance = newGoalDistance;
    distTraveled = 0.0;
    }*/
    public void init() {
        //oldDist = encoder.getDistance();
        oldTime = Timer.getFPGATimestamp();
        goalVelocity = 0.0;
        //goalDistance = 0.0;
        //distTraveled = 0.0;
        iterm = 0.0;
        enable();
    }

    public void enable() {
        enabled = true;
    }

    public void disable() {
        enabled = false;
        motor.set(0.0);
    }

    public void setReversed(boolean r) {
        reversed = r;
    }
}

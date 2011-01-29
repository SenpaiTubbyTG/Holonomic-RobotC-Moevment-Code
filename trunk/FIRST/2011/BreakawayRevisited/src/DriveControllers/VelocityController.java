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

    public static final double kDefaultPeriod = .05;
    private double m_period = kDefaultPeriod;
    private final double kp = 1.0;
    private final double ki = 0.02;
    double iterm = 0.0;
    private double goalVelocity = 0.0;
    private DiscoEncoder encoder;
    private Jaguar motor;
    private boolean reversed = false;
    private double output = 0.0;
    //private double oldDist;
    //private double distTraveled;
    //private double goalDistance = 0.0;
    private double velocity = 0.0;
    java.util.Timer m_controlLoop;

    /**
     * 
     */
    private class VelocityControllerTask extends TimerTask {

        private VelocityController m_velocityController;

        public VelocityControllerTask(VelocityController vc) {
            if (vc == null) {
                throw new NullPointerException("Given VelocityController was null");
            }
            m_velocityController = vc;
        }

        public void run() {
            m_velocityController.controller();
            Timer.delay(0.05);
        }
    }

    public void init() {
        m_controlLoop = new java.util.Timer();
        m_controlLoop.schedule(new VelocityControllerTask(this), 0L, (long) (m_period * 1000));
        //oldDist = encoder.getDistance();
    }

    public VelocityController(DiscoEncoder e, Jaguar m) {
        encoder = e;
        motor = m;
    }

    public VelocityController(DiscoEncoder e, Jaguar m, boolean r) {
        encoder = e;
        motor = m;
        reversed = r;
    }

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

    private synchronized double adjustVelocity(double goalVelocity) {
        double error = goalVelocity - encoder.getRate();
        iterm += (m_period * error);
        //distTraveled += distDiff;
        double result = velocityToOutput(goalVelocity) + (error * kp) + (ki * iterm); // + (kp * error);
        return result;
    }

    public synchronized double controller() {  //distance in inches
        output = adjustVelocity(goalVelocity);
        motor.set(output);
        return output;
    }

    public double getOutput() {
        return output;
    }

    public double getVelocity() {
        return velocity;
    }

    public double getGoalVelocity() {
        return goalVelocity;
    }

    public double setGoalVelocity(double newVelocity) {
        if (reversed) {
            goalVelocity = -newVelocity;
        } else {
            goalVelocity = newVelocity;
        }
        iterm = 0.0;
        output = velocityToOutput(goalVelocity);
        return velocityToOutput(goalVelocity);
    }

    /**
     * Free the VelocityControllerTask
     */
    protected void free() {
        m_controlLoop.cancel();
        m_controlLoop = null;
    }

    public void setReversed(boolean r) {
        reversed = r;
    }

    /*public void setGoalDistance(double newGoalDistance) {
    goalDistance = newGoalDistance;
    distTraveled = 0.0;
    }*/

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
}

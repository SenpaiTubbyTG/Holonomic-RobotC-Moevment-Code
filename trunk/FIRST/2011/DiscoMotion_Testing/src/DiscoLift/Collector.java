package DiscoLift;

import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Nelson
 */
public class Collector {

    static final double k_outSpeed = 0.5;
    static final double k_inSpeed = -0.5;
    public static final double k_outDuration = 1.0;
    public static final int k_outButton = 3;
    public static final int k_inButton = 2;
    private double currentSpeed;
    private Victor collectorMotor;
    boolean running = false;

    public Collector(Victor coll) {
        collectorMotor = coll;
        currentSpeed = 0.0;
    }

    public void run(double speed) {
        collectorMotor.set(speed);
    }

    public void periodic(boolean[] buttons) {
        if (!running) {
            if (buttons[k_outButton]) {
                currentSpeed = k_outSpeed;
            } else if (buttons[k_inButton]) {
                currentSpeed = k_inSpeed;
            } else {
                currentSpeed = 0.0;
            }
        }
        this.run(currentSpeed);
    }
}

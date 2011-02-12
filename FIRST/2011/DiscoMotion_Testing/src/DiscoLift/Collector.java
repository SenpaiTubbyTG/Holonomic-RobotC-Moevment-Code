package DiscoLift;

import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Nelson
 */
public class Collector {

    public static final double k_inSpeed = 0.5;
    public static final double k_outSpeed = -0.5;
    public static final double k_outDuration = 1.0;
    public static final int k_outButton = 2;
    private double currentSpeed;
    private double startTime;
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
                startTime = Timer.getFPGATimestamp();
                currentSpeed = k_outSpeed;
            } else {
                currentSpeed = 0.0;
            }
        } else {
            if ((Timer.getFPGATimestamp() - startTime) > k_outDuration) {
                currentSpeed = 0.0;
            }
        }
        this.run(currentSpeed);
    }
}

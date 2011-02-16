package DiscoLift;

import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.*;

/**
 * 
 * @author Nelson Chen
 */
public class Arm {

    public static final double k_armUpSpeed = -0.5;
    public static final double k_armDownSpeed = 0.4;
    public static final double k_collectorOutSpeed = 0.5;
    public static final double k_collectorInSpeed = -0.5;
    private Victor armMotor;
    private Victor collectorMotor;
    private DigitalInput upSwitch;
    private DigitalInput downSwitch;

    public Arm(Victor arm, Victor collect) {
        armMotor = arm;
        collectorMotor = collect;
    }

    public Arm(Victor arm, Victor collect, DigitalInput up, DigitalInput down) {
        this(arm, collect);
        upSwitch = up;
        downSwitch = down;
    }

    public void collect() {
        down();
        tubeIn();
    }

    public void up() {
        if (upSwitch.get()) {
            armMotor.set(k_armUpSpeed);
        } else {
            stopArm();
        }
    }


    public void down() {
        if (downSwitch.get()) {
            armMotor.set(k_armDownSpeed);
        } else {
            stopArm();
        }
    }

    public void stopArm() {
        armMotor.set(0.0);
    }

    public void stopCollector() {
        collectorMotor.set(0.0);
    }

    public void tubeIn() {
        collectorMotor.set(k_collectorInSpeed);
    }
    public void tubeIn(double speed) {
        collectorMotor.set(speed);
    }

    public void tubeOut() {
        collectorMotor.set(k_collectorOutSpeed);
    }
}

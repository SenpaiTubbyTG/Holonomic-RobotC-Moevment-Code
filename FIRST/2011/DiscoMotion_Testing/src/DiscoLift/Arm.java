package DiscoLift;

import edu.wpi.first.wpilibj.*;

/**
 * 
 * @author Nelson Chen
 */
public class Arm {

    private static final double k_armUpSpeed = -0.4;
    private static final double k_armDownSpeed = 0.3;
    static final double k_collectorOutSpeed = 0.5;
    static final double k_collectorInSpeed = -0.5;

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

    public void tubeIn() {
        collectorMotor.set(k_collectorInSpeed);
    }

    public void tubeOut() {
        collectorMotor.set(k_collectorOutSpeed);
    }

    public void up() {
        if (!upSwitch.get()) {
            armMotor.set(k_armUpSpeed);
        } else {
            armMotor.set(0.0);
        }
    }

    public void collect() {
        down();
        tubeIn();
    }

    public void down() {
        if (!downSwitch.get()) {
            armMotor.set(k_armDownSpeed);
        } else {
            armMotor.set(0.0);
        }
    }
}

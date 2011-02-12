
package DiscoLift;

import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Nelson Chen
 */
public class Arm {

    private static final int k_armUpButton = 6;
    private static final int k_armDownButton = 7;

    private static final double k_armUpSpeed = 0.3;
    private static final double k_armDownSpeed = -0.3;

    private Victor armMotor;
    private DigitalInput upSwitch;
    private DigitalInput downSwitch;

    public Arm(Victor motor, DigitalInput up, DigitalInput down) {
        armMotor = motor;
        upSwitch = up;
        downSwitch = down;
    }

    public void periodic(boolean[] liftHandle) {
        if(liftHandle[k_armUpButton] && !upSwitch.get()) {
            armMotor.set(k_armUpSpeed);
        }
        else if(liftHandle[k_armDownButton] && !downSwitch.get()) {
            armMotor.set(k_armDownSpeed);
        }
        else {
            armMotor.set(0.0);
        }
    }

    
}

package DiscoLift;

import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.*;
import discobot.HW;

/**
 * 
 * @author Nelson Chen
 */
public class Arm {

    public static double k_armUpSpeed = -0.4;
    public static double k_armDownSpeed = 0.3;
    public static final double k_collectorOutSpeed = 0.5;
    public static final double k_collectorInSpeed = -0.5;

    public void updateArmSpeed() {
        k_armUpSpeed = HW.driverStation.getBatteryVoltage() / HW.k_MaxVoltage * -0.4;
        k_armDownSpeed = HW.driverStation.getBatteryVoltage() / HW.k_MaxVoltage * 0.3;
    }

    public void collect() {
        down();
        tubeIn();
    }

    public void up() {
        if (!isUp()) {
            HW.armMotor.set(k_armUpSpeed);
        } else {
            stopArm();
        }
    }


    public void down() {
        if (!isDown()) {
            HW.armMotor.set(k_armDownSpeed);
        } else {
            stopArm();
        }
    }

    public void stopArm() {
        HW.armMotor.set(0.0);
    }

    public void stopCollector() {
        HW.collectorMotor.set(0.0);
    }

    public void tubeIn() {
        HW.collectorMotor.set(k_collectorInSpeed);
    }
    public void tubeIn(double speed) {
        HW.collectorMotor.set(speed);
    }

    public void tubeOut() {
        HW.collectorMotor.set(k_collectorOutSpeed);
    }

    public boolean isUp() {
        return !HW.armSwitchUp.get();
    }
    public boolean isDown() {
        return !HW.armSwitchDown.get();
    }
}

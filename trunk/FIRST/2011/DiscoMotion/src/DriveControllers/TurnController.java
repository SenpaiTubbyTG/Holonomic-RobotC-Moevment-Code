package DriveControllers;

import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.Gyro;
import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson
 */
public class TurnController {
    private DiscoDriveConverter driveConverter;
    private PIDController gyroController;
    private double incrementStartTime;
    private Gyro gyro;

    public TurnController(Gyro g) {
        gyro = g;
        gyroController = new PIDController(0.1, 0.0, 0.0, gyro, driveConverter);
        driveConverter = 
                new DiscoDriveConverter(0.0, 0.0, 0.0, DiscoDriveConverter.Output.kTwist);
        incrementStartTime = Timer.getFPGATimestamp();
    }

    /**
     * Changes the setpoint of the turnController
     * @param setpt - new setpoint/goal heading
     */
    public void setSetpoint(double setpt) {
        gyroController.setSetpoint(setpt);
    }

    /**
     * for TELEOP, increments the Setpoint based on a passed joystick value
     * @param inc - right joystick, x-axis value
     */
    public void incrementSetpoint(double inc) {
        double currentTime = Timer.getFPGATimestamp();
        double newHeading = gyroController.getSetpoint() +
                            (inc * (currentTime - incrementStartTime));
        gyroController.setSetpoint(newHeading);
        incrementStartTime = currentTime;
    }

    /**
     * sets PID constants/gains
     * @param kp - new Proportional gain
     * @param ki - new Integral gain
     * @param kd - new Derivative gain
     */
    public void setPID(double kp, double ki, double kd) {
        gyroController.setPID(kp, ki, kd);
    }

    /**
     * enables the turnController
     */
    public void enable() {
        gyroController.enable();
        incrementStartTime = Timer.getFPGATimestamp();
    }

    /**
     * disables the turnController
     */
    public void disable() {
        gyroController.disable();
    }

    /**
     * Output of TurnController
     * Rotation value, -1 to 1
     * @return twist value of the DiscoDriveConverter
     */
    public double getRotation() {
        return driveConverter.getTwist();
    }

}

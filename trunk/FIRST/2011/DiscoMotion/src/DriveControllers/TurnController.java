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

    public void setSetpoint(double setpt) {
        gyroController.setSetpoint(setpt);
    }

    public void incrementSetpoint(double inc) {
        double currentTime = Timer.getFPGATimestamp();
        double newHeading = gyroController.getSetpoint() +
                            (inc * (currentTime - incrementStartTime));
        gyroController.setSetpoint(newHeading);
        incrementStartTime = currentTime;
    }

    public void setPID(double kp, double ki, double kd) {
        gyroController.setPID(kp, ki, kd);
    }

    public void enable() {
        gyroController.enable();
        incrementStartTime = Timer.getFPGATimestamp();
    }

    public void disable() {
        gyroController.disable();
    }

    public double getRotation() {
        return driveConverter.getTwist();
    }

}

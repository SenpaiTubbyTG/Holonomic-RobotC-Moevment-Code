package DriveControllers;

import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.Gyro;

/**
 * @author Nelson
 */
public class TurnController {
    private DiscoDriveConverter driveConverter;
    private PIDController gyroController;

    private Gyro gyro;

    public TurnController(Gyro g) {
        gyro = g;
        gyroController = new PIDController(0.1, 0.0, 0.45, gyro, driveConverter);
        driveConverter = 
                new DiscoDriveConverter(0.0, 0.0, 0.0, DiscoDriveConverter.Output.kTwist);
    }

    public void setSetpoint(double setpt) {
        gyroController.setSetpoint(setpt);
    }

    public void enable() {
        gyroController.enable();
    }

    public void disable() {
        gyroController.disable();
    }

    public double getRotation() {
        return driveConverter.getTwist();
    }

}

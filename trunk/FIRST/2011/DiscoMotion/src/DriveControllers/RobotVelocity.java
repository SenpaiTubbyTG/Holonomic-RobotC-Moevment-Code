package DriveControllers;

import Sensors.VelocityMatrices;
import edu.wpi.first.wpilibj.PIDController;

/**
 *
 * @author Nelson Chen
 */
public class RobotVelocity {

    private VelocityMatrices xVelocity;
    private VelocityMatrices yVelocity;
    private DiscoDriveConverter xVelocityOutput;
    private DiscoDriveConverter yVelocityOutput;
    private PIDController xVelocityController;
    private PIDController yVelocityController;

    public static RobotVelocity robotVelocity = new RobotVelocity();

    /**
     * singleton constructor
     */
    private RobotVelocity() {
        xVelocity = new VelocityMatrices(VelocityMatrices.VelocityOutput.kXvelocity);
        yVelocity = new VelocityMatrices(VelocityMatrices.VelocityOutput.kYvelocity);
        xVelocityOutput =
                new DiscoDriveConverter(0.0, 0.0, 0.0, DiscoDriveConverter.Output.kSpeed);
        yVelocityOutput =
                new DiscoDriveConverter(0.0, 0.0, 0.0, DiscoDriveConverter.Output.kSpeed);
        xVelocityController = new PIDController(0.1, 0.0, 0.0, xVelocity, xVelocityOutput);
        yVelocityController = new PIDController(0.1, 0.0, 0.0, yVelocity, yVelocityOutput);
    }

    public void setXvelocity(double xVel) {
        xVelocityController.setSetpoint(xVel);
    }

    public void setYvelocity(double yVel) {
        yVelocityController.setSetpoint(yVel);
    }

    public void setXvelocityPID(double kp, double ki, double kd) {
        xVelocityController.setPID(kp, ki, kd);
    }

    public void setYvelocityPID(double kp, double ki, double kd) {
        yVelocityController.setPID(kp, ki, kd);
    }

    public void enableX() {
        xVelocityController.enable();
    }

    public void enableY() {
        yVelocityController.enable();
    }

    public void disableX() {
        xVelocityController.disable();
    }

    public void disableY() {
        yVelocityController.disable();
    }

    public double getXvelocity() {
        return xVelocityOutput.getSpeed();
    }

    public double getYvelocity() {
        return yVelocityOutput.getSpeed();
    }
}

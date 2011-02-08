/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package DriveControllers;

import Sensors.VelocityMatrices;
import edu.wpi.first.wpilibj.PIDController;

/**
 *
 * @author Nelson Chen
 */
public class RobotVelocity {
    private DiscoDriveConverter xVelocityOutput;
    private DiscoDriveConverter yVelocityOutput;
    private PIDController xVelocityController;
    private PIDController yVelocityController;

    public RobotVelocity() {
        xVelocityOutput =
                new DiscoDriveConverter(0.0, 0.0, 0.0, DiscoDriveConverter.Output.kSpeed);
        xVelocityController =
                new PIDController(0.1, 0.0, 0.0, VelocityMatrices.velocityMatrices, xVelocityOutput);
        yVelocityOutput =
                new DiscoDriveConverter(0.0, 0.0, 0.0, DiscoDriveConverter.Output.kSpeed);
        yVelocityController =
                new PIDController(0.1, 0.0, 0.0, VelocityMatrices.velocityMatrices, yVelocityOutput);
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

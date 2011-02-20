package DriveControllers;

import Sensors.DiscoGyro;
import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.Timer;

/**
 * @author Nelson
 */
public class TurnController implements PIDOutput {

    private double output;
    private PIDController gyroController;
    //private double incrementStartTime;
    private DiscoGyro gyro;

    public TurnController(DiscoGyro g) {
        gyro = g;
        gyroController = new PIDController(0.023, 0.0, 0.05, gyro, this);
        gyroController.setOutputRange(-0.75, 0.75);
        //incrementStartTime = Timer.getFPGATimestamp();
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
        if (Math.abs(inc) > .05) {
            //double currentTime = Timer.getFPGATimestamp();
            double newHeading = gyroController.getSetpoint()
                    + (inc * 5);// * (currentTime - incrementStartTime));
            gyroController.setSetpoint(newHeading);
            //incrementStartTime = currentTime;
        }
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

    public double getSetpoint() {
        return gyroController.getSetpoint();
    }

    public double getError() {
        return gyroController.getError();
    }

    /**
     * enables the turnController
     */
    public void enable() {
        gyroController.enable();
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
        return output;
    }

    public void pidWrite(double out) {
        output = out;
    }

    public void reset() {
        reset(0.0);
    }

    public void reset(double angle) {
        setSetpoint(angle);
        gyro.reset(angle);
        gyroController.reset();
        gyroController.enable();
    }

    /**
     * Should turn the robot to the nearest orientation
     * @param newOrientation
     */
    public void turnToOrientation(double newOrientation) {
        newOrientation = Math.abs(newOrientation % 360); //Make sure the angle is between and 0-359
        double currentAngle = getSetpoint();			//Need to decide if this should be getAngle or getSetpoint not sure yet

        int sign = ((currentAngle >= 0) ? 1 : -1);
        
        //should be faster than calling Math.abs
        currentAngle = currentAngle * sign;
        double numberOfFullTurns = Math.floor(currentAngle / 360);
        
        //if its negative invert the angle because -90 is the same orientation as 270
        double currentOrientation = ((sign == -1) ? (360 - (currentAngle % 360)) : (currentAngle % 360));


        if (newOrientation != currentOrientation) {
            double out;
            //never spin more than 180 degress
            if (currentOrientation - newOrientation >= 180) {
                out = newOrientation + 360;
            } else if (newOrientation - currentOrientation >= 180) {
                out = newOrientation - 360;
            } else {
                out = newOrientation;
            }
            out = ((sign == -1) ? (360 - out) : out);			//Convert to negative angle
            out = ((numberOfFullTurns * 360 * sign) + out);		//Add back the full turns
            setSetpoint(out);
        }
    }

    public double getP() {
        return gyroController.getP();
    }
    public double getD() {
        return gyroController.getD();
    }

    public void setAngle(double angle) {
        gyro.setAngle(angle);
        reset(angle);
    }
}

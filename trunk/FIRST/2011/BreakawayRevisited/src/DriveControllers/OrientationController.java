/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DriveControllers;

import Utils.*;
import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Nelson
 */
public class OrientationController {

    final double ki = 20.0;
    double iterm = 0.0;
    final double itermMax = 30;
    final double maxError = 1.0;
    double turnVelocity = 20.0;
    double originalHeading;
    final double goalHeading = 0.0;
    double oldTime;
    Gyro gyro;  //positive angle change is clockwise turn
    VelocityController leftMotor;
    VelocityController rightMotor;
    double leftGoalVelocity;
    double rightGoalVelocity;
    double leftVelocityOutput;
    double rightVelocityOutput;

    public OrientationController(Gyro g, VelocityController l, VelocityController r) {
        leftMotor = l;
        rightMotor = r;
        gyro = g;
        originalHeading = gyro.getAngle();
    }

    public void initialize() {
        oldTime = Timer.getFPGATimestamp();
        //goalHeading = gyro.getAngle();
        iterm = 0.0;
    }

    /*public void setTurn(double degrees) {
    originalHeading = gyro.getAngle();
    goalHeading = originalHeading + degrees;
    leftVelocity = turnVelocity;
    rightVelocity = turnVelocity;
    }*/
    private void adjustVelocity() {
        double timeDiff = (Timer.getFPGATimestamp() - oldTime);

        double error = goalHeading + gyro.getAngle();
        //DiscoUtils.debugPrintln("\n\nHeading error: " + error);

        if(error < maxError)
            iterm = 0.0;

        if (Math.abs(iterm) < itermMax) {
            iterm += error * timeDiff;
            DiscoUtils.debugPrintln("\n\nHeading iterm: " + iterm);
            DiscoUtils.debugPrintln("Gyro: " + gyro.getAngle());
        }
        leftVelocityOutput = limit(leftGoalVelocity - iterm * ki);
        rightVelocityOutput = limit(rightGoalVelocity + iterm * ki);
        DiscoUtils.debugPrintln("leftOutput: " + leftVelocityOutput);
        DiscoUtils.debugPrintln("rightOutput: " + rightVelocityOutput);
        DiscoUtils.debugPrintln("leftVelocity: " + leftMotor.getVelocity());
        DiscoUtils.debugPrintln("rightVelocity: " + rightMotor.getVelocity());
        DiscoUtils.debugPrintln("OLDleftGoal: " + leftMotor.getGoalVelocity());
        DiscoUtils.debugPrintln("OLDrightGoal: " + rightMotor.getGoalVelocity());
    }

    private double limit(double value) {
        if (value >= 100.0) {
            return 100.0;
        } else if (value <= -100.0) {
            return -100.0;
        } else {
            return value;
        }
    }

    public void controller() {
        if ((Timer.getFPGATimestamp() - oldTime) > 0.05) {
            adjustVelocity();
            oldTime = Timer.getFPGATimestamp();
            leftMotor.setGoalVelocity(leftVelocityOutput);
            rightMotor.setGoalVelocity(rightVelocityOutput);
            rightMotor.controller();
            leftMotor.controller();
        } else {
            rightMotor.controller();
            leftMotor.controller();
        }
    }

    public void setVelocity(double lVelocity, double rVelocity) {
        //goalHeading = gyro.getAngle();
        leftGoalVelocity = lVelocity;
        rightGoalVelocity = rVelocity;
        oldTime = Timer.getFPGATimestamp() + 0.1;
        iterm = 0.0;
        controller();
    }

    public double getLeftOutput() {
        return 0.0;
    }

    public double getRightOutput() {
        return 0.0;
    }
}

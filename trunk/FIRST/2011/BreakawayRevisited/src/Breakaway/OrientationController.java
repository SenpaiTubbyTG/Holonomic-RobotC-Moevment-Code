/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Breakaway;

import Utils.*;
import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Nelson
 */
public class OrientationController {

    final double ki = 0.02;
    double iterm = 0.0;
    final double itermMax = 20;

    double turnSpeed = 0.5;

    double originalHeading;
    double goalHeading;
    double oldTime;

    Gyro gyro;  //positive angle change is clockwise turn
    VelocityController leftMotor;
    VelocityController rightMotor;

    double leftVelocity;
    double rightVelocity;
    Tuple output;

    public OrientationController(Gyro g, VelocityController l, VelocityController r) {
        leftMotor = l;
        rightMotor = r;
        gyro = g;
        originalHeading = gyro.getAngle();
    }

    public void setTurn(double degrees) {
        originalHeading = gyro.getAngle();
        goalHeading = originalHeading + degrees;
        leftVelocity = turnSpeed;
        rightVelocity = turnSpeed;
    }

    public void turnControl() {
        double timeDiff = (Timer.getFPGATimestamp() - oldTime);

        double error = gyro.getAngle() - goalHeading;
        DiscoUtils.debugPrintln("Heading error: " + error);

        if (Math.abs(iterm) < itermMax) {
            iterm += error * timeDiff;
            DiscoUtils.debugPrintln("Heading iterm: " + iterm);
        }
        leftMotor.setGoalVelocity(leftVelocity + iterm);
        rightMotor.setGoalVelocity(rightVelocity + iterm);
        DiscoUtils.debugPrintln("TurnControl: " + output.toString());
    }

    public void setVelocity(double lVelocity, double rVelocity) {
        goalHeading = gyro.getAngle();
        leftVelocity = lVelocity;
        rightVelocity = rVelocity;
        oldTime = Timer.getFPGATimestamp();
    }

    public Tuple controller() {
        if ((Timer.getFPGATimestamp() - oldTime) > 0.3) {
            turnControl();
            oldTime = Timer.getFPGATimestamp();
            return output;
        }
        else {
            output.set(leftMotor.controller(), rightMotor.controller());
            return output;
        }
    }
    
    
    
}

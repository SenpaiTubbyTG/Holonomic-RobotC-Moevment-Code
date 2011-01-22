/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Breakaway;

import Utils.DiscoUtils;
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

    Gyro gyro;
    VelocityController leftMotor;
    VelocityController rightMotor;

    double output = 0.0;

    public OrientationController(Gyro g, VelocityController l, VelocityController r) {
        leftMotor = l;
        rightMotor = r;
        gyro = g;
        originalHeading = gyro.getAngle();
    }

    public void setTurn(double degrees) {
        originalHeading = gyro.getAngle();
        goalHeading = originalHeading + degrees;
    }

    public void turnControl() {
        
    }
    
}

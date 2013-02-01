package disco.utils;

import com.sun.squawk.util.MathUtils;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.communication.UsageReporting;

public class BetterDrive extends RobotDrive {
    public BetterDrive(SpeedController a, SpeedController b,
            SpeedController c, SpeedController d) {
        super(a,b,c,d);
    }
    
    double scalar = 2.5;
    
    public void tankDrive(double leftValue, double rightValue, boolean squaredInputs) {

        // square the inputs (while preserving the sign) to increase fine control while permitting full power
        leftValue = limit(leftValue);
        rightValue = limit(rightValue);
        if(squaredInputs) {
            if (leftValue >= 0.0) {
                leftValue = (MathUtils.pow(leftValue, scalar));
            } else {
                leftValue = -(MathUtils.pow(leftValue, scalar));
            }
            if (rightValue >= 0.0) {
                rightValue = (MathUtils.pow(rightValue, scalar));
            } else {
                rightValue = -(MathUtils.pow(rightValue, scalar));
            }
        }
        setLeftRightMotorOutputs(leftValue, rightValue);
    }
    public void arcadeDrive(double moveValue, double rotateValue, boolean squaredInputs) {
        // local variables to hold the computed PWM values for the motors

        double leftMotorSpeed;
        double rightMotorSpeed;
        
        

        moveValue = limit(moveValue);
        rotateValue = limit(rotateValue);

        if (squaredInputs) {
            // square the inputs (while preserving the sign) to increase fine control while permitting full power
            if (moveValue >= 0.0) {
                moveValue =  MathUtils.pow(moveValue, scalar);
            } else {
                moveValue = -MathUtils.pow(moveValue, scalar);
            }
            if (rotateValue >= 0.0) {
                rotateValue = MathUtils.pow(rotateValue, scalar);
            } else {
                rotateValue = -MathUtils.pow(rotateValue, scalar);
            }
        }

        if (moveValue > 0.0) {
            if (rotateValue > 0.0) {
                leftMotorSpeed = moveValue - rotateValue;
                rightMotorSpeed = Math.max(moveValue, rotateValue);
            } else {
                leftMotorSpeed = Math.max(moveValue, -rotateValue);
                rightMotorSpeed = moveValue + rotateValue;
            }
        } else {
            if (rotateValue > 0.0) {
                leftMotorSpeed = -Math.max(-moveValue, rotateValue);
                rightMotorSpeed = moveValue + rotateValue;
            } else {
                leftMotorSpeed = moveValue - rotateValue;
                rightMotorSpeed = -Math.max(-moveValue, -rotateValue);
            }
        }

        setLeftRightMotorOutputs(leftMotorSpeed, rightMotorSpeed);
    }
}

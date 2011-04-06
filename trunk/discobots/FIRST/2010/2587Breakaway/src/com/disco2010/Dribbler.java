/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.disco2010;

import edu.wpi.first.wpilibj.*;

/**
 * Dribbler used to controller the dribbler on the side of our robot
 * 
 */
public class Dribbler {

    SpeedController leftDribblerSC;
    SpeedController rightDribblerSC;

    private int[] invertedMotors = {1, 1, 1};

    /**
     * kLeftMotor - used by invert motors to tell it what motor to invert
     */
    public static final int kLeftDribbler = 1;

    /**
     * kRightMotor - used by invert motors to tell it what motor to invert
     */
    public static final int kRightDribbler = 2;


    /**
     * Dribbler class used to controller the dribbler on our robot
     * @param dribblerLeft - the left speed controller of the dribbler
     * @param dribblerRight - the right speed controller of the dribbler
     */
    public void Dribbler(SpeedController dribblerLeft, SpeedController dribblerRight) {
        leftDribblerSC = dribblerLeft;
        rightDribblerSC = dribblerRight;
    }

    /**
     * Invert a motor direction.
     * This is used when a motor should run in the opposite direction as the drive
     * code would normally run it. Motors that are direct drive would be inverted, the
     * Drive code assumes that the motors are geared with one reversal.
     * 1 = Left Motor
     * 2 = Right Motor
     * 3 = Front Motor
     * 4 = Rear Motor
     * @param motor The motor index to invert.
     * @param isInverted True if the motor should be inverted when operated.
     */
    public void setInvertedMotor(final int motor, final boolean isInverted) {
        if (motor >= 1 && motor <= 2) {
            invertedMotors[motor] = isInverted ? -1 : 1;
        } else {
            DiscoUtils.errorPrintln("Invert Dribbler Motor Error: Motor value out of range");
        }
    }

    /**
     * dribble
     * @param drive - the drive train to get movement information from
     */
    public void dribble(DiscoDrive drive) {
        double direction = drive.getDirection();

        if (direction >= 315 && direction <= 45){ //Moving Forward
            set(-1,-.5);
            DiscoUtils.debugPrintln("Dribble FWD");
        } else if (direction > 45 && direction <= 135) { //Moving Right
            set(-1,-1);
            DiscoUtils.debugPrintln("Dribble RIGHT");
        } else if (direction > 135 && direction <= 225) { //Moving Backwards
            set(-.5,-1);
            DiscoUtils.debugPrintln("Dribble REV");
        } else { //Moving Left
            set(-1,-1);
            DiscoUtils.debugPrintln("Dribble LEFT");
        }
    }

    /**
     * Set the speed of the dribblers
     * @param left - the left dribbler speed
     * @param right - the right dirbbler speed
     */
    public void set(double left, double right) {
        leftDribblerSC.set(left);
        rightDribblerSC.set(right);
    }
}

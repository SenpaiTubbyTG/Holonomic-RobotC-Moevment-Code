/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.disco2010;

import edu.wpi.first.wpilibj.*;

/**
 *
 * @author JAG
 */
public class DigitalIO {

    private boolean prevButton;
    private long prevTime = 0;
    private boolean output;

    private int shotTime = 4000000; //In Us
    private boolean prevUpButton;
    private boolean prevDownButton;
    private boolean rollover = false;
    private int counter;
    
    public DigitalIO() {
    }

    public void SetShotTime(int time) {
        shotTime = time;
    }

    public boolean ShotTimer(boolean button) {

        if (button == true && prevButton == false) {
            prevTime = Timer.getUsClock();
            output = true;
        } else if (Timer.getUsClock() <= (prevTime + shotTime)) {
            output = true;
        } else {
            output = false;
        }

        prevButton = button;
        return output;
    }

    public boolean toggleSwitch(boolean button) {
        if (button == true && prevButton == false) {
            output = !output;
        }
        prevButton = button;
        return output;

    }

    public int count(boolean upButton, boolean downButton, int limit) {
        if ((upButton == true) && (prevUpButton == false)) {
            // If we are less than the limit, then add one.  Otherwise if rollover is enabled,
            // the set to zero.

            if (counter < limit) {
                counter++;
            } else if (rollover == true) {
                counter = 0;
            }
        }

        // perform the decreasing bit counting on a 0 to 1 transition of the down bit.

        if ((downButton == true) && (prevDownButton == false)) {
            // If we are greater than zero, then subtract one.  Otherwise if rollover is enabled,
            // the set to the limit.

            if (counter > 0) {
                counter--;
            } else if (rollover == true) {
                counter = limit;
            }
        }

        // Store the new up & down bits and counter for the next call.

        prevUpButton = upButton;
        prevDownButton = downButton;

        return counter;
    }
}

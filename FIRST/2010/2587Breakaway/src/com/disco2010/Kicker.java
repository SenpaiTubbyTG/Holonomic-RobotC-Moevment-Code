/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.disco2010;

import edu.wpi.first.wpilibj.Joystick.*;
import edu.wpi.first.wpilibj.Timer;

/**
 *
 * @author Nelson
 */
public class Kicker {

    public Kicker() {
    }

    public int getChannel() {
        return HW.loadSwitch.getChannel();
    }

    public boolean getFrontSwitch() {
        return HW.kickSwitch.get();
    }

    public boolean getBackSwitch() {
        return HW.loadSwitch.get();
    }

    public void load() {
        if (HW.loadSwitch.get() == true)
        {
            HW.kickerMotor.set(-0.3);
        }
        else
            HW.kickerMotor.set(0.0);
    }

    public void kill() {
            HW.kickerMotor.set(0.0);
    }

    public void kick(int speed) {
            HW.kickerMotor.set(1.0);
            Timer.delay(0.05);
            switch(speed)
            {
                case 1: HW.kickerMotor.set(0.25);break;
                case 2: HW.kickerMotor.set(0.5);break;
                case 3: HW.kickerMotor.set(0.75);break;
                case 4: HW.kickerMotor.set(1.0);break;
                default: HW.kickerMotor.set(0.0);break;
            }
            //else if(HW.kickhandle.getRawButton(3))
                //HW.kickerMotor.set(0.5);
            //else if(HW.kickhandle.getRawButton(5))
                //HW.kickerMotor.set(0.75);
            //HW.kickerMotor.set(1.0);
    }

    public void moveBar(boolean directionUp)
    {
        if(directionUp)
        {
            HW.kickerBar.set(0.4);
        }
        else
        {
            HW.kickerBar.set(-0.4);
        }
    }

    public void joystick() {
        HW.kickerMotor.set(HW.kickhandle.getX());
    }
}

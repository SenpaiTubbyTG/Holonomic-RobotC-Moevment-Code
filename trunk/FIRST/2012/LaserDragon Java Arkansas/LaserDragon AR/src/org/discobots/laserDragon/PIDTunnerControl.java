/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.discobots.laserDragon;

import edu.wpi.first.wpilibj.Joystick;

/**
 *
 * @author mrdouglass
 */
public class PIDTunnerControl{
    private Joystick controlStick;
    public PIDTunnerControl(int stick){
        controlStick = new Joystick(stick);
    }
    public int changePGain(){
        if(controlStick.getRawButton(7)){
            return -1;
        } else if(controlStick.getRawButton(6)){
            return 1;
        } else {
            return 0;
        }
    }
    public int changeIGain(){
        if(controlStick.getRawButton(8)){
            return -1;
        } else if(controlStick.getRawButton(9)){
            return 1;
        } else {
            return 0;
        }
    }
    public int changeDGain(){
        if(controlStick.getRawButton(10)){
            return -1;
        } else if(controlStick.getRawButton(11)){
            return 1;
        } else {
            return 0;
        }
    }
    public int changeChange(){
        if(controlStick.getRawButton(1)){
            return -1;
        } else if(controlStick.getRawButton(4)){
            return 1;
        } else {
            return 0;
        }
    }
    public int changeSetPoint(){
        if(controlStick.getRawButton(2)){
            return -1;
        } else if(controlStick.getRawButton(3)){
            return 1;
        } else {
            return 0;
        }
    }
    public boolean displayGains(){
        if(controlStick.getRawButton(5)){
            return true;
        } else {
            return false;
        }
    }
}

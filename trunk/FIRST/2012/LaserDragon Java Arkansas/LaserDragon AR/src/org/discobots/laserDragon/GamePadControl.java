package org.discobots.laserDragon;

import edu.wpi.first.wpilibj.Joystick;

public class GamePadControl implements RobotControlSystem{
    
    //indexing means the state that uses indexer and mouth.
    //bridge means state the uses whacker
    private final int INDEXING = 0, BRIDGE = 1;
    private int state = INDEXING;
    private Joystick stick1, stick2;
    
    public GamePadControl(int s1, int s2){
        stick1 = new Joystick(s1);
        stick2 = new Joystick(s2);
    }
    
    public int mouthInput(){
        if(state == INDEXING){
            if(stick1.getRawButton(7) || stick2.getRawButton(7)){
               return BACKWARD; 
            } else if(stick1.getRawButton(5) || stick2.getRawButton(5)){
                return FORWARD;
            } else {
                return NONE;
            }
        } else {
            return NONE;
        }
    }

    public int indexerInput(){
        if(state == INDEXING){
            if((stick1.getRawButton(6) && stick1.getRawButton(8)) 
               ||(stick2.getRawButton(6) && stick2.getRawButton(8))){
               return SEND; 
            } else if(stick1.getRawButton(6) || stick2.getRawButton(6)){
                return FORWARD;
            } else if(stick1.getRawButton(8) || stick2.getRawButton(8)){
                return BACKWARD;
            } else {
                return NONE;
            }
        } else {
            return NONE;
        }
    }

    public int shooterEnableInput(){
        if(stick1.getRawButton(1) || stick2.getRawButton(1)){
            return SHOOTER_ENABLE;
        } else {
            return NONE;
        }
    }

    public int shooterSpeedInput(){
        if(stick1.getRawButton(4) || stick2.getRawButton(4)){
            return SHOOTER_INC;
        } else if(stick1.getRawButton(2) || stick2.getRawButton(2)){
            return SHOOTER_DEC;
        } else {
            return NONE;
        }
    }

    public int hoodTiltInput(){
        if((stick1.getRawAxis(6)>0.9 || stick2.getRawAxis(6)>0.9)){
            return FORWARD;
        } else if((stick1.getRawAxis(6)<-0.9 || stick2.getRawAxis(6)<-0.9)){
            return BACKWARD;
        } else {
            return NONE;
        }
    }

    public int whackerInput(){
        if(state == BRIDGE){
            if(stick1.getRawButton(6) || stick2.getRawButton(6)){
                return FORWARD;
            } else {
                return BACKWARD;
            }
        } else {
            return NONE;
        }
    }

    public int brakeInput(){
        if(state == BRIDGE){
            if(stick1.getRawButton(5) || stick2.getRawButton(5)){
                return FORWARD;
            } else {
                return NONE;
            }
        } else {
            return NONE;
        }
    }

    public double leftDriveInput(){
        return -stick1.getRawAxis(2);
    }

    public double rightDriveInput(){
        return -stick1.getRawAxis(4);
    }
    
    private boolean lastCheckStateValue = false;
    public void checkControllerState(){
        if(lastCheckStateValue == false && 
           (stick1.getRawAxis(5)>0.9 || stick2.getRawAxis(5)>0.9)){
            state = state == INDEXING ? BRIDGE : INDEXING;
        }
        lastCheckStateValue = (stick1.getRawAxis(5)>0.9 || stick2.getRawAxis(5)>0.9);
    }
}

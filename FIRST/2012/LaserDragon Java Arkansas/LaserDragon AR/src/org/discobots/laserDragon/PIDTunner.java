/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.discobots.laserDragon;

import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.Victor;

/**
 *
 * @author mrdouglass
 */
public class PIDTunner extends SimpleRobot{
    private final int
                        shooter1Channel  = 5,  shooter1Slot = 1,
                        shooter2Channel  = 6,  shooter2Slot = 1,
                        encoderChannel   = 10,  encoderSlot  = 2;
    
    DiscoCounterEncoder encoder;
    PIDController       shooterPID;
    ShooterDrive        shooterDrive;
    PIDTunnerControl    controls;
    
    public PIDTunner(){
        encoder = new DiscoCounterEncoder(encoderSlot, encoderChannel, 1);
        Victor shooter1 = new Victor(shooter1Slot, shooter1Channel);
        Victor shooter2 = new Victor(shooter2Slot, shooter2Channel);
        shooterDrive = new ShooterDrive(shooter1, shooter2);
        shooterPID = new PIDController(0.0, 0.0, 0.0, encoder, shooterDrive);
        shooterPID.setInputRange(100, 3500);
        shooterPID.setOutputRange(0, 1.0);
        shooterPID.setSetpoint(1600);
        shooterPID.disable();
        controls = new PIDTunnerControl(1);
    }
    
    public void robotInit(){
        System.out.println("Running the PID Tunner");
    }
    
    public void disabled(){
        shooterPID.disable();
    }
    
    public void operatorControl(){
        shooterPID.enable();
        double pGain = 0, iGain = 0, dGain = 0;
        double setPoint = 1600;
        double change = 1;
        boolean update;
        while(isEnabled()){
            int c;
            update = false;
            if((c = pChange()) != 0){
                pGain += change*c;
                update = true;
            }
            if((c = iChange()) != 0){
                iGain += change*c;
                update = true;
            }
            if((c = dChange()) != 0){
                dGain += change*c;
                update = true;
            }
            if((c = setPointChange()) != 0){
                setPoint += change*c;
                update = true;
            }
            int changeChange = changeChange();
            if(changeChange == -1){
                change *= 0.1;
            } else if(changeChange == 1){
                change *= 10;
            }
            // only update every 100 loops
            if(update){
                shooterPID.setPID(pGain, iGain, dGain);
                shooterPID.setSetpoint(setPoint);
                
            }
            if(displayOutput()){
                String output = "P: " + pGain +
                                " I: " + iGain +
                                " D: " + dGain + "\n" +
                                "Setpoint: " + setPoint +
                                " Change: " + change +
                                " RPM: " + encoder.getRPM() + 
                                "\n------------------------";
                System.out.println(output);                
            }
        }
    }
    
    /* these methods are a buffer between the raw controls and the
       operator Controls method. These methods cause buttons to trigger only once
       per press 
    */
    private int lastPValue = 0;
    private int pChange(){
        int value = controls.changePGain();
        int res;
        if(value == lastPValue){
            res = 0;
        } else {
            res = value;
        }
        lastPValue = value;
        return res;
    }
    
    private int lastIValue = 0;
    private int iChange(){
        int value = controls.changeIGain();
        int res;
        if(value == lastIValue){
            res = 0;
        } else {
            res = value;
        }
        lastIValue = value;
        return res;
    }
    
    private int lastDValue = 0;
    private int dChange(){
        int value = controls.changeDGain();
        int res;
        if(value == lastDValue){
            res = 0;
        } else {
            res = value;
        }
        lastDValue = value;
        return res;
    }
    
    private int lastSetPointValue = 0;
    private int setPointChange(){
        int value = controls.changeSetPoint();
        int res;
        if(value == lastSetPointValue){
            res = 0;
        } else {
            res = value;
        }
        lastSetPointValue = value;
        return res;
    }
    
    private int lastChangeValue = 0;
    private int changeChange(){
        int value = controls.changeChange();
        int res;
        if(value == lastChangeValue){
            res = 0;
        } else {
            res = value;
        }
        lastChangeValue = value;
        return res;
    }
    
    private boolean lastDisplayInput = false;
    private boolean displayOutput(){
        boolean res = (lastDisplayInput == false) && 
                      (controls.displayGains() == true);
        lastDisplayInput = controls.displayGains();
        return res;
    }
}
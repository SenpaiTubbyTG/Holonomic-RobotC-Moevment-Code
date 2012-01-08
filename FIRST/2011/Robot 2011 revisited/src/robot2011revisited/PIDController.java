/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package javaapplication23;

public class PIDController {

    boolean enabled;
    double input;
    double output;
    double error;
    double errorLast;
    double errorTotal;
    double setPosition;
    double currentPosition;
    double KP;
    double KI;
    double KD;
    double armMin;
    double armMax;

    public PIDController(){
        enabled = true;
        error = 0.0;
        errorLast = 0.0;
        errorTotal = 0.0;
        armMin = 0;
        armMax = 300;
    }
    public void enable(){
        if(enabled == false)
            enabled = true;
    }
    public void disable(){
        if(enabled == true)
            enabled = false;
    }
    public void setPID(double kp, double ki, double kd){
        this.KP = kp;
        this.KI = ki;
        this.KD = kd;
    }
      public void setSetpoint(double position) {
        if (this.enabled) {
            if (position < armMin) {
                position = armMin;
            } else if (position > armMax) {
                position = armMax;
            } else {
                setPosition = position;
            }
        }
    }

    public double calcPID(double setposition, double currentposition){
        if(enabled)
        {
            setPosition = setposition;
            currentPosition = currentposition;
            errorLast = error;
            error = setPosition - currentPosition;
            errorTotal += error;
            output = (KP*error) + (KI*errorTotal) + (KD*(error-errorLast));
            return output;
        }
        else
            return 0.0;
    }

}

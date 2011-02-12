package Sensors;

import edu.wpi.first.wpilibj.Gyro;

/**
 * Extends gyro to allow us to reset the angle to what ever value we want.
 * @author JAG
 */
public class DiscoGyro extends Gyro{

    private double m_resetAngleValue =0;

    public DiscoGyro(int channel){
        super(channel);
    }

    /**
     *
     * @return the value of the gyro plus our reset angle positions
     */
    public double getAngle(){
        return m_resetAngleValue + super.getAngle();
    }

    public void setAngle(double angle){
        m_resetAngleValue = angle;
        super.reset();
    }

    /**
     * Reset by setting th angle to zero and reseting the gyo accumulator
     */
    public void reset(){
        setAngle(0);
    }

    /**
     * Return the angle with our adjustments
     * @return
     */
    public double PIDGet(){
        return getAngle();
    }
}

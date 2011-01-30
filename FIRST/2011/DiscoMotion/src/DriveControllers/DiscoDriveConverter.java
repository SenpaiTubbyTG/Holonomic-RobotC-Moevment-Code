/*
 * 
 */
package DriveControllers;

import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.PIDSource;

/**
 * This class is an object that is used to store a drive value that will be
 * integrated with other values to determine the final drive output. This allows
 * us to do sensor integration and also have more control of the final drive output.
 *
 * Also allows you to feed the output of one PIDController into the input of another
 * @author JAG
 */
public class DiscoDriveConverter implements PIDOutput, PIDSource {

    /**
     * Class lets you select which output will be controlled by the PIDloop
     * Most of the time will be speed but may be the others
     */
    public static class Output {

        /**
         * The integer value representing this enumeration
         */
        public final int value;
        static final int kSpeed_val = 0;
        static final int kDirection_val = 1;
        static final int kTwist_val = 2;
        /**
         * Use Speed for PIDGet and PIDWrite
         */
        public static final Output kSpeed = new Output(kSpeed_val);
        /**
         * Use Direction for PIDGet and PIDWrite
         */
        public static final Output kDirection = new Output(kDirection_val);
        /**
         * Use Twist for PIDGet and PIDWrite
         */
        public static final Output kTwist = new Output(kTwist_val);

        private Output(int value) {
            this.value = value;
        }
    }
    private double m_speed = 0.0;
    private double m_direction = 0.0;
    private double m_Twist = 0.0;
    private Output m_output;

    /**
     * Takes in the default values and the value that should be changed and outputed by the PID control loop
     * @param inputSpeed
     * @param inputDirection
     * @param inputTwist
     * @param output
     */
    public DiscoDriveConverter(double inputSpeed, double inputDirection, double inputTwist, Output output) {
        m_speed = inputSpeed;
        m_direction = inputDirection;
        m_Twist = inputTwist;
        m_output = output;
    }

    public void pidWrite(double input) {
        switch (m_output.value) {
            case Output.kSpeed_val:
                setSpeed(input);
            case Output.kDirection_val:
                setDirection(input);
            case Output.kTwist_val:
                setTwist(input);
            default:
                DiscoUtils.debugPrintln("Output Type not matched in DiscoDriveConverter");
        }
    }

    public double pidGet() {
        switch (m_output.value) {
            case Output.kSpeed_val:
                return getSpeed();
            case Output.kDirection_val:
                return getDirection();
            case Output.kTwist_val:
                return getTwist();
            default:
                return 0.0;
        }
    }

    public double getSpeed() {
        return m_speed;
    }

    public double getDirection() {
        return m_direction;
    }

    public double getTwist() {
        return m_Twist;
    }

    public void setSpeed(double speed) {
        m_speed = speed;
    }

    public void setDirection(double direction) {
        m_direction = direction;
    }

    public void setTwist(double twist) {
        m_Twist = twist;
    }

    public void setOutput(Output output) {
        m_output = output;
    }
}

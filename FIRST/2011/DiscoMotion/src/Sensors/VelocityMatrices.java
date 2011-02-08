package Sensors;

import Sensors.Jama.*;
import edu.wpi.first.wpilibj.PIDSource;
import edu.wpi.first.wpilibj.can.CANTimeoutException;
import discobot.HW;

/**
 * @author Nelson Chen
 */
public class VelocityMatrices implements PIDSource {

    public static class VelocityOutput {

        /**
         * The integer value representing this enumeration
         */
        public final int value;
        static final int kXvelocity_val = 0;
        static final int kYvelocity_val = 1;
        static final int kRotationalVelocity_val = 2;
        /**
         * Use x-velocity for PIDGet
         */
        public static final VelocityOutput kXvelocity = new VelocityOutput(kXvelocity_val);
        /**
         * Use y-velocity for PIDGet
         */
        public static final VelocityOutput kYvelocity = new VelocityOutput(kYvelocity_val);
        /**
         * Use Twist for PIDGet
         */
        public static final VelocityOutput kRotationalVelocity = new VelocityOutput(kRotationalVelocity_val);

        private VelocityOutput(int value) {
            this.value = value;
        }
    }

    /*
     * TODO: run in own thread, at least for matrices
     */
    private final double thetaFR = 45.0;
    private final double thetaFL = 135.0;
    private final double thetaBL = 225.0;
    private final double thetaBR = 315.0;
    private VelocityOutput m_output = VelocityOutput.kXvelocity;
    //private final double radius = 0.635; //radius (wheel-to-wheel) in meters
    //private final double mass = 54.4310844;   //mass in kg
    //private final double alpha = 0.5; //weight distribution constant
    private Matrix wheelVelMat = new Matrix(4, 1);
    private Matrix velCouplMat = new Matrix(3, 4);
    private Matrix velocityMatrix = new Matrix(3, 1);
    //private Matrix wheelForceMat = new Matrix(4, 1);
    //private Matrix forceCouplMat = new Matrix(3, 4);
    //private Matrix accelMatrix   = new Matrix(3, 1);
    //Singleton class instance
    public static VelocityMatrices velocityMatrices = new VelocityMatrices();

    /**
     * singleton constructor initializing the velocity coupling matrix (constant)
     */
    private VelocityMatrices() {
        initVelCouplMat();
        //initForceCouplMat();
    }

    /**
     * helper method for setting wheel velocity matrix values
     * wheel velocities obtained directly from encoders (via Jaguars)
     */
    private void updateWheelVelocities() throws CANTimeoutException {
        wheelVelMat.set(0, 0, HW.frontLeftDM.getSpeed());
        wheelVelMat.set(1, 0, HW.frontRightDM.getSpeed());
        wheelVelMat.set(2, 0, HW.rearRightDM.getSpeed());
        wheelVelMat.set(3, 0, HW.rearLeftDM.getSpeed());
    }

    /**
     * calculates velocity = velocity coupling matrix * wheel velocity matrix
     * updates wheel velocities before calculating velocity
     */
    public void calcVelocity() {
        try {
            updateWheelVelocities();
            velocityMatrix = velCouplMat.times(wheelVelMat);
        } catch (CANTimeoutException e) {
            e.printStackTrace();
        }
    }

    /**
     * used by PIDController object, returns velocity depending on current VelocityOutput variable
     * @return PID input
     */
    public double pidGet() {
        calcVelocity();
        switch (m_output.value) {
            case VelocityOutput.kXvelocity_val:
                return getXvelocity();
            case VelocityOutput.kYvelocity_val:
                return getYvelocity();
            case VelocityOutput.kRotationalVelocity_val:
                return getRotationalVelocity();
            default:    //should never be reached
                return 0.0;
        }
    }

    /**
     * Changes VelocityOutput type (x, y, or rotational velocity)
     * Default is x-velocity
     * @param output new VelocityOutput type
     */
    public void setOutput(VelocityOutput output) {
        m_output = output;
    }

    private void initVelCouplMat() {
        double[][] velCoupl = new double[4][3];
        velCoupl[0][0] = -Math.sin(thetaFR);
        velCoupl[0][1] = Math.cos(thetaFR);
        velCoupl[0][2] = 1;

        velCoupl[1][0] = -Math.sin(thetaFL);
        velCoupl[1][1] = Math.cos(thetaFL);
        velCoupl[1][2] = 1;

        velCoupl[2][0] = -Math.sin(thetaBL);
        velCoupl[2][1] = Math.cos(thetaBL);
        velCoupl[2][2] = 1;

        velCoupl[3][0] = -Math.sin(thetaBR);
        velCoupl[3][1] = Math.cos(thetaBR);
        velCoupl[3][2] = 1;
        velCouplMat = new Matrix(velCoupl);
        velCouplMat = velCouplMat.inverse();
    }

    public double getXvelocity() {
        return velocityMatrix.get(0, 0);
    }

    public double getYvelocity() {
        return velocityMatrix.get(1, 0);
    }

    public double getRotationalVelocity() {
        return velocityMatrix.get(2, 0);
    }

    public Matrix getVelocityVector() {
        return velocityMatrix;
    }
    /*
    private void initForceCouplMat() {
    double[][] forceCoupl = new double[3][4];
    forceCoupl[0][0] = -Math.sin(thetaFR);
    forceCoupl[0][1] = -Math.sin(thetaFL);
    forceCoupl[0][2] = -Math.sin(thetaBL);
    forceCoupl[0][3] = -Math.sin(thetaBR);

    forceCoupl[1][0] = Math.cos(thetaFR);
    forceCoupl[1][1] = Math.cos(thetaFL);
    forceCoupl[1][2] = Math.cos(thetaBL);
    forceCoupl[1][3] = Math.cos(thetaBR);

    forceCoupl[2][0] = 1 / alpha;
    forceCoupl[2][1] = 1 / alpha;
    forceCoupl[2][2] = 1 / alpha;
    forceCoupl[2][3] = 1 / alpha;

    forceCouplMat = new Matrix(forceCoupl);
    }

    public void calcAccel() {
    accelMatrix = forceCouplMat.times(wheelForceMat).times(1/mass);
    }

    public Matrix getAccelMat() {
    return accelMatrix;
    }

    // This code is for the acceleration of the robot.
    public void setWheelForceMat(double f1, double f2, double f3, double f4) {
    wheelForceMat.set(0, 0, f1);
    wheelForceMat.set(1, 0, f2);
    wheelForceMat.set(2, 0, f3);
    wheelForceMat.set(3, 0, f4);
    }
    public Matrix getWheelForceMat() {
    return wheelForceMat;
    }
     */
}

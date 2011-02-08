package Sensors;

import Sensors.Jama.*;

/**
 * @author pavchag
 */
public class VelocityMatrices {

    /*
     * this should run in its own thread eventually
     * -nelson
     */

    public static final double mass = 54.4310844;   //mass in kg
    public static final double alpha = 0.5; //weight distribution constanc
    public static final double thetaFR = 45.0;
    public static final double thetaFL = 135.0;
    public static final double thetaBL = 225.0;
    public static final double thetaBR = 315.0;
    public static final double radius = 0.635; //radius (wheel-to-wheel) in meters

    public static double xVel;
    static Matrix wheelVelMat   = new Matrix(4, 1);
    static Matrix wheelForceMat = new Matrix(4, 1);
    static Matrix velCouplMat   = new Matrix(3, 4);
    static Matrix forceCouplMat = new Matrix(3, 4);
    static Matrix accelMatrix   = new Matrix(3, 1);
    static Matrix velocityMatrix= new Matrix(3, 1);

    /*
     *TODO: use encoder values for parameters or take wheel velocities directly
     */
    public static void setWheelVelMat(double v1, double v2, double v3, double v4) {
        wheelVelMat.set(0, 0, v1);
        wheelVelMat.set(1, 0, v2);
        wheelVelMat.set(2, 0, v3);
        wheelVelMat.set(3, 0, v4);
    }

    /*
     * 
     */
    public static void calcVelocity() {
        System.out.println("VELOCITY COUPLING MATRIX, PSEUDOINVERTED");
        
        double[][] raw = velCouplMat.getArray();
        for(int r=0;r<raw.length;r++) {
            for(int c=0;c<raw[r].length;c++)
                System.out.print(raw[r][c] + "\t\t\t");
            System.out.println();
        }

        System.out.println("\n\nWHEEL VELOCITY MATRIX");

        raw = wheelVelMat.getArray();
        for(int r=0;r<raw.length;r++) {
            for(int c=0;c<raw[r].length;c++)
                System.out.print(raw[r][c]);
            System.out.println();
        }
        velocityMatrix = velCouplMat.times(wheelVelMat);
    }
    /*
     *
     */
    public static void calcAccel() {
        accelMatrix = forceCouplMat.times(wheelForceMat).times(1/mass);
    }
    /*
     * 
     */
    public static Matrix getAccelMat() {
        return accelMatrix;
    }

    // This code is for the acceleration of the robot.
    public static void setWheelForceMat(double f1, double f2, double f3, double f4) {
        wheelForceMat.set(0, 0, f1);
        wheelForceMat.set(1, 0, f2);
        wheelForceMat.set(2, 0, f3);
        wheelForceMat.set(3, 0, f4);
    }

    public static Matrix getVelCouplMat() {
        return velCouplMat;
    }

    public static Matrix getWheelVelMat() {
        return wheelVelMat;
    }
    public static Matrix getWheelForceMat() {
        return wheelForceMat;
    }
    public static Matrix getVelocityVector() {
        return velocityMatrix;
    }

    public static void initVelCouplMat() {
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

    public static void initForceCouplMat() {
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

}

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Jama;

import Jama.*;
import java.util.*;
/**
 *
 * @author pavchag
 */
public class GetMatrices
{
    double theta = Math.PI/2;

    double[][] wheelVel = new double[4][1];
    double[][] velCoupl = new double[3][4];
    double[][] wheelForce = new double[4][1];
    double[][] forceCoupl = new double[3][4];
    
    public Matrix getWheelVelMat(double v1, double v2, double v3, double v4)
    {
        wheelVel[0][0] = v1;
        wheelVel[1][0] = v2;
        wheelVel[2][0] = v3;
        wheelVel[3][0] = v4;
        Matrix wheelVelMat = new Matrix(wheelVel);
        return wheelVelMat;
    }
    public Matrix getVelCouplMat()
    {
        velCoupl[0][0] = -Math.sin(Math.PI/2);
        velCoupl[0][1] = Math.cos(Math.PI/2);
        velCoupl[0][2] = 1;

        velCoupl[1][0] = -Math.sin(Math.PI/2);
        velCoupl[1][1] = Math.cos(Math.PI/2);
        velCoupl[1][2] = 1;

        velCoupl[2][0] = -Math.sin(Math.PI/2);
        velCoupl[2][1] = Math.cos(Math.PI/2);
        velCoupl[2][2] = 1;

        velCoupl[3][0] = -Math.sin(Math.PI/2);
        velCoupl[3][1] = Math.cos(Math.PI/2);
        velCoupl[3][2] = 1;
        Matrix velCouplMat = new Matrix(velCoupl);
        return velCouplMat;
    }

    // This code is for the acceleration of the robot.
    public Matrix getWheelForceMat(double f1, double f2, double f3, double f4)
    {
        wheelForce[0][0] = f1;
        wheelForce[1][0] = f2;
        wheelForce[2][0] = f3;
        wheelForce[3][0] = f4;
        Matrix wheelForceMat = new Matrix(wheelForce);
        return wheelForceMat;
    }
    public Matrix getForceCouplMat(double alpha)
    {
        forceCoupl[0][0] = -Math.sin(Math.PI/2);
        forceCoupl[0][1] = -Math.sin(Math.PI/2);
        forceCoupl[0][2] = -Math.sin(Math.PI/2);
        forceCoupl[0][3] = -Math.sin(Math.PI/2);

        forceCoupl[1][0] = Math.cos(Math.PI/2);
        forceCoupl[1][1] = Math.cos(Math.PI/2);
        forceCoupl[1][2] = Math.cos(Math.PI/2);
        forceCoupl[1][3] = Math.cos(Math.PI/2);

        forceCoupl[2][0] = 1/alpha;
        forceCoupl[2][1] = 1/alpha;
        forceCoupl[2][2] = 1/alpha;
        forceCoupl[2][3] = 1/alpha;

        Matrix forceCouplMat = new Matrix(forceCoupl);
        return forceCouplMat;
    }
}

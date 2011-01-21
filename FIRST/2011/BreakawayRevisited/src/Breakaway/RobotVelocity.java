/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Breakaway;

import Jama.*;
import java.util.*;
/**
 *
 * @author pavchag
 */
public class RobotVelocity
{
    double theta = Math.PI/2;

    double[][] forceVect = new double[0][3];
    public void ForceVect(double f1, double f2, double f3, double f4)
    {
        forceVect[0][0] = f1;
        forceVect[0][0] = f2;
        forceVect[0][0] = f3;
        forceVect[0][0] = f4;
    }

    double[][] forceCoupl = new double[4][3];
    public void ForceCoupl(double alpha)
    {
        forceCoupl[0][0] = -Math.sin(theta);
        forceCoupl[0][1] = -Math.sin(theta);
        forceCoupl[0][2] = -Math.sin(theta);
        forceCoupl[0][3] = -Math.sin(theta);

        forceCoupl[1][0] = Math.cos(theta);
        forceCoupl[1][1] = -Math.cos(theta);
        forceCoupl[1][2] = Math.cos(theta);
        forceCoupl[1][3] = -Math.cos(theta);

        forceCoupl[2][0] = 1/alpha;
        forceCoupl[2][1] = 1/alpha;
        forceCoupl[2][2] = 1/alpha;
        forceCoupl[2][3] = 1/alpha;
    }
    
    double[][] robotAccelVect = new double[0][2];
    public void RobotAccelVect(double ax, double ay, double Rw)
    {
        robotAccelVect[0][0] = ax;
        robotAccelVect[0][1] = ay;
        robotAccelVect[0][2] = Rw;
    }

    double[][] wheelVelVect = new double[3][0];
    public void WheelVelVect(double v1, double v2, double v3, double v4)
    {
        wheelVelVect[0][0] = v1;
        wheelVelVect[0][1] = v2;
        wheelVelVect[0][2] = v3;
        wheelVelVect[0][3] = v4;
    }

    double[][] velCoupl = new double[3][4];
    public void VelCoupl()
    {
        velCoupl[0][0] = -Math.sin(theta);
        velCoupl[0][1] = Math.cos(theta);
        velCoupl[0][2] = 1;

        velCoupl[1][0] = -Math.sin(theta);
        velCoupl[1][1] = Math.cos(theta);
        velCoupl[1][2] = 1;

        velCoupl[2][0] = -Math.sin(theta);
        velCoupl[2][1] = Math.cos(theta);
        velCoupl[2][2] = 1;

        velCoupl[3][0] = -Math.sin(theta);
        velCoupl[3][1] = Math.cos(theta);
        velCoupl[3][2] = 1;
    }

    double[][] robotVelVect = new double[2][0];
    public void RobotVelVect(double vx, double vy, double Rw)
    {
        robotVelVect[0][0] = vx;
        robotVelVect[1][0] = vy;
        robotVelVect[2][0] = Rw;
    }

}

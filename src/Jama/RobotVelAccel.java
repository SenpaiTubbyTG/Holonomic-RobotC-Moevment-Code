/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Jama;

/**
 *
 * @author pavchag
 */
public class RobotVelAccel
{
    public double M;
    GetMatrices matrices = new GetMatrices();
    public Matrix getRobotVelocity(double v1, double v2, double v3, double v4)
    {
        Matrix robotVelMat = new Matrix(3,1);
        robotVelMat = matrices.getWheelVelMat(v1, v2, v3, v4).times(Matrix.pinv(matrices.getVelCouplMat()));
        return robotVelMat;
    }
    public Matrix getRobotAcceleration(double alpha, double f1, double f2, double f3, double f4)
    {
        Matrix robotAccelMat = new Matrix(3,1);
        robotAccelMat = matrices.getForceCouplMat(alpha).times(matrices.getWheelForceMat(f1, f2, f3, f4).times(1/M));
        return robotAccelMat;
    }
}
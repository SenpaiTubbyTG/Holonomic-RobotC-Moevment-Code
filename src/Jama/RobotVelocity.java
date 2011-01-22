/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Jama;

/**
 *
 * @author pavchag
 */
public class RobotVelocity
{
    public double M;
    GetMatrices matrices = new GetMatrices();
    public Matrix getRobotVelocity(double v1, double v2, double v3, double v4)
    {
        Matrix robotVelMat = new Matrix(3,1);
        matrices.getWheelVelMat(v1, v2, v3, v4).times(Matrix.pinv(matrices.getVelCouplMat()));
        return robotVelMat;
    }
}
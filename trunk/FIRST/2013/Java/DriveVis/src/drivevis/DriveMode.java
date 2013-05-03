/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package drivevis;

/**
 *
 * @author sam
 */
public interface DriveMode {

    public double getLeftOut();

    public double getRightOut();

    public void calcLR(double y, double x);

    @Override
    public String toString();
}

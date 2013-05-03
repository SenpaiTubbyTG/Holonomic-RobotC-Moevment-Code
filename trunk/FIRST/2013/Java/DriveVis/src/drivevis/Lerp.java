/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package drivevis;

/**
 *
 * @author sam
 */
public class Lerp implements DriveMode {

    private double driveLeft = 0;
    private double driveRight = 0;
    double a = 0.5;
    double b = 1;

    @Override
    public double getLeftOut() {
	return driveLeft;
    }

    @Override
    public double getRightOut() {
	return driveRight;
    }

    @Override
    public void calcLR(double y, double x) {


	if (y >= 0 && x >= 0) {
	    driveLeft = x * b + y * (1 - x * b);
	    driveRight = -1 * x * b + y * ((1 - x * (a + 1)) + x * b);
	} else if (y >= 0 && x < 0) {
	    driveLeft = x * b + y * (1 + x * (1 + a) - x * b);
	    driveRight = -1 * x * b + y * (1 + x * b);
	} else if (y < 0 && x >= 0) {
	    driveLeft = x * b - y * (x * (a + 1) - 1 - x * b);
	    driveRight = -1 * x * b - y * (-1 + x * b);
	} else if (y < 0 && x < 0) {
	    driveLeft = x * b - y * (-1 - x * b);
	    driveRight = -1 * x * b - y * (-1 - x * (a + 1) + x * b);
	}
    }

    @Override
    public String toString() {
	return "LERP";
    }
}

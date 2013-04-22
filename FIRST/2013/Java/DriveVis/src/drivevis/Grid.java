/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package drivevis;

import java.awt.Color;
import java.awt.GridLayout;
import java.util.LinkedHashMap;
import javax.swing.BorderFactory;
import javax.swing.JPanel;

/**
 *
 * @author sam
 */
public class Grid extends JPanel {

    private Square[][] squares;
    private int center = 0;
    private int square_size;
    private double driveLeft = 0, driveRight = 0;
    private int squaresPerRow = 0;
    private String thisMode;
    public static final LinkedHashMap<Integer, String> modes = new LinkedHashMap<Integer, String>();

    public Grid(int div_quad, int parentSize) {
	modes.put(0, "ARCADE");
	modes.put(1, "CHEESY");
	modes.put(2, "LERP");
	thisMode = modes.get(0);
	squaresPerRow = div_quad * 2 + 1;
	squares = new Square[squaresPerRow][squaresPerRow];
	center = div_quad - 1;//start at 0
	square_size = parentSize / (squaresPerRow);
	GridLayout layout = new GridLayout(squaresPerRow, squaresPerRow);
	this.setLayout(layout);

	createGrid();
    }

    private void createGrid() {
	for (int x = 0; x < squares.length; x++) {
	    for (int y = 0; y < squares[x].length; y++) {
		squares[y][x] = new Square(y - center - 1, center + 1 - x, square_size, (squaresPerRow - 1) / 2.0);//it's backwards
		calcOutput(squares[y][x].getJoyY(), -1 * squares[y][x].getJoyX());
		squares[y][x].setOutput(Math.round(driveLeft * 100) / 100.0, Math.round(driveRight * 100) / 100.0);
		squares[y][x].setBorder(BorderFactory.createLineBorder(Color.black));
		this.add(squares[y][x]);
		//System.out.println(square_size);
	    }
	}
    }

    private void recalculate() {
	for (int x = 0; x < squares.length; x++) {
	    for (int y = 0; y < squares[x].length; y++) {
		calcOutput(squares[y][x].getJoyY(), -1 * squares[y][x].getJoyX());
		squares[y][x].setOutput(Math.round(driveLeft * 100) / 100.0, Math.round(driveRight * 100) / 100.0);
		//System.out.println(square_size);
	    }
	}
    }

    public void setMode(int newMode) {
	thisMode = modes.get(newMode);
	recalculate();
    }
    double skimGain = 0.2;
    double turnGain = 1.3;
    double threshold = 0.2;

    //move=y, rotate=x
    public void calcOutput(double moveValue, double rotateValue) {
	if (thisMode.equals("ARCADE")) {
	    double moveSign = moveValue >= 0 ? 1 : -1;
	    double rotateSign = rotateValue >= 0 ? 1 : -1;

	    //Remove comments to get real version
//	    moveValue = moveSign * Map(Math.abs(moveValue));
//	    rotateValue = rotateSign * Map(Math.abs(rotateValue));

	    arcadeDrive(moveValue, rotateValue, false);
	}

	if (thisMode.equals("CHEESY")) {
	    double move = moveValue;
	    double turn = -rotateValue;

	    if (Math.abs(move) > threshold) {
		turn = turn * (turnGain * Math.abs(move));
	    }

	    double tempLeft = move + turn;
	    double tempRight = move - turn;

	    tempLeft = tempLeft + skim(tempRight);
	    tempRight = tempRight - skim(tempLeft);

	    //remove this to get real version
	    double max = Math.max(Math.abs(tempLeft), Math.abs(tempRight));
	    if(max > 1){
                tempLeft = tempLeft / max;
                tempRight = tempRight / max;
	    }
	    //end remove

	    driveLeft=tempLeft;
	    driveRight=tempRight;
	}
	if (thisMode.equals("LERP")) {
	    double a = 0.5;
	    double b = 1;
	    double x = -1 * rotateValue;
	    double y = moveValue;

	    if (y >= 0 && x >= 0) {
		//driveLeft = x * b + y * (1 - x * b);
		driveLeft = x * b + y * (1 - x * b);
		driveRight = -1 * x * b + y * ((1 - x * (a + 1)) + x * b);
	    } else if (y >= 0 && x < 0) {
		driveLeft = x * b + y * (1 + x * (1 + a) - x * b);
		driveRight = -1 * x * b + y * (1 + x * b);
	    } else if (y < 0 && x >= 0) {
		driveLeft = x * b - y * (x * (a + 1) - 1 - x * b);
		driveRight=-1*x*b-y*(-1+x*b);
	    }
	    else if(y<0 && x<0){
		driveLeft=x*b-y*(-1-x*b);
		driveRight=-1*x*b-y*(-1-x*(a+1)+x*b);
	    }
	}
    }

    private double skim(double v) {
	if (v > 1.0) {
	    return -((v - 1.0) * skimGain);
	} else if (v < -1.0) {
	    return -((v + 1.0) * skimGain);
	} else {
	    return 0;
	}
    }

    //The map from drivetrain class
    private static double Map(double stickVal) {
	double x = 10.0 * stickVal;
	//the secret formula
	//return 0.024 + 0.296*x - 0.085*x*x + 0.011*x*x*x - 0.000447*x*x*x*x;
	return 0.308 * x + 0.0327 * x * x * x + 0.000113 * x * x * x * x * x - 0.147 * x * x - 0.00314 * x * x * x * x;
    }

    //arcade drive from RobotDrive.java
    public void arcadeDrive(double moveValue, double rotateValue, boolean squaredInputs) {

	double leftMotorSpeed;
	double rightMotorSpeed;

	if (squaredInputs) {
	    // square the inputs (while preserving the sign) to increase fine control while permitting full power
	    if (moveValue >= 0.0) {
		moveValue = (moveValue * moveValue);
	    } else {
		moveValue = -(moveValue * moveValue);
	    }
	    if (rotateValue >= 0.0) {
		rotateValue = (rotateValue * rotateValue);
	    } else {
		rotateValue = -(rotateValue * rotateValue);
	    }
	}

	if (moveValue > 0.0) {
	    if (rotateValue > 0.0) {
		leftMotorSpeed = moveValue - rotateValue;
		rightMotorSpeed = Math.max(moveValue, rotateValue);
	    } else {
		leftMotorSpeed = Math.max(moveValue, -rotateValue);
		rightMotorSpeed = moveValue + rotateValue;
	    }
	} else {
	    if (rotateValue > 0.0) {
		leftMotorSpeed = -Math.max(-moveValue, rotateValue);
		rightMotorSpeed = moveValue + rotateValue;
	    } else {
		leftMotorSpeed = moveValue - rotateValue;
		rightMotorSpeed = -Math.max(-moveValue, -rotateValue);
	    }
	}

	setLeftRightMotorOutputs(leftMotorSpeed, rightMotorSpeed);
    }

    private void setLeftRightMotorOutputs(double leftMotorSpeed, double rightMotorSpeed) {
	driveLeft = leftMotorSpeed;
	driveRight = rightMotorSpeed;
    }
}

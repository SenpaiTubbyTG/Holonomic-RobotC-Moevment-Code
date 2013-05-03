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
    private DriveMode thisMode;
    public static final LinkedHashMap<Integer, DriveMode> modes = new LinkedHashMap<>();

    public Grid(int div_quad, int parentSize) {
	/*
	 * Just add a new <? implements DriveMode>, add it to this list, and it will work
	 */
	modes.put(0, new Arcade());
	modes.put(1, new Cheesy());
	modes.put(2, new Lerp());


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
		thisMode.calcLR(squares[y][x].getJoyY(), squares[y][x].getJoyX());
		squares[y][x].setOutput(Math.round(thisMode.getLeftOut() * 100) / 100.0, Math.round(thisMode.getRightOut() * 100) / 100.0);
		squares[y][x].setBorder(BorderFactory.createLineBorder(Color.black));
		this.add(squares[y][x]);
		//System.out.println(square_size);
	    }
	}
    }

    private void recalculate() {
	for (int x = 0; x < squares.length; x++) {
	    for (int y = 0; y < squares[x].length; y++) {
		thisMode.calcLR(squares[y][x].getJoyY(), squares[y][x].getJoyX());
		squares[y][x].setOutput(Math.round(thisMode.getLeftOut() * 100) / 100.0, Math.round(thisMode.getRightOut() * 100) / 100.0);
		//System.out.println(square_size);
	    }
	}
    }

    public void setMode(int newMode) {
	thisMode = modes.get(newMode);
	recalculate();
    }
}

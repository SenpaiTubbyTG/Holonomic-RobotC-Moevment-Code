package drivevis;

import java.awt.Color;
import java.awt.Dimension;
import javax.swing.JLabel;
import javax.swing.SwingConstants;

/**
 *
 * @author sam
 */
public class Square extends JLabel{
    private double left=0, right=0;
    private double joy_x=0, joy_y=0;
    int quadrant=0;


    public Square(int x_pos, int y_pos, int side, double positionDivision){
	super();
	this.setPreferredSize(new Dimension(side,side));
	joy_x=x_pos/positionDivision;
	joy_y=y_pos/positionDivision;
	this.setToolTipText("Joystick: ("+joy_x+" , "+joy_y+")");
	this.setHorizontalAlignment(SwingConstants.CENTER);
	this.setForeground(Color.white);
    }

    public void setOutput(double l, double r){
	left=l;
	right=r;
	this.setText(left+" , "+right);
	this.setOpaque(true);
	this.setBackground(new Color(computeColor(left),0,computeColor(right)));
    }

    public double getJoyX(){
	return joy_x;
    }

    public double getJoyY(){
	return joy_y;
    }

    public int computeColor(double in){
	if(in<-1){
	    in=-1;
	}
	if(in>1){
	    in=1;
	}
	int colorCenter=255/2;

	return (int) (colorCenter+in*255/2);
    }
}
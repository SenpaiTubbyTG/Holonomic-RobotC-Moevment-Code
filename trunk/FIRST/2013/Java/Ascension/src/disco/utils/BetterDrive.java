package disco.utils;

import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.SpeedController;

public class BetterDrive extends RobotDrive {
    public BetterDrive(SpeedController a, SpeedController b,
            SpeedController c, SpeedController d) {
        super(a,b,c,d);
    }

    private double Map(double stickVal){
	double x=10.0*stickVal;
	//the secret formula
	return 0.024 + 0.296*x - 0.085*x*x + 0.011*x*x*x - 0.000447*x*x*x*x;
    }

    public void tankDrive(double leftValue, double rightValue, boolean smoothed) {
	if(smoothed){
	    //what? no sign fuction? dumdum.
	    double leftSign= leftValue>=0 ? 1 : -1;
	    double rightSign= rightValue>=0 ? 1 : -1;

	    leftValue=leftSign*Map(Math.abs(leftValue));
	    rightValue=rightSign*Map(Math.abs(rightValue));
	}
	super.tankDrive(leftValue, rightValue, false);
    }

    public void tankDrive(double leftValue,double rightValue){
	super.tankDrive(leftValue, rightValue,false);
    }

    public void arcadeDrive(double moveValue, double rotateValue,boolean smoothed) {
	if(smoothed){
	    //what? no sign fuction? dumdum.
	    double moveSign= moveValue>=0 ? 1 : -1;
	    double rotateSign= rotateValue>=0 ? 1 : -1;

	    moveValue=moveSign*Map(Math.abs(moveValue));
	    rotateValue=rotateSign*Map(Math.abs(rotateValue));
	}
	super.arcadeDrive(moveValue, rotateValue, false);//no thanks, I'll scale those myself. Reminds me of a story...
	/*Harold walks into the toilet paper shop, and the guy at the counter says
	 * "what color toilet paper would you like?"
	 * Harold says "white please. I'll color it myself."
	 * Adapted from Captain Underpants
	 */
    }

    public void arcadeDrive(double moveValue,double turnValue){
	super.arcadeDrive(moveValue, moveValue, false);
    }
}

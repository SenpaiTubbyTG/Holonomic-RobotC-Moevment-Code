package disco.commands.drivetrain;

import disco.commands.CommandBase;
import disco.utils.GamePad;

public class CheesyArcade extends CommandBase {
    
    private double move;
    private double turn;
    private GamePad gamepad;
    
    private double skimGain = 0.1;
    private double turnGain = 1.3;
    private double threshold = 0.2;
    
    public CheesyArcade() {
        requires(drivetrain);
    }
    
    protected void initialize() {
        if (oi.getJoy1() instanceof GamePad) {
            gamepad = (GamePad) oi.getJoy1();
        } else {
            throw new IllegalStateException("Gamepads are required to use this commmand.");
        }
    }
    
    protected void execute() {
        move=turn=0;
        calculateInput();
        
        if (Math.abs(move) > threshold) {
            turn = turn  * (turnGain * Math.abs(move));
        }
            
        double tempLeft = move + turn;
        double tempRight = move - turn;
        
        double left = tempLeft + skim(tempRight);
        double right = tempRight + skim(tempLeft);
        
        drivetrain.tankDriveUnsmoothed(left, right);
    }
    
    protected boolean isFinished() {
        return false;
    }
    
    protected void end() {
        drivetrain.arcadeDrive(0, 0);
    }
    
    protected void interrupted() {
        end();
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
    
    protected void calculateInput(){
        if(gamepad != null){
	    move=gamepad.getLY();
	    move=Math.abs(move)>threshold ? move : 0;
	    turn=gamepad.getLX();
	    turn=Math.abs(turn)>threshold ? turn : 0;

            move+=gamepad.getRY()/2;
            turn+= gamepad.getRX()/2;
	}
	else{
	    throw new IllegalStateException("Gamepads are required to use this commmand.");
	}
    }
}

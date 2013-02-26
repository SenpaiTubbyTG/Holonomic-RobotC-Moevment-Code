/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.commands.shooter;

import disco.commands.CommandBase;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.PIDSource;

public class ShooterControlled extends CommandBase {
    
    PIDController frontController;
    PIDController backController;
    public static double  kP = 0.0100,
                kI = 0.0000,
                kD = 0.00;
    
    double frontCorrection;
    double backCorrection;
    
    // Setpoint in RPM
    public ShooterControlled(double setpoint) {
        requires(shooter);
        requires(compressor);
        shooter.setSetpoint(setpoint);
        frontController = new PIDController(kP, kI, kD, frontSource, frontOutput);
        backController = new PIDController(kP, kI, kD, backSource, backOutput);
    }

    protected void initialize() {
        frontController.enable();
        backController.enable();
        frontController.setSetpoint(shooter.getSetpoint());
        backController.setSetpoint(shooter.getSetpoint());
	compressor.set(false);
    }

    protected void execute() {
        CommandBase.shooter.setFrontPower(frontCorrection > 0 ? frontCorrection : 0);
        CommandBase.shooter.setBackPower(backCorrection > 0 ? backCorrection : 0);
        //on target if within 5%
        boolean onTarget=Math.abs( (shooter.getBackRPM()-shooter.getSetpoint()) / shooter.getSetpoint() )<0.03;
        shooter.setOnTarget(onTarget);
    }

    protected boolean isFinished() {
        return false;
    }

    protected void end() {
        frontController.disable();
        backController.disable();
        shooter.setPower(0);
	compressor.set(true);
        shooter.setOnTarget(false);
    }

    protected void interrupted() {
        end();
    }
    
    // PID
    private PIDOutput frontOutput = new PIDOutput() {
        public void pidWrite(double output) {
            frontCorrection = output;
        }        
    };
    private PIDOutput backOutput = new PIDOutput() {
        public void pidWrite(double output) {
            backCorrection = output;
        }        
    };
    private PIDSource frontSource = new PIDSource() {
        public double pidGet() {
            return shooter.getFrontRPM();
        }
    };
    private PIDSource backSource = new PIDSource() {
        public double pidGet() {
            return shooter.getBackRPM();
        }
    };
    
    public void setP(double p){
        kP=p;
        frontController.setPID(kP, kI, kD);
        backController.setPID(kP, kI, kD);
    }
    public void setI(double i){
        kI=i;
        frontController.setPID(kP, kI, kD);
        backController.setPID(kP, kI, kD);
    }
    public void setD(double d){
        kD=d;
        frontController.setPID(kP, kI, kD);
        backController.setPID(kP, kI, kD);
    }
}
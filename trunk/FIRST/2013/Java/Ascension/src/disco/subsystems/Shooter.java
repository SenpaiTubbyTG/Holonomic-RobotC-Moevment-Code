package disco.subsystems;

import disco.HW;
import disco.commands.shooter.ShooterBangBang;
import disco.utils.DiscoCounterEncoder;
import edu.wpi.first.wpilibj.Relay;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.PIDSubsystem;
import edu.wpi.first.wpilibj.command.Subsystem;

public class Shooter extends Subsystem {
    private Victor m_shooterFront;
    private Victor m_shooterBack;
    private DiscoCounterEncoder m_encoderFront;
    private DiscoCounterEncoder m_encoderBack;

    public static final int IN=0;
    public static final int OUT=1;
    private Relay m_pneumatic;
    
    private boolean enabled=false;
    private boolean onTarget=false;
    private double setpoint=0;
    public final double m_defaultSetpoint=5000;

    public Shooter(){
	m_shooterFront=new Victor(HW.ShooterFrontSlot,HW.ShooterFrontChannel);
	m_shooterBack=new Victor(HW.ShooterBackSlot,HW.ShooterBackChannel);

	m_encoderFront=new DiscoCounterEncoder(HW.shooterEncoderFrontSlot,HW.shooterEncoderFrontChannel,2);
        m_encoderFront.setUpSourceEdge(true, true);
        m_encoderFront.setMaxPeriod(1);
        m_encoderFront.start();
        setSetpoint(m_defaultSetpoint);

        m_encoderBack=new DiscoCounterEncoder(HW.shooterEncoderBackSlot,HW.shooterEncoderBackChannel,2);
        m_encoderBack.setUpSourceEdge(true, true);
        m_encoderBack.start();
        m_encoderBack.setMaxPeriod(1);
        
        m_pneumatic=new Relay(HW.shootPneumaticSlot,HW.shootPneumaticChannel);
        m_pneumatic.set(Relay.Value.kReverse);
        m_pneumatic.setDirection(Relay.Direction.kReverse);
    }

    public void initDefaultCommand() {
    }
    
    public void setSetpoint(double setpoint){
        this.setpoint=setpoint;
    }
    public double getSetpoint(){
        return this.setpoint;
    }
    
    public void enable(){
        this.enabled=true;
        new ShooterBangBang().start();
    }
    public void disable(){
        Command com=this.getCurrentCommand();
        if(com!=null){
            com.cancel();
        }
        this.enabled=false;
    }
    public boolean isEnabled(){
        return this.enabled;
    }

    public void setPower(double power){
	setFrontPower(power);
	setBackPower(power);
    }

    public void setFrontPower(double power){
	m_shooterFront.set(power);
    }

    public void setBackPower(double power){
	m_shooterBack.set(power);
    }

    public double getFrontPower(){
	return m_shooterFront.get();
    }

    public double getBackPower(){
	return m_shooterBack.get();
    }

    public void setPneumatic(int position){
        if(position==IN){
	    m_pneumatic.set(Relay.Value.kReverse);
	}
	else if(position==OUT){
	    m_pneumatic.set(Relay.Value.kOff);
	}
    }

    public Relay.Value getPneumatic(){
        return m_pneumatic.get();
    }

    public double getFrontRPM() {
	return m_encoderFront.getFilteredRPM();
    }
    public double getBackRPM() {
	return m_encoderBack.getFilteredRPM();
    }
    
    public void setOnTarget(boolean val){
        onTarget=val;
    }
    public boolean isOnTarget(){
        return onTarget;
    }
}
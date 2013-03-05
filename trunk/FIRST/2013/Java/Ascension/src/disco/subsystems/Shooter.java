package disco.subsystems;

import disco.HW;
import disco.commands.shooter.RawShooter;
import disco.commands.shooter.ShooterBangBang;
import disco.commands.shooter.ShooterControlled;
import disco.utils.DiscoCounterEncoder;
import edu.wpi.first.wpilibj.AnalogChannel;
import edu.wpi.first.wpilibj.Relay;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.Subsystem;

public class Shooter extends Subsystem {

    private Talon m_shooterFront;
    private Talon m_shooterBack;
    private DiscoCounterEncoder m_encoderFront;
    private DiscoCounterEncoder m_encoderBack;
    private AnalogChannel loadSensor;

    public static final int IN=0;
    public static final int OUT=1;
    
    private Relay m_shoot;
    private Relay m_clearSmall;
    private Relay m_clearLarge;
    
    private boolean enabled=false;
    private boolean onTarget=false;
    private double setpoint=0;
    public final double m_defaultSetpoint=6000;
    
    
    public double frontPWM=0.65;
    public double backPWM=0.55;
    public double difference = 0;
    
    
    public static final int MODE_BANG=0;
    public static final int MODE_OPEN_LOOP=1;
    public static final int MODE_CLOSED_LOOP=2;
    private int thisMode=0;

    public Shooter(){
	m_shooterFront=new Talon(HW.ShooterFrontSlot,HW.ShooterFrontChannel);
	m_shooterBack=new Talon(HW.ShooterBackSlot,HW.ShooterBackChannel);

	m_encoderFront=new DiscoCounterEncoder(HW.shooterEncoderFrontSlot,HW.shooterEncoderFrontChannel,2);
        //m_encoderFront.setUpSourceEdge(true, true);
        m_encoderFront.setSemiPeriodMode(true);
        m_encoderFront.setMaxPeriod(.03);
        m_encoderFront.start();

        m_encoderBack=new DiscoCounterEncoder(HW.shooterEncoderBackSlot,HW.shooterEncoderBackChannel,2);
        //m_encoderBack.setUpSourceEdge(true, true);
        m_encoderBack.setSemiPeriodMode(true);
        m_encoderBack.setMaxPeriod(.03);
        m_encoderBack.start();
        
        setSetpoint(m_defaultSetpoint);
        
        m_shoot=new Relay(HW.shootPneumaticSlot,HW.shootPneumaticChannel);
        m_shoot.set(Relay.Value.kReverse);
        m_shoot.setDirection(Relay.Direction.kReverse);
        
        //m_clearLarge = new Relay(HW.clearLargeSlot, HW.clearSmallChannel);
//        m_clearLarge.set(Relay.Value.kReverse);
//        m_clearLarge.setDirection(Relay.Direction.kReverse);
        
        m_clearSmall = new Relay(HW.clearSmallSlot, HW.clearSmallChannel);
        m_clearSmall.set(Relay.Value.kReverse);
        m_clearSmall.setDirection(Relay.Direction.kReverse);
        
        loadSensor=new AnalogChannel(HW.frisbeeLoadedSlot,HW.frisbeeLoadedChannel);
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
        switch(thisMode){
            case MODE_BANG:
                new ShooterBangBang().start();
                break;
            case MODE_OPEN_LOOP:
                new RawShooter().start();
                break;
            case MODE_CLOSED_LOOP:
                new ShooterControlled(this.getSetpoint()).start();
                break;
            default:
                new ShooterBangBang().start();
        }
        
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
    
    public void setMode(int mode){
        thisMode=mode;
    }
    public int getMode(){
        return thisMode;
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

    public void setPneuShoot(int position){
        if(position==IN){
	    m_shoot.set(Relay.Value.kReverse);
	} else if(position==OUT){
	    m_shoot.set(Relay.Value.kOff);
	}
    }
    public void setPneuClear(int position) {
        if(position==IN){
	    m_clearSmall.set(Relay.Value.kReverse);
	} else if(position==OUT){
	    m_clearSmall.set(Relay.Value.kOff);
	}
    }

    public Relay.Value getPneuShoot(){
        return m_shoot.get();
    }
    public Relay.Value getPneuClear(){
        return m_clearSmall.get();
    }

    public double getFrontRPM() {
        double c = m_encoderFront.getRPM();
	return c;
        
    }
    public double getBackRPM() {
	double c =  m_encoderBack.getRPM();
        return c;
    }
    
    public void setOnTarget(boolean val){
        onTarget=val;
    }
    public boolean isOnTarget(){
        return onTarget;
    }
    
    public double isLoaded(){
        return loadSensor.getVoltage();
    }
}
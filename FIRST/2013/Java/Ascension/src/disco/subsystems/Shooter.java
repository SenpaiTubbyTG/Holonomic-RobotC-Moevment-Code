package disco.subsystems;

import disco.HW;
import disco.utils.DiscoCounterEncoder;
import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.DoubleSolenoid.Value;
import edu.wpi.first.wpilibj.Relay;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.command.PIDSubsystem;

public class Shooter extends PIDSubsystem {
    private Victor m_shooter1;
    private Victor m_shooter2;
    private DiscoCounterEncoder m_encoder;
//    private DiscoCounterEncoder m_encoder2;
    private static double   kP=0.01,
			    kI=0,
			    kD=0,
			    kF=0.000;

    public static final int IN=0;
    public static final int OUT=1;
    private Relay m_pneumatic;

    public Shooter(){
	super("shooter",kP,kI,kD,kF);
	m_shooter1=new Victor(HW.Shooter1Slot,HW.Shooter1Channel);
	m_shooter2=new Victor(HW.Shooter2Slot,HW.Shooter2Channel);

	m_encoder=new DiscoCounterEncoder(HW.shooterEncoderSlot,HW.shooterEncoderChannel,1);
	m_encoder.setSemiPeriodMode(false);
        m_encoder.start();
        setSetpoint(6200);

  /*      m_encoder2=new DiscoCounterEncoder(HW.shooterEncoder2Slot,HW.shooterEncoder2Channel,1);
	m_encoder2.setSemiPeriodMode(false);
        m_encoder2.start();
        setSetpoint(6200);*/
        
        m_pneumatic=new Relay(HW.shootPneumaticSlot,HW.shootPneumaticChannel);
        m_pneumatic.set(Relay.Value.kReverse);
        m_pneumatic.setDirection(Relay.Direction.kReverse);
    }

    public void initDefaultCommand() {}

    public void setPower(double power){
	setPower1(power);
	setPower2(power);
    }

    public void setPower1(double power){
	m_shooter1.set(power);
    }

    public void setPower2(double power){
	m_shooter2.set(power);
    }

    public double getPower1(){
	return m_shooter1.get();
    }

    public double getPower2(){
	return m_shooter2.get();
    }

    public void setPneumatic(int position){
        if(position==IN){
	    m_pneumatic.set(Relay.Value.kOff);
	}
	else if(position==OUT){
	    m_pneumatic.set(Relay.Value.kReverse);
	}
    }

    public Relay.Value getPneumatic(){
        return m_pneumatic.get();
    }

    protected double returnPIDInput() {
	return m_encoder.getRPM();
//	return 0;
    }

    protected void usePIDOutput(double output) {
	setPower(output);
    }

    public double getRPM() {
	return m_encoder.getRPM();
    }
}
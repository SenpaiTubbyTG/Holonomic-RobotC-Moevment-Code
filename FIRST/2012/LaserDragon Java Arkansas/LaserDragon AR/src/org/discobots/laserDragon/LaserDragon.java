package org.discobots.laserDragon;


import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.buttons.Button;
import edu.wpi.first.wpilibj.buttons.DigitalIOButton;

public class LaserDragon extends SimpleRobot {
    
    Joystick m_leftStick, m_rightStick, m_shootStick;
    RobotDrive drive;
    Victor m_shooter1;
    Victor m_shooter2;
    PIDController shooterPID;
    Victor m_indexer;
    Victor m_mouth;
    Victor m_tiltMotor;
    Victor m_waker;
    DiscoCounterEncoder m_shooterEncoder;
    Counter m_shooterCounter;
    AnalogChannel m_pot;
    DigitalInput m_Chamber;
    DigitalInput m_Bridge;
    Relay m_BridgeRelay;
    Relay m_SpotlightRelay;
    
    public LaserDragon(){
        m_leftStick = new Joystick(1);
        m_rightStick = new Joystick(2);
        m_shootStick = new Joystick(3);
        drive = new RobotDrive(9,10,7,8); // these values need to be checked
        drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        m_shooter1 = new Victor(1,5);
        m_shooter2 = new Victor(1,6);
        m_indexer = new Victor(2,4);
        m_indexer = new Victor(2,1);
        m_tiltMotor = new Victor(1,4);
        m_waker = new Victor(2,8);
        m_shooterEncoder = new DiscoCounterEncoder(2,3,1);
        m_shooterEncoder.setMaxPeriod(0.6);
        m_shooterEncoder.start();
        m_pot = new AnalogChannel(1,3);
        m_Chamber = new DigitalInput(1,7);
        m_Bridge = new DigitalInput(2,7);
        m_BridgeRelay = new Relay(2,8);
        m_SpotlightRelay = new Relay(2,1);
        
        //pid controls
        initPID();
    }
    
    public void initPID(){
        shooterPID = new PIDController(0.0017, 0.0068, 0, m_shooterEncoder, m_shooter1);
        shooterPID.setInputRange(200, 3600);
        shooterPID.setOutputRange(0, 1.0);
    }
    
    public void autonomous(){
        
    }

    public void operatorControl(){
        while(isEnabled()){
            drive.tankDrive(m_leftStick, m_rightStick);
            mouthControl();
            indexerControl();
        }
    }
    
    public void mouthControl(){
        if(m_shootStick.getRawButton(2)){
            m_mouth.set(1);
        } else if(m_shootStick.getRawButton(3)){
            m_mouth.set(-1);
        } else {
            m_mouth.set(0);
        }
    }
    
    public void indexerControl(){
        if(m_shootStick.getRawButton(1) && m_shootStick.getRawButton(4)){
            m_indexer.set(-1);
        } else if(m_shootStick.getRawButton(1) && !m_Chamber.get()){
            m_indexer.set(1);
        } else {
            m_indexer.set(0);
        }
    }
}
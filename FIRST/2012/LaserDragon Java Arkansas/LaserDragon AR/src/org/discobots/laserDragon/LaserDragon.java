package org.discobots.laserDragon;


import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.buttons.Button;
import edu.wpi.first.wpilibj.buttons.DigitalIOButton;
import edu.wpi.first.wpilibj.camera.AxisCamera;

public class LaserDragon extends SimpleRobot {
    
    //EDIT THESE WHEN MAKING HARDWARE CHANGES
    private final int
                     // motor port assignment
                     leftFrontDriveChannel   =9,   leftFrontDriveSlot  =1,
                     leftBackDriveChannel    =10,  leftBackDriveSlot   =1,
                     rightFrontDriveChannel  =7,   rightFrontDriveSlot =1, 
                     rightBackDriveChannel   =8,   rightBackDriveSlot  =1,
                     mouthChannel            =1,   mouthSlot           =2,
                     indexerChannel          =4,   indexerSlot         =2,
                     shooter1Channel         =5,   shooter1Slot        =1,
                     shooter2Channel         =6,   shooter2Slot        =1,
                     tiltMotorChannel        =4,   tiltMotorSlot       =1,
                     // Pneumatic Solenoids
                     rightWhackerChannel     =2,   rightWhackerSlot    =1,
                     leftWhackerChannel      =3,   leftWhackerSlot     =1,
                     // Digital inputs
                     chamberChannel          =7,   chamberSlot         =1,
                     bridgeChannel           =7,   bridgeSlot          =2,
                     encoderChannel          =3,   encoderSlot         =2,
                     pressureSwitchChannel   =11,  pressureSwitchSlot  =2,
                     // analog inputs
                     potChannel              =3,   potSlot             =1,
                     // relay  output (spotlight and compressor)
                     spotlightChannel        =1,   spotlightSlot       =2,
                     compressorChannel       =7,   compressorSlot      =2;
                     
                     
    
    RobotControlSystem controls;
    Victor m_shooter1;
    Victor m_shooter2;
    Victor m_indexer;
    Victor m_mouth;
    Victor m_tiltMotor;
    RobotDrive drive;
    DiscoCounterEncoder m_shooterEncoder;
    PIDController shooterPID;
    AnalogChannel m_pot;
    DigitalInput m_Chamber;
    DigitalInput m_Bridge;
    Relay m_SpotlightRelay;
    Solenoid m_rightWhacker;
    Solenoid m_leftWhacker;
    Compressor m_compressor;
    
    AxisCamera m_goalCamera, m_ballCamera;
    
    public LaserDragon(){
        // initialization of channels and slots for all robot systems. USE CAUTION
        controls = new ThreeJoystickControl(1,2,3); // sticks 1, 2, and 3 (interchangeable)
        drive = new RobotDrive(leftFrontDriveChannel, leftBackDriveChannel,
                               rightFrontDriveChannel, rightBackDriveChannel);
        drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        m_shooter1 = new Victor(shooter1Slot, shooter1Channel);
        m_shooter2 = new Victor(shooter2Slot, shooter2Channel);
        m_indexer = new Victor(indexerSlot, indexerChannel);
        m_mouth   = new Victor(mouthSlot, mouthChannel);
        m_tiltMotor = new Victor(tiltMotorSlot, tiltMotorChannel);
        m_shooterEncoder = new DiscoCounterEncoder(encoderSlot, encoderChannel, 1);
        m_shooterEncoder.setMaxPeriod(0.6);
        m_shooterEncoder.start();
        m_pot = new AnalogChannel(potSlot, potChannel);
        m_Chamber = new DigitalInput(chamberSlot, chamberChannel);
        m_Bridge = new DigitalInput(bridgeSlot, bridgeChannel);
        m_SpotlightRelay = new Relay(spotlightSlot, spotlightChannel);
        
        //pneumatics
        m_rightWhacker = new Solenoid(rightWhackerSlot, rightWhackerChannel);
        m_leftWhacker  = new Solenoid(leftWhackerSlot,  leftWhackerChannel);
        m_compressor = new Compressor(pressureSwitchSlot, pressureSwitchChannel,
                                    compressorSlot, compressorChannel);
        
        // initialize cameras
        m_goalCamera = AxisCamera.getInstance("10.25.87.11");
        m_ballCamera = AxisCamera.getInstance("10.25.87.12");
        //pid controls
        initPID();
    }
    
    public void initPID(){
        shooterPID = new PIDController(0.0017, 0.0068, 0, m_shooterEncoder, m_shooter1);
        shooterPID.setInputRange(100, 3500);
        shooterPID.setOutputRange(0, 1.0);
        shooterPID.setSetpoint(1600);
        shooterPID.enable();
    }
    
    public void autonomous(){
    }

    public void operatorControl(){
        m_compressor.start();
        while(isEnabled()){
            drive.tankDrive(controls.rightDriveInput(),
                            controls.leftDriveInput());
            mouthControl();
            indexerControl();
        }
    }
    
    public void mouthControl(){
        int mouthState = controls.mouthInput();
        switch(mouthState){
            case RobotControlSystem.FORWARD:
                m_mouth.set(1); break;
            case RobotControlSystem.BACKWARD:
                m_mouth.set(-1); break;
            case RobotControlSystem.NONE:
                m_mouth.set(0); break;
        }
    }
    
    public void indexerControl(){
        int indexerState = controls.indexerInput();
        switch(indexerState){
            case RobotControlSystem.SEND:
                m_indexer.set(1); break;
            case RobotControlSystem.BACKWARD:
                m_indexer.set(-1); break;
            case RobotControlSystem.FORWARD:
                if(m_Chamber.get()){
                    m_indexer.set(1);
                } else {
                    m_indexer.set(0);
                }
                break;
            case RobotControlSystem.NONE:
                m_indexer.set(0); break;
        }
    }
   
    public void whackerControl(){
        int whackerState = controls.whackerInput();
        //check this for functionality
        switch(whackerState){
            case RobotControlSystem.FORWARD:
                m_rightWhacker.set(true);
                m_leftWhacker.set(true);
                break;
            case RobotControlSystem.BACKWARD:
                m_rightWhacker.set(false);
                m_leftWhacker.set(false);
                break;
        }
    }
    
    public void shooterControl(){
        int shootSpeedState = controls.shooterSpeedInput();
        int shootEnableState = controls.shooterEnableInput();
        if(shooterPID.isEnable()){
            double currentSetpoint = shooterPID.getSetpoint();
            switch(shootSpeedState){
                case RobotControlSystem.SHOOTER_INC:
                    if(currentSetpoint < 3500){
                        shooterPID.setSetpoint(currentSetpoint+100);
                    }
                    break;
                case RobotControlSystem.SHOOTER_DEC:
                    if(currentSetpoint > 100){
                        shooterPID.setSetpoint(currentSetpoint+100);
                    }
                    break;
            }
        }
        switch(shootEnableState){
            case RobotControlSystem.SHOOTER_ENABLE:
                if(shooterPID.isEnable()){
                    shooterPID.disable();
                    m_compressor.start();
                } else {
                    shooterPID.enable();
                    m_compressor.stop();
                }
                break;
        }
    }
    
    public void hoodTiltControl(){
        int hoodState = controls.hoodTiltInput();
        switch(hoodState){
            case RobotControlSystem.FORWARD:
                m_tiltMotor.set(1); break;
            case RobotControlSystem.BACKWARD:
                m_tiltMotor.set(-1);
            case RobotControlSystem.NONE:
                m_tiltMotor.set(0);
        }
    }
    
    private class LaserDragonTracker extends Thread{
        public void run(){
            
        }
    }
}
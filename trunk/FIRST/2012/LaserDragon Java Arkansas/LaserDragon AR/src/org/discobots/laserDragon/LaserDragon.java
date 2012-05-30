package org.discobots.laserDragon;


import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.buttons.Button;
import edu.wpi.first.wpilibj.buttons.DigitalIOButton;
import edu.wpi.first.wpilibj.camera.AxisCamera;
import edu.wpi.first.wpilibj.camera.AxisCameraException;
import edu.wpi.first.wpilibj.image.ColorImage;
import edu.wpi.first.wpilibj.image.NIVisionException;

/*public class LaserDragon extends PIDTunner{
}*/
    
public class LaserDragon extends SimpleRobot{
   //EDIT THESE WHEN MAKING HARDWARE CHANGES  
    private final int
                     // motor port assignment
                     leftFrontDriveChannel   =8,   leftFrontDriveSlot  =1,
                     leftBackDriveChannel    =10,  leftBackDriveSlot   =1,
                     rightFrontDriveChannel  =7,   rightFrontDriveSlot =1, 
                     rightBackDriveChannel   =9,   rightBackDriveSlot  =1,
                     mouthChannel            =2,   mouthSlot           =2,
                     indexerChannel          =1,   indexerSlot         =2,
                     shooter1Channel         =5,   shooter1Slot        =1,
                     shooter2Channel         =6,   shooter2Slot        =1,
                     tiltMotorChannel        =4,   tiltMotorSlot       =1,
                     // Pneumatic Solenoids
                     lowerWhackerChannel     =5,   whackerSlot         =2,
                     liftWhackerChannel      =6,
                     liftBrakeChannel        =7,   brakeSlot           =2,
                     lowerBrakeChannel       =8,   
                     // Digital inputs
                     chamberChannel          =7,   chamberSlot         =1,
                     bridgeChannel           =7,   bridgeSlot          =2,
                     encoderChannel          =10,   encoderSlot         =2,
                     pressureSwitchChannel   =1,  pressureSwitchSlot  = 1,
                     // analog inputs
                     potChannel              =3,   potSlot             =1,
                     // relay  output (spotlight and compressor)
                     spotlightChannel        =4,   spotlightSlot       =2,
                     indexerLEDChannel       =1,   indexerLEDSlot      =2,
                     shooterLEDChannel       =2,   shooterLEDSlot      =2,
                     compressorChannel       =8,   compressorSlot      =2;
                     
                     
    // the joystick control from driver's station
    RobotControlSystem controls;
    //Shooter Hardware
    Victor m_shooter1;
    Victor m_shooter2;
    ShooterDrive m_shooterDrive;
    // robot victors
    Victor m_indexer;
    Victor m_mouth;
    Victor m_tiltMotor; 
    // drivetrain
    RobotDrive drive;
    // robot sensors
    DiscoCounterEncoder m_shooterEncoder;
    PIDController shooterPID;
    AnalogChannel m_pot;
    DigitalInput m_Chamber;
    DigitalInput m_Bridge;
    //light relays
    Relay m_SpotlightRelay;
    Relay m_indexerLED;
    Relay m_shooterLED;
    // pneumatics
    DoubleSolenoid m_whacker;
    DoubleSolenoid m_brake;
    Compressor m_compressor;
    //camera/tracking
    AxisCamera m_goalCamera, m_ballCamera;
    LaserDragonTracker visionTracker;
    
    public LaserDragon(){
        // initialization of channels and slots for all robot systems. USE CAUTION
        controls = new ThreeJoystickControl(1,2,3); // sticks 1, 2, and 3 (interchangeable)
        drive = new RobotDrive(leftFrontDriveChannel, leftBackDriveChannel,
                               rightFrontDriveChannel, rightBackDriveChannel);
        drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        m_shooter1 = new Victor(shooter1Slot, shooter1Channel);
        m_shooter2 = new Victor(shooter2Slot, shooter2Channel);
        m_shooterDrive = new ShooterDrive(m_shooter1, m_shooter2);
        m_indexer = new Victor(indexerSlot, indexerChannel);
        m_mouth   = new Victor(mouthSlot, mouthChannel);
        m_tiltMotor = new Victor(tiltMotorSlot, tiltMotorChannel);
        m_shooterEncoder = new DiscoCounterEncoder(encoderSlot, encoderChannel, 1);
        m_shooterEncoder.setMaxPeriod(0.6);
        m_shooterEncoder.start();
        m_pot = new AnalogChannel(potSlot, potChannel);
        m_Chamber = new DigitalInput(chamberSlot, chamberChannel);
        m_Bridge = new DigitalInput(bridgeSlot, bridgeChannel);
        m_SpotlightRelay = new Relay(spotlightSlot, spotlightChannel, Relay.Direction.kForward);
        m_indexerLED     = new Relay(indexerLEDSlot, indexerLEDChannel, Relay.Direction.kForward);
        m_shooterLED     = new Relay(shooterLEDSlot, shooterLEDChannel, Relay.Direction.kForward);
        
        //pneumatics
        m_whacker = new DoubleSolenoid(whackerSlot, lowerWhackerChannel, liftWhackerChannel);
        m_brake    = new DoubleSolenoid(brakeSlot, lowerBrakeChannel, liftBrakeChannel);
        m_compressor = new Compressor(pressureSwitchSlot, pressureSwitchChannel,
                                     compressorSlot, compressorChannel);
        
        // initialize cameras
        //m_goalCamera = AxisCamera.getInstance("10.25.87.11");
        //m_ballCamera = AxisCamera.getInstance("10.25.87.12");
        visionTracker = new LaserDragonTracker(4, m_goalCamera);
        //pid controls
        initPID();   
    }
    
    public void initPID(){
        shooterPID = new PIDController(0.0017, 0.0068, 0, m_shooterEncoder, m_shooterDrive);
        shooterPID.setInputRange(100, 3500);
        shooterPID.setOutputRange(0, 1.0);
        shooterPID.setSetpoint(1600);
        shooterPID.disable();
    }
    
    public void disabled(){
        shooterPID.disable();
        m_compressor.stop();
        drive.tankDrive(0,0);
        m_indexer.set(0);
        m_mouth.set(0);
        m_tiltMotor.set(0);
        m_whacker.set(DoubleSolenoid.Value.kReverse);
        m_brake.set(DoubleSolenoid.Value.kReverse);
        
        System.out.println("disabled");
    }
    
    public void autonomous(){
    }

    public void operatorControl(){
        m_compressor.start();
        System.out.println("Operator Control"); 
        while(isEnabled()){
            drive.tankDrive(controls.leftDriveInput(),
                            controls.rightDriveInput());
            mouthControl();
            indexerControl();
            shooterControl();
            whackerControl();
            brakeControl();
            hoodTiltControl();
            LEDController();
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
    
    private static double indexerPower = 0.5;
    public void indexerControl(){
        int indexerState = controls.indexerInput();
        switch(indexerState){
            case RobotControlSystem.SEND:
                m_indexer.set(indexerPower); break;
            case RobotControlSystem.BACKWARD:
                m_indexer.set(-indexerPower); break;
            case RobotControlSystem.FORWARD:
                if(m_Chamber.get()){
                    m_indexer.set(indexerPower);
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
                m_whacker.set(DoubleSolenoid.Value.kForward);
                break;
            case RobotControlSystem.BACKWARD:
                m_whacker.set(DoubleSolenoid.Value.kReverse);
                break;
        }
    }
    
    private int prevShootEnableState;
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
                        shooterPID.setSetpoint(currentSetpoint-100);
                    }
                    break;
            }
        }
        if(shootEnableState == RobotControlSystem.SHOOTER_ENABLE &&
           prevShootEnableState == RobotControlSystem.NONE){
            if(shooterPID.isEnable()){
                shooterPID.disable();
                m_compressor.start();
            } else {
                shooterPID.enable();
                m_compressor.stop();
            } 
        }
        prevShootEnableState = shootEnableState;
    }
    
    private int prevBrakeInput;
    public void brakeControl(){
        int brakeInput = controls.brakeInput();
        if(brakeInput == RobotControlSystem.FORWARD && 
           prevBrakeInput == RobotControlSystem.NONE){
            if(m_brake.get() == DoubleSolenoid.Value.kForward){
                m_brake.set(DoubleSolenoid.Value.kReverse);
                System.out.println("reverse");
            } else if(m_brake.get() == DoubleSolenoid.Value.kReverse){
                m_brake.set(DoubleSolenoid.Value.kForward);
                System.out.println("forward");
            }
        }
        prevBrakeInput = brakeInput;
    }
    
    public void hoodTiltControl(){
        int hoodState = controls.hoodTiltInput();
        switch(hoodState){
            case RobotControlSystem.FORWARD:
                m_tiltMotor.set(1); break;
            case RobotControlSystem.BACKWARD:
                m_tiltMotor.set(-1); break;
            case RobotControlSystem.NONE:
                m_tiltMotor.set(0);
        }
    }
    
    private int shooterLEDTogglePeriod;
    private long lastShooterLEDToggleTime;
    private boolean lastShooterPIDState;
    private Relay.Value lastShooterLEDState;
    public void LEDController(){
        // indexer lights
        if(m_indexer.get() != 0 || m_mouth.get() != 0){
            m_indexerLED.set(Relay.Value.kForward);
        } else {
            m_indexerLED.set(Relay.Value.kOff);
        }
        
        // shooter lights
        if(shooterPID.isEnable()){
            if(lastShooterPIDState == false){
                lastShooterLEDToggleTime = System.currentTimeMillis();
                lastShooterLEDState = Relay.Value.kOff;
            }
            shooterLEDTogglePeriod = (int)(5625*m_shooterEncoder.getPeriod() - 62.5);
            long currentTime = System.currentTimeMillis();
            if(currentTime-lastShooterLEDToggleTime >= shooterLEDTogglePeriod){
                lastShooterLEDState = (lastShooterLEDState == Relay.Value.kForward) ?
                                      Relay.Value.kOff : Relay.Value.kForward;
                m_shooterLED.set(lastShooterLEDState);
                lastShooterLEDToggleTime = currentTime;
            }
        } else if(lastShooterPIDState == true){
            m_shooterLED.set(Relay.Value.kOff);
        }
        
        lastShooterPIDState = shooterPID.isEnable();  
    } 
}
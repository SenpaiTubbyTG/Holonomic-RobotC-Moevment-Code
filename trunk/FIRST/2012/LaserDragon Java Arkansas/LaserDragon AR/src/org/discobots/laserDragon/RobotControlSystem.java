package org.discobots.laserDragon;

/**
 * this interface is designed to define a setup for Joysticks. I have written
 * this to simplify the addition of new setup types
 * @author mrdouglass
 */
public interface RobotControlSystem {
    public static final int 
                            // direct up-down control
                            NONE = 0, // for readability
                            FORWARD = 1,
                            BACKWARD = 2,
                            // special indexer "sending" component
                            SEND = 3,
                            // shooter system control
                            SHOOTER_INC = 0,
                            SHOOTER_DEC = 1,
                            SHOOTER_ENABLE = 2,
                            SHOOTER_DISABLE = 3;
    
    public abstract int mouthInput();
    public abstract int indexerInput();
    public abstract int shooterEnableInput();
    public abstract int shooterSpeedInput();
    public abstract int hoodTiltInput();
    public abstract int whackerInput();
    public abstract double leftDriveInput();
    public abstract double rightDriveInput();
}
/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package com.disco2013;


import edu.wpi.first.wpilibj.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Main extends IterativeRobot {
    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public static Victor LFM = new Victor(1);
    public static Victor LBM = new Victor(2);
    public static Victor RFM = new Victor(3);
    public static Victor RBM = new Victor(4);
    public static Victor Shooter1 = new Victor(5);
    public static RobotDrive drive = new RobotDrive(LFM,LBM,RFM,RBM);
    public static Joystick Stick1 = new Joystick(1);
    public static Joystick Stick2 = new Joystick(2);
    public void robotInit() {
    
    }

    /**
     * This function is called periodically during autonomous
     */
    public void autonomousPeriodic() {

    }

    /**
     * This function is called periodically during operator control
     */
    public void teleopPeriodic() {
        drive.tankDrive(Stick1.getY(),Stick2.getY());
        if(Stick1.getRawButton(1)==true)
        {
            Shooter1.set(0.25);
        }
        else if(Stick1.getRawButton(2)==true)
        {
            Shooter1.set(0.5);
        }
        else if(Stick1.getRawButton(3)==true)
        {
            Shooter1.set(0.75);
        }
        else if(Stick1.getRawButton(4)==true)
        {
            Shooter1.set(1.0);
        }
        }
    }

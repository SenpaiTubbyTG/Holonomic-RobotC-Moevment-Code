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
    
    public void robotInit() {
        HW.drive.setSafetyEnabled(false);
        Watchdog.getInstance().setEnabled(false);
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        HW.drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        
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
        HW.drive.tankDrive(HW.Stick1.getLY(),HW.Stick1.getRY());
        //System.out.println(Shooter1.get());
        
        
        if(HW.Stick1.getRawButton(HW.Stick1.BTN_X)==true)
        {
            HW.Shooter1.set(0.25);
        }
        else if(HW.Stick1.getRawButton(HW.Stick1.BTN_Y)==true)
        {
            HW.Shooter1.set(0.5);
        }
        else if(HW.Stick1.getRawButton(HW.Stick1.BTN_B)==true)
        {
            HW.Shooter1.set(0.75);
        }
        else if(HW.Stick1.getRawButton(HW.Stick1.BTN_A)==true)
        {
            HW.Shooter1.set(1.0);
        }
        else 
        {
            HW.Shooter1.set(0.0);
        }
    
        }
}

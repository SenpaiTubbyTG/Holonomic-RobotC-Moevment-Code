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
        HW.drive.tankDrive(HW.Stick1.getY(),HW.Stick2.getY());
        if(HW.Stick1.getRawButton(1)==true)
        {
            HW.Shooter1.set(0.25);
        }
        else if(HW.Stick1.getRawButton(2)==true)
        {
            HW.Shooter1.set(0.5);
        }
        else if(HW.Stick1.getRawButton(3)==true)
        {
            HW.Shooter1.set(0.75);
        }
        else if(HW.Stick1.getRawButton(4)==true)
        {
            HW.Shooter1.set(1.0);
        }
        }
    }

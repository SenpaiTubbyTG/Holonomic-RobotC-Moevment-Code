/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package com.disco2010;

import edu.wpi.first.wpilibj.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Main extends IterativeRobot {
       public static Autonomous auton = new Autonomous();
       public static Teleop teleop = new Teleop();
       public static Init init = new Init();
       int zone = 2;
       String display = "strafe/turn";

    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit()
    {
        init.Init();
        
    }

    /**
     * This function is called once everytime the robot is disabled
     */
    public void disabledInit() 
    {
        HW.rightEncoder.reset();
        HW.rightEncoder.stop();

        //HW.leftEncoder.reset();
        //HW.leftEncoder.stop();
        
        HW.testEncoder.reset();
        HW.testEncoder.stop();

        HW.camPan.set(0.5);
        HW.camTilt.set(0.5);
    }

    /**
     * Periodic code for disabled mode should go here.
     */
    public void disabledPeriodic() 
    {
        HW.rightEncoder.stop();
        HW.rightEncoder.reset();
    }

    /**
     * This function is called once befor Autonomous
     */
    public void autonomousInit() 
    {
        init.AutonInit();
        if(HW.autonMode.get())
        {
            zone = 3;
            display = "GOALKEEPER";
        }
        
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser2, 1, "Autonomous Zone: " + display);
        DriverStationLCD.getInstance().updateLCD();
    }

    /**
     * This function is called periodically during autonomous
     */
    public void autonomousPeriodic() 
    {
        //auton.switchAuton(zone);  //autonomous zone selection
                                     //zone legend: 1=striker, 2=mid, 3=goalkeeper
        //auton.GoalZoneStraightBlind();
    } /**
     * This function is called periodically during operator control
     */
    public void teleopInit()
    {
        init.TeleopInit();
    }
    public void teleopPeriodic() {
        teleop.start();
    }
}

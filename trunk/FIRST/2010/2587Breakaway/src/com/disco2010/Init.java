/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.disco2010;

import edu.wpi.first.wpilibj.Watchdog;

/**
 * @purpose Initialize the auton and teleop things.
 * @author pavchag
 */
public class Init{
    public void Init()
    {
        HW.drive.setInvertedMotor(DiscoDrive.kLeftMotor, true); //Invert Left
        HW.drive.setInvertedMotor(DiscoDrive.kRightMotor, true); //Invert Right
        HW.drive.setInvertedMotor(DiscoDrive.kFrontMotor, false); //Don't Invert Front
        HW.drive.setInvertedMotor(DiscoDrive.kRearMotor, false); //Don't Invert Rear

        /*
         * Send Blank Data to the Dashboard on Initilization
         */
        Target[] newTargets = new Target[1];
        newTargets[0] = new Target();
        newTargets[0].m_majorRadius = 0;
        newTargets[0].m_minorRadius = 0;
        newTargets[0].m_score = 0;
        HW.trackerDash.updateVisionDashboard(0.0, 0.0, 0.0, 0.0, newTargets);

        //HW.ultra.setAutomaticMode(true);
    }
    public void AutonInit()
    {
        Watchdog.getInstance().setExpiration(1000);

        HW.rightEncoder.setDistancePerPulse((8*Math.PI)/((77/75)*128));
        //HW.leftEncoder.setDistancePerPulse((8*Math.PI)/((77/75)*128));
        //HW.frontEncoder.setDistancePerPulse((8*Math.PI)/((22/15)*128));
        //HW.rearEncoder.setDistancePerPulse((8*Math.PI)/((22/15)*128));

        HW.rightEncoder.start();
        HW.rightEncoder.reset();

        //HW.leftEncoder.start();
        //HW.leftEncoder.reset();
    }

    public void TeleopInit()
    {
        HW.rightEncoder.setDistancePerPulse((8*Math.PI)/187);
        HW.testEncoder.setDistancePerPulse((8*Math.PI)/187);
        //HW.frontEncoder.setDistancePerPulse((8*Math.PI)/((22/15)*128));
        //HW.rearEncoder.setDistancePerPulse((8*Math.PI)/((22/15)*128));
        HW.testEncoder.setMinRate(0.1);
        HW.testEncoder.setMaxPeriod(2.0);
        HW.rightEncoder.start();
        HW.rightEncoder.reset();
        HW.testEncoder.start();
        HW.testEncoder.reset();
    }

}

/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package Breakaway;


import Utils.DiscoUtils;
import edu.wpi.first.wpilibj.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Main extends IterativeRobot {
    double rDistance = 0.0;
    double lDistance = 0.0;
    double startTime = 0.0;
    double tEncRate = 0.0;
    double lEncStartDist = 0.0;

    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit()
    {
        HW.drive.setInvertedMotor(DiscoDrive.kLeftMotor, true); //Invert Left
        HW.drive.setInvertedMotor(DiscoDrive.kRightMotor, true); //Invert Right
        HW.drive.setInvertedMotor(DiscoDrive.kFrontMotor, false); //Don't Invert Front
        HW.drive.setInvertedMotor(DiscoDrive.kRearMotor, false); //Don't Invert Rear
    }

    /**
     * This function is called once everytime the robot is disabled
     */
    public void disabledInit()
    {
        HW.leftEncoder.reset();
        HW.leftEncoder.stop();
        HW.rightEncoder.reset();
        HW.rightEncoder.stop();
    }

    /**
     * Periodic code for disabled mode should go here.
     */
    public void disabledPeriodic()
    {
        HW.leftEncoder.reset();
        HW.leftEncoder.stop();
        HW.rightEncoder.stop();
        HW.rightEncoder.reset();
    }

    /**
     * This function is called once befor Autonomous
     */
    public void autonomousInit() { }

    /**
     * This function is called periodically during autonomous
     */
    public void autonomousPeriodic() {} /**
     * This function is called periodically during operator control
     */
    public void teleopInit()
    {
        HW.leftEncoder.setDistancePerPulse((8*Math.PI)/94);
        HW.leftEncoder.start();
        HW.leftEncoder.reset();
        HW.rightEncoder.setDistancePerPulse((8*Math.PI)/94);
        HW.rightEncoder.start();
        HW.rightEncoder.reset();
    }
    public void teleopPeriodic() {
        HW.drive.basicDrive(0.0, 0.0, HW.driveStick1.getY(), HW.driveStick2.getY());
        startTime = Timer.getFPGATimestamp();
        lEncStartDist = HW.rightEncoder.getDistance();
        
        //HW.drive.holonomicDrive(HW.driveStick1.getMagnitude(), HW.driveStick1.getDirectionDegrees(), HW.driveStick2.getX());
        //Drive system altered: 2 wheels removed, holonomic drive is no more

        //lDistance += (Timer.getFPGATimestamp() - startTime) * lEncRate;
        Timer.delay(0.1);
        tEncRate = (HW.leftEncoder.getDistance() - lEncStartDist) / (Timer.getFPGATimestamp() - startTime);
        DiscoUtils.debugPrintln("Test Encoder Rate: " + HW.leftEncoder.getRate());
        DiscoUtils.debugPrintln("Test Encoder Dist: " + HW.leftEncoder.getDistance());
        DiscoUtils.debugPrintln("Test Encoder Period: " + HW.leftEncoder.getPeriod());
        DiscoUtils.debugPrintln("Right Encoder Rate: " + HW.rightEncoder.getRate());
        DiscoUtils.debugPrintln("Test Encoder Calculated: " + tEncRate);
    }
    
}

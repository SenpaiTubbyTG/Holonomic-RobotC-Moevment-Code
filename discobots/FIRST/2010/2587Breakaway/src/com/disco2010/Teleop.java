/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.disco2010;

import edu.wpi.first.wpilibj.*;

/**
 * @purpose This is where all of the teleop code is located.
 * @author pavchag
 */
public class Teleop {

    double ballIn;
    boolean kicking = false;
    boolean loading;
    Timer loadTime;
    double rDistance = 0.0;
    double lDistance = 0.0;
    double startTime = 0.0;
    double lEncRate = 0.0;
    double lEncStartDist = 0.0;

    public void start() {
        
        Watchdog.getInstance().setExpiration(1000);
        startTime = Timer.getFPGATimestamp();
        lEncStartDist = HW.rightEncoder.getDistance();

        //HW.drive.holonomicDrive(HW.driveStick1.getMagnitude(), HW.driveStick1.getDirectionDegrees(), HW.driveStick2.getX());
        //Drive system altered: 2 wheels removed, holonomic drive is no more
        HW.drive.basicDrive(0.0, 0.0, HW.driveStick1.getY(), HW.driveStick2.getY());
        
        //lDistance += (Timer.getFPGATimestamp() - startTime) * lEncRate;
        Timer.delay(0.1);
        lEncRate = (HW.rightEncoder.getDistance() - lEncStartDist) / (Timer.getFPGATimestamp() - startTime);
        DiscoUtils.debugPrintln("Left Encoder Rate: " + HW.testEncoder.getRate());
        DiscoUtils.debugPrintln("Left Encoder Dist: " + HW.testEncoder.getDistance());
        DiscoUtils.debugPrintln("Left Encoder Period: " + HW.testEncoder.getPeriod());
        DiscoUtils.debugPrintln("Right Encoder Rate: " + HW.rightEncoder.getRate());
        DiscoUtils.debugPrintln("Left Encoder Calculated: " + lEncRate);

        /*DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser2, 1, "LEncDist:                                 ");
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser3, 1, "LECalRat:                                 ");
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser4, 1, "LEClsRat:                                 ");
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser5, 1, "REncDist:                                 ");
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser6, 1, "REncRate:                                 ");
        DriverStationLCD.getInstance().updateLCD();
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser2, 1, "LEncDist: " + HW.leftEncoder.getDistance());
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser3, 1, "LECalRat: " + lEncRate);
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser4, 1, "LEClsRat: " + HW.leftEncoder.getRate());
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser5, 1, "REncDist: " + HW.rightEncoder.getDistance());
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser6, 1, "REncRate: " + HW.rightEncoder.getRate());
        DriverStationLCD.getInstance().updateLCD();*/
        
        //rDistance += (Timer.getFPGATimestamp() - startTime) * HW.rightEncoder.getRate();

        /*bar up/down
        if (HW.kickhandle.getRawButton(6) && HW.barUpSwitch.get()) {
            HW.kicker.moveBar(true);
        } else if (HW.kickhandle.getRawButton(7) && HW.barDownSwitch.get()) {
            HW.kicker.moveBar(false);
        } else {
            HW.kickerBar.set(0.0);
        }*/

        /* DRIBBLER
        HW.rightDribbler.set(-HW.kickhandle.getAxis(Joystick.AxisType.kY));
        HW.leftDribbler.set(HW.kickhandle.getAxis(Joystick.AxisType.kY));
        */
       /* KICKER
        if (HW.kickhandle.getTrigger()
                || HW.driveStick2.getTrigger()
                && HW.kickSwitch.get()
                && !kicking) {
            HW.kicker.kick(4);
            loading = false;
            kicking = true;
        } else if (HW.kickhandle.getRawButton(5) == true
                || HW.driveStick2.getRawButton(5)
                && HW.kickSwitch.get() == true
                && !kicking) {
            HW.kicker.kick(3);
            loading = false;
            kicking = true;
        } else if (HW.kickhandle.getRawButton(3) == true
                || HW.driveStick2.getRawButton(3)
                && HW.kickSwitch.get() == true
                && !kicking) {
            HW.kicker.kick(2);
            loading = false;
            kicking = true;
        } else if (HW.kickhandle.getRawButton(4) == true
                || HW.driveStick2.getRawButton(4)
                && HW.kickSwitch.get() == true
                && !kicking) {
            HW.kicker.kick(1);
            loading = false;
            kicking = true;
        } else if (!HW.kickhandle.getTrigger()
                && !HW.kickhandle.getRawButton(4)
                && !HW.kickhandle.getRawButton(3)
                && !HW.kickhandle.getRawButton(5)
                && !HW.driveStick2.getTrigger()
                && !HW.driveStick2.getRawButton(4)
                && !HW.driveStick2.getRawButton(3)
                && !HW.driveStick2.getRawButton(5)
                && HW.loadSwitch.get()) {
            HW.kicker.load();
            loading = true;
            kicking = false;
        }
        if (!HW.loadSwitch.get()) {
            HW.kicker.kill();
            loading = false;
            kicking = false;
        }

        if (HW.kickhandle.getRawButton(2)) {
            HW.camPan.set(0.5);
            HW.camTilt.set(0.5);
        }*/
        
        //Camera Control for Subsystem Operator
        /*if (HW.kickhandle.getRawButton(11)) {
            HW.camTilt.set(DiscoUtils.rawToPosition((double) HW.camTilt.getRaw()) + 0.05);
        } else if (HW.kickhandle.getRawButton(10)) {
            HW.camTilt.set(DiscoUtils.rawToPosition((double) HW.camTilt.getRaw()) - 0.05);
        }

        if (HW.kickhandle.getRawButton(8)) {
            HW.camPan.set(DiscoUtils.rawToPosition((double) HW.camPan.getRaw()) + 0.05);
        } else if (HW.kickhandle.getRawButton(9)) {
            HW.camPan.set(DiscoUtils.rawToPosition((double) HW.camPan.getRaw()) - 0.05);
        }*/

        /* DEBUG PRINTING
        //DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser4, 1, "I/O 8 = " + HW.autonMode.get());
        //DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser5, 1, "kickSwitch " + kickSwitch);
        //DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser5, 1, "REncDist: " + HW.rightEncoder.getDistance());
        //DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser6, 1, "LEncDist: " + HW.leftEncoder.getDistance());
        //String windowUp;
        //String windowDown;
        //String kickSwitch;
        //String loadSwitch;

        /*if(!HW.barUpSwitch.get())
        windowUp = "Pressed";
        else windowUp = "Nope";

        if(!HW.barDownSwitch.get())
        windowDown = "Pressed";
        else windowDown = "Nope";*/

        /*if(!HW.kickSwitch.get())
        kickSwitch = "Pressed";
        else kickSwitch = "Nope";*/

        /*if(!HW.loadSwitch.get())
        loadSwitch = "Pressed";
        else loadSwitch = "Nope";
        System.out.println("TstEncDst: " + HW.leftEncoder.getDistance());
        System.out.println("Distance: " + HW.rightEncoder.getDistance());
        System.out.println("Raw: " + HW.rightEncoder.getRaw());
        System.out.println("Get: " + HW.rightEncoder.get());
         */

        /* The Tracking lines
        //HW.tracker.track();
         */
    }
}

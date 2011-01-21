/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.disco2010;
import edu.wpi.first.wpilibj.Watchdog;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.DriverStationLCD;

/**
 * @purpose All of the different autonomous modes go here
 * @author pavchag
 */
public class Autonomous {
    boolean firstTime = true;
    long beginTime;
    int kickNo = 1;
    int kickStrength = 2;
    int kickMax;
    double speed = 0.0;
/*----------------------------
 * ZONE DEMARCATION
 *
 * ZONE 1 = 1 BALL ATTACK ZONE
 * ZONE 2 = 2 BALLS MID ZONE
 * ZONE 3 = 3 BALLS GOAL ZONE
 */
    /*public void switchAuton(int zone)
    {
        switch(zone)
        {
            case 1:MidZone();kickStrength = 3;break;
            case 2:MidZone();break;
            case 3:GoalZoneBasic();break;
            default:MidZone();
        }
    }

    public void autonKick()
    {
        HW.drive.basicDrive(0, 0, 0, 0);
        long kickStartTime = Timer.getUsClock();
        if(HW.tracker.centered && checkCenteredCam())
        {
            if(HW.kickSwitch.get() && ((Timer.getUsClock() - kickStartTime) < 1000000))
            {
                HW.kicker.kick(kickStrength);
            }
        }
        else
        //HW.rightEncoder.reset();
        //HW.leftEncoder.reset();
    }

    public void blindAutonKick()
    {
        long kickStartTime = Timer.getUsClock();
        while(HW.kickSwitch.get() && ((Timer.getUsClock() - kickStartTime) < 500000))
        {
            HW.kicker.kick(2);
        }
        //HW.rightEncoder.reset();
        //HW.leftEncoder.reset();
        HW.kicker.load();
    }

    private void displayStuff()
    {
        System.out.println("Right Distance: "+HW.rightEncoder.getDistance());
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser5, 1,
                                               "REncDist: " + HW.rightEncoder.getDistance());
        System.out.println("Left Distance: "+HW.leftEncoder.getDistance());
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser5, 1,
                                               "LEncDist: " + HW.leftEncoder.getDistance());
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser6, 1, "Gyro: " + HW.gyro.getAngle());
        DriverStationLCD.getInstance().updateLCD();
    }

    public void clearPrint()
    {
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser4, 1, "                     ");
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser5, 1, "                     ");
    }

    public void accelStraight()
    {
        if(Math.abs(HW.rightEncoder.getDistance()) == Math.abs(HW.leftEncoder.getDistance()))
        {
            for(double x=0.0;x<=0.4;x+=0.01)
                HW.drive.basicDrive(x,x,0.0,0.0);
        }

        else if(Math.abs(HW.rightEncoder.getDistance()) < Math.abs(HW.leftEncoder.getDistance()))
        {
            for(double x=0.0;x<=0.4;x+=0.01)
                HW.drive.basicDrive(x, x-0.01, 0.0, 0.0);
        }
        else if(Math.abs(HW.rightEncoder.getDistance()) > Math.abs(HW.leftEncoder.getDistance()))
        {
            for(double x=0;x<=0.4;x+=0.01)
                HW.drive.basicDrive(x-0.01, x, 0.0, 0.0);
        }
    }

    public void driveStraight()
    {
        if(Math.abs(HW.rightEncoder.getDistance()) == Math.abs(HW.leftEncoder.getDistance()))
        {
            HW.drive.basicDrive(0.4,0.4,0.0,0.0);
        }

        else if(Math.abs(HW.rightEncoder.getDistance()) < Math.abs(HW.leftEncoder.getDistance()))
        {
            HW.drive.basicDrive(0.4, 0.39, 0.0, 0.0);
        }
        else if(Math.abs(HW.rightEncoder.getDistance()) > Math.abs(HW.leftEncoder.getDistance()))
        {
            HW.drive.basicDrive(0.39, 0.4, 0.0, 0.0);
        }
        DriverStationLCD.getInstance().println(DriverStationLCD.Line.kMain6, 1, "DRIVING STRAIGHT");
        DriverStationLCD.getInstance().updateLCD();
    }
    
    public void strafe(double time)
    {
        for(double x=0.0;x<=1.0;x+=0.005)
        {
            if(Math.abs(HW.rightEncoder.getDistance()) > Math.abs(HW.leftEncoder.getDistance()))
                HW.drive.autonDrive(0.0, 0.0, x, -(x-0.01));
            else if(Math.abs(HW.rightEncoder.getDistance()) < Math.abs(HW.leftEncoder.getDistance()))
                HW.drive.autonDrive(0.0, 0.0, x-0.01, -x);
            else HW.drive.autonDrive(0.0, 0.0, x, -x);
        }
        Timer.delay(time);
        HW.drive.autonDrive(0.0, 0.0, 0.0, 0.0);
        resetEncoders();
    }

    public void resetEncoders()
    {
        HW.rightEncoder.reset();
        HW.leftEncoder.reset();
        clearPrint();
    }

    public void turnCCW()
    {
        for(double x=0.0;x<=0.75;x+=0.01)
            HW.drive.holonomicDrive(0.0, 0.0, -x);
        Timer.delay(0.35);
        HW.drive.autonDrive(0.0, 0.0, 0.0, 0.0);
        resetEncoders();
    }

    public boolean checkCenteredCam()
    {
        if(DiscoUtils.rawToPosition((double) HW.camPan.getRaw()) <= 0.6 && DiscoUtils.rawToPosition((double) HW.camPan.getRaw()) >= 0.4)
            return true;
        else
            return false;
    }

    public void MidZone()
    {
        if(firstTime)
        {
            if(HW.barDownSwitch.get())
            {
                HW.kicker.moveBar(false);
                Timer.delay(0.5);
                HW.kickerBar.set(0.0);
            }
            HW.rightEncoder.reset();
            HW.leftEncoder.reset();
            kickMax = 2;
            //HW.rightDribbler.set(-0.25);
            //HW.leftDribbler.set(0.25);
            strafe(1.0);        //for the damn plate at bayou regional
            turnCCW();
            HW.drive.basicDrive(0.0, 0.0, 0.0, 0.0);
            firstTime = false;
        }
        else
        {
            HW.drive.basicDrive(0.0, 0.0, 0.0, 0.0);
            Timer.delay(1.0);
        }

    }

    public void GoalZoneSingle()
    {
        kickMax = 1;
        if(firstTime)
        {
            if(HW.barDownSwitch.get())
            {
                HW.kicker.moveBar(false);
                Timer.delay(0.5);
                HW.kickerBar.set(0.0);
            }
            HW.rightEncoder.reset();
            HW.leftEncoder.reset();
            firstTime = false;
            HW.camTilt.set(0.5);
            HW.camPan.set(0.5);
        }
        if(HW.loadSwitch.get())
                HW.kicker.load();
        if(kickNo <= kickMax)
        {
            displayStuff();
            Watchdog.getInstance().feed();
            if((Math.abs(HW.rightEncoder.getDistance()) <= 20.0 ||
               Math.abs(HW.leftEncoder.getDistance()) <= 20.0)) //&&
               //HW.ultra.getRangeInches() >= 4.0)
                driveStraight();

            if (Math.abs(HW.rightEncoder.getDistance()) >= 20.0 && 
                Math.abs(HW.leftEncoder.getDistance()) >= 20.0)// &&
                //HW.ultra.getRangeInches() <= 4.0)
            {
                //autonKick();

                long kickStartTime = Timer.getUsClock();
                while(Timer.getUsClock() - kickStartTime < 400000 && HW.kickSwitch.get())
                {
                    HW.kicker.kick(4);
                }
                HW.kicker.kill();
            }
            Watchdog.getInstance().feed();
            kickNo++;
        }

        if(kickNo > kickMax)
            turnCCW();
    }

    public void GoalZoneStraight()
    {
        
        if(firstTime)
        {
            if(HW.barDownSwitch.get())
            {
                HW.kicker.moveBar(false);
                Timer.delay(0.5);
                HW.kickerBar.set(0.0);
            }
            HW.rightEncoder.reset();
            HW.leftEncoder.reset();
            firstTime = false;
            HW.camTilt.set(0.5);
            HW.camPan.set(0.5);
            kickMax = 3;
        }
        HW.tracker.track();
        if(HW.loadSwitch.get())
            HW.kicker.load();
        if(kickNo <= kickMax)
        {
            displayStuff();
            Watchdog.getInstance().feed();
            if((Math.abs(HW.rightEncoder.getDistance()) <= 20.0 ||
               Math.abs(HW.leftEncoder.getDistance()) <= 20.0))// &&
               //HW.ultra.getRangeInches() >= 4.0)
                driveStraight();

            if (Math.abs(HW.rightEncoder.getDistance()) >= 20.0 &&
                Math.abs(HW.leftEncoder.getDistance()) >= 20.0)// &&
                //HW.ultra.getRangeInches() <= 4.0)
            {
                autonKick();
            }
            Watchdog.getInstance().feed();
            kickNo++;
        }

        if(kickNo > kickMax)
            turnCCW();
    }

    public void GoalZoneStraightBlind()
    {
        if(firstTime)
        {
            if(HW.barDownSwitch.get())
            {
                HW.kicker.moveBar(false);
                Timer.delay(0.5);
                HW.kickerBar.set(0.0);
            }
            HW.rightEncoder.reset();
            HW.leftEncoder.reset();
            firstTime = false;
            HW.camTilt.set(0.5);
            HW.camPan.set(0.5);
            kickMax = 3;
        }
        if(HW.loadSwitch.get())
            HW.kicker.load();
        if(kickNo <= kickMax)
        {
            displayStuff();
            Watchdog.getInstance().feed();
            if(Math.abs(HW.rightEncoder.getDistance()) <= 20.0 ||
               Math.abs(HW.leftEncoder.getDistance()) <= 20.0)
                driveStraight();

            if (Math.abs(HW.rightEncoder.getDistance()) >= 20.0 &&
                Math.abs(HW.leftEncoder.getDistance()) >= 20.0)
            {
                blindAutonKick();
            }
            Watchdog.getInstance().feed();
            kickNo++;
        }

        if(kickNo > kickMax)
            turnCCW();
    }

    public void GoalZoneBasic()
    {
        if(firstTime)
        {
            DriverStationLCD.getInstance().println(DriverStationLCD.Line.kMain6, 1, "12:25 am");
            DriverStationLCD.getInstance().updateLCD();
            Watchdog.getInstance().setExpiration(5.0);
            Watchdog.getInstance().feed();
            kickMax = 3;
            if(HW.barDownSwitch.get())
            {
                HW.kicker.moveBar(false);
                Timer.delay(0.5);
                HW.kickerBar.set(0.0);
                Watchdog.getInstance().feed();
            }
            displayStuff();
            HW.rightEncoder.reset();
            HW.leftEncoder.reset();
            HW.camTilt.set(0.5);
            HW.camPan.set(0.5);
            displayStuff();
            HW.rightEncoder.reset();
            HW.leftEncoder.reset();
            beginTime = Timer.getUsClock();
            Watchdog.getInstance().feed();
            while((Math.abs(HW.rightEncoder.getDistance()) <= 30.0 ||
                  Math.abs(HW.leftEncoder.getDistance()) <= 30.0) &&
                  Timer.getUsClock() - beginTime <= 1500000)
                    {
                        Watchdog.getInstance().feed();
                        if(speed <= 0.5)
                        {
                            HW.drive.holonomicDrive(speed, 0.0, -speed/5);
                            speed += 0.01;
                        }
                        else
                            HW.drive.holonomicDrive(speed, 0.0, -speed/8);
                    }
            firstTime = false;
        }
        if(HW.loadSwitch.get())
            HW.kicker.load();

        if(kickNo < kickMax)
        {
            Watchdog.getInstance().feed();
            blindAutonKick();
            if(HW.loadSwitch.get())
                HW.kicker.load();
            beginTime = Timer.getUsClock();
            while((Math.abs(HW.rightEncoder.getDistance()) <= 40.0 ||
                  Math.abs(HW.leftEncoder.getDistance()) <= 40.0) &&
                  Timer.getUsClock() - beginTime <= 2000000)
                    {
                        Watchdog.getInstance().feed();
                        HW.drive.holonomicDrive(speed, 0.0, -speed/8);
                    }
            kickNo++;
        }
        else if(kickNo == kickMax)
        {
            HW.drive.holonomicDrive(speed, 0.0, -speed/10);
            Watchdog.getInstance().feed();
            blindAutonKick();
            Timer.delay(0.5);
            kickNo++;
            turnCCW();
            HW.drive.basicDrive(0.0, 0.0, 0.0, 0.0);
            Watchdog.getInstance().feed();
        }
        else
        {
            HW.drive.basicDrive(0.0, 0.0, 0.0, 0.0);
            Watchdog.getInstance().feed();
            Timer.delay(1.0);
        }
    }*/

}

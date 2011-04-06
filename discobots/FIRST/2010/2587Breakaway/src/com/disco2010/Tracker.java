/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.disco2010;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.camera.*;
import edu.wpi.first.wpilibj.image.*;

/**
 *
 * @author Nelson
 */
public class Tracker {

    boolean targetFound;
    double kScoreThreshold = .02;
    double searchPan;
    double sprinkle;
    double tiltSearch;
    boolean searchPanIncrease;
    int failCount;
    AxisCamera cam;
    boolean centered;
    TrackerDashboard trackerDashboard;

    boolean lastTrigger;
    boolean lockedOn = false;

    /**
     * @class Tracker
     * @purpose  Constructor for the Tracker Class
     * @param panServo - The Servo object that will pan the camera
     * @param tiltServo - The Servo object that will tilt the camera
     */
    public Tracker(Servo panServo, Servo tiltServo) {
        cam = AxisCamera.getInstance();
        cam.writeResolution(AxisCamera.ResolutionT.k320x240);
        cam.writeBrightness(0);
        cam.writeRotation(AxisCamera.RotationT.k0);
        targetFound = false;
        searchPan = 0.1;
        sprinkle = 0.1;
        searchPanIncrease = true;
        tiltSearch = 0.25;
        failCount = 0;
        trackerDashboard = new TrackerDashboard();

        lastTrigger = false;

        HW.gyro.setSensitivity(.007);
        HW.drive.initiateTurnController();
    }

    private void debugCamPan(Target[] targets) {
        DiscoUtils.debugPrintln("Raw Value: " + HW.camPan.getRaw());
        DiscoUtils.debugPrintln("Converted raw value: " + DiscoUtils.rawToPosition((double) HW.camPan.getRaw()));
        DiscoUtils.debugPrintln("Horizontal Angle: " + targets[0].getHorizontalAngle());
        DiscoUtils.debugPrintln("HorizontalAngle/180 = " + (targets[0].getHorizontalAngle() / 180.0));
        DiscoUtils.debugPrintln("CamPan set to: " + ((targets[0].getHorizontalAngle() / 180.0) + DiscoUtils.rawToPosition((double) HW.camPan.getRaw())));
    }

    private void debugCamTilt(double change) {
        DiscoUtils.debugPrintln("camTilt set to " + ((DiscoUtils.rawToPosition(HW.camPan.getRaw())) + change));
    }

    public void sprinklePan() {
        HW.camPan.set(sprinkle);
        //HW.camTilt.set(tiltSearch);
        sprinkle += 0.04;
        if (sprinkle >= 1.0) {
            sprinkle = 0;
        }
        centered = false;
    }

    private void failCount() {
        failCount++;
        if (failCount >= 5) {
            failCount = 0;
            targetFound = false;
        }
    }

    private void panTrack(Target[] targets) {
        if (targets[0].m_xPos < -0.25 || targets[0].m_xPos > 0.25) {
            //debugCamPan(targets);
            HW.camPan.set(DiscoUtils.rawToPosition((double) HW.camPan.getRaw()) - (targets[0].getHorizontalAngle() / 180.0));
            centered = false;
        } else if (targets[0].m_xPos < -0.01 && targets[0].m_xPos > -0.25) {
            HW.camPan.set((DiscoUtils.rawToPosition((double) HW.camPan.getRaw())) - 0.001);
            centered = true;
        } else if (targets[0].m_xPos > 0.01 && targets[0].m_xPos < 0.25) {
            HW.camPan.set((DiscoUtils.rawToPosition((double) HW.camPan.getRaw())) + 0.001);
            centered = true;
        }
        sprinkle = DiscoUtils.rawToPosition((double) HW.camPan.getRaw());
    }

    private void tiltTrack(Target[] targets) {
        if (targets[0].m_yPos < -0.05) {
            HW.camTilt.set(DiscoUtils.rawToPosition((double) HW.camTilt.getRaw()) + 0.01);
            //debugCamTilt(0.01);
        } else if (targets[0].m_yPos > 0.05) {
            HW.camTilt.set(DiscoUtils.rawToPosition((double) HW.camTilt.getRaw()) - 0.01);
            //debugCamTilt(-0.01);
        }
        tiltSearch = DiscoUtils.rawToPosition((double) HW.camTilt.getRaw());
    }

    /**
     * @class track
     * @purpose Track the Target WILL LOCK ON
     */

    public void track() {
        long startTime = Timer.getUsClock();
        ColorImage image = null;
        try
        {
            if (cam.freshImage())
            {
                image = cam.getImage();
                Thread.yield();
                Target[] targets = Target.findCircularTargets(image);
                Thread.yield();
                image.free();
                if (targets.length == 0 || targets[0].m_score < kScoreThreshold)
                {
                    if (!targetFound) //this is where the camera will pan to search for a target
                    {
                        sprinklePan();    //Sprinkler-style panning, the preferred method
                    }
                    Target[] newTargets = new Target[targets.length + 1];
                    newTargets[0] = new Target();
                    newTargets[0].m_majorRadius = 0;
                    newTargets[0].m_minorRadius = 0;
                    newTargets[0].m_score = 0;
                    for (int i = 0; i < targets.length; i++)
                    {
                        newTargets[i + 1] = targets[i];
                    }
                    trackerDashboard.updateVisionDashboard(0.0, HW.gyro.getAngle(), 0.0, 0.0, newTargets);
                    failCount();
                }
                else
                {

                            //trackerDashboard.updateVisionDashboard(0.0, gyro.getAngle(), 0.0, targets[0].m_xPos / targets[0].m_xMax, targets);
                            panTrack(targets);
                            tiltTrack(targets);
                            DriverStationLCD.getInstance().println(DriverStationLCD.Line.kMain6, 1, "TARGET FOUND");
                            DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser2, 1, "Target Angle: " + targets[0].getHorizontalAngle());
                            DriverStationLCD.getInstance().updateLCD();

                            targetFound = true;
                            failCount = 0;
                }
            }

        }
        catch (NIVisionException ex)
        {
            ex.printStackTrace();
        }
        catch (AxisCameraException ex)
        {
            ex.printStackTrace();
        }
        //DiscoUtils.debugPrintln("Time : " + (Timer.getUsClock() - startTime) / 1000000.0);
        //DiscoUtils.debugPrintln("Gyro Angle: " + HW.gyro.getAngle());
    }

    public void findTargets() {
        long startTime = Timer.getUsClock();
        HW.drive.orientOff();
        ColorImage image = null;
        try {
            if (cam.freshImage()) {
                image = cam.getImage();
                Thread.yield();
                Target[] targets = Target.findCircularTargets(image);
                Thread.yield();
                image.free();

                if (targets.length == 0 || targets[0].m_score < kScoreThreshold) {
                    Target[] newTargets = new Target[targets.length + 1];
                    newTargets[0] = new Target();
                    newTargets[0].m_majorRadius = 0;
                    newTargets[0].m_minorRadius = 0;
                    newTargets[0].m_score = 0;
                    DriverStationLCD.getInstance().println(DriverStationLCD.Line.kMain6, 1, "NO TARGET FOUND");
                    DriverStationLCD.getInstance().updateLCD();
                    for (int i = 0; i < targets.length; i++) {
                        newTargets[i + 1] = targets[i];
                    }
                    trackerDashboard.updateVisionDashboard(0.0, HW.gyro.getAngle(), 0.0, 0.0, newTargets);
                    }
                else {
                    DriverStationLCD.getInstance().println(DriverStationLCD.Line.kMain6, 1, "               ");
                    DriverStationLCD.getInstance().println(DriverStationLCD.Line.kMain6, 1, "TARGET FOUND");
                    DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser2, 1, "Target Angle: " + targets[0].getHorizontalAngle());
                    trackerDashboard.updateVisionDashboard(0.0, HW.gyro.getAngle(), 0.0, targets[0].m_xPos / targets[0].m_xMax, targets);
                    DriverStationLCD.getInstance().updateLCD();
                    targetFound = true;
                    failCount = 0;
                }
            }
        }
        catch (NIVisionException ex)
        {
            ex.printStackTrace();
        }
        catch (AxisCameraException ex)
        {
            ex.printStackTrace();
        }
        DiscoUtils.debugPrintln("Time : " + (Timer.getUsClock() - startTime) / 1000000.0);
        DiscoUtils.debugPrintln("Gyro Angle: " + HW.gyro.getAngle());
    }


}

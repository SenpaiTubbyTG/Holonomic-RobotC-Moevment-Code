
package org.discobots.laserDragon;

import edu.wpi.first.wpilibj.camera.AxisCamera;
import edu.wpi.first.wpilibj.camera.AxisCameraException;
import edu.wpi.first.wpilibj.image.ColorImage;
import edu.wpi.first.wpilibj.image.NIVisionException;

public class LaserDragonTracker{
        
        private boolean enabled;
        private int maxTargets;
        Target[] targets;
        
        private AxisCamera goalCamera;
        
        public LaserDragonTracker(int max, AxisCamera gc){
            goalCamera = gc;
            maxTargets = max;
            enabled = false;
        }
        
        public void trackTargets(){
            ColorImage image;
            if(goalCamera.freshImage()){
                try{
                    image = goalCamera.getImage();
                } catch (AxisCameraException e){
                    System.out.println("AxisCameraException within trackTargets()");
                } catch (NIVisionException e){
                    System.out.println("NIVisionException within trackTargets()");
                }
            }
        }
        
        public void enable(){
            enabled = true;
        }
        public void disbale(){
            enabled = false;
        }
        public boolean isEnabled(){return enabled;}
}

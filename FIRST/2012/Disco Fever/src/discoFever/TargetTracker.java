/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package discoFever;

import edu.wpi.first.wpilibj.camera.AxisCamera;

/**
 *
 * @author mdouglass101
 */
public class TargetTracker {
    
    private AxisCamera m_camera;
    private BackboardTarget[] m_targets;
    
    public TargetTracker(AxisCamera camera){
        m_camera = camera;
        
    }
}

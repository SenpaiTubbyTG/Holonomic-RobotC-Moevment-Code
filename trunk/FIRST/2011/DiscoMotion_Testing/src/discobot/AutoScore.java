/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package discobot;

/**
 *
 * @author JAG
 */
public class AutoScore {
    private static double kHangDistance = 30;
    private static boolean enabled= false;



    public static void hangTube(){
        if (!isAutoScore()){
            enable();
        }
        HW.lift.setSetpoint(HW.lift.getPosition() - kHangDistance);
    }

    private static void enable(){
        enabled = true;
    }

    private static void disable(){
        enabled = false;
    }
    public static boolean isAutoScore(){
        return enabled;
    }
}

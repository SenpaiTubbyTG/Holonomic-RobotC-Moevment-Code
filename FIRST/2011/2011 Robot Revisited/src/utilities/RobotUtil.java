
package utilities;

/**
 *
 * @author Mitchell
 */
public class RobotUtil {
    
    public static void delay(long milliseconds){ 
        long startTime = System.currentTimeMillis();
        while(System.currentTimeMillis()-startTime>milliseconds);
    }
    
    /*
     * these 2 variables and 2 methods help to organize the structure of the
     * autonomous. This is a good substitute to using threads and it is simple.
     * The caller sets a duration for a task that it wants to complete. It calls
     * taskDurationElapsed() to know wether the duration has elapsed. Setting a
     * new duration overides the old duration
     */
    private static long beginTime;
    private static long duration;
    public static void setTaskDuration(long milliseconds){
        beginTime = System.currentTimeMillis();
        duration = milliseconds;
    }
    public static boolean taskDurationElapsed(){
        return System.currentTimeMillis()-beginTime > duration;
    }
}

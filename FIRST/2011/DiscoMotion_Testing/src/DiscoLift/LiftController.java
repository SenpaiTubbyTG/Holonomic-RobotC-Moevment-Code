/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DiscoLift;

import Sensors.DiscoEncoder;
import discobot.HW;
import java.util.TimerTask;

/**
 *
 * @author JAG
 */
public class LiftController {

    public static final double kDefaultPeriod = .01;
    protected java.util.Timer m_controlLoop;
    protected double m_period = kDefaultPeriod;

    private double m_defaultLiftSpeedUp = 0.5;
    private double m_defaultLiftSpeedDown = -0.5;

    private static final int kLiftUp = 200;
    private static final int kLiftMiddle = 100;
    private static final int kLiftDown = 0;


    private class LiftControllerTask extends TimerTask {

        private LiftController m_controller;

        public LiftControllerTask (LiftController controller) {
            if (controller == null) {
                throw new NullPointerException("Given LiftController was null");
            }
            m_controller = controller;
        }

        public void run() {
            m_controller.checkForLimits();
        }
    }

    public static LiftController singleton = new LiftController();

    private LiftController() {
         m_controlLoop = new java.util.Timer();
         //m_controlLoop.scheduleAtFixedRate(new LiftControllerTask(this), 0L, (long) (m_period * 1000));
    }

    private void checkForLimits(){
        if (HW.liftLimitInnerDown.get() && HW.liftLimitMiddleDown.get()){
            setPosition(kLiftDown);
        } else if (HW.liftLimitInnerDown.get() && HW.liftLimitMiddleUp.get()) {
            setPosition(kLiftMiddle);
        } else if (HW.liftLimitInnerUp.get() && HW.liftLimitMiddleDown.get()){
            setPosition(kLiftMiddle);
        } else if (HW.liftLimitInnerUp.get() && HW.liftLimitMiddleUp.get()){
            setPosition(kLiftUp);
        }
    }

    private void setPosition(int position){

    }

    private void liftUp(){
        HW.lift.set(m_defaultLiftSpeedUp);
    }

    private void liftDown(){
        HW.lift.set(this.m_defaultLiftSpeedDown);
    }

}

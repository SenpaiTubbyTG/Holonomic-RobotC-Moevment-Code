/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DiscoLift;

import Sensors.DiscoEncoder;
import discobot.HW;
import discobot.PWMJaguar;
import java.util.TimerTask;

/**
 *
 * @author JAG
 */
public class LiftController {

    public static final double kDefaultPeriod = .01;
    private PWMJaguar m_jaguar;
    protected java.util.Timer m_controlLoop;
    protected double m_period = kDefaultPeriod;

    private double m_defaultLiftSpeedUp = 0.5;
    private double m_defaultLiftSpeedDown = -0.5;

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

    public LiftController() {
        /*m_jaguar = new PWMJaguar(HW.LiftMotorAddress);
        m_jaguar.setEncoderChannels(HW.liftEncoderA, HW.liftEncoderB, false);
        m_jaguar.changeControlMode(PWMJaguar.ControlMode.kPosition);
        m_jaguar.configEncoderCodesPerRev(HW.liftEncoderCodesPerRev);

         m_controlLoop = new java.util.Timer();

         m_controlLoop.schedule(new LiftControllerTask(this), 0L, (long) (m_period * 1000));
    */}

    private void checkForLimits(){
        if (HW.liftLimitInnerDown.get() && HW.liftLimitOuterDown.get()){
            setPosition(HW.setPositionDown);
        } else if (HW.liftLimitInnerDown.get() && HW.liftLimitOuterUp.get()) {
            setPosition(HW.setPositionMiddle);
        } else if (HW.liftLimitInnerUp.get() && HW.liftLimitOuterDown.get()){
            setPosition(HW.setPositionMiddle);
        } else if (HW.liftLimitInnerUp.get() && HW.liftLimitOuterUp.get()){
            setPosition(HW.setPositionUp);
        } 
    }

    private void setPosition(int position){

    }

}

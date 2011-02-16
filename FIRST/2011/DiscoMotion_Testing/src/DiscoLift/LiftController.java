/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DiscoLift;

import DriveControllers.PositionController;
import Utils.DiscoUtils;
import discobot.HW;
import edu.wpi.first.wpilibj.Encoder.PIDSourceParameter;
import edu.wpi.first.wpilibj.PIDOutput;
import java.util.TimerTask;

/**
 *
 * @author JAG
 */
public class LiftController implements PIDOutput {

    public static final double kDefaultPeriod = .1;
    public static final double m_speedScaleFactor = 20;
    protected java.util.Timer m_controlLoop;
    protected double m_period = kDefaultPeriod;
    private static final int kLiftUp = 850;
    private static final int kLiftMiddle = 393;
    private static final int kLiftDown = 0;
    private static PositionController positionController;
    private double output = 0.0;

    private class LiftControllerTask extends TimerTask {

        private LiftController m_controller;

        public LiftControllerTask(LiftController controller) {
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
        HW.liftEncoder.setPIDSourceParameter(PIDSourceParameter.kDistance);
        HW.liftEncoder.start();
        positionController = new PositionController(0.0, 0.0, 0.0, HW.liftEncoder, this, kDefaultPeriod, true);
        positionController.disable();
        positionController.setInputRange(kLiftDown, kLiftUp);
        positionController.setOutputRange(-.4, .4);
        m_controlLoop = new java.util.Timer();
        m_controlLoop.scheduleAtFixedRate(new LiftControllerTask(this), 0L, (long) (m_period * 1000));
    }

    public void pidWrite(double pidOut) {
        output = -pidOut;
        HW.lift.set(output);
    }

    public void enablePIDControl() {
        if (!positionController.isEnable()) {
            positionController.enable();
        }
    }

    public void disablePIDControl() {
        if (positionController.isEnable()) {
            positionController.disable();
        }
    }

    public double getPostition(){
        return HW.liftEncoder.getRawPosition();
    }

    public void setPID(double P, double I, double D) {
        positionController.setPID(P, I, D);
    }

    private void checkForLimits() {
        if (!HW.liftLimitInnerDown.get() && !HW.liftLimitMiddleDown.get()) {
            HW.liftEncoder.setPosition(kLiftDown);
        } else if (!HW.liftLimitInnerDown.get() && !HW.liftLimitMiddleUp.get()) {
            HW.liftEncoder.setPosition(kLiftMiddle);
        } else if (!HW.liftLimitInnerUp.get() && !HW.liftLimitMiddleDown.get()) {
            HW.liftEncoder.setPosition(kLiftMiddle);
        } else if (!HW.liftLimitInnerUp.get() && !HW.liftLimitMiddleUp.get()) {
            HW.liftEncoder.setPosition(kLiftUp);
        }
    }

    public void setSetpoint(int position) {
        if (positionController.isEnable()) {
            positionController.setSetpoint(position);
        } else {
            DiscoUtils.errorPrintln("Position Control is not enabled for the Lift");
        }
    }

    public boolean isLiftDown() {
        return !HW.liftLimitInnerDown.get() && !HW.liftLimitMiddleDown.get();
    }

    public boolean isLiftUp() {
        return !HW.liftLimitInnerUp.get() && !HW.liftLimitMiddleUp.get();
    }

    public double getLiftSpeed() {
        return output;
    }

    public void setLiftSpeed(double speed) {
        if (positionController.isEnable()) {
            positionController.setSetpoint(HW.liftEncoder.getRawPosition() + speed * m_speedScaleFactor);
        } else {
            output = speed;
            if (speed < 0 && !isLiftDown()) {
                HW.lift.set(output);
            } else if (speed > 0 && !isLiftUp()) {
                HW.lift.set(output);
            } else {
                output = 0.0;
                HW.lift.set(output);
            }

        }
    }
}

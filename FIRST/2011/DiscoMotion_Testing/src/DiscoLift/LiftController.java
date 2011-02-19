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
import edu.wpi.first.wpilibj.PIDSource;
import java.util.TimerTask;

/**
 *
 * @author JAG
 */
public class LiftController implements PIDOutput, PIDSource {

    public static final double kDefaultPeriod = .1;
    public static final double m_speedScaleFactor = 30;
    protected java.util.Timer m_controlLoop;
    protected double m_period = kDefaultPeriod;
    private static final int kLiftUp = 830;
    private static final int kLiftMiddle = 393;
    private static final int kLiftDown = 0;
    private static PositionController positionController;
    private double output = 0.0;
    public static final int kLiftD = 0;
    public static final int kLiftM1 = 370;
    public static final int kLiftM2 = 390;
    public static final int kLiftH1 = 790;
    public static final int kLiftH2 = 820;
    public static final double kLiftMaxSpeedDown = -.3;
    public static final double kLiftSpeedMaxUp = .5;

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
        positionController = new PositionController(0.0, 0.0, 0.0, this, this, kDefaultPeriod, false);
        positionController.disable();
        positionController.setSetpoint(0.0);
        positionController.setOutputRange(kLiftMaxSpeedDown, kLiftSpeedMaxUp);
        positionController.setInputRange(0, kLiftUp);
        m_controlLoop = new java.util.Timer();
        m_controlLoop.scheduleAtFixedRate(new LiftControllerTask(this), 0L, (long) (m_period * 1000));
    }

    public double pidGet() {
        return getPosition();
    }

    public void pidWrite(double pidOut) {
        output = pidOut;
        HW.liftMotor.set(output);
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

    public double getSetpoint() {
        return positionController.getSetpoint();
    }

    public double getPosition() {
        return HW.liftEncoder.getRawPosition();
    }

    public void setPID(double P, double I, double D) {
        positionController.setPID(P, I, D);
    }

    private void checkForLimits() {
        if (isLiftDown()) {
            HW.liftEncoder.setPosition(kLiftDown);
        } else if (isLiftMiddle()) {
            HW.liftEncoder.setPosition(kLiftMiddle);
            DiscoUtils.debugPrintln("LIFT IN MIDDLE");
        } else if (isLiftUp()) {
            HW.liftEncoder.setPosition(kLiftUp);
            DiscoUtils.debugPrintln("LIFT IS UP");
        }
    }

    public void setSetpoint(double position) {
        if (positionController.isEnable()) {
            positionController.setSetpoint(position);
        } else {
            DiscoUtils.errorPrintln("Position Control is not enabled for the Lift");
        }
    }

    public void setLiftSpeed(double speed) {
        if (positionController.isEnable()) {
            positionController.setSetpoint(HW.liftEncoder.get() + speed * m_speedScaleFactor);
        } else {
            output = speed;
            if (speed < 0 && !isLiftDown()) {
                HW.liftMotor.set(output);
            } else if (speed > 0 && !isLiftUp()) {
                HW.liftMotor.set(output);
            } else {
                output = 0.0;
                HW.liftMotor.set(output);
            }

        }
    }

    public boolean isLiftDown() {
        return !HW.liftLimitInnerDown.get() && !HW.liftLimitMiddleDown.get();
    }

    public boolean isLiftMiddle() {
        return (!HW.liftLimitInnerUp.get() && !HW.liftLimitMiddleDown.get())
                || (!HW.liftLimitInnerDown.get() && !HW.liftLimitMiddleUp.get());
    }

    public boolean isLiftUp() {
        return !HW.liftLimitInnerUp.get() && !HW.liftLimitMiddleUp.get();
    }

    public double getLiftSpeed() {
        return output;
    }

    public double getError() {
        return positionController.getError();
    }

    public double getP() {
        return positionController.getP();
    }

    public double getI() {
        return positionController.getI();
    }

    public double getD() {
        return positionController.getD();
    }
}

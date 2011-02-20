package discobot;

import edu.wpi.first.wpilibj.*;
import Utils.*;

/**
 *
 * @author Nelson Chen
 */
public class Disabled {

    private static int i = 0;

    public static void periodic() {
    }

    public static void continuous() {
        if (i > 100000) {
            DiscoUtils.debugPrintln("FL Range: " + HW.sonarFrontLeft.getRangeInches());
            /*DiscoUtils.debugPrintln("L  Range: " + HW.sonarLeft.getRangeInches());
            DiscoUtils.debugPrintln("FL Range: " + HW.sonarFrontLeft.getRangeInches());
            DiscoUtils.debugPrintln("FL Error: " + HW.sonarControllerFrontLeft.getError());
            DiscoUtils.debugPrintln("FL Setpt: " + HW.sonarControllerFrontLeft.getSetpoint());*/
            DiscoUtils.debugPrintln("ENCODERS:  "
                    + "FL=" + HW.encoderFrontLeft.getRawPosition()
                    + " / FR=" + HW.encoderFrontRight.getRawPosition()
                    + " / RR=" + HW.encoderRearRight.getRawPosition()
                    + " / RL=" + HW.encoderRearLeft.getRawPosition());
            //DiscoUtils.debugPrintln("FL: " + HW.encoderFrontLeft.getRawPosition());
            //DiscoUtils.debugPrintln("liftGet: " + HW.lift.pidGet());
            //DiscoUtils.debugPrintln("RR: " + HW.encoderRearRight.getRawPosition());
            //DiscoUtils.debugPrintln("RL: " + HW.encoderRearLeft.getRawPosition());
            /*DiscoUtils.debugPrintln("Arm up: " + HW.arm.isUp());
            DiscoUtils.debugPrintln("Arm down: " + HW.arm.isDown());*/
            /*DiscoUtils.debugPrintln("\nisLiftUp: " + HW.lift.isLiftUp());
            DiscoUtils.debugPrintln("isLiftMiddle: " + HW.lift.isLiftMiddle());
            DiscoUtils.debugPrintln("isLiftDown: " + HW.lift.isLiftDown());
            DiscoUtils.debugPrintln("\nInnerDown: " + HW.liftLimitInnerDown.get());
            DiscoUtils.debugPrintln("InnerUp: " + HW.liftLimitInnerUp.get());
            DiscoUtils.debugPrintln("MiddleDown: " + HW.liftLimitMiddleDown.get());
            DiscoUtils.debugPrintln("MiddleUp: " + HW.liftLimitMiddleUp.get());*/
            i = 0;
        } else {
            i++;
        }
    }
}

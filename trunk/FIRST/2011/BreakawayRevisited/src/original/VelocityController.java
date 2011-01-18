package original;

/**
 *
 * @author Nelson
 */
public class VelocityController {
    
    private

    /*private final double KI = 0;
    private final double KP = 1;
    private final double KD = 1;
    private double error;
    private double iError;
    private static double totalError;
    private double target;

    public VelocityController() {
    }

    public void setVelocity(double newTarget, double currentVelocity) {
        target = newTarget;
        error = newTarget - currentVelocity;    //difference in velocity
    }

    private double getP() {
        double p = error * KP;
        return p;
    }

    private double getI() {
        iError = iError + error;

        // Limit integral error
        if (iError > 200) {
            iError = 200;
        }
        if (iError < -200) {
            iError = -200;
        }

        double i = iError * KI;
        return i;
    }

    private double getD() {
        double dError = error - totalError;
        double d = dError * KD;
        return d;
    }

    public double PIDcontrol() {
        double output = getP() + getI() + getD();

        // Store values
        totalError = error;
        // Return output
        return output;
    }

    public double getTarget() {
        return target;
    }*/
}

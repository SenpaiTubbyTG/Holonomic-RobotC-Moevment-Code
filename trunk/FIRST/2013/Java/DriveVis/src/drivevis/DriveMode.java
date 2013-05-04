package drivevis;

/**
 *
 * @author sam
 */
public interface DriveMode {

    public double getLeftOut();

    public double getRightOut();

    public void calcLR(double y, double x);

    public String Name();
}

package Utils;

/**
 * @author Nelson
 */
public class DataNode {

    double leftVelocity;
    double rightVelocity;
    double time;
    double gyroAngle;
    DataNode next;

    public DataNode(double lVeloc, double rVeloc, double t, double angle) {
        leftVelocity = lVeloc;
        rightVelocity = rVeloc;
        time = t;
        gyroAngle = angle;
    }

    public void setNext(DataNode n) {
        next = n;
    }

    public DataNode getNext() {
        return next;
    }
}

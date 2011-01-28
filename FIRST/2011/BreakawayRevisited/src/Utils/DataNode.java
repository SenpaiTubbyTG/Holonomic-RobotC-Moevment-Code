package Utils;

/**
 * @author Nelson
 */
public class DataNode {

    double data;
    double time;

    //memory reference for the next node in the linked list
    DataNode next;

    /** -------------------------------------------------------
    @method DataNode Constructor
    @param t - timestamp
    @param d - data; generic for greater versatility
    @purpose constructor - creates a new DataNode with timestamp and data in double format
    @author Nelson Chen
    @written Jan 27, 2011
    ------------------------------------------------------- */

    public DataNode(double t, double d) {
        time = t;
        data = d;
    }

    public void setNext(DataNode n) {
        next = n;
    }

    public DataNode getNext() {
        return next;
    }

    /** -------------------------------------------------------
    @method toString
    @param leftMotor - The
    @purpose returns String representation of the DataNode
    @author Nelson Chen
    @written Jan 27, 2011
    ------------------------------------------------------- */
    public String toString() {
        return time + "," + data;
    }

}

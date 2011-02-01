package Utils;

/** -------------------------------------------------------
 * @class DataQueue
 * @purpose queue class for storing DataNodes
 * @author Nelson Chen
 * @written Jan 27, 2011
------------------------------------------------------- */
public class DataQueue {

    private DataNode head = null;
    private DataNode tail = null;

    public void enQueue(double n, double t) {
        if (head == null) {
            DataNode buffer = new DataNode(n, t);
            head = buffer;
            tail = buffer;
        } else {
            DataNode buffer = new DataNode(n, t);
            tail.setNext(buffer);
            tail = buffer;
        }
    }

    public void empty() {
        head = null;
        tail = null;
    }

    public DataNode peek() {
        return head;
    }

    public String deQueue() {
        if (head != null) {
            DataNode buffer = head;
            head = head.getNext();
            return buffer.toString();
        } else {
            return null;
        }
    }

    /** -------------------------------------------------------
     * @class DataNode
     * @purpose stores data in self-referencing objects for use in DataQueue
     * Timestamp is added to each entry
     * @author Nelson Chen
     * @written Jan 27, 2011
    ------------------------------------------------------- */
    private class DataNode {

        double data;
        double time;
        //memory reference for the next node in the linked list
        DataNode next;

        /** -------------------------------------------------------
        @method DataNode Constructor
        @param d - data; generic for greater versatility
        @purpose constructor - creates a new DataNode with timestamp and data in double format
        ------------------------------------------------------- */
        public DataNode(double d, double t) {
            time = t;
            data = d;
        }

        public void setNext(DataNode n) {
            next = n;
        }

        public DataNode getNext() {
            return next;
        }

        /**
         * returns String representation of the DataNode
         * @param leftMotor - The
         */
        public String toString() {
            return time + "," + data;
        }
    }
}

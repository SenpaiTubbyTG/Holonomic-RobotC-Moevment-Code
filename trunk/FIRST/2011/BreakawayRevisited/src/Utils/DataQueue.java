package Utils;

import edu.wpi.first.wpilibj.Timer;

/** -------------------------------------------------------
 * @class DataQueue
 * @purpose queue class for storing DataNodes
 * @author Nelson Chen
 * @written Jan 27, 2011
------------------------------------------------------- */
public class DataQueue {

    DataNode head;
    DataNode tail;

    public DataQueue() {
        head = null;
        tail = null;
    }

    public void enQueue(double n) {
        if (head == null && tail == null) {
            head = new DataNode(n);
            tail = new DataNode(n);
        } else {
            tail.setNext(new DataNode(n));
            tail = new DataNode(n);
        }
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
        public DataNode(double d) {
            time = Timer.getFPGATimestamp();
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

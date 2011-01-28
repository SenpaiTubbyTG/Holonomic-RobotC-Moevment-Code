package Utils;

/**
 * @author Nelson
 */
public class DataQueue {

    DataNode head;
    DataNode tail;

    public DataQueue() {
        head = null;
        tail = null;
    }

    public void enQueue(DataNode n) {
        if (head == null && tail == null) {
            head = n;
            tail = n;
        } else {
            tail.setNext(n);
            tail = n;
        }
    }

    public DataNode peek() {
        return head;
    }

    public DataNode deQueue() {
        if(head != null) {
            DataNode buffer = head;
            head = head.getNext();
            return buffer;
        }
        else
            return null;
    }
}

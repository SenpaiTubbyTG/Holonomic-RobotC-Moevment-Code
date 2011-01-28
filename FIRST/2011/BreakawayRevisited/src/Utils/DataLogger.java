package Utils;

/** -------------------------------------------------------
 * @class DataLogger
 * @purpose Class for logging a single variable as the robot runs
 * Uses a DataQueue to accumulate log entries during execution
 * Data should be written to a file after the robot is disabled
 * @author Nelson Chen
 * @written Jan 27, 2011
------------------------------------------------------- */
public class DataLogger {

    private final String filename;
    private final String header;
    //FileIO Utility for writing file
    private FileIO file;
    //DataQueue for storing data in a queue
    private DataQueue dataLog = new DataQueue();

    /** -------------------------------------------------------
    @method DataLogger Constructor
    @param name - file name
    @param header - file header, should be the name of the variable/data being logged
    @purpose constructor - creates a new DataLogger that automatically appends time to the header
    ------------------------------------------------------- */
    public DataLogger(String name, String hdr) {
        filename = name;
        header = "time," + hdr;
    }

    /**
     * adds another entry to the datalog
     * @param entry - DataNode to be added to the DataQueue
     */
    public void addEntry(DataNode entry) {
        dataLog.enQueue(entry);
    }

    /**
     * writes the contents of dataLog (DataQueue object) to a file
     */
    public void writeData() {
        file = new FileIO(filename);
        file.writeLine(header);
        DataNode buffer = dataLog.deQueue();
        while (buffer != null) {
            file.writeLine(buffer.toString());
            buffer = dataLog.deQueue();
        }
    }
}

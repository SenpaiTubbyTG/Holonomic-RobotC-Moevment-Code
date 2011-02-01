package Utils;

import java.util.TimerTask;
import edu.wpi.first.wpilibj.Timer;

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

    public static final double kDefaultPeriod = .05;
    private double m_period = kDefaultPeriod;
    java.util.Timer m_controlLoop;
    private boolean m_enabled = false;
    private double m_startTime;
    private double entryValue = 0.0;


    private class DataLoggerTask extends TimerTask {

        private DataLogger m_dataLogger;

        public DataLoggerTask(DataLogger dataLogger) {
            if (dataLogger == null) {
                throw new NullPointerException("Given DataLogger was null");
            }
            m_dataLogger = dataLogger;
        }

        public void run() {
            if(m_enabled) {
                m_dataLogger.addEntry(entryValue);
            }
        }
    }

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

    public void init() {
        m_controlLoop = new java.util.Timer();
        m_controlLoop.schedule(new DataLoggerTask(this), 0L, (long) (m_period * 1000));
    }

    public void disable() {
        m_enabled = false;
    }
    public void enable() {
        m_enabled = true;
    }

    public void setEntryValue(double v) {
        entryValue = v;
    }
    /**
     * adds another entry to the datalog
     * @param entry - DataNode to be added to the DataQueue
     */
    private synchronized void addEntry(double entryData) {
        dataLog.enQueue(entryData, (Timer.getFPGATimestamp() - m_startTime));
    }

    /**
     * writes the contents of dataLog (DataQueue object) to a file
     */
    public void writeData() {
        file = new FileIO(filename + ".csv");
        file.writeLine(header);
        while (dataLog.peek() != null) {
            file.writeLine(dataLog.deQueue());
        }
    }
}

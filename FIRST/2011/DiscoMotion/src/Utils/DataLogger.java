package Utils;

import java.util.TimerTask;
import edu.wpi.first.wpilibj.Timer;

/** -------------------------------------------------------
 * @class DataLogger
 * @purpose Class for logging variables as the robot runs
 * Uses DataLogEntry class to accumulate log entries during execution
 * Data should be written to a file after the robot is disabled
 * @author Nelson Chen
 * @written Jan 27, 2011
------------------------------------------------------- */
public class DataLogger {

    private final String filename = "DataLog";
    private String header;
    //FileIO Utility for writing file
    private FileIO file;
    public final double kDefaultPeriod = .5;
    private double m_period = kDefaultPeriod;
    private java.util.Timer m_controlLoop;
    private boolean m_enabled = false;
    protected double entryValues[];
    private DataLoggerTask m_task;
    public static DataLogger dataLogger = new DataLogger();

    private class DataLoggerTask extends TimerTask {

        private DataLogger m_dataLogger;

        public DataLoggerTask(DataLogger dataLogger) {
            if (dataLogger == null) {
                throw new NullPointerException("Given DataLogger was null");
            }
            m_dataLogger = dataLogger;
        }

        public void run() {
            if (m_enabled) {
                m_dataLogger.addEntry(entryValues);
            }
        }
    }

    private DataLogger() {
        init();
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

    public void setTimeOffset(double offset) {
        DataLogHelper.setTimeOffset(offset);
    }

    public void setEntryValue(double[] v) {
        entryValues = v;
    }

    /**
     * adds another entry to the datalog
     * @param entry - DataNode to be added to the DataQueue
     */
    private synchronized void addEntry(double[] entryData) {
        if (m_enabled) {
            new DataLogHelper(entryData);
        }
    }

    public void setHeader(String[] hdr) {
        header = "time";
        for (int k = 0; k < hdr.length; k++) {
            header += "," + hdr[k];
        }
    }

    /**
     * writes the contents of dataLog (DataLogHelper stack) to a file
     */
    public void writeData(String[] hdr) {
        header = "time";
        for (int k = 0; k < hdr.length; k++) {
            header += "," + hdr[k];
        }
        file = new FileIO(filename + ".csv");
        file.writeLine(header);
        String[] data = DataLogHelper.getData();
        for (int k = 0; k < data.length; k++) {
            file.writeLine(data[k]);
        }
    }

    public void writeData() {
        file = new FileIO(filename + ".csv");
        file.writeLine(header);
        String[] data = DataLogHelper.getData();
        for (int k = 0; k < data.length; k++) {
            file.writeLine(data[k]);
        }
    }
}

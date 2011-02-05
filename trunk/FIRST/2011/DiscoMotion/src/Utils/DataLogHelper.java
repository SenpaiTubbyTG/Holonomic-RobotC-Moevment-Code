package Utils;

import edu.wpi.first.wpilibj.Timer;
import Utils.*;

/** -------------------------------------------------------
 * @class DataLogEntry
 * @purpose 
 * @author Nelson Chen
 * @written Feb 4, 2011
------------------------------------------------------- */
public class DataLogHelper {

    double m_time;
    double[] m_value;
    DataLogHelper m_nextEntry;
    static DataLogHelper m_topEntry = null;
    static int numEntries;
    static double m_timeOffset = 0.0;

    public DataLogHelper(double[] val) {
        m_value = val;
        m_time = Timer.getFPGATimestamp();
        m_nextEntry = m_topEntry;
        m_topEntry = this;
        numEntries++;
    }

    public static String[] getData() {
        String[] log = new String[numEntries];
        int counter = 0;
        for (DataLogHelper ptr = m_topEntry; ptr != null; ptr = ptr.m_nextEntry) {
            String buffer = String.valueOf(ptr.m_time - m_timeOffset);
            for (int k = 0; k < ptr.m_value.length; k++) {
                buffer += "," + ptr.m_value[k];
            }
            log[counter] = buffer;
            counter++;
        }
        return log;
    }

    public static void setTimeOffset(double offset) {
        m_timeOffset = offset;
    }
}

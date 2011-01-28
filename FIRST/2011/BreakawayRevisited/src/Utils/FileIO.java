package Utils;

import java.io.*;
import javax.microedition.io.Connector;
import com.sun.squawk.microedition.io.FileConnection;

/**
 * @author Nelson
 */
public class FileIO {

    private DataOutputStream logFile;
    private FileConnection connection;

    /** -------------------------------------------------------
    @method FileIO Constructor
    @param fileName - file name
    @purpose constructor - creates a FileIO Utility for writing files (reading to be added)
    @author Nelson Chen
    @written Jan 27, 2011
    ------------------------------------------------------- */
    public FileIO(String fileName) {
        try {
            connection = (FileConnection) Connector.open("file:///" + fileName,
                    Connector.WRITE);
            connection.create();
            logFile = connection.openDataOutputStream();
        } catch (Exception e) {
            DiscoUtils.debugPrintln("File Write Error");
        }
    }

    /** -------------------------------------------------------
    @method writeString
    @param text - String to write
    @purpose writes a String to a file, does NOT append a crlf
    @author Nelson Chen
    @written Jan 27, 2011
    ------------------------------------------------------- */
    public void writeString(String text) {
        try {
            logFile.writeChars(text);
            logFile.flush();
        } catch (Exception e) {
            DiscoUtils.debugPrintln("File Write Error");
        }
    }

    /** -------------------------------------------------------
    @method writeString
    @param newLine - String to write
    @purpose writes a String to a file, DOES append a crlf
    @author Nelson Chen
    @written Jan 27, 2011
    ------------------------------------------------------- */
    public void writeLine(String newLine) {
        try {
            logFile.writeChars(newLine + "\n");
            logFile.flush();
        } catch (Exception e) {
            DiscoUtils.debugPrintln("File Write Error");
        }
    }

    /** -------------------------------------------------------
    @method newLine
    @purpose writes a CRLF (advances down a line)
    @author Nelson Chen
    @written Jan 27, 2011
    ------------------------------------------------------- */
    public void newLine() {
        try {
            logFile.writeChars("\n");
            logFile.flush();
        } catch (Exception e) {
            DiscoUtils.debugPrintln("File Write Error");
        }
    }

    /** -------------------------------------------------------
    @method close
    @purpose closes the reader/writer
    @author Nelson Chen
    @written Jan 27, 2011
    ------------------------------------------------------- */
    public void close() {
        try {
            logFile.close();
        } catch (Exception e) {
            DiscoUtils.debugPrintln("File Write Error");
        }

    }
}

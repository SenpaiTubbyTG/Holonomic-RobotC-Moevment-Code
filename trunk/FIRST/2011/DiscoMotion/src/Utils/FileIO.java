package Utils;

import java.io.*;
import javax.microedition.io.Connector;
import com.sun.squawk.microedition.io.FileConnection;

/**
 * @author Nelson
 */
public class FileIO {

    private DataOutputStream logFile;
    public DataInputStream inFile;
    private FileConnection connection;

    /** -------------------------------------------------------
    @method FileIO Constructor
    @param fileName - file name
    @purpose constructor - creates a FileIO Utility for reading and writing files
    @author Nelson Chen
    @written Jan 27, 2011
    ------------------------------------------------------- */
    public FileIO(String fileName) {
        try {
            connection = (FileConnection) Connector.open("file:///" + fileName,
                    Connector.READ_WRITE);
            connection.create();
            logFile = connection.openDataOutputStream();
            inFile = connection.openDataInputStream();
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
    @method writeLine
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
    @method readLine
    @purpose reads and returns a String
    @author Nelson Chen
    @written Jan 27, 2011
    ------------------------------------------------------- */
    public String readUTF() {
        try {
            return inFile.readUTF();
        } catch (Exception e) {
            DiscoUtils.debugPrintln("File Read Error");
            return "File Read Error";
        }
    }

    /** -------------------------------------------------------
    @method readDouble
    @purpose reads and returns a double
    @author Nelson Chen
    @written Jan 27, 2011
    ------------------------------------------------------- */
    public double readDouble() {
        try {
            return inFile.readDouble();
        } catch (Exception e) {
            DiscoUtils.debugPrintln("File Read Error");
            return -999.999;
        }
    }

    /** -------------------------------------------------------
    @method close
    @purpose closes the reader and writer
    @author Nelson Chen
    @written Jan 27, 2011
    ------------------------------------------------------- */
    public void close() {
        try {
            logFile.close();
            inFile.close();
        } catch (Exception e) {
            DiscoUtils.debugPrintln("File Write Error");
        }

    }
}

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package csvsplitter;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.StringTokenizer;

/**
 *
 * @author Nelson
 */
public class Main {

    static String[] header = null;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        double[][] data = getData();
        for (int c = 1; c < data[0].length; c++) {
            try {
                BufferedWriter writer = new BufferedWriter(new FileWriter(header[c] + ".csv"));
                for (int r = 0; r < data.length; r++) {
                    writer.write(Double.toString(data[r][0]) + ","
                            + Double.toString(data[r][c]));
                    writer.newLine();
                }
                writer.close();

            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    static double[][] getData() {
        try {
            BufferedReader reader = new BufferedReader(new FileReader("DataLog.csv"));
            String buff = reader.readLine();
            String[] rawData = new String[100000];
            int k = 0;
            while (buff != null) {
                rawData[k] = buff;
                buff = reader.readLine();
                k++;
            }
            StringTokenizer buffer = new StringTokenizer(rawData[0], ",");
            int totalRows = k - 1;
            int totalCols = buffer.countTokens();
            header = new String[totalCols];
            for (int x = 0; x < totalCols; x++) {
                header[x] = buffer.nextToken();
            }

            double data[][] = new double[totalRows][totalCols];
            for (int r = 1; r < totalRows; r++) {
                buffer = new StringTokenizer(rawData[r], ",");
                for (int c = 0; c < totalCols; c++) {
                    data[r - 1][c] = Double.parseDouble(buffer.nextToken());
                }
            }
            return data;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Utils;

import com.sun.squawk.util.StringTokenizer;

/**
 * Class PIDTuner
 *
 * gets PIDConstants from a file, PIDTuning.csv
 * File can be of any length as long as it follows this format:
 *
 * kP,kI,kD,[doesn't matter after this; label is recommended]
 * 
 * example:
 * 0.13,0.0052,0.021,examplePIDController
 * 1.2,0.0,0.0,examplePIDController2
 * 10.5,0.0,5.323,examplePIDController3
 *
 *
 * @author Nelson Chen
 */

public class PIDTuner {

    private static double[][] PIDkonstants;

    /**
     * returns PID constants read from a file (PIDTuning.csv)
     * @return double matrix of PID constants in order according to file
     */
    public static double[][] getPIDConstants() {
        return PIDkonstants;
    }

    public static double[] getPIDConstants(int row) {
        return PIDkonstants[row];
    }

    public static double[][] readFile() {
        String[] rawData = FileIO.readFromFile("PIDTuning.csv");
        PIDkonstants = new double[rawData.length][3];
        for (int r = 0; r < PIDkonstants.length; r++) {
            for (int c = 0; c < 3; c++) {
                StringTokenizer buff = new StringTokenizer(rawData[r], ",");
                PIDkonstants[r][c] = Double.parseDouble(buff.nextToken());
            }
        }
        //PIDkonstants matrix should now be initialized with values from the file
        return PIDkonstants;
    }

}

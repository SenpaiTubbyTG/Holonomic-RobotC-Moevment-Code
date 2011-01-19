/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Utils;

/**
 *
 * @author Nelson
 */
public class Tuple {
    public double dist;
    public double time;
    public double pos;
    public double d;

    public Tuple(double d, double t, double p, double four) {
        dist = d;
        time = t;
        pos = p;
        d = four;
    }

    public Tuple(double d, double t, double p) {
        dist = d;
        time = t;
        pos = p;
    }

    public Tuple(double d, double t) {
        dist = d;
        time = t;
    }

}

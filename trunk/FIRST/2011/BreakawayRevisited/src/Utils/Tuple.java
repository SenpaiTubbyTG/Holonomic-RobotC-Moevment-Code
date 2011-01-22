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
    public double a;
    public double b;
    public double c;
    public double d;

    public Tuple(double d, double t, double p, double four) {
        a = d;
        b = t;
        c = p;
        d = four;
    }

    public Tuple(double d, double t, double p) {
        a = d;
        b = t;
        c = p;
    }

    public Tuple(double d, double t) {
        a = d;
        b = t;
    }

    public void set(double newA, double newB) {
        a = newA;
        b = newB;
    }

    public String toString() {
        return "a: " + a + "\tb: " + b;
    }


}

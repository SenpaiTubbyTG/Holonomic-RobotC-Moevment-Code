/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.discobots.laserDragon;

public class Target{
    double xCenter, yCenter, distance;
    public Target(double x, double y, double d){
        xCenter = x;
        yCenter = y;
        distance = d;
    }
    public double getXPosition(){ return xCenter;}
    public double getYPosition(){ return yCenter;}
    public double getDistance() { return distance;}
}

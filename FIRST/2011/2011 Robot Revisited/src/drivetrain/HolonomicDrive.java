package drivetrain;
/*\
 * This class is used to control a holonomic drive train
 */

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.Gyro;

public class HolonomicDrive {

    Jaguar m_frontLeft, m_frontRight, m_backLeft, m_backRight;
    Joystick m_rotationStick, m_directionStick;
    Gyro m_gyro;
    
    final double turnConstant;

    public HolonomicDrive(Jaguar frontLeft, Jaguar frontRight,
                          Jaguar backLeft, Jaguar backRight,
                          Joystick leftStick, Joystick rightStick,
                          Gyro gyro){
        m_frontLeft = frontLeft;
        m_frontRight = frontRight;
        m_backLeft = backLeft;
        m_backRight = backRight;
        m_rotationStick = leftStick;
        m_directionStick = rightStick;
        m_gyro = gyro;
        
        turnConstant = 1.0;
    }

    public void drive(){
        double stickAngle = m_directionStick.getDirectionRadians();
        double driveMagnitude = m_directionStick.getMagnitude();
        double driveAngle = stickAngle - Math.toRadians(m_gyro.getAngle());
        double turnAngle = m_rotationStick.getDirectionRadians();
        double turnMagnitude = m_rotationStick.getMagnitude();
        double turnOffset = Math.toRadians(m_gyro.getAngle()) - turnAngle;
        
        // this section clarifies offset so that the robot does not attempt a
        // turn greater than 180 degrees
        if(turnOffset >Math.PI){
            turnOffset -= 2*Math.PI;
        } else if(turnOffset<-Math.PI){
            turnOffset += 2*Math.PI;
        }
        
        //// the turn outPut is the product of the offset, magnitude, and an
        //// arbitrary turn constant divided by 2PI, the # of radians in a circle
        double turnOutput = (turnConstant*turnOffset*turnMagnitude)/(2*Math.PI);
        
        if(driveMagnitude + turnOffset > 1.0){
            driveMagnitude = 1.0-turnOffset;
        }
        
        double flOutput = Math.cos(driveAngle - Math.PI/4.0);
        double frOutput = -Math.sin(driveAngle - Math.PI/4.0);
        double blOutput = Math.sin(driveAngle-Math.PI/4.0);
        double brOutput = -Math.cos(driveAngle-Math.PI/4.0);
        double[] outputs = {flOutput, frOutput, blOutput, brOutput};

        /// get maximum value of the above
        double max = flOutput;
        for(int i=0; i<4; i++){
            if(max<outputs[i]){
                max = outputs[i];
            }
        } for(int i=0; i<4; i++){
            outputs[i] = outputs[i]*(driveMagnitude/max);
        }
        
        m_frontLeft.set(flOutput-turnOutput);
        m_frontRight.set(frOutput+turnOutput);
        m_backLeft.set(blOutput-turnOutput);
        m_backRight.set(brOutput+turnOutput);
    }
}

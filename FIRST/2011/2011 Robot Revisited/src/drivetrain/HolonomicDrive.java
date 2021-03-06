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

    /*
     * this method converts inputs from the joystick into magnitudes and sends
     * them to a more general holonomicDrive method
     */
    public void operatorDrive(){
        double fieldDriveAngle = m_directionStick.getDirectionRadians();
        double driveMagnitude = m_directionStick.getMagnitude();
        double fieldTurnAngle = m_rotationStick.getDirectionRadians();
        double turnMagnitude = m_rotationStick.getMagnitude();
        holonomicDrive(fieldDriveAngle, driveMagnitude, fieldTurnAngle, turnMagnitude);
    }
    
    /*
     * this method is used for controlling the holonomic drive system. The robot
     * will move at fieldDriveAngle (radians) with respect to the field and at a speed 
     * proportional to driveMagnitude (0, 1). The robot will turn to 
     * fieldTurnAngle (radians) and remain at this heading with a speed proportional
     * to turnMagnitude (0, 1). THIS METHOD SHOULD BE CALLED REPEATEDLY WITH
     * DESIRED INPUT TO WORK CORRECTLY
     */
    public void holonomicDrive(double fieldDriveAngle, double driveMagnitude, 
                               double fieldTurnAngle, double turnMagnitude){
        double driveAngle = fieldDriveAngle - Math.toRadians(m_gyro.getAngle());
        double turnOffset = fieldTurnAngle  - Math.toRadians(m_gyro.getAngle());
        
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
        
        if(driveMagnitude + turnOutput > 1.0){
            driveMagnitude = 1.0-turnOutput;
        }
        
        double flOutput = Math.cos(driveAngle  + Math.PI/4.0);
        double frOutput = -Math.sin(driveAngle + Math.PI/4.0);
        double blOutput = Math.sin(driveAngle  +Math.PI/4.0);
        double brOutput = -Math.cos(driveAngle +Math.PI/4.0);
        double[] outputs = {flOutput, frOutput, blOutput, brOutput};

        /// get maximum value of the above
        double max = flOutput;
        for(int i=0; i<4; i++){
            if(max<Math.abs(outputs[i])){
                max = Math.abs(outputs[i]);
            }
        } for(int i=0; i<4; i++){
            outputs[i] = outputs[i]*(driveMagnitude/max);
        }
        
        System.out.println(outputs[0]-turnOutput + " ");
        System.out.println(outputs[1]+turnOutput + " ");
        System.out.println(outputs[2]-turnOutput + " ");
        System.out.println(outputs[3]+turnOutput + " ");
        
        m_frontLeft.set(outputs[0]-turnOutput);
        m_frontRight.set(outputs[1]+turnOutput);
        m_backLeft.set(outputs[2]-turnOutput);
        m_backRight.set(outputs[3]+turnOutput);
    }
}

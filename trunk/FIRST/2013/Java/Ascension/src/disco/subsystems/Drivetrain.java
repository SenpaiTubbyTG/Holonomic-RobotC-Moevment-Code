/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package disco.subsystems;

import disco.HW;
import disco.commands.drivetrain.AssistedTank;
import disco.commands.drivetrain.RawJoyTank;
import disco.utils.BetterDrive;
import disco.utils.MaxbotixSonar;
import edu.wpi.first.wpilibj.CounterBase;
import edu.wpi.first.wpilibj.CounterBase.EncodingType;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.Ultrasonic;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.Gyro;
import edu.wpi.first.wpilibj.command.Subsystem;


public class Drivetrain extends Subsystem {
    private Victor leftDrive1;
    private Victor leftDrive2;
    private Victor RightDrive1;
    private Victor RightDrive2;
    private RobotDrive drive;

    private MaxbotixSonar frontSonar1;
    private MaxbotixSonar frontSonar2;
    private MaxbotixSonar leftSonar;
    private Encoder leftEncoder;
    private Encoder rightEncoder;

    private DigitalInput pyramidSwitchLeft;
    private DigitalInput pyramidSwitchRight;

    private Gyro gyro;

    public Drivetrain(){
	super("Drivetrain");
	leftDrive1=new Victor(HW.LeftDrive1Slot,HW.LeftDrive1Channel);
	leftDrive2=new Victor(HW.LeftDrive2Slot,HW.LeftDrive2Channel);
	RightDrive1=new Victor(HW.RightDrive1Slot,HW.RightDrive1Channel);
	RightDrive2=new Victor(HW.RightDrive2Slot,HW.RightDrive2Channel);
	drive=new BetterDrive(leftDrive1,leftDrive2,RightDrive1,RightDrive2);
	//what is wrong with this picture?
	drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
	drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
	drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
	drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
	drive.setSafetyEnabled(false);

        frontSonar1=new MaxbotixSonar(HW.maxbotixsonar1Slot,HW.maxbotixsonar1Channel,MaxbotixSonar.Unit.kInches);
        frontSonar2=new MaxbotixSonar(HW.maxbotixsonar2Slot,HW.maxbotixsonar2Channel,MaxbotixSonar.Unit.kInches);
        leftSonar=new MaxbotixSonar(HW.maxbotixsonar3Slot,HW.maxbotixsonar3Channel,MaxbotixSonar.Unit.kInches);

        leftEncoder=new Encoder(    HW.leftEncoderSlot,HW.leftEncoderAChannel,
                                    HW.leftEncoderSlot,HW.leftEncoderBChannel,false,EncodingType.k4X);
        rightEncoder=new Encoder(    HW.rightEncoderSlot,HW.rightEncoderAChannel,
                                    HW.rightEncoderSlot,HW.rightEncoderBChannel,false,EncodingType.k4X);
	leftEncoder.start();
	rightEncoder.start();

        pyramidSwitchLeft = new DigitalInput(HW.limitSwitchLeftSlot, HW.limitSwitchLeftChannel);
        pyramidSwitchRight = new DigitalInput(HW.limitSwitchRightSlot, HW.limitSwitchRightChannel);

        gyro = new Gyro(HW.gyroSlot, HW.gyroChannel);
        gyro.setSensitivity(0.007);
    }

    public void initDefaultCommand() {
        setDefaultCommand(new AssistedTank());
    }

    public void tankDrive(double left,double right){
	drive.tankDrive(left, right,true);
    }
    public void tankDriveUnsmoothed(double left, double right){
        drive.tankDrive(left,right,false);
    }

    public void arcadeDrive(double move, double turn) {
	drive.arcadeDrive(move,turn,true);
    }

    public double getFrontSonar1(){
        return frontSonar1.getMedianRange();
    }
    public double getFrontSonar2(){
        return frontSonar2.getMedianRange();
    }
    public double getLeftSonar(){
        return leftSonar.getMedianRange();
    }

    public int getLeftEncoder() {
	return leftEncoder.get();
    }
    public int getRightEncoder(){
	return rightEncoder.get();
    }
    public double getGyroAngle() {
        return gyro.getAngle();
    }

    public boolean getLeftPyramid(){
        return !pyramidSwitchLeft.get();
    }
    public boolean getRightPyramid(){
        return !pyramidSwitchRight.get();
    }
}
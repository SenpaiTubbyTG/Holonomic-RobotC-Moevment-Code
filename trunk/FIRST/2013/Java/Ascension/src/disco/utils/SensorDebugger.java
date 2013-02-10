
package disco.utils;

import disco.commands.CommandBase;
import disco.subsystems.*;
import edu.wpi.first.wpilibj.command.Command;

public class SensorDebugger extends Thread{ 
    private Collector collector;
    private CompressorSub compressor;
    private Drivetrain drivetrain;
    private Shooter shooter;
    
    public SensorDebugger() {
        collector = CommandBase.collector;
        compressor = CommandBase.compressor;
        drivetrain = CommandBase.drivetrain;
        shooter = CommandBase.shooter;
        workingDriveGyro = false;
        workingDriveEncoderRight = false;
        workingDriveEncoderLeft = false;
        workingDriveSonarFront1 = false;
        workingDriveSonarFront2 = false;
        workingDriveSonarRight = false;
        workingDriveSonarLeft = false;
        workingShooterEncoder1 = false;
        workingShooterEncoder2 = false;
    }
    
    public void run() {
        try {
            while (true) {
                Command driveCommand = drivetrain.getCurrentCommand();
                Command shootCommand = shooter.getCurrentCommand();
                Command collectCommand = collector.getCurrentCommand();
                Command compressCommand = compressor.getCurrentCommand();
                
                // Check Drive related stuff
                double encDriveLeft = drivetrain.getLeftEncoder();
                double encDriveRight = drivetrain.getRightEncoder();
                double pwmDriveLeft = drivetrain.getPWMLeft();
                double pwmDriveRight = drivetrain.getPWMRight();
                Thread.sleep(1000);
                double encDriveLeftB = drivetrain.getLeftEncoder();
                double encDriveRightB = drivetrain.getRightEncoder();
                if ((encDriveLeftB - encDriveLeft > 0 && pwmDriveLeft > 0.3) || (encDriveLeftB - encDriveLeft < 0 && pwmDriveLeft < -0.3)) {
                    workingDriveEncoderLeft = true;
                }
                if ((encDriveRightB - encDriveRight > 0 && pwmDriveRight > 0.3) || (encDriveRightB - encDriveRight < 0 && pwmDriveRight < -0.3)) {
                    workingDriveEncoderRight = true;
                }
                
                // Check Shoot related stuff
                
                
                
                
            }
        } catch (Exception e){
            System.out.println("Error at Sensor Debugger");
            System.out.println("Error: " + e.getMessage());
        }
    }
    
    
    
    public static boolean 
            workingDriveGyro,
            workingDriveEncoderRight,
            workingDriveEncoderLeft,
            workingDriveSonarFront1,
            workingDriveSonarFront2,
            workingDriveSonarRight,
            workingDriveSonarLeft,
            workingShooterPneumatics,
            workingShooterEncoder1,
            workingShooterEncoder2;
}

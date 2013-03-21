package disco;

import disco.commands.SaveData;
import disco.commands.drivetrain.*;
import disco.commands.pneumatics.*;
import disco.commands.shooter.*;
import disco.utils.GamePad;
import disco.utils.GamePad.AxisButton;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.buttons.Button;
import edu.wpi.first.wpilibj.buttons.JoystickButton;

/**
 * This class is the glue that binds the controls on the physical operator
 * interface to the commands and command groups that allow control of the robot.
 */
public class OI {

    private int gp1_mode = GamePad.MODE_D;
    private GamePad gp1 = new GamePad(1, gp1_mode);

    private int gp2_mode = GamePad.MODE_D;
    private GamePad gp2 = new GamePad(2, gp2_mode);

    //JOYSTICK 1
    private Button b_diffInc=new AxisButton(gp1,GamePad.DPAD_Y_U);
    private Button b_diffDec=new AxisButton(gp1,GamePad.DPAD_Y_D);
    private Button b_toggleShooter=new JoystickButton(gp1,gp1.BUMPER_R);
    private Button b_shooterInc=new AxisButton(gp1,GamePad.DPAD_X_R);
    private Button b_shooterDec=new AxisButton(gp1,GamePad.DPAD_X_L);
    private Button b_shoot=new JoystickButton(gp1,gp1.TRIGGER_R);
    private Button b_clear=new JoystickButton(gp1,gp1.TRIGGER_L);
    private Button b_cycleShooter=new JoystickButton(gp1,gp1.BTN_BACK);
    private Button b_autoSet = new JoystickButton(gp1, gp1.BTN_A);

//    private Button b_turn=new JoystickButton(gp1,gp1.BTN_Y);
//    private Button b_dist=new JoystickButton(gp1,gp1.BUMPER_R);
    private Button b_cycleDrive=new JoystickButton(gp1,gp1.BTN_START);
    private Button b_compressorToggle=new JoystickButton(gp1,gp1.BTN_X);
    private Button b_saveData=new JoystickButton(gp1,gp1.BUMPER_L);



    //JOYSTICK 2
    private Button b_autoShift=new JoystickButton(gp2,gp2.BTN_A);
    private Button b_shiftUp=new JoystickButton(gp2,gp2.BTN_B);
    private Button b_shiftDown=new JoystickButton(gp2,gp2.BTN_X);

    private Button b_autoShoot=new JoystickButton(gp2,gp2.CLICK_R);


    public OI() {
	b_diffInc.whenPressed(new ShooterIncDiff());
	b_diffDec.whenPressed(new ShooterDecDiff());

        b_toggleShooter.whenPressed(new ShooterToggle());
        b_shooterInc.whenPressed(new ShooterInc());
        b_shooterDec.whenPressed(new ShooterDec());
        b_shoot.whenPressed(new disco.commands.pneumatics.Shoot()); //Why does netbeans think I mean command shoot in package commands.shooter? that doesn't even exist.
        b_clear.whenPressed(new Clear());
        b_cycleShooter.whenPressed(new cycleShooter());
	b_autoSet.whenPressed(new AutoSetRPM());

//        b_turn.whenPressed(new DriveAngleEncoder(90));
//        b_dist.whenPressed(new DriveDistance(36));
        b_cycleDrive.whenPressed(new cycleDrive());

        b_compressorToggle.whenPressed(new ToggleCompressor());

        b_saveData.whenPressed(new SaveData());

	b_autoShift.whenPressed(new AutoShift());
	b_shiftUp.whenPressed(new ShiftUp());
	b_shiftDown.whenPressed(new ShiftDown());

	b_autoShoot.whenPressed(new AutoShoot(5,1000,100));
    }

    public Joystick getJoy1() {
	return gp1;
    }

    public Joystick getJoy2() {
	return gp2;
    }
}

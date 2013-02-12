package disco;

import disco.commands.collector.CollectorToggle;
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

    //private Button b_toggleCollect=new JoystickButton(gp1,gp1.BTN_START);

//    private Button b_diffInc=new AxisButton(gp1,GamePad.DPAD_Y_U);
//    private Button b_diffDec=new AxisButton(gp1,GamePad.DPAD_Y_D);

    private Button b_toggleShooter=new JoystickButton(gp1,gp1.BTN_X);
    private Button b_shooterInc=new AxisButton(gp1,GamePad.DPAD_X_R);
    private Button b_shooterDec=new AxisButton(gp1,GamePad.DPAD_X_L);
    private Button b_shoot=new JoystickButton(gp1,gp1.BTN_A);

    private Button b_makeTank=new JoystickButton(gp1,gp1.BUMPER_R);
    private Button b_makeArcade=new JoystickButton(gp1,gp1.BUMPER_L);
    private Button b_turn=new JoystickButton(gp1,gp1.BTN_Y);

    private Button b_compressorToggle=new JoystickButton(gp1,gp1.BTN_B);

    //// CREATING BUTTONS
    // One type of button is a joystick button which is any button on a joystick.
    // You create one by telling it which joystick it's on and which button
    // number it is.
    // Joystick stick = new Joystick(port);
    // Button button = new JoystickButton(stick, buttonNumber);

    // Another type of button you can create is a DigitalIOButton, which is
    // a button or switch hooked up to the cypress module. These are useful if
    // you want to build a customized operator interface.
    // Button button = new DigitalIOButton(1);
    // There are a few additional built in buttons you can use. Additionally,
    // by subclassing Button you can create custom triggers and bind those to
    // commands the same as any other Button.
    //// TRIGGERING COMMANDS WITH BUTTONS
    // Once you have a button, it's trivial to bind it to a button in one of
    // three ways:
    // Start the command when the button is pressed and let it run the command
    // until it is finished as determined by it's isFinished method.
    // button.whenPressed(new ExampleCommand());
    // Run the command while the button is being held down and interrupt it once
    // the button is released.
    // button.whileHeld(new ExampleCommand());
    // Start the command when the button is released  and let it run the command
    // until it is finished as determined by it's isFinished method.
    // button.whenReleased(new ExampleCommand());
    public OI() {
//        b_toggleCollect.whenPressed(new CollectorToggle());
//
//	b_diffInc.whenPressed(new ShooterIncDiff());
//	b_diffDec.whenPressed(new ShooterDecDiff());

        b_toggleShooter.whenPressed(new ShooterToggle());
        b_shooterInc.whenPressed(new ShooterInc());
        b_shooterDec.whenPressed(new ShooterDec());

        b_shoot.whenPressed(new Shoot());

        b_makeTank.whenPressed(new AssistedTank());
        b_makeArcade.whenPressed(new JoyArcadeTwoSpeed());
        b_turn.whenPressed(new DriveAngleGyro(90));

        b_compressorToggle.whenPressed(new ToggleCompressor());
    }

    public Joystick getJoy() {
	return gp1;
    }
}

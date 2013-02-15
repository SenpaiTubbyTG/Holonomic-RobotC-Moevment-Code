package disco;

import disco.commands.*;
import disco.commands.collector.*;
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

    private static int gp1_mode = GamePad.MODE_D;
    private static GamePad gp1 = new GamePad(1, gp1_mode);

    //private static Button b_toggleCollect=new JoystickButton(gp1,gp1.BTN_START);
    
    private static Button b_diffInc=new AxisButton(gp1,GamePad.DPAD_Y_U);
    private static Button b_diffDec=new AxisButton(gp1,GamePad.DPAD_Y_D);
    private static Button b_driveMode = new JoystickButton(gp1, gp1.BTN_BACK);
    private static Button b_drivePIDMode = new JoystickButton(gp1, gp1.BTN_START);
    private static Button b_shootPIDMode = new JoystickButton(gp1, gp1.BTN_X);
    

    private static Button b_toggleShooter=new JoystickButton(gp1,gp1.BTN_X);
    //private static Button b_shooterInc=new AxisButton(gp1,GamePad.DPAD_Y_U);
    //private static Button b_shooterDec=new AxisButton(gp1,GamePad.DPAD_Y_D);
    private static Button b_shoot=new JoystickButton(gp1,gp1.BTN_A);

    //private static Button b_makeTank=new JoystickButton(gp1,gp1.BUMPER_R);
    //private static Button b_makeArcade=new JoystickButton(gp1,gp1.BUMPER_L);
    //private static Button b_turn=new JoystickButton(gp1,gp1.BTN_Y);

    //private static Button b_compressorToggle=new JoystickButton(gp1,gp1.BTN_B);

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
	b_diffInc.whenPressed(new ShooterIncDiff());
	b_diffDec.whenPressed(new ShooterDecDiff());

        b_toggleShooter.whenPressed(new ShooterToggle());
        b_driveMode.whenPressed(new CycleDriveModes());
        b_drivePIDMode.whenPressed(new CycleDrivePIDMode());
        b_shootPIDMode.whenPressed(new CycleShooterModes());
        //b_shooterInc.whenPressed(new ShooterInc());
        //b_shooterDec.whenPressed(new ShooterDec());

        b_shoot.whenPressed(new Shoot());

        //b_makeTank.whenPressed(new AssistedTank());
        //b_makeArcade.whenPressed(new JoyArcadeTwoSpeed());
        //b_turn.whenPressed(new DriveAngleEncoder(90));

        //b_compressorToggle.whenPressed(new ToggleCompressor());
    }

    public Joystick getJoy() {
	return gp1;
    }
}

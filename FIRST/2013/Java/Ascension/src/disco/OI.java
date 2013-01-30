package disco;

import disco.commands.collector.CollectorDec;
import disco.commands.collector.CollectorInc;
import disco.commands.collector.CollectorToggle;
import disco.commands.drivetrain.JoyArcadeTwoSpeed;
import disco.commands.drivetrain.RawJoyTank;
import disco.commands.shooter.ShooterDec;
import disco.commands.shooter.ShooterInc;
import disco.commands.shooter.ShooterToggle;
import disco.utils.GamePad;
import disco.utils.GamePad.AxisButton;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.buttons.Button;
import edu.wpi.first.wpilibj.buttons.DigitalIOButton;
import edu.wpi.first.wpilibj.buttons.JoystickButton;

/**
 * This class is the glue that binds the controls on the physical operator
 * interface to the commands and command groups that allow control of the robot.
 */
public class OI {

    private int gp1_mode = GamePad.MODE_D;
    private GamePad gp1 = new GamePad(1, gp1_mode);

//    private Button b_toggleCollector=new JoystickButton(gp1,gp1.BTN_X);
//    private Button b_collectorInc=new AxisButton(gp1,GamePad.DPAD_Y_U);
//    private Button b_collectorDec=new AxisButton(gp1,GamePad.DPAD_Y_D);
    
    private Button b_toggleShooter=new JoystickButton(gp1,gp1.BTN_Y);
    private Button b_shooterInc=new JoystickButton(gp1,gp1.BTN_B);
    private Button b_shooterDec=new JoystickButton(gp1,gp1.BTN_X);
    
    private Button b_makeTank=new JoystickButton(gp1,gp1.BUMPER_R);
    private Button b_makeArcade=new JoystickButton(gp1,gp1.BUMPER_L);

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
//	b_toggleCollector.whenPressed(new CollectorToggle());
//	b_collectorInc.whenPressed(new CollectorInc());
//	b_collectorDec.whenPressed(new CollectorDec());
        
        b_toggleShooter.whenPressed(new ShooterToggle());
        b_shooterInc.whenPressed(new ShooterInc());
        b_shooterDec.whenPressed(new ShooterDec());
        
        b_makeTank.whenPressed(new RawJoyTank());
        b_makeArcade.whenPressed(new JoyArcadeTwoSpeed());
    }

    public Joystick getJoy() {
	return gp1;
    }
}

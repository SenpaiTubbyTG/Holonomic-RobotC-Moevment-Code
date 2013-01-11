
package disco.practice;

import disco.practice.commands.*;
import disco.practice.commands.Pneumatics.ToggleCompressor;
import disco.practice.commands.Pneumatics.WhacksOff;
import disco.practice.commands.Pneumatics.WhacksOn;
import disco.practice.commands.Tower.HoodFar;
import disco.practice.commands.Tower.HoodKey;
import disco.practice.commands.Tower.ManualIndex;
import disco.practice.commands.Tower.ManualMouth;
import disco.practice.commands.Tower.ShooterDec;
import disco.practice.commands.Tower.ShooterInc;
import disco.practice.commands.Tower.ToggleShooter;
import disco.practice.subsystems.Indexer;
import disco.practice.subsystems.Intake;
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
    private int gp1_mode=GamePad.MODE_D;
    private GamePad gp1=new GamePad(1, gp1_mode);

    private Button b_toggleLights=new JoystickButton(gp1,gp1.CLICK_L);

    private Button b_mouthIn=new JoystickButton(gp1,gp1.BUMPER_R);
    private Button b_mouthOut=new AxisButton(gp1,gp1.TRIGGER_R);

    private Button b_indexerUp=new JoystickButton(gp1,gp1.BUMPER_L);
    private Button b_indexerDown=new AxisButton(gp1,gp1.TRIGGER_L);

    private Button b_whackerUp=new JoystickButton(gp1,gp1.BTN_BACK);
    private Button b_whackerDown=new JoystickButton(gp1,gp1.BTN_START);

    private Button b_toggleShooter=new JoystickButton(gp1,GamePad.DPAD_X_R);
    private Button b_shooterInc=new AxisButton(gp1,GamePad.DPAD_Y_U);
    private Button b_shooterDec=new AxisButton(gp1,GamePad.DPAD_Y_D);

    private Button b_toggleCompressor=new JoystickButton(gp1, gp1.BTN_B);

    private Button b_hoodKey=new JoystickButton(gp1,gp1.BTN_Y);
    private Button b_hoodFar=new JoystickButton(gp1,gp1.BTN_A);
    //// CREATING BUTTONS
    // One type of button is a joystick button which is any button on a joystick.
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

    public OI(){
	b_toggleLights.whenPressed(new ToggleAllLights());

	b_mouthIn.whileHeld(new ManualMouth(Intake.IN));
	b_mouthOut.whileHeld(new ManualMouth(Intake.OUT));

	b_indexerUp.whileHeld(new ManualIndex(Indexer.UP));
	b_indexerDown.whileHeld(new ManualIndex(Indexer.DOWN));

	b_whackerDown.whenPressed(new WhacksOn());
	b_whackerUp.whenPressed(new WhacksOff());

	b_toggleShooter.whenPressed(new ToggleShooter());

	b_shooterInc.whenPressed(new ShooterInc());
	b_shooterDec.whenPressed(new ShooterDec());

	b_toggleCompressor.whenPressed(new ToggleCompressor());

	b_hoodKey.whenPressed(new HoodKey());
	b_hoodFar.whenPressed(new HoodFar());
    }

    public Joystick getJoy(){
	return gp1;
    }
}


package drivevis;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Map;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.WindowConstants;

/**
 *
 * @author sam
 *
 * Plots drivetrain outputs on a grid of inputs.
 * inputs: joystick [-1...1]x[-1...1]
 * outputs: drivetrain [-1...1]x[-1...1]
 */
public class DriveVis extends JFrame{
    static DriveVis frame;
    static JPanel panel=new JPanel();
    static Grid g;
    //resolution of the grid
    public static final int divisions=5;
    public static final int size=800;


    public static void main(String[] args) {
	frame=new DriveVis();
	frame.setTitle("DriveVis by Sam Dietrich, FRC 2587 The Discobots");

	JPanel options=new JPanel();
	options.setMaximumSize(new Dimension(800,100));
	options.setMinimumSize(new Dimension(100,25));
	ButtonGroup modeButs=new ButtonGroup();
	for(Map.Entry<Integer,DriveMode> m :  Grid.getModes().entrySet()){
	    JRadioButton but=new JRadioButton(m.getValue().Name());
	    but.addActionListener(new modeListener());
	    but.setActionCommand(String.valueOf(m.getKey()));
	    modeButs.add(but);
	    options.add(but);
	}
	panel.add(options);
    }

    public DriveVis(){
	setSize(size,size);
        setBackground(Color.white);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	panel.setLayout(new BoxLayout(panel,BoxLayout.Y_AXIS));

	g=new Grid(divisions, size);
	panel.add(g);
	this.add(panel);
	pack();

        setSize(size,size);
        setVisible(true);
    }

    static class modeListener implements ActionListener{ //why does this need to be static? please tell me
	@Override
	public void actionPerformed(ActionEvent e) {
	    int newMode=Integer.parseInt(e.getActionCommand());
	    g.setMode(newMode);
	    //It looks cooler without this line. trust me.
	    //panel.repaint();
	}
    }


}

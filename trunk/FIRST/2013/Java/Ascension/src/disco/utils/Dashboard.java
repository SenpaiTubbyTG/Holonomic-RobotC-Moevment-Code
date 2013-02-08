<xml version="1.0">
<dashboard>
	<widget field="shooter" type="PIDSubsystem" class="edu.wpi.first.smartdashboard.gui.elements.PIDEditor">
		<location x="223" y="201"/>
	</widget>
	<widget field="Air Full" type="Boolean" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="209" y="119"/>
		<width>127</width>
	</widget>
	<widget field="Compressor" type="Subsystem" class="edu.wpi.first.smartdashboard.gui.elements.Subsystem">
		<location x="208" y="93"/>
	</widget>
	<widget field="Front sonar 1" type="Number" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="209" y="42"/>
	</widget>
	<widget field="Compressor State" type="String" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="202" y="147"/>
	</widget>
	<widget field="Left joy X" type="Number" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="436" y="149"/>
	</widget>
	<widget field="Left joy Y" type="Number" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="428" y="87"/>
	</widget>
	<widget field="Checkbox 1" type="Boolean" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="432" y="185"/>
	</widget>
	<widget field="Checkbox 2" type="Boolean" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="443" y="214"/>
	</widget>
	<widget field="Shooter PWM" type="Number" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="0" y="168"/>
	</widget>
	<widget field="Collector Power" type="Number" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="0" y="147"/>
	</widget>
	<widget field="Right joy Y" type="Number" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="0" y="126"/>
	</widget>
	<widget field="Drivetrain" type="Subsystem" class="edu.wpi.first.smartdashboard.gui.elements.Subsystem">
		<location x="0" y="105"/>
	</widget>
	<widget field="Shooter Setpoint" type="Number" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="0" y="63"/>
	</widget>
	<widget field="Collector" type="Subsystem" class="edu.wpi.first.smartdashboard.gui.elements.Subsystem">
		<location x="211" y="68"/>
	</widget>
	<widget field="Sonar" type="Number" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="0" y="21"/>
	</widget>
	<widget field="Slider 1" type="Number" class="edu.wpi.first.smartdashboard.gui.elements.TextBox">
		<location x="0" y="0"/>
	</widget>
	<widget field="Shooter RPM" type="Number" class="edu.wpi.first.smartdashboard.gui.elements.SimpleDial">
		<location x="573" y="74"/>
		<width>200</width>
		<height>127</height>
		<property name="Upper Limit" value="14000.0"/>
		<property name="Tick Interval" value="500.0"/>
	</widget>
</dashboard>
<live-window>
</live-window>
</xml>
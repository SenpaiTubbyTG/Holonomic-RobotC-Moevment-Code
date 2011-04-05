//declare PIDController instance
PIDController arm;

int goal_value = 1000;
int k_P = 100;
int k_I = 0;
int k_D = 20;

pre_auton() {
	init(arm);
	setSetpoint(arm, goal_value);
	setPIDs(arm, k_P, k_I, k_D);
	enable(arm);
}

autonomous() {
	motor[arm1] = motor[arm2] = calculatePID(arm);
}

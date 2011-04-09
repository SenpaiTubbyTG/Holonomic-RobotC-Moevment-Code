//declare PIDController instance
PIDController arm;

int goal_value = 1000;
int k_P = 100;
int k_I = 0;
int k_D = 20;

void pre_auton() {
	init(arm);
	setSetpoint(arm, goal_value);
	setPIDs(arm, k_P, k_I, k_D);
	enable(arm);
}

task autonomous() {
	while(true) {
		motor[arm1] = motor[arm2] = calculatePID(arm);
	}
}

task usercontrol() {
	while(true) {
		motor[arm1] = motor[arm2] = calculatePID(arm);
	}

}

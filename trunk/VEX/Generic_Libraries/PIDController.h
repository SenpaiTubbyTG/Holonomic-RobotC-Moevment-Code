
//enables the PIDController
void enable(PIDController controller);
//disables the PIDController
void disable(PIDController controller);

//change the setpoint/goal value of the PIDController
void setSetpoint(PIDController controller, int newSetpoint);

//change the PID Constant/gain values
void setPIDs(PIDController controller, int kP, int kI, int kD);

//set input/output ranges
void setInputRange(PIDController controller, int min, int max);
void setOutputRange(PIDController controller, int min, int max);

//set maximum allowed error
void setMaxError(PIDController controller, int maxError);

//returns a boolean value based on whether or not currentError <= maxError
bool onTarget(PIDController controller);

//add ONE to continuous section(s) like autonomous or teleop
void calculatePID(PIDController controller);
int calculatePID(PIDController controller);
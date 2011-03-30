typedef struct {
	double k_P;
	double k_I;
	double k_D;

	bool enabled;

	double minInput;
	double maxInput;
	double minOutput;
	double maxOutput;

	double setpoint;
	double result;
	double input;
	double error;
	double prevError;
	double totalError;

	int inputSensorIndex;
	int outputMotorIndex;
} PIDController;

void enable(PIDController controller) {
	controller.enabled = true;
}

void disable(PIDController controller) {
	controller.enabled = false;
}

void setSetpoint(PIDController controller, double newSetpoint) {
	controller.setpoint = newSetpoint;
}

void setPIDs(PIDController controller, double kP, double kI, double kD) {
	controller.k_P = kP;
	controller.k_I = kI;
	controller.k_D = kD;
}

void setInputRange(PIDController controller, double min, double max) {
	controller.minInput = min;
	controller.maxInput = max;
}

void setOutputRange(PIDController controller, double min, double max) {
	controller.minOutput = min;
	controller.maxOutput = max;
}

void calculatePID(PIDController controller) {

	if (controller.enabled) {
		controller.input = SensorValue[controller.inputSensorIndex];
		controller.error = controller.setpoint - controller.input;
		            if (abs(controller.error) > (controller.maxInput - controller.minInput) / 2) {
		                if (controller.error > 0) {
		                    controller.error = controller.error - controller.maxInput + controller.minInput;
		                } else {
		                    controller.error = controller.error + controller.maxInput - controller.minInput;
		                }
		            }

		        if ( ((controller.totalError + controller.error) * controller.k_I < controller.maxOutput)
		                && ((controller.totalError + controller.error) * controller.k_I > controller.minOutput) ) {
		            controller.totalError += controller.error;
		        }

		        controller.result = (controller.k_P * controller.error +
		                              controller.k_I * controller.totalError +
		                              controller.k_D * (controller.error - controller.prevError));
		        controller.prevError = controller.error;

		        if (controller.result > controller.maxOutput) {
		            controller.result = controller.maxOutput;
		        } else if (controller.result < controller.minOutput) {
		            controller.result = controller.minOutput;
		        }

		motor[controller.outputMotorIndex] = controller.result;
	}
}

double calculatePID(PIDController controller) {

	if (controller.enabled) {
		controller.input = SensorValue[controller.inputSensorIndex];
		controller.error = controller.setpoint - controller.input;
		            if (abs(controller.error) > (controller.maxInput - controller.minInput) / 2) {
		                if (controller.error > 0) {
		                    controller.error = controller.error - controller.maxInput + controller.minInput;
		                } else {
		                    controller.error = controller.error + controller.maxInput - controller.minInput;
		                }
		            }

		        if ( ((controller.totalError + controller.error) * controller.k_I < controller.maxOutput)
		                && ((controller.totalError + controller.error) * controller.k_I > controller.minOutput) ) {
		            controller.totalError += controller.error;
		        }

		        controller.result = (controller.k_P * controller.error +
		                              controller.k_I * controller.totalError +
		                              controller.k_D * (controller.error - controller.prevError));
		        controller.prevError = controller.error;

		        if (controller.result > controller.maxOutput) {
		            controller.result = controller.maxOutput;
		        } else if (controller.result < controller.minOutput) {
		            controller.result = controller.minOutput;
		        }
		  return controller.result;
    } else {
    return 0.0;
  }
}

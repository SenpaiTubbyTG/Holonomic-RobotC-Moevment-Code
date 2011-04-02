typedef struct {
	int k_P;
	int k_I;
	int k_D;

	bool enabled;

	int minInput;
	int maxInput;
	int minOutput;
	int maxOutput;
	int maxError;

	int setpoint;
	int result;
	int input;
	int error;
	int prevError;
	int totalError;

	int inputSensorIndex;
	int outputMotorIndex;
} PIDController;

void enable(PIDController controller) {
	controller.enabled = true;
}

void disable(PIDController controller) {
	controller.enabled = false;
}

void setMaxError(PIDController controller, int maxError) {
	controller.maxError = maxError
}

bool onTarget(PIDController controller) {
	int error = abs(controller.setpoint - SensorValue[controller.inputSensorIndex]);
	if (error <= maxError) {
		return true;
	} else {
		return false;
	}
}

void setSetpoint(PIDController controller, int newSetpoint) {
	controller.setpoint = newSetpoint;
}

void setPIDs(PIDController controller, int kP, int kI, int kD) {
	controller.k_P = kP;
	controller.k_I = kI;
	controller.k_D = kD;
}

void setInputRange(PIDController controller, int min, int max) {
	controller.minInput = min;
	controller.maxInput = max;
}

void setOutputRange(PIDController controller, int min, int max) {
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

int calculatePID(PIDController controller) {

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

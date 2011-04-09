typedef struct {
	int k_P;
	int k_I;
	int k_D;

	//enabled = 0 for false, = 1 for true
	int enabled;

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

void init(PIDController controller) {
	controller.k_P = 0;
	controller.k_I = 0;
	controller.k_D = 0;
	controller.enabled = 0;
	controller.minInput = 0;
	controller.maxInput = 0;
	controller.minOutput = -127;
	controller.maxOutput = 127;
	controller.maxError = 0;
	controller.totalError = 0;
	controller.prevError = 0;
}

void init(PIDController controller, int inputIndex) {
	init(controller);
	controller.inputSensorIndex = inputIndex;
}

void init(PIDController controller, int inputIndex, int outputIndex) {
	init(controller);
	controller.inputSensorIndex = inputIndex;
	controller.outputMotorIndex = outputIndex;
}

void enable(PIDController controller) {
	controller.enabled = 1;
}

void disable(PIDController controller) {
	controller.enabled = 0;
}

void setMaxError(PIDController controller, int maxError) {
	if(maxError >= 0);
	controller.maxError = maxError;
}

bool onTarget(PIDController controller) {
	int error = abs(controller.setpoint - SensorValue[controller.inputSensorIndex]);
	if (error <= controller.maxError) {
		return 1;
	} else {
		return 0;
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
	if(max > min) {	
		controller.minInput = min;
		controller.maxInput = max;
	}
}

void setOutputRange(PIDController controller, int min, int max) {
	if(max > min && min >= -127 && max <= 127) {
		controller.minOutput = min;
		controller.maxOutput = max;
	}	
}

int calculatePID(PIDController controller) {

	if (controller.enabled == 1) {
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

		        controller.result = (controller.error / controller.k_P +// inverted and switch from "*" to "/"
                                               controller.totalError / controller.k_I + // inverted and switch from "*" to "/"
                                               (controller.error - controller.prevError) / controller.k_D);
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

int calculatePID(PIDController controller, int input) {

        if (controller.enabled == 1) {
                controller.input = input;
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

                        controller.result = (controller.error / controller.k_P +// inverted and switch from "*" to "/"
                                               controller.totalError / controller.k_I + // inverted and switch from "*" to "/"
                                               (controller.error - controller.prevError) / controller.k_D);
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

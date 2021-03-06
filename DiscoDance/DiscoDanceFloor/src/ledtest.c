#include <stdio.h>
#include "roneos.h"

#define BEHAVIOR_TASK_PRIORITY		(BACKGROUND_TASK_PRIORITY + 1)
#define BEHAVIOR_TASK_PERIOD		100

void backgroundTask(void* parameters);
void behaviorTask(void* parameters);

/******** user code ********/

int main(void) {
	systemPreInit();
	systemInit();

	//initButtonSensor();

	//osTaskCreate(backgroundTask, "background", 256, NULL, BACKGROUND_TASK_PRIORITY);
	osTaskCreate(behaviorTask, "behavior", 4096, NULL, BEHAVIOR_TASK_PRIORITY);
	osTaskStartScheduler(); /* Start the scheduler. */
	return 0;/* memory problem if os gets here.*/
}

// the background task runs all the time.  Put slow stuff here, like compute intensive functions
// or large data transfers, like getting the Yun's map from the robot.
void backgroundTask(void* parameters) {
	for (;;) {
		// delay to let other tasks run at same priority
		osTaskDelay(100);
	}
}

// behaviors run every 50ms.  They should be designed to be short, and terminate quickly.
// they are used for robot control.  Watch this space for a simple behavior abstraction
// to appear.
void behaviorTask(void* parameters) {
	uint32 lastWakeTime = osTaskGetTickCount();

	for (;;) {
		//if (getButtonSensor(BUTTON_SENSOR_BASE, BUTTON_SENSOR_PIN)) {}

		//leds_set(LED_BLUE, LED_PATTERN_PULSE, LED_BRIGHTNESS_MED, LED_RATE_MED);
		blinkyLedSet(1);
		osTaskDelayUntil(&lastWakeTime, 400); //500 mili seconds
		blinkyLedSet(0);
		osTaskDelayUntil(&lastWakeTime, 400);


		osTaskDelayUntil(&lastWakeTime, BEHAVIOR_TASK_PERIOD);

	}
}

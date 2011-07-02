#include <string.h>

#include "inc/lm3s8962.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/ssi.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#include "driverlib/debug.h"
#include "driverlib/pwm.h"

#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"

#include "roneos.h"
#include "bump_sensor.h"

static uint8 bumpers;
static boolean bumperArr[8];

//returns the bumper value(s) for the specified bits
/*uint8 get_bumpers(uint8 bumper) {
	return bumpers & bumper;
}*/

void update_bumpers(uint8 new_values) {
	bumpers = new_values;
}

uint8 get_bumpers() {
	return bumpers;
}

void bumper_debug_print()
{
	cprintf("Bumpers: %02X = ", bumpers);
	print_in_binary_bits(bumpers);
}




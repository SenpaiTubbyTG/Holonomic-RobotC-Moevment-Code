/**
 * @file leds.c
 */



#include "inc/lm3s8962.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/ssi.h"

#include "roneos.h"


#define LED_MODE_SYSCTL			SYSCTL_PERIPH_GPIOF
#define LED_MODE_PORT			GPIO_PORTF_BASE
#define LED_MODE_PIN 			GPIO_PIN_3

#define LED_DEMO_BLINK_DELAY  	80000
#define LED_DEMO_BLINK_COUNT  	2

#define LED_ONOFF_ALL_MASK 0xFFFF


void led_latch(void);
void led_latch_onoff_data(uint32 code);
void led_latch_dimmer_data(void);

uint8 led_dimmers[LED_NUM_ELEMENTS] = { 0 };

/**
 * @brief Latches the LED.
 *
 * Turns the LCD on and then off with a delay of 1.
 * @returns void
 */
void led_latch(void) {
	MAP_GPIOPinWrite(LED_LE_PORT, LED_LE_PIN, LED_LE_PIN);
	MAP_SysCtlDelay(1);
	MAP_GPIOPinWrite(LED_LE_PORT, LED_LE_PIN, 0);
}

/**
 * @brief Latches the first 16 bits from code into the binary on/off state of the controller.
 *
 * @param code data to be latched
 * @returns void
 */
void led_latch_onoff_data(uint32 code) {
	volatile uint8 q;
	SPISelectDevice(SPI_LEDS_ONOFF);

	// Enable on/off writes
	MAP_GPIOPinWrite(LED_MODE_PORT, LED_MODE_PIN, 0);
	MAP_SSIDataPut(SSI0_BASE, code);
	while (MAP_SSIBusy(SSI0_BASE)) {q++;}
	led_latch();
	SPIDeselect();
}

/**
 * @brief Latches the stored LED dimmer data (16 x 8 bytes) into the adjustable 7-bit part.
 * of the LED controller.
 *
 * This is the primary low-level interface to the LEDs.
 * @returns void
 */
void led_latch_dimmer_data(void) {
	uint8 i, q;
	uint8 led_dimmers_shifted[LED_NUM_ELEMENTS];
	static uint8 led_dimmers_old[LED_NUM_ELEMENTS] = {0xFF};
	boolean update_data = false;

	for (i = 0; i < LED_NUM_ELEMENTS; i++) {
		if (led_dimmers_old[i] != led_dimmers[i]) {
			led_dimmers_old[i] = led_dimmers[i];
			update_data = true;
		}
	}

	if(update_data) {
		i = 0;
		led_dimmers_shifted[i++] = led_dimmers[15];
		led_dimmers_shifted[i++] = led_dimmers[LED_RED_START_IDX + 4];
		led_dimmers_shifted[i++] = led_dimmers[LED_RED_START_IDX + 3];
		led_dimmers_shifted[i++] = led_dimmers[LED_RED_START_IDX + 2];
		led_dimmers_shifted[i++] = led_dimmers[LED_RED_START_IDX + 1];
		led_dimmers_shifted[i++] = led_dimmers[LED_RED_START_IDX + 0];

		led_dimmers_shifted[i++] = led_dimmers[LED_GREEN_START_IDX + 4];
		led_dimmers_shifted[i++] = led_dimmers[LED_GREEN_START_IDX + 3];
		led_dimmers_shifted[i++] = led_dimmers[LED_GREEN_START_IDX + 2];
		led_dimmers_shifted[i++] = led_dimmers[LED_GREEN_START_IDX + 1];
		led_dimmers_shifted[i++] = led_dimmers[LED_GREEN_START_IDX + 0];

		led_dimmers_shifted[i++] = led_dimmers[LED_BLUE_START_IDX + 4];
		led_dimmers_shifted[i++] = led_dimmers[LED_BLUE_START_IDX + 3];
		led_dimmers_shifted[i++] = led_dimmers[LED_BLUE_START_IDX + 2];
		led_dimmers_shifted[i++] = led_dimmers[LED_BLUE_START_IDX + 1];
		led_dimmers_shifted[i++] = led_dimmers[LED_BLUE_START_IDX + 0];

		SPISelectDevice(SPI_LEDS_DIMMER);
		// Enable dimmer writes
		MAP_GPIOPinWrite(LED_MODE_PORT, LED_MODE_PIN, LED_MODE_PIN);
		for (i = 0; i < LED_NUM_ELEMENTS; i++) {
			MAP_SSIDataPut(SSI0_BASE, led_dimmers_shifted[i]);
			while (MAP_SSIBusy(SSI0_BASE)) {q++;}
		}
		led_latch();
		SPIDeselect();
	}
}

/**
 * @brief Initializes the LEDs.
 *
 * Configure the LED_MODE pin as output.
 * Turns off all dimmer.
 * Latches dimmer data.
 * Latches on/off data with a mask (FFFF).
 * Sets the LED properties - color red, pattern circle, brightness high, and rate fast.
 * @returns void
 */
void led_init(void) {
	MAP_SysCtlPeripheralEnable(LED_MODE_SYSCTL);
	MAP_GPIOPinTypeGPIOOutput(LED_MODE_PORT, LED_MODE_PIN);
	MAP_GPIOPinWrite(LED_MODE_PORT, LED_MODE_PIN, 0);
	led_set_dimmer_all(0);
	led_latch_dimmer_data();
	led_latch_onoff_data(LED_ONOFF_ALL_MASK);

	leds_set(LED_RED, LED_PATTERN_CIRCLE, LED_BRIGHTNESS_HIGH, LED_RATE_FAST);
}

/**
 * @brief Sets the brightness of a specified dimmer.
 *
 * If the index exceeds the number of elements in the LED (16), does nothing.
 * If the value exceeds the maximum brightness(7F), uses the maximum as the value instead.
 * @param led_idx indicates which dimmer's brightness is to be set
 * @param val brightness to be set
 * @returns void
 */
void led_set_dimmer(uint32 led_idx, uint32 val) {
	if (led_idx >= LED_NUM_ELEMENTS) {
		// bad LED number.  exit
		return;
	}
	if (val > LED_MAX_DIMMER) {
		val = LED_MAX_DIMMER;
	}
	led_dimmers[led_idx] = val;
}

/**
 * @brief Sets the brightness of all dimmers of a specified color.
 *
 * If the specified color does not match the existing colors, does nothing.
 * @param led_color specifies the dimmer color to be set
 * @param dimmer brightness to be set
 * @returns void
 */
void led_set_dimmer_color(uint32 led_color, uint32 dimmer) {
	uint8 startIdx;
	int i;

	switch (led_color) {
	case LED_RED:
		startIdx = LED_RED_START_IDX;
		break;
	case LED_GREEN:
		startIdx = LED_GREEN_START_IDX;
		break;
	case LED_BLUE:
		startIdx = LED_BLUE_START_IDX;
		break;
	default:
		return;
	}

	for (i = startIdx; i < (startIdx + LED_NUM_ELEMENTS_PER_COLOR); i++) {
		//instead of setting the dimmers directly, use the previously defined function in order
		//to detect errors!!
		led_set_dimmer(i,(uint8)dimmer);
		//led_dimmers[i] = (uint8)dimmer;
	}
}

/**
 * @brief Sets the brightness of all dimmers on the robot.
 *
 * @param dimmer the brightness to be set
 * @returns void
 */
void led_set_dimmer_all(uint32 dimmer) {

	int i;
	for (i = 0; i < LED_NUM_ELEMENTS; i++) {
		led_dimmers[i] = (uint8)dimmer;
	}
}

/******** LED animations ********/
uint8 led_animation_color;
uint8 led_animation_pattern;
uint8 led_animation_brightness;
uint8 led_animation_rate;
uint32 led_animation_counter = 0;

#define LED_PATTERN_SHIFTS	4
#define LED_PATTERN_LENGH	10

//										   00,01,02,03,04,05,06,07,08,09
uint8 circle_pattern[LED_PATTERN_LENGH] = { 8,16,12, 7, 5, 3, 1, 0, 0, 0};
uint8 circle_counters[LED_NUM_ELEMENTS_PER_COLOR] = {0,2,4,6,8};
uint8 circle_state[LED_NUM_ELEMENTS_PER_COLOR] = {0};

uint8 pattern_counter = 0;
//										  00,01,02,03,04,05,06,07,08,09
uint8 pulse_pattern[LED_PATTERN_LENGH] = { 1, 3, 8,12,16,12, 8, 3, 1, 0};

//										  00,01,02,03,04,05,06,07,08,09
uint8 blink_pattern[LED_PATTERN_LENGH] = { 0, 0,16,16,16,16,16, 0, 0, 0};



/**
 * @brief Sets the properties of the LED animation.
 *
 * Sets the color, patter, brightness, and rate of the LED animation.
 * @returns void
 */
void leds_set(uint8 color, uint8 pattern, uint8 brightness, uint8 rate) {
	led_animation_color = color;
	led_animation_pattern = pattern;
	led_animation_brightness = brightness;
	led_animation_rate = rate;
}

/**
 * @brief Updates LED animation.
 *
 * Updates LED animation according to the color, pattern, brightness, and rate previously set.
 * Sets properties using the leds_set function.
 * @returns void
 */
void leds_update(void) {
	uint8 i, c, val;
	uint8 colorStartIdx, colorEndIdx;

	if (led_animation_color == LED_ALL) {
		colorStartIdx = LED_RED;
		colorEndIdx = LED_BLUE;
	} else {
		colorStartIdx = led_animation_color;
		colorEndIdx = led_animation_color;
	}

	if (led_animation_pattern == LED_PATTERN_MANUAL) {
		// do nothing
	} else {
		led_set_dimmer_all(0);
		switch (led_animation_pattern) {
		case LED_PATTERN_ON: {
			for (c = colorStartIdx; c <= colorEndIdx; c++) {
				led_set_dimmer_color(c, led_animation_brightness);
			}
			break;
		}
		case LED_PATTERN_BLINK:
		case LED_PATTERN_PULSE: {
			uint8 pattern_counter_next;
			led_animation_counter++;
			if (led_animation_counter > (led_animation_rate >> 1)) {
				led_animation_counter = 0;
				pattern_counter++;
				if (pattern_counter >= LED_PATTERN_LENGH) {
					pattern_counter = 0;
				}
			}
			pattern_counter_next = pattern_counter + 1;
			if (pattern_counter_next >= LED_PATTERN_LENGH) {
				pattern_counter_next = 0;
			}

			for (c = colorStartIdx; c <= colorEndIdx; c++) {
				if (led_animation_pattern == LED_PATTERN_BLINK) {
					led_set_dimmer_color(c, (blink_pattern[pattern_counter] * led_animation_brightness) >> LED_PATTERN_SHIFTS);
				} else {
					uint16 v0 = pulse_pattern[pattern_counter];
					uint16 v1 = pulse_pattern[pattern_counter_next];
					uint16 val = (v1 - v0) * led_animation_counter / led_animation_rate + v0;
					//led_set_dimmer_color(c, (pulse_pattern[pattern_counter] * led_animation_brightness) >> LED_PATTERN_SHIFTS);
					led_set_dimmer_color(c, (val * led_animation_brightness) >> LED_PATTERN_SHIFTS);
				}
			}
			break;
		}
		case LED_PATTERN_CIRCLE: {
			uint8 idx;
			led_animation_counter++;
			if (led_animation_counter > (led_animation_rate >> 1)) {
				// circle animations run twice as fast to counteract the interpolation
				led_animation_counter = 0;
				val = circle_state[0];
				for (i = 0; i < LED_NUM_ELEMENTS_PER_COLOR; i++) {
					circle_counters[i]++;
					if (circle_counters[i] >= LED_PATTERN_LENGH) {
						circle_counters[i] = 0;
					}
				}
				for (i = 0; i < LED_NUM_ELEMENTS_PER_COLOR; i++) {
					circle_state[i] = circle_pattern[circle_counters[i]];
				}
			}
			for (c = colorStartIdx; c <= colorEndIdx; c++) {
				idx = c * LED_NUM_ELEMENTS_PER_COLOR;
				for (i = 0; i < LED_NUM_ELEMENTS_PER_COLOR; ++i) {
					led_set_dimmer(idx++, ((uint32)circle_state[i] * (uint32)led_animation_brightness) >> LED_PATTERN_SHIFTS);
				}
			}
			break;
		}
		case LED_PATTERN_COUNT: {
			// led_animation_rate contains the count
			uint8 idx = colorStartIdx * LED_NUM_ELEMENTS_PER_COLOR;
			uint8 val;
			led_animation_counter++;
			if (led_animation_counter > LED_RATE_FAST) {
				led_animation_counter = 0;
				pattern_counter++;
				if (pattern_counter >= LED_PATTERN_LENGH) {
					pattern_counter = 0;
				}
			}

			if(led_animation_rate > LED_NUM_ELEMENTS_PER_COLOR) {
				led_animation_rate = LED_NUM_ELEMENTS_PER_COLOR;
			}
			val = ((8 + (pulse_pattern[pattern_counter] >> 1)) * led_animation_brightness)  >> LED_PATTERN_SHIFTS;
			for (i = 0; i < led_animation_rate; i++) {
				led_set_dimmer(idx++, val);
			}
			break;
		}
		default:
			break;
		}
	}
	led_latch_dimmer_data();
}

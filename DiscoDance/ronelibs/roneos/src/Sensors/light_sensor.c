/**
 * @file light_sensor.c
 */

#include "inc/lm3s8962.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_qei.h"

#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

//#include "pm.h"
//#include "plat.h"
//#include "stellaris.h"

#include "roneos.h"

#define LIGHT_SENSOR_FL_ADC_CHANNEL 0
#define LIGHT_SENSOR_FR_ADC_CHANNEL 1
#define LIGHT_SENSOR_R_ADC_CHANNEL 2

/**
 * @brief Initializes light sensor.
 *
 * Sets sampling speed and configures and enables the light sensor.
 * @returns void
 */
void light_sensor_init(void) {
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);

	//Set sampling speed
	MAP_SysCtlADCSpeedSet(SYSCTL_ADCSPEED_500KSPS);

	//Disable sample sequences for configuration
	MAP_ADCSequenceDisable(ADC_BASE, LIGHT_SENSOR_FL_ADC_CHANNEL);
	MAP_ADCSequenceDisable(ADC_BASE, LIGHT_SENSOR_FR_ADC_CHANNEL);
	MAP_ADCSequenceDisable(ADC_BASE, LIGHT_SENSOR_R_ADC_CHANNEL);

	//Timer Trigger, priorities are same as number
	MAP_ADCSequenceConfigure(ADC_BASE, LIGHT_SENSOR_FL_ADC_CHANNEL, ADC_TRIGGER_PROCESSOR, LIGHT_SENSOR_FL_ADC_CHANNEL);
	MAP_ADCSequenceConfigure(ADC_BASE, LIGHT_SENSOR_FR_ADC_CHANNEL, ADC_TRIGGER_PROCESSOR, LIGHT_SENSOR_FR_ADC_CHANNEL);
	MAP_ADCSequenceConfigure(ADC_BASE, LIGHT_SENSOR_R_ADC_CHANNEL,  ADC_TRIGGER_PROCESSOR, LIGHT_SENSOR_R_ADC_CHANNEL);

	MAP_ADCSequenceStepConfigure(ADC_BASE, LIGHT_SENSOR_FL_ADC_CHANNEL, 0, ADC_CTL_CH0 | ADC_CTL_END);
	MAP_ADCSequenceStepConfigure(ADC_BASE, LIGHT_SENSOR_FR_ADC_CHANNEL, 0, ADC_CTL_CH1 | ADC_CTL_END);
	MAP_ADCSequenceStepConfigure(ADC_BASE, LIGHT_SENSOR_R_ADC_CHANNEL,  0, ADC_CTL_CH2 | ADC_CTL_END);

	//Config sequence steps
	// ADC_SSCTL3_R = (ADC_SSCTL3_TS0 | ADC_SSCTL3_END0);
	MAP_ADCSequenceEnable(ADC_BASE, LIGHT_SENSOR_FL_ADC_CHANNEL);
	MAP_ADCSequenceEnable(ADC_BASE, LIGHT_SENSOR_FR_ADC_CHANNEL);
	MAP_ADCSequenceEnable(ADC_BASE, LIGHT_SENSOR_R_ADC_CHANNEL);
}


//only values 0, 1, 2, allowed. Error check in python.
int32 light_sensor_get_value(uint32 light_sensor) {
	/**
	 *	@brief Gets the ADC value of the specified light sensor.
	 *
	 *	If the input light sensor is not recognized, returns 0
	 *	@param light_sensor specifies which light sensor you want to check (only 0, 1, 2 are allowed)
	 *	@returns the ADC value; 0 if the input parameter is not recognized
	 */
	uint32 adc_val;
	uint32 samples = 0;

	if(light_sensor > LIGHT_SENSOR_REAR) {
		return 0;
	}
	MAP_ADCProcessorTrigger(ADC_BASE, light_sensor);
	while (samples < 1) {
		samples = MAP_ADCSequenceDataGet(ADC_BASE, light_sensor, &adc_val);
	}
	return adc_val;
}

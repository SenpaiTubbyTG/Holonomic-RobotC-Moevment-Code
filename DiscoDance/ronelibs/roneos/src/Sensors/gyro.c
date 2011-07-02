/**
 * @file gyro.c
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

#define GYRO_ADC_CHANNEL 3

/**
 * @brief Initializes gyro.
 *
 * Sets sampling speed, configures and enables the gyro.
 * @returns void
 */
void gyro_init(void) {
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);

	//Set sampling speed
	MAP_SysCtlADCSpeedSet(SYSCTL_ADCSPEED_500KSPS);

	//Disable sample sequences for configuration
	MAP_ADCSequenceDisable(ADC_BASE, GYRO_ADC_CHANNEL);

	//Timer Trigger, priorities are same as number
	MAP_ADCSequenceConfigure(ADC_BASE, GYRO_ADC_CHANNEL, ADC_TRIGGER_PROCESSOR, GYRO_ADC_CHANNEL);

	MAP_ADCSequenceStepConfigure(ADC_BASE, GYRO_ADC_CHANNEL, 0, ADC_CTL_CH3 | ADC_CTL_END);

	//Config sequence steps
	MAP_ADCSequenceEnable(ADC_BASE, GYRO_ADC_CHANNEL);

}

/**
 * @brief Gets the ADC value of the gyro.
 *
 * @returns the value of the gyro
 */
int32 gyro_get_value(void) {
	uint32 adc_val = 22;
	uint32 samples = 0;

	MAP_ADCProcessorTrigger(ADC_BASE, GYRO_ADC_CHANNEL);

	while (samples < 1) {
		samples = MAP_ADCSequenceDataGet(ADC_BASE, GYRO_ADC_CHANNEL, &adc_val);
	}
	return adc_val;
}

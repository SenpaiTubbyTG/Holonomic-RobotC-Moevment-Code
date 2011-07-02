/**
 * @file spi.c
 */

#include "inc/lm3s8962.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"

#include "roneos.h"

uint8 SPIWordSize;
uint8 SPIMode;
static osSemaphoreHandle spiMutex;

/**
 * @brief Initializes SPI unit.
 *
 * Enables peripherals
 * Configures GPIO
 * Sets radio, accelerometer, and LED as output
 * Sets word size as 0
 * @returns void
 */
void SPIInit(void) {
	volatile unsigned long ulLoop;
	//TODO Sig, is this read important?  What is it doing?
	ulLoop = SYSCTL_RCGC2_R;

	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	// configure SSI pins for periphial control
	MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5);
	MAP_GPIOPinConfigure(GPIO_PA2_SSI0CLK);
	//MAP_GPIOPinConfigure(GPIO_PA3_SSI0FSS);
	MAP_GPIOPinConfigure(GPIO_PA4_SSI0RX);
	MAP_GPIOPinConfigure(GPIO_PA5_SSI0TX);

	// enable pull down
    MAP_GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PA4_SSI0RX, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);
    MAP_GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PA5_SSI0TX, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);

	// enable all peripherals for the SPI Radio Control
	MAP_SysCtlPeripheralEnable(LED_LE_SYSCTL);

	// drive select pins to correct values while they are still in input mode
	SPIDeselectISR();

	// enable the select pins for output
	MAP_GPIOPinTypeGPIOOutput(LED_LE_PORT, LED_LE_PIN);

	// force the port to be enabled by the first call to SPIConfigure()
	SPIWordSize = 0;

	spiMutex = osSemaphoreCreateMutex();
}

/**
 *	@brief Sets the SPI word size and data format
 *
 *	@param ulBase is the SSI port
 *	@param wordSize is the new word size to be set
 *	@param mode is the new transmission mode
 *	@returns void
 */
// note must be called after you have the mutex - after
void SPIConfigure(uint32 ulBase, uint8 wordSize, uint8 mode) {
	if ((wordSize != SPIWordSize) || (mode != SPIMode)) {
		// cache word size value
		SPIWordSize = wordSize;
		SPIMode = mode;

		MAP_SSIDisable(ulBase);

		// Configure the SSI0 port for master mode.
		//TODO Determine what speed we set the SPI clock to, it might be a bottleneck.
		MAP_SSIConfigSetExpClk(ulBase, MAP_SysCtlClockGet() / 2, SPIMode, SSI_MODE_MASTER, 1000000, SPIWordSize);

		// Enable the SSI port.
		MAP_SSIEnable(ulBase);
	}
}



/**
 * @brief Cancels all selections.
 *
 * Makes all SPI devices inactive.
 * @returns void
 */
void SPIDeselect() {
	// do the actual deselect
	SPIDeselectISR();

	// return the mutex, enable the radio IRQ
	osSemaphoreGive(spiMutex);
}

void SPIDeselectISR() {
	// wait until the last transfer is finished
	volatile uint8 q;
	while (MAP_SSIBusy(SSI0_BASE)) {q++;}

	//Assert all select/latch pins inactive
	MAP_GPIOPinWrite(LED_LE_PORT, LED_LE_PIN, 0);
}


/**
 * @brief Selects a SPI device and sets its wordsize.
 *
 * Does not select anything if the input parameter is not recognized.
 * @param device to be selected
 * @param wordsize of the device to be set
 * @returns void
 */
void SPISelectDevice(uint8 device) {
	// disable the radio IRQ, get the mutex
	osSemaphoreTake(spiMutex, portMAX_DELAY);

	// Do the work
	SPISelectDeviceISR(device);
}


void SPISelectDeviceISR(uint8 device) {
	unsigned long junk;
	volatile uint8 q;

	// deassert the previous device
	SPIDeselectISR();

	// clear the receive FIFO
	while (MAP_SSIDataGetNonBlocking(SSI0_BASE, &junk)) {q++;}

	switch (device) {
		case SPI_LEDS_ONOFF: {
			SPIConfigure(SSI0_BASE, SPI_LEDS_ONOFF_WORDSIZE, SSI_FRF_MOTO_MODE_0);
			// nothing to do here.  The LED controller is a shift register
			break;
		}
		case SPI_LEDS_DIMMER: {
			SPIConfigure(SSI0_BASE, SPI_LEDS_DIMMER_WORDSIZE, SSI_FRF_MOTO_MODE_0);
			// nothing to do here.  The LED controller is a shift register
			break;
		}
		case SPI_NULL:
		default: {
			break;
		}
	}
}

void SPIConfigureMSP8(void) {
	SPIConfigure(SSI0_BASE, 8, SSI_FRF_MOTO_MODE_1);
}




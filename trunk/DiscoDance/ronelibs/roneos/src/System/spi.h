/*
 * spi.h
 *
 *  Created on: Mar 26, 2011
 *      Author: jamesm
 */

#ifndef SPI_H_
#define SPI_H_

#define SPI_NULL                               	0
#define SPI_LEDS_ONOFF                          3
#define SPI_LEDS_DIMMER                         4

#define SPI_LEDS_ONOFF_WORDSIZE                 16
#define SPI_LEDS_DIMMER_WORDSIZE                7

#define LED_LE_SYSCTL                           SYSCTL_PERIPH_GPIOD
#define LED_LE_PORT                             GPIO_PORTD_BASE
#define LED_LE_PIN                              GPIO_PIN_2

void SPIInit(void);
void SPISelectDevice(uint8 device);
void SPISelectDeviceISR(uint8 device);
void SPIDeselect(void);
void SPIDeselectISR(void);
void SPIConfigureMSP8(void);

#endif /* SPI_H_ */

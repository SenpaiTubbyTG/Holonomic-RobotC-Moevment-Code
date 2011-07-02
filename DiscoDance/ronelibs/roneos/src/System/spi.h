/*
 * spi.h
 *
 *  Created on: Mar 26, 2011
 *      Author: jamesm
 */

#ifndef SPI_H_
#define SPI_H_

#define SPI_NULL                               	0
#define SPI_RADIO                               1
#define SPI_ACCELEROMETER                       2
#define SPI_LEDS_ONOFF                          3
#define SPI_LEDS_DIMMER                         4
#define SPI_MSP430								5
#define SPI_MSP430_9							6
#define SPI_SDCARD								7

#define SPI_RADIO_WORDSIZE                      8
#define SPI_ACCELEROMETER_WORDSIZE              8
#define SPI_LEDS_ONOFF_WORDSIZE                 16
#define SPI_LEDS_DIMMER_WORDSIZE                7
#define SPI_MSP430_WORDSIZE						8
#define SPI_SDCARD_WORDSIZE						8

#define RADIO_SELECT_PORT                       GPIO_PORTA_BASE
#define RADIO_SELECT_PERIPH                     SYSCTL_PERIPH_GPIOA
#define RADIO_SELECT_PIN                        GPIO_PIN_7

#define LED_LE_SYSCTL                           SYSCTL_PERIPH_GPIOA
#define LED_LE_PORT                             GPIO_PORTA_BASE
#define LED_LE_PIN                              GPIO_PIN_6

#define MSP430_SELECT_SYSCTL              		SYSCTL_PERIPH_GPIOA
#define MSP430_SELECT_PORT						GPIO_PORTA_BASE
#define MSP430_SELECT_PIN						GPIO_PIN_3

#define SDCARD_SELECT_SYSCTL					SYSCTL_PERIPH_GPIOA
#define SDCARD_SELECT_PORT						GPIO_PORTA_BASE
#define SDCARD_SELECT_PIN						GPIO_PIN_7

void SPIInit(void);
void SPISelectDevice(uint8 device);
void SPISelectDeviceISR(uint8 device);
void SPIDeselect(void);
void SPIDeselectISR(void);
void SPIConfigureMSP8(void);

#endif /* SPI_H_ */

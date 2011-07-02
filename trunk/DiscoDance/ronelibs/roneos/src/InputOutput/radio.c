/**
 * @file radio.c
 *
 *  Created on: Jul 9, 2010
 *      Author: sjb2
 */
#include <stdio.h>
#include <string.h>

#ifdef PART_LM3S9B92
#include "inc/lm3s9b92.h"
#endif
#ifdef PART_LM3S8962
#include "inc/lm3s8962.h"
#endif

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_qei.h"

#include "driverlib/flash.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/qei.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/ssi.h"
#include "driverlib/interrupt.h"

//#include "pm.h"
//#include "plat.h"
//#include "stellaris.h"
#include "nRF24L01.h"
#include "hal_nrf_reg.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "roneos.h"

/**Begin Pin Definitions for the Radio**/
/**
 *SS=PA7, SLP_TR=PA6
 *RST=PG0
 *IRQ=PC5
 **/

#define RADIO_IRQ_PORT 			GPIO_PORTC_BASE
#define RADIO_IRQ_SYSCTL 		SYSCTL_PERIPH_GPIOC
#define RADIO_IRQ_PIN 			GPIO_PIN_5
#define RADIO_INT 				INT_GPIOC
#define RADIO_CE_PIN            GPIO_PIN_2
#define RADIO_CE_PORT           GPIO_PORTB_BASE
#define RADIO_CE_SYSCTL         SYSCTL_PERIPH_GPIOB
#define RADIO_XMIT_IRQ_TIMEOUT	3

char radio_frame[RADIO_MESSAGE_LENGTH + 1];
uint8 radio_frame_size;
uint8 radio_frame_LQI;
boolean radio_got_new_message = false;
boolean radio_got_irq = false;

#define RADIO_COMMS_QUEUE_RECV_SIZE	5
#define RADIO_COMMS_QUEUE_XMIT_SIZE	2
osQueueHandle radioCommsQueueRecv;
osQueueHandle radioCommsQueueXmit;

/**
 * @brief Gets the SPI data in the specified register.
 *
 * @param reg the register (represented by 32 bits) to read data from
 * @returns the 32-bit SPI data in the register
 */
uint32 radio_read_register_isr(uint32 reg) {
	uint32 chip_status;
	uint32 spi_data;

	SPISelectDeviceISR(SPI_RADIO);
	MAP_SSIDataPut(SSI0_BASE, reg);
	MAP_SSIDataGet(SSI0_BASE, &chip_status);
	MAP_SSIDataPut(SSI0_BASE, 0x00);
	MAP_SSIDataGet(SSI0_BASE, &spi_data);
	SPIDeselectISR();

	return spi_data;
}

/**
 * @brief Writes something into the specified register.
 *
 * Writes the first 8 bits of the 32-bit value into the register.
 * @param reg the register to write into
 * @param val 32-bit value to be written into the register
 * @returns the radio chip status
 */
uint32 radio_write_register_isr(uint32 reg, uint32 val) {
	uint32 chip_status;
	uint32 spi_data;

	SPISelectDeviceISR(SPI_RADIO);
	MAP_SSIDataPut(SSI0_BASE, WRITE_REG | (reg & 0x3F));
	MAP_SSIDataGet(SSI0_BASE, &chip_status);
	MAP_SSIDataPut(SSI0_BASE, val);
	MAP_SSIDataGet(SSI0_BASE, &spi_data);
	SPIDeselectISR();

	return chip_status;
}

/**
 * @brief Writes a command into the radio.
 *
 * @param command command to be written into the radio
 * @returns void
 */
void radio_write_command_isr(uint32 command) {
	uint32 chip_status;
	//    uint32 spi_data;

	SPISelectDeviceISR(SPI_RADIO);
	MAP_SSIDataPut(SSI0_BASE, command);
	MAP_SSIDataGet(SSI0_BASE, &chip_status);
	SPIDeselectISR();

}
/**
 * @brief Gets the SPI data in the specified register.
 *
 * @param reg the register (represented by 32 bits) to read data from
 * @returns the 32-bit SPI data in the register
 */
uint32 radio_read_register(uint32 reg) {
	uint32 chip_status;
	uint32 spi_data;

	SPISelectDevice(SPI_RADIO);
	MAP_SSIDataPut(SSI0_BASE, reg);
	MAP_SSIDataGet(SSI0_BASE, &chip_status);
	MAP_SSIDataPut(SSI0_BASE, 0x00);
	MAP_SSIDataGet(SSI0_BASE, &spi_data);
	SPIDeselect();

	return spi_data;
}

/**
 * @brief Writes something into the specified register.
 *
 * Writes the first 8 bits of the 32-bit value into the register.
 * @param reg the register to write into
 * @param val 32-bit value to be written into the register
 * @returns the radio chip status
 */
uint32 radio_write_register(uint32 reg, uint32 val) {
	uint32 chip_status;
	uint32 spi_data;

	SPISelectDevice(SPI_RADIO);
	MAP_SSIDataPut(SSI0_BASE, WRITE_REG | (reg & 0x3F));
	MAP_SSIDataGet(SSI0_BASE, &chip_status);
	MAP_SSIDataPut(SSI0_BASE, val);
	MAP_SSIDataGet(SSI0_BASE, &spi_data);
	SPIDeselect();

	return chip_status;
}

/**
 * @brief Writes a command into the radio.
 *
 * @param command command to be written into the radio
 * @returns void
 */
void radio_write_command(uint32 command) {
	uint32 chip_status;
	//    uint32 spi_data;

	SPISelectDevice(SPI_RADIO);
	MAP_SSIDataPut(SSI0_BASE, command);
	MAP_SSIDataGet(SSI0_BASE, &chip_status);
	SPIDeselect();

}

/**
 * @brief Enables the radio chip.
 *
 * Sets the chip-enable PIN as high.
 * @returns void
 */
void radio_ce_on(void) {
	MAP_GPIOPinWrite(RADIO_CE_PORT, RADIO_CE_PIN, RADIO_CE_PIN);
}

/**
 * @brief Disables the radio chip.
 *
 * Sets the chip-enable PIN as low.
 * @returns void
 */
void radio_ce_off(void) {
	MAP_GPIOPinWrite(RADIO_CE_PORT, RADIO_CE_PIN, 0);
}

/**
 * @brief Sets the transmit mode.
 *
 * @returns void
 */
void radio_set_tx_mode_isr(void) {
	radio_ce_off();
	radio_write_register_isr(STATUS, (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT));//clear int bits
	// power on the radio, primary tx
	radio_write_register_isr(CONFIG, (1 << PWR_UP) | (0 << PRIM_RX));
	radio_ce_on();
	//TODO should this happen before CE goes high?
	radio_write_command_isr(FLUSH_TX);
}

/**
 * @brief Sets the transmit mode.
 *
 * @returns void
 */
void radio_set_tx_mode(void) {
	radio_ce_off();
	radio_write_register(STATUS, (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT));//clear int bits
	// power on the radio, primary tx
	radio_write_register(CONFIG, (1 << PWR_UP) | (0 << PRIM_RX));
	radio_ce_on();
	//TODO should this happen before CE goes high?
	radio_write_command(FLUSH_TX);
}

/**
 * @brief Sets the receive mode.
 *
 * @returns void
 */
void radio_set_rx_mode_isr(void) {
	uint32 id;

	radio_ce_off();
	//    id = roneID;
	//    radio_set_id(id);

	// power on the radio, primary rx
	radio_write_register_isr(CONFIG, (1 << PWR_UP) | (1 << PRIM_RX));
	radio_ce_on();

	//TODO should this happen before CE goes high?
	radio_write_command_isr(FLUSH_RX);
}

#if 0
/**
 * @brief Sets the address to receive from.
 *
 * @param addrPtr pointer to the address from which data is received
 * @param size size of the data to be received
 * @returns void
 */
void radio_set_rx_addr(char* addrPtr, uint8 size) {
	uint32 buffer;
	int i;

	SPISelectDevice(SPI_RADIO, 8);
	//set addr
	MAP_SSIDataPut(SSI0_BASE, WRITE_REG | RX_ADDR_P0);
	MAP_SSIDataGet(SSI0_BASE, &buffer);

	for (i = 0; i < size; i++) {
		MAP_SSIDataPut(SSI0_BASE, addrPtr[i]);
		MAP_SSIDataGet(SSI0_BASE, &buffer);
	}
	SPIDeselect();
}

/**
 * @brief Sets the address to transmit to.
 *
 * @param addrPtr pointer to the address to which data is transmitted
 * @param size of the data to be transmitted
 * @returns void
 */
void radio_set_tx_addr(char* addrPtr, uint8 size) {
	uint32 buffer;
	int i;

	SPISelectDevice(SPI_RADIO, 8);
	//set addr
	MAP_SSIDataPut(SSI0_BASE, WRITE_REG | TX_ADDR);
	MAP_SSIDataGet(SSI0_BASE, &buffer);
	for (i = 0; i < size; i++) {
		MAP_SSIDataPut(SSI0_BASE, addrPtr[i]);
		MAP_SSIDataGet(SSI0_BASE, &buffer);
	}
	SPIDeselect();
}
#endif

/**
 * @brief Sends a message through the radio.
 *
 * @param message_ptr pointer to the message to be sent
 * @param size size of the message to be sent
 *
 * Can't call this funtion from within an ISR
 */
//TODO lots of hacks in here to deal with radio bugs
void radio_send_message(char* message_ptr, uint32 size) {
	uint32 chip_status;
	uint32 spi_data;
	uint32 actualBytes = size;
	uint8 i;

	// flush transmit FIFO

	//DEBUG serial_send_string("radio xmit \"");
	//DEBUG serial_send_string(message_ptr);
	//DEBUG serial_send_string_crlf("\"");
	// put a message in the transmit fifo.
	radio_set_tx_mode();
	radio_got_irq = false;

	SPISelectDevice(SPI_RADIO);
	//TODO get variable length xmit working
	size = RADIO_MESSAGE_LENGTH;
	MAP_SSIDataPut(SSI0_BASE, WR_NAC_TX_PLOAD);//noack
	//    MAP_SSIDataPut(SSI0_BASE, WR_TX_PLOAD);//ack
	MAP_SSIDataGet(SSI0_BASE, &chip_status);
	while (size > 0) {
		if (actualBytes > 0) {
			MAP_SSIDataPut(SSI0_BASE, *message_ptr++);
			actualBytes--;
		} else {
			MAP_SSIDataPut(SSI0_BASE, 0);
		}
		MAP_SSIDataGet(SSI0_BASE, &spi_data);
		size--;
	}
	SPIDeselect();

	//busy wait for interrupt
	for (i = 0; i < RADIO_XMIT_IRQ_TIMEOUT; ++i) {
		if (radio_got_irq == TRUE) {
			break;
		}
		osTaskDelay(1);
	}
	//serial_send_string_crlf("return from send");
	//TODO radio driver error hack.  grumble...
	//TODO sjb2: So I think the big problem here is that we can't get a realistic understanding of how fast the
	//radio is transmitting unless we are blocking on this call until we get a tx interrupt, then we should return.
}

//void radio_send_message_string(char* message_ptr) {
//	// send strlen +1 bytes to xmit the null termination char
//	radio_send_message(message_ptr, strlen(message_ptr) + 1);
//}

#if 0
/**
 * @brief Sets which specific radio to receive from.
 *
 * Deprecated!
 * @param rx_id the ID of the radio you want to receive from
 * @returns void
 */
void radio_set_id(uint32 rx_id) {
	char id_ptr[5];
	uint32 res = 0;
	int i;
	for (i = 0; i < 3; i++) {
		res = res << 8;
		res |= (rx_id & 0xFF);
		rx_id = rx_id >> 8;
	}

	id_ptr[0] = (0xFF & res);
	id_ptr[1] = (0xFF & (res >> 8));
	id_ptr[2] = (0xFF & (res >> 16));
	id_ptr[3] = 0x00;
	id_ptr[4] = 0x00;
	spi_get_mutex();
	radio_set_tx_addr(id_ptr, 5);
	radio_set_rx_addr(id_ptr, 5);
	spi_put_mutex();
}
#endif

/**
 * @brief Enables radio interrupt.
 *
 * @returns void
 */
void radio_int_enable(void) {
	MAP_GPIOPinIntEnable(RADIO_IRQ_PORT, RADIO_IRQ_PIN);
	MAP_IntEnable(RADIO_INT);
}

/**
 * @brief Disables radio interrupt.
 *
 * @returns void
 */
void radioIntDisable(void) {
	MAP_GPIOPinIntDisable(RADIO_IRQ_PORT, RADIO_IRQ_PIN);
	MAP_IntDisable(RADIO_INT);
}

boolean radio_error = false;
boolean packet_sucess = false;
uint8 radio_state_transition_command = 0;
uint8 radio_state_transition_goal_state = 0;
uint8 radio_state_transition_actual_state = 0;

/**
 * @brief Gets whether there is a radio error.
 *
 * @returns TRUE or FALSE depending on whether there is an error
 */
boolean radio_get_error(void) {
	return radio_error;
}

/**
 * @brief Gets whether the previous packet was successfully sent.
 *
 * @returns TRUE or FALSE depending on the success of sending packet
 */
boolean radio_get_success() {
	return packet_sucess;
}
void radio_packet_process(packet * message) {
	//Should not return from these special commands
	if (message->command == COMMAND_RESET) {
		//do reset
		SysCtlReset();
	} else if (message->command == COMMAND_PROGRAM) {
		//enter bootloader
		systemBootloader();
	}
}
/**
 * @brief Handles radio interrupt.
 *
 * @returns void
 */
void radio_int_handler(void) {
	uint32 status;
	uint8 pipe;
	uint32 chip_status;
	uint32 spi_data;
	int i;
	portBASE_TYPE val;
	portBASE_TYPE taskWoken = pdFALSE;

	// We don't need to get the SPI mutex here because we're in an interrupt
	// the radio irq is disabled by selecting any other SPI device

	//clear interrupt register. read interrupts
	status = radio_write_register_isr(STATUS, (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT));
	MAP_GPIOPinIntClear(RADIO_IRQ_PORT, RADIO_IRQ_PIN);
	//status = radio_write_register(STATUS, 0x70);    //clear ints
	//serial_send_hexbyte("radio int ", status);

	if (status & (1 << MASK_TX_DS)) {
		//transmit finished go to rx mode
		//serial_send_string("Packet Success :)\r\n");
		packet_sucess = true;
		radio_set_rx_mode_isr();
	}
	if (status & (1 << MASK_MAX_RT)) {
		//reach maximum retransmissions.
		//Give up. Can retry by toggling CE.
		//serial_send_string("Packet Drop :(\r\n");
		packet_sucess = false;
		radio_set_rx_mode_isr();
	}
	if (status & (1 << MASK_RX_DR)) {
		//receipt of message
		MAP_SSIDataPut(SSI0_BASE, RD_RX_PLOAD_W);
		MAP_SSIDataGet(SSI0_BASE, &spi_data);
		MAP_SSIDataPut(SSI0_BASE, 0);
		MAP_SSIDataGet(SSI0_BASE, &spi_data);
		//TODO hack is a few lines down
		//radio_frame_size = (uint8) spi_data;

		SPISelectDeviceISR(SPI_RADIO);
		MAP_SSIDataPut(SSI0_BASE, RD_RX_PLOAD);
		MAP_SSIDataGet(SSI0_BASE, &chip_status);
		//TODO can check status to see if fifo is empty.

		//TODO ugly hack to deal with the radio message size bug
		radio_frame_size = RADIO_MESSAGE_LENGTH;
		for (i = 0; i < radio_frame_size; i++) {
			MAP_SSIDataPut(SSI0_BASE, 0x00);
			MAP_SSIDataGet(SSI0_BASE, &spi_data);
			radio_frame[i] = (char)spi_data;
			//TODO hack until we get var length packets working
			//            if (spi_data == 0) {
			//                radio_frame_size = i + 1;
			//                break;
			//            }
		}
		//TODO hack: add a null just to be careful...
		//        radio_frame[i] = 0;
		SPIDeselectISR();

		radio_write_command_isr(FLUSH_RX);
		val = osQueueSendFromISR(radioCommsQueueRecv, (void*)(&radio_frame[0]), &taskWoken);
		//TODO commented out packet processing for downloading
		//radio_packet_process((packet *) &radio_frame[0]);
		//DEBUG
		//serial_send_long(" s3 ", radio_frame_size);
		//serial_send_string_crlf(radio_frame);
		radio_got_new_message = true;
	}
	radio_got_irq = true;
}

void __attribute__ ((interrupt)) __cs3_isr_gpio_c(void) {
	radio_int_handler();
}

/**
 * @brief Initializes the radio.
 *
 * @returns void
 */
void radio_init(void) {
	radioCommsQueueRecv = osQueueCreate(RADIO_COMMS_QUEUE_RECV_SIZE, RADIO_MESSAGE_LENGTH);
	radioCommsQueueXmit = osQueueCreate(RADIO_COMMS_QUEUE_XMIT_SIZE, RADIO_MESSAGE_LENGTH);

	//Enable all peripherals for the SPI Radio Control
	MAP_SysCtlPeripheralEnable(RADIO_IRQ_SYSCTL);
	MAP_SysCtlPeripheralEnable(RADIO_CE_SYSCTL);

	//Set up interrupt on the Radio IRQ line
	MAP_GPIOPinTypeGPIOInput(RADIO_IRQ_PORT, RADIO_IRQ_PIN);
	MAP_GPIOPadConfigSet(RADIO_IRQ_PORT, RADIO_IRQ_PIN, GPIO_STRENGTH_2MA,
			GPIO_PIN_TYPE_STD_WPU);
	MAP_GPIOIntTypeSet(RADIO_IRQ_PORT, RADIO_IRQ_PIN, GPIO_FALLING_EDGE);
	MAP_GPIOPinIntEnable(RADIO_IRQ_PORT, RADIO_IRQ_PIN);

	//Enable CE
	radio_ce_off();
	MAP_GPIOPinTypeGPIOOutput(RADIO_CE_PORT, RADIO_CE_PIN);

	//TODO try to enable dynamic message length.  but maybe we don't care...
	//    radio_write_register(EN_AA, (1 << ENAA_P1) | (1 << ENAA_P0));//enable autoack
	//    radio_write_register(EN_RXADDR, (1 << ERX_P0) | (1 << ERX_P1));//enable rx

	//    radio_write_register(EN_AA, (1 << ENAA_P0));//enable autoack
	radio_write_register_isr(EN_AA, 0x00);//disable autoack
	//    radio_write_register(EN_RXADDR, (1 << ERX_P0));//enable rx
	//    radio_write_register(SETUP_AW, 0x11);//addr size is 5 bytes
	//    radio_write_register(SETUP_RETR, 0x03);//default retransmission

	radio_write_register_isr(RX_PW_P0, RADIO_MESSAGE_LENGTH);
	//    radio_write_register(DYNPD, (1 << DPL_P1) | (1 << DPL_P0));//dyna payload

	radio_write_register_isr(FEATURE, (1 << EN_DPL) | (1 << EN_DYN_ACK));

	//    radio_write_register(RX_PW_P0, 0x0f); //set size to max
	radio_write_register_isr(STATUS, (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT)); //set int bits

	radio_set_rx_mode_isr();
	radio_int_enable();
}

//uint8 radio_get_status(void) {
//	//clears interrupts
//	uint32 status;
//	status = radio_write_register(STATUS, 0x00);
//	return status;
//}

/**
 * @brief Checks whether there is a message.
 *
 * @param message pointer to the message to be checked
 * @param message_size_ptr pointer to thesize of the message
 * @param message_link_quality_ptr pointer to the link quality of the message
 * @returns TRUE if there is a message, FALSE if not
 */
boolean radio_get_message(char* message, uint32* message_size_ptr,
		uint32* message_link_quality_ptr) {
	portBASE_TYPE val;
	//TODO needs to be changed if we get message length working, could
	//add a separate queue that deals with the  msg lens.

	val = osQueueReceive(radioCommsQueueRecv, (void *)(message), 0);
	if (val == pdPASS) {
		//serial_send_string_crlf("New message received");
		return TRUE;
	} else {
		//serial_send_string_crlf("No new messages");
		return FALSE;
	}

	//	int i;
	//    if (radio_got_new_message) {
	//        *message_size_ptr = radio_frame_size;
	//        *message_link_quality_ptr = 128;
	//        for (i = 0; i < radio_frame_size; i++) {
	//            message[i] = radio_frame[i];
	//        }
	//        radio_got_new_message = false;
	//        osTaskDelay(1);
	//        return true;
	//    } else {
	//        *message_size_ptr = 0;
	//        *message_link_quality_ptr = 0;
	//        message[0] = 0;
	//        osTaskDelay(1);
	//        return false;
	//    }
}

/**
 * @brief Null terminates the radio message.
 *
 * Deprecated!
 * @param message pointer to the message to be terminated
 * @param message_link_quality_ptr pointer to the link quality of the message
 * @returns void
 */
uint32 radio_get_message_string(char* message, uint32* message_link_quality_ptr) {
	uint32 message_size = 0;
	return radio_get_message(message, &message_size, message_link_quality_ptr);
}

/**
 * @brief Gets the link quality.
 *
 * @returns void
 */
uint32 radio_get_link_quality(void) {
	return radio_read_register(CD);
}

//void radio_send_bytes_id(char * message_ptr, uint8 size, uint32 rx_id) {
//    //    radio_set_id(rx_id);
//    radio_send_message(message_ptr, size);
//}
//
//void radio_send_string_id(char * message_ptr, uint32 rx_id) {
//	// send strlen +1 bytes to xmit the null termination char
//    radio_send_bytes_id(message_ptr, strlen(message_ptr) + 1, rx_id);
//}


/**
 * @file ir_comms.c
 *
 *  Created on: Jul 22, 2010
 *      Author: jamesm
 */
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

#include "roneos.h"

#include "../src/crc/crctest.h"	//TESTING

#define IR_RECEIVERS_PERIPH 			SYSCTL_PERIPH_GPIOD
#define IR_RECEIVERS_BASE 				GPIO_PORTD_BASE

#define TRANSMIT_FREQUENCY 				38000
#define ENCODED_MESSAGE_NUM_WORDS 		2
// 1250 = 800us per bit
#define TRANSMIT_BIT_FREQUENCY			1250

#define IR_COMMS_MESSAGE_AND_CRC_LENGTH     (IR_COMMS_MESSAGE_LENGTH_MAX + 2)

uint32 ir_comms_pwm_on_setting;

// packet preamble is 6 bits
#define IR_COMMS_PREAMBLE   				0x07
#define IR_COMMS_PREAMBLE_SIZE   			6

#define CRC_AND_STOP_BIT_LENGTH				12 + 1

uint32 recv_msg_bits[IR_COMMS_NUM_OF_RECEIVERS][ENCODED_MESSAGE_NUM_WORDS];
//uint32 ir_comms_irq_count[IR_COMMS_NUM_OF_RECEIVERS];
//uint32 ir_comms_process_bits = 0;

uint32 preamble_mask[ENCODED_MESSAGE_NUM_WORDS];
uint32 preamble_bits[ENCODED_MESSAGE_NUM_WORDS];

uint8 ir_comms_message_length = IR_COMMS_MESSAGE_LENGTH_DEFAULT;
uint8 ir_comms_message_bit_count;
uint8 ir_comms_message_left_justify_shifts = 0;
uint32 ir_comms_interrupt_count = 0;



#define IR_COMMS_QUEUE_RECV_SIZE	50
#define IR_COMMS_QUEUE_XMIT_SIZE	10
osQueueHandle irCommsQueueRecv;
osQueueHandle irCommsQueueXmit;

extern const uint16 CRC16_TABLE[];


uint16 crc_update(uint16 crc, const unsigned char *data, unsigned int data_len)
{
    unsigned int tbl_idx;

    while (data_len--) {
        tbl_idx = (crc ^ *data) & 0xff;
        crc = (CRC16_TABLE[tbl_idx] ^ (crc >> 8)) & 0xffff;

        data++;
    }
    return crc & 0xffff;
}


/**
 * @brief Calculates the CRC for the message.
 *
 * @param msg[] the mssage to be calculated
 * @returns the CRC for the message
 */
uint16 CRCcalculate(uint8 msg[]) {
    uint16 crc = 0x0000;
    int i;
    for (i = 0; i < ir_comms_message_length; i++) {
        crc = crc_update(crc, (unsigned char *)&msg[i], 1);
    }
    crc = crc ^ 0x0000;
    return crc;
}


/**
 * @brief Clears the first two bits (buffer) of the message.
 *
 * @returns void
 */
void clear_msg_bits_buffer(uint32* bitBufferPtr) {
	bitBufferPtr[0] = 0;
	bitBufferPtr[1] = 0;
}

/**
 * @brief Shifts a specified number of bits of the data into buffer.
 *
 * @param bitBufferPtr pointer to the buffer to be shifted into
 * @param data the data whose bits are shifted
 * @param bitCount how many bits should be shifted
 * @returns void
 */
void shift_bits_into_buffer(uint32* bitBufferPtr, uint32 data, uint8 bitCount) {
	if (bitCount < 32) {
		uint32 mask = (1 << bitCount) - 1;
		bitBufferPtr[0] <<= bitCount;
		bitBufferPtr[0] |= (bitBufferPtr[1] >> (32 - bitCount));
		bitBufferPtr[1] <<= bitCount;
		bitBufferPtr[1] |= (data & mask);
	} else if (bitCount < 64) {
		bitCount -= 32;
		bitBufferPtr[0] = bitBufferPtr[1] << bitCount;
		bitBufferPtr[0] |= (data >> (32 - bitCount));
		bitBufferPtr[1] = data << bitCount;
	} else {
		clear_msg_bits_buffer(bitBufferPtr);
	}
}

/**
 * @brief Shifts one bit of data into buffer.
 *
 * @param bitBufferPtr pointer to the buffer to be shifted into
 * @param data the data whose bits are shifted
 * @returns void
 */
void shift_bit_into_buffer(uint32* bitBufferPtr, uint32 data) {
	bitBufferPtr[0] <<= 1;
	bitBufferPtr[0] |= (bitBufferPtr[1] >> 31);
	bitBufferPtr[1] <<= 1;
	bitBufferPtr[1] |= (data & 0x01);;
}


//void print_bit_buffer(char* name, uint32* buffer) {
//	serial_send_string(name);
//	for (int i = 0; i < ENCODED_MESSAGE_NUM_WORDS; i++) {
//		serial_send_hexbyte(",", (buffer[i] >> 24) & 0x00FF);
//		serial_send_hexbyte(",", (buffer[i] >> 16) & 0x00FF);
//		serial_send_hexbyte(",", (buffer[i] >> 8) & 0x00FF);
//		serial_send_hexbyte(",", (buffer[i] & 0x00FF));
//	}
//	serial_send_string_crlf("");
//}


/**
 * @brief Enables ir_comms.
 *
 * @returns void
 */
void ir_comms_int_enable() {
    MAP_IntEnable(INT_TIMER1A);
}

/**
 * @brief Disables ir_comms.
 *
 * @returns void
 */
void ir_comms_int_disable() {
    MAP_IntDisable(INT_TIMER1A);
}

/**
 * @brief Sets the length of the message to be sent.
 *
 * @param msg_length length of the message
 * @returns void
 */
void ir_comms_set_message_length(uint8 msg_length) {

	if (msg_length > IR_COMMS_MESSAGE_LENGTH_MAX) {
		msg_length = IR_COMMS_MESSAGE_LENGTH_MAX;
	}
	ir_comms_int_disable();
	ir_comms_message_length = msg_length;
	ir_comms_message_bit_count = IR_COMMS_PREAMBLE_SIZE + 9 * msg_length + CRC_AND_STOP_BIT_LENGTH;
	ir_comms_message_left_justify_shifts = (64 - ir_comms_message_bit_count);

	uint32 mask = (1 << IR_COMMS_PREAMBLE_SIZE) - 1;
    clear_msg_bits_buffer(preamble_mask);
    clear_msg_bits_buffer(preamble_bits);
    shift_bits_into_buffer(preamble_mask, mask, IR_COMMS_PREAMBLE_SIZE);
    shift_bits_into_buffer(preamble_bits, IR_COMMS_PREAMBLE, IR_COMMS_PREAMBLE_SIZE);
    shift_bits_into_buffer(preamble_mask, 0, ir_comms_message_bit_count - IR_COMMS_PREAMBLE_SIZE);
    shift_bits_into_buffer(preamble_bits, 0, ir_comms_message_bit_count - IR_COMMS_PREAMBLE_SIZE);
    ir_comms_int_enable();

//    serial_send_long("ir_comms_message_length",ir_comms_message_length);
//    serial_send_string_crlf("");
//    serial_send_long("ir_comms_message_bit_count",ir_comms_message_bit_count);
//    serial_send_string_crlf("");
//    serial_send_long("ir_comms_message_left_justify_shifts",ir_comms_message_left_justify_shifts);
//    serial_send_string_crlf("");
//    print_bit_buffer("preamble_mask", preamble_mask);
//    print_bit_buffer("preamble_bits", preamble_bits);
}


/**
 * @brief Sends out a message through IR transmitters.
 *
 * Message is 1-5 bytes of data, first byte is robot ID
 * @param irMessagePtr pointer to the ir_comms_message struct that contains the message to be sent
 * @returns whether the message is sent (TRUE/FALSE)
 */
//
boolean ir_comms_send_message(ir_comms_message* irMessagePtr) {

	portBASE_TYPE val;

	val = osQueueSend(irCommsQueueXmit, (void*)(irMessagePtr), 0);
    if (val == pdPASS) {
        return TRUE;
    } else {
        return FALSE;
    }
}


//
/**
 * @brief Gets a message through IR transmitters.
 *
 * @param irMessagePtr pointer to the ir_comms_message struct that contains receiver information
 * @returns TRUE if there is a message, FALSE if not
 */
boolean ir_comms_get_message(ir_comms_message* irMessagePtr) {

	portBASE_TYPE val;

	val = osQueueReceive(irCommsQueueRecv, (void*)(irMessagePtr), 0);
    if (val == pdPASS) {
        return TRUE;
    } else {
    	irMessagePtr->data[0] = 0;
    	irMessagePtr->receiverBits = 0;
        return FALSE;
    }
}

/**
 * @brief Initliazes IRComms.
 *
 * Creates the OS message queues.
 * Initializes IR port for GPIO and set it as input.
 * Sets PWM pins; computes and sets pwm period based on system clock.
 * Enables PWM generators and output state.
 * Enables a 1250hz (800us) interrupt.
 * @returns void
 */
void ir_comms_init(void) {
	uint32 pwm_period;
	ir_comms_message msg_test;

	ir_comms_set_message_length(IR_COMMS_MESSAGE_LENGTH_DEFAULT);

	// init the OS message queues
	irCommsQueueRecv = osQueueCreate(IR_COMMS_QUEUE_RECV_SIZE, sizeof(ir_comms_message));
	irCommsQueueXmit = osQueueCreate(IR_COMMS_QUEUE_XMIT_SIZE, sizeof(ir_comms_message));

	// init the IR port for gpio, set to input
    MAP_SysCtlPeripheralEnable(IR_RECEIVERS_PERIPH);
    MAP_GPIOPinTypeGPIOInput(IR_RECEIVERS_BASE, 0xFF);

    //set the pins as pwm pins
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinConfigure(GPIO_PE0_PWM4);
    MAP_GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_0);

    // Compute the PWM period based on the system clock.
    pwm_period = MAP_SysCtlClockGet() / TRANSMIT_FREQUENCY;
    ir_comms_pwm_on_setting = (pwm_period * 50) / 100;

    // Set the PWM period.
    MAP_PWMGenConfigure(PWM_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN
            | PWM_GEN_MODE_NO_SYNC);
    MAP_PWMGenPeriodSet(PWM_BASE, PWM_GEN_2, pwm_period);

    // Enable the PWM generator.
    MAP_PWMGenEnable(PWM_BASE, PWM_GEN_2);
    //enable output state.
    MAP_PWMOutputState(PWM_BASE, PWM_OUT_4_BIT, true);

    // enable a 1250hz (800us) interrupt // jl71
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_32_BIT_PER);
    MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, SysCtlClockGet() / TRANSMIT_BIT_FREQUENCY);

    MAP_IntEnable(INT_TIMER1A);
    MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    MAP_TimerEnable(TIMER1_BASE, TIMER_A);
}


//this interrupt reads all 8 ir receivers and transmits IR transmit data for interrobot data
// it is called every 800us
void ir_comms_transmit_receive_handler(void) {
    register uint8 receive_bits;
    static uint32 xmit_msg_bits[ENCODED_MESSAGE_NUM_WORDS];
    static uint32 xmit_msg_bit_count;
    static uint32 pwm_setting_for_next_bit = 0;
    ir_comms_message ir_message;
	uint32 data_and_stop_bit;
    int i, j, receiver;
    portBASE_TYPE val;
    portBASE_TYPE taskWoken = pdFALSE;

    uint32 recv_msg_bits2[ENCODED_MESSAGE_NUM_WORDS];

    boolean got_message = false;
    uint16 CRC_message, CRC_calculated;
    boolean phase_error;
    uint8 msg_data[IR_COMMS_MESSAGE_AND_CRC_LENGTH];
//    uint32 bits = ir_comms_process_bits;
    uint32 stopBit;
    uint32 currentTime;
    static uint32 printme = 0;
//    int receiver, i, j;
//    portBASE_TYPE val;



    // read the ir bits now to process later
    receive_bits = ~((uint8)MAP_GPIOPinRead(IR_RECEIVERS_BASE, 0xFF));

    // transmit data using PWM to generate 38khz waveform
    MAP_PWMPulseWidthSet(PWM_BASE, PWM_OUT_4, pwm_setting_for_next_bit);

    // set the xmit bits up for next time
    if (xmit_msg_bit_count == 0) {

    	//get the next message from the xmit buffer

    	val = osQueueReceiveFromISR(irCommsQueueXmit, (void*)(&ir_message), &taskWoken);
        if (val == pdPASS) {
    		// you have a message to xmit.
        	//clear_msg_bits_buffer(xmit_msg_bits);
        	shift_bits_into_buffer(xmit_msg_bits, IR_COMMS_PREAMBLE, IR_COMMS_PREAMBLE_SIZE);
        	for (i = 0; i < ir_comms_message_length; i++) {
        		data_and_stop_bit = ir_message.data[i] << 1;
        		shift_bits_into_buffer(xmit_msg_bits, data_and_stop_bit, 9);
        	}

    		data_and_stop_bit = CRCcalculate(ir_message.data) << 1;

    		// only transmit 13 bits (12 bits + 1 stop bit)
    		shift_bits_into_buffer(xmit_msg_bits, data_and_stop_bit, CRC_AND_STOP_BIT_LENGTH);

        	// Left justify the output data
        	shift_bits_into_buffer(xmit_msg_bits, 0, ir_comms_message_left_justify_shifts);

        	// set the bit counter to start transmitting message bits on the next irq
        	xmit_msg_bit_count = ir_comms_message_bit_count;

        	//print_in_binary(xmit_msg_bits);

        	//print_bit_buffer("xmit", xmit_msg_bits);
    	}
    }

    if (xmit_msg_bit_count > 0) {
        if (xmit_msg_bits[0] & 0x80000000) {
            pwm_setting_for_next_bit = ir_comms_pwm_on_setting;
        } else {
            pwm_setting_for_next_bit = 0;
        }
        xmit_msg_bit_count--;
        shift_bit_into_buffer(xmit_msg_bits, 0);

        //TODO clear the receive bits so you don't receive your own transmission
        // this will be removed when we are ready to test obstacle detection
        //receive_bits = 0;
    } else {
        pwm_setting_for_next_bit = 0;
    }


    ir_message.receiverBits = 0;

    // shift in bits from 8 receivers
	currentTime = osTaskGetTickCountFromISR();
//    ir_comms_interrupt_count++;
    for (receiver = 0; receiver < IR_COMMS_NUM_OF_RECEIVERS; receiver++) {
    	// shift in the new bit for this receiver
    	shift_bit_into_buffer(recv_msg_bits[receiver], (receive_bits >> receiver));
        // look for a preamble to flag candidate packets
    	if (((recv_msg_bits[receiver][0] & preamble_mask[0]) == preamble_bits[0]) &&
    		((recv_msg_bits[receiver][1] & preamble_mask[1]) == preamble_bits[1])) {
        	// there is a preamble at the front of this packet.  Copy the current bits to temporary buffers for processing
    		//print_in_binary(recv_msg_bits2);
    		recv_msg_bits2[0] = recv_msg_bits[receiver][0];
			recv_msg_bits2[1] = recv_msg_bits[receiver][1];

    		shift_bits_into_buffer(recv_msg_bits2, 0, ir_comms_message_left_justify_shifts + IR_COMMS_PREAMBLE_SIZE);

    		phase_error = false;
            for (i = 0; i < ir_comms_message_length; i++) {
            	msg_data[i] = (uint8)(recv_msg_bits2[0] >> 24);
            	stopBit = recv_msg_bits2[0] & 0x00800000;
            	if (stopBit != 0) {
            		phase_error = true;
            	}
                shift_bits_into_buffer(recv_msg_bits2, 0, 9);
            }
            CRC_message = (uint16)(recv_msg_bits2[0] >> 16);
            CRC_calculated = CRCcalculate(msg_data);

            //make the calculated CRC 12-bit
            CRC_calculated = (CRC_calculated & 0x0FFF) << 4;



            if ((!phase_error) & (CRC_message == CRC_calculated)) {
                if (!got_message) {
                    // first message being processed this interrupt
                    for (j = 0; j < ir_comms_message_length; j++) {
                    	ir_message.data[j] = msg_data[j];
                    }
                    ir_message.receiverBits = (1 << receiver);
                    ir_message.CRC = CRC_message;
                	ir_message.timeStamp = currentTime;
                    got_message = true;
                    //DEBUG serial_send_long(" R", i);
                    //DEBUG serial_send_long("", i);
                } else {
                    //check to see if this has the same data and same CRC
                	boolean match = true;
                	if(ir_message.CRC != CRC_message) {
                		match = false;
                		//DEBUG serial_send_string(" !CRC");
                	}
					for (j = 0; j < ir_comms_message_length; j++) {
						if (ir_message.data[j] != msg_data[j]) {
							match = false;
							//DEBUG serial_send_long(" !data", j);
						}
                	}
					if(match) {
						// same irq count, same data, same crc. update receiver bits
						ir_message.receiverBits |= (1 << receiver);
						//DEBUG serial_send_long("", i);
					}
                }
            }
            //DEBUG serial_send_string_crlf("");
    	}
	}
    if (got_message) {
    	val = osQueueSendFromISR(irCommsQueueRecv, (void*)(&ir_message), &taskWoken);
    	//TODO trap the return val and so something with it
   }

}

// Called when timer 1a goes off
void __attribute__ ((interrupt)) __cs3_isr_timer1a (void) {
	ir_comms_transmit_receive_handler();
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
}


// Note: I changed first byte to 1 to prevent a message of all 0s from having a correct CRC
const uint16 CRC16_TABLE[256] = {
    0x0001, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
    0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
    0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
    0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
    0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
    0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
    0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
    0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
    0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
    0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
    0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
    0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
    0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
    0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
    0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
    0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
    0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
    0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
    0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
    0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
    0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
    0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
    0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
    0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
    0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
    0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
    0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
    0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
    0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
    0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
    0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
    0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040  };


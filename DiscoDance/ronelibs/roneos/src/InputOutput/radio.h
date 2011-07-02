/*
 * radio.h
 *
 *  Created on: Mar 26, 2011
 *      Author: jamesm
 */

#ifndef RADIO_H_
#define RADIO_H_

#define RADIO_MESSAGE_LENGTH    32

/**
 * Commands
 */



void radio_init(void);
void radio_int_handler(void);
void radio_int_enable(void);
void radioIntDisable(void);
void radio_set_rx_remote(void);
void radio_packet_process(packet * message);

void radio_send_message(char* message, uint32 size);
//TODO not tested, do not use
//void radio_send_message_string(char* message);

boolean radio_get_message(char* message, uint32* message_size_ptr,
		uint32* message_link_quality_ptr);
//TODO not tested, do not use
//uint32 radio_get_message_string(char* message, uint32* message_link_quality_ptr);


//void radio_send_string_id(char * message_ptr, uint32 rx_id);
//void radio_send_bytes_id(char * message_ptr, uint8 size, uint32 rx_id);

uint32 radio_get_link_quality(void);
uint8 radio_get_success(void);

#endif /* RADIO_H_ */

/*
 * ir_comms.h
 *
 *  Created on: Mar 26, 2011
 *      Author: jamesm
 */

#ifndef IR_COMMS_H_
#define IR_COMMS_H_

#define IR_COMMS_MESSAGE_LENGTH_MAX         5
#define IR_COMMS_MESSAGE_LENGTH_DEFAULT     4

#define IR_COMMS_NUM_OF_RECEIVERS           8
#define IR_COMMS_RECEIVER_FRONT_LEFT        0
#define IR_COMMS_RECEIVER_LEFT_FRONT        1
#define IR_COMMS_RECEIVER_LEFT_REAR         2
#define IR_COMMS_RECEIVER_REAR_LEFT         3
#define IR_COMMS_RECEIVER_REAR_RIGHT        4
#define IR_COMMS_RECEIVER_RIGHT_REAR        5
#define IR_COMMS_RECEIVER_RIGHT_FRONT       6
#define IR_COMMS_RECEIVER_FRONT_RIGHT       7

#define IR_COMMS_RECEIVER_FRONT_LEFT_BIT 	(1 << IR_COMMS_RECEIVER_FRONT_LEFT)
#define IR_COMMS_RECEIVER_LEFT_FRONT_BIT 	(1 << IR_COMMS_RECEIVER_LEFT_FRONT)
#define IR_COMMS_RECEIVER_LEFT_REAR_BIT 	(1 << IR_COMMS_RECEIVER_LEFT_REAR)
#define IR_COMMS_RECEIVER_REAR_LEFT_BIT 	(1 << IR_COMMS_RECEIVER_REAR_LEFT)
#define IR_COMMS_RECEIVER_REAR_RIGHT_BIT 	(1 << IR_COMMS_RECEIVER_REAR_RIGHT)
#define IR_COMMS_RECEIVER_RIGHT_REAR_BIT 	(1 << IR_COMMS_RECEIVER_RIGHT_REAR)
#define IR_COMMS_RECEIVER_RIGHT_FRONT_BIT 	(1 << IR_COMMS_RECEIVER_RIGHT_FRONT)
#define IR_COMMS_RECEIVER_FRONT_RIGHT_BIT 	(1 << IR_COMMS_RECEIVER_FRONT_RIGHT)

#define IR_COMMS_RECEIVER_0_ANGLE	        0.3927
#define IR_COMMS_RECEIVER_1_ANGLE	        1.1781
#define IR_COMMS_RECEIVER_2_ANGLE	        1.9635
#define IR_COMMS_RECEIVER_3_ANGLE	        2.7489
#define IR_COMMS_RECEIVER_4_ANGLE	        3.5343
#define IR_COMMS_RECEIVER_5_ANGLE	        4.3197
#define IR_COMMS_RECEIVER_6_ANGLE	        5.1051
#define IR_COMMS_RECEIVER_7_ANGLE	        5.8905

typedef struct ir_comms_message {
    uint8 data[IR_COMMS_MESSAGE_LENGTH_MAX];
    uint8 receiverBits;
    uint16 CRC;
    uint32 timeStamp;
} ir_comms_message;


// returns true is the message could be placed on the xmit queue, false if not
boolean ir_comms_send_message(ir_comms_message* irMessagePtr);

// returns true is there was a message, false if not
boolean ir_comms_get_message(ir_comms_message* irMessagePtr);

// sets the length of all the IR messages.  Allowable valued are from 1-5
void ir_comms_set_message_length(uint8 msg_length);

void ir_comms_init(void);
//void ir_comms_process_buffers(void);

//TODO orientation xmit testing
void orientation_xmit_latch(void);
void orientation_xmit_set_output_pins(uint8 data);

#endif /* IR_COMMS_H_ */

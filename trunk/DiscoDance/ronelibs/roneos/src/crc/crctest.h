/*
 * crctest.h
 *
 *  Created on: Jun 3, 2011
 *      Author: Jennifer
 */

#ifndef CRCTEST_H_
#define CRCTEST_H_


//void jenCheckMessage(ir_comms_message* messageToCheck);
//int jenCompareMessage(ir_comms_message* messageToCompare);
//void jenCRCErrorInc(void);
//void jenCRCNoErrorInc(void);
void jenPrintDataPercent(void);
void jenPrintDataDetail(void);
void print_crc_log(void);

void print_in_binary(uint32 myMessage[2]);
void print_in_binary_bits(uint8 eightBitMessage);

#endif /* CRCTEST_H_ */

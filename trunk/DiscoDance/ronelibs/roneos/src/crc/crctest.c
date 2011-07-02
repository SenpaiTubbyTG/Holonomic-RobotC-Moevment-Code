/*
 * crctest.c
 *
 *  Created on: Jun 3, 2011
 *      Author: Jennifer
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "roneos.h"
#include "crctest.h"

uint8 neighborArray[4] = {34,10,19,17};
int neighborLength = 4;

unsigned int jenError = 0;
unsigned int ghostError = 0;
unsigned int jenTotalMessages = 0;
unsigned int printOnce = -1;
//int crcError = 0;
//int crcNoError = 0;
int static JENTRUE = 1;
int static JENFALSE = 0;



/*void jenCheckMessage(ir_comms_message* messageToCheck) {
	uint8 jenNeighborID;
	uint8 jenReceive;
	char nbrMessage;
	int hasGhost = JENTRUE;
	int i;

	//test for ghost message or error
	jenNeighborID = messageToCheck->data[0];
	//cprintf("neighborID: %d \n", jenNeighborID);
	for (i = 0; i < neighborLength; i++) {
		if (jenNeighborID == neighborArray[i]) {
			hasGhost = JENFALSE;
		}
	}

	if (hasGhost == JENTRUE) {
		ghostError++;
	} else if (jenCompareMessage(messageToCheck) == JENFALSE) {
		jenError++;
	} else {
		jenTotalMessages++;
	}


}

int jenCompareMessage(ir_comms_message* messageToCompare) {
	char constantString[3] = "abc";
	unsigned int sameMessage = JENTRUE;
	int i;

	for (i = 0; i < 3; i++) {
		if (constantString[i] != messageToCompare->data[i+1]) {
			sameMessage = JENFALSE;
		}
	}
	return sameMessage;
}*/


//void jenCRCErrorInc(void){
//	//cprintf("CRC Error! \n");
//	crcError++;
//}

//void jenCRCNoErrorInc(void){
//	crcNoError++;
//}

void jenPrintDataDetail(void){
	int jenTotalError;
	jenTotalError = ghostError + jenError;
	cprintf("CRC Failures: %d \n", jenError);
	cprintf("Ghost neighbors: %d \n", ghostError);
	cprintf("Total errors: %d \n", jenTotalError);
	cprintf("Total messages: %d \n", jenTotalMessages);
	cprintf("   \n");
}

void print_crc_log(void) {
	int jenTotalError;
	if (jenTotalMessages % 500 < 3) {
		jenTotalError = ghostError + jenError;
		if (printOnce != jenTotalMessages) {
			printOnce = jenTotalMessages;
			cprintf("crc: %d | ghosts: %d | totalE: %d | totalMSG: %d \n",jenError,ghostError,jenTotalError,jenTotalMessages);
		}
	}
}

void print_in_binary_bits(uint8 eightBitMessage) {
	int i;
	for (i = 0; i < 8; i++) {
		if(eightBitMessage & 0x80) {
			cprintf("1");
		} else {
			cprintf("0");
		}
		eightBitMessage <<= 1;
	}
	cprintf(" \n");
}

void print_in_binary(uint32 myMessage[2]) {
	int i;
	int j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 32; j++) {
			if (myMessage[i] & 0x80000000) {
				cprintf("1");
			} else {
				cprintf("0");
			}
			myMessage[i] = myMessage[i] << 1;
		}
		cprintf(" ");
	}
	cprintf(" \n");
}



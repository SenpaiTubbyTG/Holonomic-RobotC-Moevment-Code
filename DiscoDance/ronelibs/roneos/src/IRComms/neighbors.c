/**
 * @file neighbors.c
 *
 *  Created on: Mar 2, 2011
 *      Author: jamesm
 */
#include <stdio.h>
#include <stdlib.h>
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
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/flash.h"

#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"

#include "roneos.h"

#include "../src/crc/crctest.h"	//TESTING



/******** Defines ********/
#define MILLIRAD_BYTE_CONV	25


/******** Variables ********/
static uint32 neighbor_period = NEIGHBOR_PERIOD_DEFAULT;
static uint32 neighbor_timeout = NEIGHBOR_PERIOD_DEFAULT * NEIGHBOR_TIMEOUT_ROUNDS;
static boolean neighbor_nbrnbr_enable = FALSE;
static boolean neighbor_xmit_enable = TRUE;
static irRangeData obstacleData;
static boolean irObstacleDataReceive = FALSE;

static nbrData nd;
static osSemaphoreHandle neighborsMutex;


/******** Functions ********/
static void neighborsTask(void* parameters);


/**
 * @defgroup <Neighbor System>
 * @{
 * 	Neighbor system allows a robot to communicate with its neighbors.\n
 * 	Function neighborsTask is performed constantly at every WHAT.\n
 *
 * }@
 */




void nbrDataInit(nbrData* nbrDataPtr) {
	nbrDataPtr->nbrsSize = 0;
	nbrDataPtr->round = 0;
}

void neighborsXmitEnable(boolean neighbor_xmit_enable_arg) {
	neighbor_xmit_enable = neighbor_xmit_enable_arg;
}

void neighborsInit(uint32 neighbor_period_arg, boolean nbrnbr_enable_arg) {
	uint32 val;
	neighbor_period = neighbor_period_arg;
	neighbor_timeout = neighbor_period_arg * NEIGHBOR_TIMEOUT_ROUNDS;
	neighbor_nbrnbr_enable = nbrnbr_enable_arg;
	nbrDataInit(&nd);

	ir_comms_set_message_length(NEIGHBOR_MESSAGE_LENGTH_WITH_ID);

	//TODO ugly hack to deal with bad CRC matches
	//neighborsSetMessage("R1");
    
	neighborsMutex = osSemaphoreCreateMutex();

	osTaskCreate( /* function */ neighborsTask,
						   /* name */ "neighbors",
					 /* stack size */ 4096,
				/* *char parameter */ NULL,
					   /* priority */ NEIGHBORS_TASK_PRIORITY );

}

void neighborsSetPeriod(uint32 neighbor_period_arg) {
	neighbor_period = neighbor_period_arg;
	neighbor_timeout = neighbor_period_arg * NEIGHBOR_TIMEOUT_ROUNDS;
}


static uint16 byteToMillirad(uint8 angle) {
    return (uint16)angle * MILLIRAD_BYTE_CONV;
}

static uint8 milliradToByte(uint16 angle) {
	return (uint8)(angle / MILLIRAD_BYTE_CONV);
}


static void nbrUpdateNbrNbr(Nbr* nbrPtr, uint8 nbr_nbr_id, int16 nbr_nbr_bearing, uint32 currentTime) {
	nbrnbr* nbrNbrPtr = nbrGetNbrNbrWithID(nbrPtr, nbr_nbr_id);
    if (!nbrNbrPtr) {
    	// make a new nbr nbr
    	if (nbrPtr->nbrnbrsSize < NEIGHBOR_MAX) {
    		nbrNbrPtr = &(nbrPtr->nbrnbrs[nbrPtr->nbrnbrsSize]);
    		nbrNbrPtr->ID = nbr_nbr_id;
    		nbrPtr->nbrnbrsSize++;
    	}
    }
	if (nbrNbrPtr) {
		nbrNbrPtr->bearing = nbr_nbr_bearing;
		nbrNbrPtr->updateTime = currentTime;
	}
}

void nbrPrint(Nbr* nbr) {
	uint8 i;
	cprintf("id %2d: nbr %2d, brg %5d, ont %5d, ontVld %d, close %d, nbrNbrSize %d",
			roneID, nbr->ID, nbr->bearing, nbr->orientation, nbr->orientationValid, nbr->closeRange, nbr->nbrnbrsSize);
	for (i = 0; i < nbr->nbrnbrsSize; ++i) {
		cprintf(",nbrnbr%d %2d, brg %5d",
				i, nbr->nbrnbrs[i].ID, nbr->nbrnbrs[i].bearing);
	}
	cprintf("\n");
}

/* Changed to print binary and not HEX
 * Flip the comments to print in HEX
 */
void obstaclePrint(uint8 bits) {
	char text[10];
    cprintf("id: %d  obstacle bits: %s", roneID, bitString8(text, bits));
}

void nbrPrintData(Nbr* nbr, uint32 round) {
	uint8 i;
	static boolean printedHeader = FALSE;
	if (!printedHeader) {
		cprintf("id,time,round,nbrID,bearing,updateTime,nbrNbrSize,nbrNbrID,nbrNbrBearing,nbrNbrUpdateTime,...\n");
		printedHeader = TRUE;
	}
	cprintf("nd,%d,%d,%d,%d,%d,%d,%d",
			roneID,osTaskGetTickCount(),round, nbr->ID, nbr->bearing, nbr->updateTime, nbr->nbrnbrsSize);
	for (i = 0; i < nbr->nbrnbrsSize; ++i) {
		cprintf(",%d,%d,%d",
				nbr->nbrnbrs[i].ID, nbr->nbrnbrs[i].bearing, nbr->nbrnbrs[i].updateTime);
	}
	cprintf("\n");
}


static const int16 ir_receiver_sin[IR_COMMS_NUM_OF_RECEIVERS] = {383,924,924,383,-383,-924,-924,-383};
static const int16 ir_receiver_cos[IR_COMMS_NUM_OF_RECEIVERS] = {924,383,-383,-924,-924,-383,383,924};


static void processNbrMessage(ir_comms_message* irMsgPtr) {
	uint8 nbr_id, i;
	Nbr* nbrPtr;
	uint8 receiverBits = irMsgPtr->receiverBits;

	if (receiverBits != 0) {
        nbr_id = irMsgPtr->data[0];
		if (nbr_id & 0x80) {
			// neighbor nbr message
			//serial_send_string_crlf("recv nbrnbr msg");
			uint8 nbr_nbr_id;
			uint16 nbr_nbr_bearing;
			nbr_id = nbr_id & 0x7F;

            nbrPtr = nbrsGetWithID(nbr_id);
            if (nbrPtr) {
                nbr_nbr_id = irMsgPtr->data[1];
                nbr_nbr_bearing = byteToMillirad(irMsgPtr->data[2]);
            	nbrUpdateNbrNbr(nbrPtr, nbr_nbr_id, nbr_nbr_bearing, irMsgPtr->timeStamp);
                if (nbr_nbr_id == roneID) {
                	// you are the nbrnbr - compute orientation of this robot
                	nbrPtr->orientation = nbr_nbr_bearing;
                	nbrPtr->orientationValid = TRUE;
                }
            }
		} else {
			// neighbor announce message
			//serial_send_string_crlf("recv nbr msg");
			if (nbr_id == roneID) {
				// this is your announce message.  check for obstacles
				//obstaclePrint(irMsgPtr->receiverBits);
	            obstacleData.bits = irMsgPtr->receiverBits;
	            obstacleData.timeStamp = irMsgPtr->timeStamp;
	            irObstacleDataReceive = TRUE;
				return;
			}
            nbrPtr = nbrsGetWithID(nbr_id);
            if (!nbrPtr) {
            	//TODO this is an ugly hack to eliminate phantom neighbors
//            	if ((irMsgPtr->data[1] != 'R') || (irMsgPtr->data[2] != '1')) {
//            		// this fails our check. discard
//            		nbrPtr = NULL;
//            	}
            	// make a new nbr
            	if (nd.nbrsSize < NEIGHBOR_MAX) {
            		nbrPtr = &nd.nbrs[nd.nbrsSize++];
            		nbrPtr->ID = nbr_id;
            		nbrPtr->orientation = 0;
            		nbrPtr->orientationValid = FALSE;
            		nbrPtr->nbrnbrsSize = 0;
            	}
            }
            if (nbrPtr) {
            	// we either have a new neighbor, or an old one to update
            	int32 x = 0;
            	int32 y = 0;
            	uint8 bitCount = 0;
            	for (i = 0; i < IR_COMMS_NUM_OF_RECEIVERS; ++i) {
					if (receiverBits & 1) {
						x += ir_receiver_cos[i];
						y += ir_receiver_sin[i];
						bitCount++;
					}
					receiverBits >>= 1;
				}
            	nbrPtr->bearing = atan2MilliRad(y, x);
            	memcpy(nbrPtr->message, &irMsgPtr->data[1], NEIGHBOR_MESSAGE_LENGTH);
            	nbrPtr->updateTime = irMsgPtr->timeStamp;
            	nbrPtr->closeRange = (bitCount > 2 ? TRUE : FALSE);
            }
		}
	}
}


uint8 irRangeGetBits(void) {
    return obstacleData.bits;
}


void neighborsGetMutex(void) {
	osSemaphoreTake(neighborsMutex, portMAX_DELAY);
}


void neighborsPutMutex(void) {
	osSemaphoreGive(neighborsMutex);
}


static void neighborsTask(void* parameters) {
	portTickType lastWakeTime, currentTime;
	ir_comms_message ir_msg;
	uint8 i, j;
	lastWakeTime = osTaskGetTickCount();
	Nbr* nbrPtr;


	//neighbor_nbrnbr_enable = FALSE;		//TESTING


	for (;;) {
		// process all the stored IR messages
		//serial_send_string_crlf("nbr start");

		neighborsGetMutex();

		currentTime = osTaskGetTickCount();

		irObstacleDataReceive = FALSE;
		while(ir_comms_get_message(&ir_msg)) {
			//jenCheckMessage(&ir_msg);		//TESTING
			processNbrMessage(&ir_msg);
		}
		if (irObstacleDataReceive == FALSE){
		    obstacleData.bits = 0;
		}

		//timeout old neighbors
		for (i = 0; i < nd.nbrsSize; ) {
			if(currentTime > (nd.nbrs[i].updateTime + neighbor_timeout)) {
				nd.nbrsSize--;
				if (i < nd.nbrsSize) {
					nd.nbrs[i] = nd.nbrs[nd.nbrsSize];
				}
			}else{
				i++;
			}
		}

		//timeout old nbr nbrs
		if (neighbor_nbrnbr_enable){
			for (i = 0; i < nd.nbrsSize; i++) {
				nbrPtr = &nd.nbrs[i];
				for (j = 0; j < nbrPtr->nbrnbrsSize; ) {
					if(currentTime > (nbrPtr->nbrnbrs[j].updateTime + neighbor_timeout)) {
						nbrPtr->nbrnbrsSize--;
						if (j < nbrPtr->nbrnbrsSize) {
							nbrPtr->nbrnbrs[j] = nbrPtr->nbrnbrs[nbrPtr->nbrnbrsSize];
						}
					}else{
						j++;
					}
				}
			}
		}

		neighborsPutMutex();


		if(neighbor_xmit_enable) {
			// wait a random offset before xmit
			//TODO make sure that we don't overrun the next interrupt
			uint32 xmitDelay = rand() % (neighbor_period - NEIGHBOR_XMIT_MIN_DELAY);
			osTaskDelay(xmitDelay);

			// send the neighbor announce message
			ir_msg.data[0] = roneID;

//			ir_msg.data[1] = 'a';	//TESTING
//			ir_msg.data[2] = 'b';	//TESTING
//			ir_msg.data[3] = 'c';	//TESTING

			//memcpy(&ir_msg.data[1], nd.message, NEIGHBOR_MESSAGE_LENGTH);
			ir_comms_send_message(&ir_msg);

			// send the nbr nbr messages
			if (neighbor_nbrnbr_enable){
				for (i = 0; i < nd.nbrsSize; i++) {
					ir_msg.data[0] = roneID | 0x80;
					ir_msg.data[1] = nd.nbrs[i].ID;
					ir_msg.data[2] = milliradToByte(nd.nbrs[i].bearing);
					ir_comms_send_message(&ir_msg);
				}
			}
		}

		nd.round++;
		osTaskDelayUntil(&lastWakeTime, neighbor_period);
	}
}


uint32 neighborsGetRound(void) {
	return(nd.round);
}


void neighborsSetMessage(char* message) {
	memcpy(nd.message, message, NEIGHBOR_MESSAGE_LENGTH);
}


Nbr* nbrsGetWithID(uint8 nbrID) {
	uint8 i;
	for (i = 0; i < nd.nbrsSize; i++) {
		if (nd.nbrs[i].ID == nbrID) {
			return &nd.nbrs[i];
		}
	}
	return NULL;
}


// fills the provided nbrList with the current set of neighbors
void nbrListCreate(NbrList* nbrListPtr) {
	uint8 i;
	for (i = 0; i < nd.nbrsSize; i++) {
		nbrListPtr->nbrs[i] = &nd.nbrs[i];
	}
	nbrListPtr->size = nd.nbrsSize;
}


// fills the provided nbrList with the current set of neighbors
void nbrListClear(NbrList* nbrListPtr) {
	nbrListPtr->size = 0;
}


Nbr* nbrListGetFirst(NbrList* nbrListPtr) {
	if (nbrListPtr->size > 0) {
		return nbrListPtr->nbrs[0];
	}else{
		return NULL;
	}
}


uint8 nbrGetID(Nbr* nbrPtr) {
	return nbrPtr->ID;
}

void nbrGetMessage(Nbr* nbrPtr, char* messagePtr) {
	memcpy(messagePtr, nbrPtr->message, NEIGHBOR_MESSAGE_LENGTH);
}

uint32 nbrGetBearing(Nbr* nbrPtr) {
	return nbrPtr->bearing;
}

uint32 nbrGetOrientation(Nbr* nbrPtr) {
	return nbrPtr->orientation;
}

boolean nbrGetOrientationValid(Nbr* nbrPtr) {
	return nbrPtr->orientationValid;
}

boolean nbrGetCloseRange(Nbr* nbrPtr) {
	return nbrPtr->closeRange;
}

uint32 nbrGetUpdateTime(Nbr* nbrPtr) {
	return nbrPtr->updateTime;
}


/******** nbrNbr getters ********/

nbrnbr* nbrGetNbrNbrWithID(Nbr* nbrPtr, uint8 nbrNbrID) {
	uint8 i;
	for (i = 0; i < nbrPtr->nbrnbrsSize; i++) {
		if (nbrPtr->nbrnbrs[i].ID == nbrNbrID) {
			return &(nbrPtr->nbrnbrs[i]);
		}
	}
	return NULL;
}


uint32 nbrNbrGetBearing(Nbr* nbrNbrPtr){
	return 0;
}


uint32 nbrNbrGetUpdateTime(Nbr* nbrNbrPtr){
	return 0;
}


void nbrGetNbrNbrList(Nbr* nbrPtr, nbrNbrList* nbrNbrList){

}



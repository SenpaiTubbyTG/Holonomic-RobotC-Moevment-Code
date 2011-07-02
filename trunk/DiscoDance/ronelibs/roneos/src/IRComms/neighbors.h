/*
 * neighbors.h
 *
 *  Created on: Mar 2, 2011
 *      Author: jamesm
 */

#ifndef NEIGHBORS_H_
#define NEIGHBORS_H_

#define NEIGHBOR_PERIOD_DEFAULT 		330
#define NEIGHBOR_TIMEOUT_ROUNDS			3
#define NEIGHBOR_XMIT_MIN_DELAY	    	30
#define NEIGHBOR_MAX					8
#define NEIGHBOR_MESSAGE_LENGTH_WITH_ID 4
#define NEIGHBOR_MESSAGE_LENGTH 		(NEIGHBOR_MESSAGE_LENGTH_WITH_ID - 1)

typedef struct nbrnbr {
	uint8 ID;
	uint16 bearing;
	uint32 updateTime;
} nbrnbr;

typedef struct nbr {
	uint8 ID;
	uint8 message[NEIGHBOR_MESSAGE_LENGTH];
	uint16 bearing;
	uint16 orientation;
	boolean orientationValid;
	boolean closeRange;
	uint32 updateTime;
	nbrnbr nbrnbrs[NEIGHBOR_MAX];
	uint8 nbrnbrsSize;
} Nbr;

typedef struct nbrData {
	Nbr nbrs[NEIGHBOR_MAX];
	uint8 nbrsSize;
	uint32 round;
	char message[NEIGHBOR_MESSAGE_LENGTH];
} nbrData;

typedef struct nbrList {
	Nbr* nbrs[NEIGHBOR_MAX];
	uint8 size;
} NbrList;

typedef struct nbrNbrList {
	Nbr* nbrNbrs[NEIGHBOR_MAX];
	uint8 size;
} nbrNbrList;

typedef struct irRangeData {
	uint8 bits;
	uint32 timeStamp;
} irRangeData;

void neighborsInit(uint32 neighbor_period, boolean orientation_enable);
void obstaclePrint(uint8 bits);
char * bitString8(char * string, uint8 val);
uint8 irRangeGetBits(void);
void neighborsSetMessage(char* message);
void neighborsSetPeriod(uint32 neighbor_period_arg);
void neighborsGetMutex(void);
void neighborsPutMutex(void);
uint32 neighborsGetRound(void);
void neighborsXmitEnable(boolean neighbor_xmit_enable_arg);

Nbr* nbrsGetWithID(uint8 nbrID);
void nbrListCreate(NbrList* nbrListPtr);
void nbrListClear(NbrList* nbrListPtr);
Nbr* nbrListGetFirst(NbrList* nbrListPtr);

uint8 nbrGetID(Nbr* nbrPtr);
void nbrGetMessage(Nbr* nbrPtr, char* messagePtr);
uint32 nbrGetBearing(Nbr* nbrPtr);
uint32 nbrGetOrientation(Nbr* nbrPtr);
boolean nbrGetOrientationValid(Nbr* nbrPtr);
boolean nbrGetCloseRange(Nbr* nbrPtr);
uint32 nbrGetUpdateTime(Nbr* nbrPtr);
void nbrPrint(Nbr* nbr);
void nbrPrintData(Nbr* nbr, uint32 round);

nbrnbr* nbrGetNbrNbrWithID(Nbr* nbrPtr, uint8 nbrNbrID);
uint32 nbrNbrGetBearing(Nbr* nbrNbrPtr);
uint32 nbrNbrGetUpdateTime(Nbr* nbrNbrPtr);
void nbrGetNbrNbrList(Nbr* nbrPtr, nbrNbrList* nbrNbrList);

#endif /* NEIGHBORS_H_ */

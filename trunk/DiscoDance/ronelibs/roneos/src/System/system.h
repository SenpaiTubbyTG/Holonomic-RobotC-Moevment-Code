/*
 * system.h
 *
 *  Created on: Mar 26, 2011
 *      Author: jamesm
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

/* Size of the stack allocated to the uIP task. */
#define BASIC_TASK_STACK_SIZE            	( configMINIMAL_STACK_SIZE * 3 )


/* Task priorities. */
#define HEARTBEAT_TASK_PRIORITY				( tskIDLE_PRIORITY + 4 )
#define NEIGHBORS_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define BACKGROUND_TASK_PRIORITY			( tskIDLE_PRIORITY )

#define sysPrintFilename() _sysPrintFilename(__FILE__)

#define NUM_TILES		16

static uint8 tileLoopCtr;
static Tile tiles[16];

void systemPreInit(void);
void systemInit(void);
void systemHeartbeatTask(void* parameters);
void systemShutdown(void); // python rone
void systemBootloader(void);
void systemPrintMemUsage(void);
uint32 systemUSBConnected(void); // python rone
uint32 systemGetId(void);

void _sysPrintFilename(char* fileName);

#endif /* SYSTEM_H_ */

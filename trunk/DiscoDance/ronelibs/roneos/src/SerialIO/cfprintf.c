/*******************************************************************
 *	@file cfprintf.c
 *    Description:
 *
 *    Author: James McLurkin, copyright iRobot 2001
 *
 *    History:
 *
 *******************************************************************/

/******** Include Files ********/
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"

#include "roneos.h"

/******** Defines ********/
#define cfprintf_TEXT_STRING_SIZE			256

#define CFPRINTF_MESSAGE_SIZE				3
#define CFPRINTF_MESSAGE_DISPLAY_IDX		0
#define CFPRINTF_MESSAGE_FORMAT_IDX			1
#define CFPRINTF_MESSAGE_ARGS_IDX			2

#define CFPRINTF_CRLF_LF					0
#define CFPRINTF_CRLF_CR					1
#define CFPRINTF_CRLF_CRLF					2
#define CFPRINTF_CRLF_LFCR					3

#define CFPRINTF_STDOUT	0
#define CFPRINTF_STDERR	1

/******** Variables ********/
static osSemaphoreHandle cfprintfMutex;
boolean cfPrintfThreadRunning = FALSE;
//If using secureCRT want CRLF
uint8 CRLFMode = CFPRINTF_CRLF_CRLF;

char cfprintfRaw_outString[cfprintf_TEXT_STRING_SIZE];
//char outStringFormattedRemote[cfprintf_TEXT_STRING_SIZE];
//uint16 outStringFormattedRemoteLength = 0;


/******** Functions ********/

/**
 *	@brief Serves the same purpose as formatted output string for the robot.
 *
 *	Processes the input string into an output string rone understands.
 *	If the input string is too large, cfprintfOverRunError is set to TRUE.
 *
 *	@returns void
 */
void cprintf(char *format, ...) {
    va_list arguments;

    va_start(arguments, format);

	int32 potentialChars;
	boolean cfprintfOverRunError = FALSE;
	char* charPtr;

	if (cfPrintfThreadRunning) {
		osSemaphoreTake(cfprintfMutex, portMAX_DELAY);
	}

	/* Process the input string and store the output in the 'outStringFormatted' */
	/* note that vsnprintf returns the number of characters that would have been
	 * written to the buffer if it were large enough. */
	potentialChars = vsnprintf(cfprintfRaw_outString, cfprintf_TEXT_STRING_SIZE, format, arguments);
	if (potentialChars > (cfprintf_TEXT_STRING_SIZE - 1)) {
		cfprintfOverRunError = TRUE;
	}

	charPtr = cfprintfRaw_outString;
	while (*charPtr != '\0') {
		if (*charPtr == '\n') {
			/* change '\n' into current CRLF mode */
			switch (CRLFMode) {
			case CFPRINTF_CRLF_LF:
				sputchar('\n');
			break;
			case CFPRINTF_CRLF_CR:
				sputchar('\r');
			break;
			case CFPRINTF_CRLF_CRLF:
				sputchar('\r');
				sputchar('\n');
			break;
			case CFPRINTF_CRLF_LFCR:
				sputchar('\n');
				sputchar('\r');
			break;
			default:
				sputchar('\n');
			break;
			}
		} else {
			sputchar(*charPtr);
			//terminalTextColor(colorAttr);
		}
		charPtr++;
	}

	if (cfPrintfThreadRunning) {
		osSemaphoreGive(cfprintfMutex);
	}

    va_end(arguments);
}

/**
 * @brief Initializes cfprintf.
 *
 * @returns void
 */
void cfprintfInit(void) {
	cfprintfMutex = osSemaphoreCreateMutex();
	cfPrintfThreadRunning = TRUE;
}


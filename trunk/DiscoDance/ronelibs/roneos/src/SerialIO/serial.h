/*
 * serial.h
 *
 *  Created on: Mar 26, 2011
 *      Author: jamesm
 */

#ifndef SERIAL_H_
#define SERIAL_H_

void serial_init(void);
void uart_int_handler(void);
void sputchar(char c);

void serial_send(const char* buffer, uint32 size);
void serial_send_string(const char* string);
int serial_get_string(char * buffer, int buflen);

#endif /* SERIAL_H_ */

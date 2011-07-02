/*
 * charger.h
 *
 *  Created on: Mar 26, 2011
 *      Author: jamesm
 */

#ifndef CHARGER_H_
#define CHARGER_H_

void charger_init(void);
void charger_enable(void);
void charger_disable(void);
uint32 charger_get_status(void); // python rone

#endif /* CHARGER_H_ */

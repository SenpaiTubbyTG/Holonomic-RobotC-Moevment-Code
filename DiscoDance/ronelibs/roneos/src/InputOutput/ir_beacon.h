/*
 * ir_beacon.h
 *
 *  Created on: Mar 26, 2011
 *      Author: jamesm
 */

#ifndef IR_BEACON_H_
#define IR_BEACON_H_

#define IR_BEACON_MAX_ID                    1023
void ir_beacon_init(void);
void ir_beacon_disable(void); // python rone
void ir_beacon_update(void);
void ir_beacon_set_data(uint32 data); // python rone

#endif /* IR_BEACON_H_ */

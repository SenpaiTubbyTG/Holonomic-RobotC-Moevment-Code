/*
 * buttons.h
 *
 *  Created on: Mar 19, 2011
 *      Author: jamesm
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#define BUTTON_RED                  0
#define BUTTON_GREEN                1
#define BUTTON_BLUE                 2

void buttons_init(void);
uint32 buttons_get(uint32 button);


#endif /* BUTTONS_H_ */

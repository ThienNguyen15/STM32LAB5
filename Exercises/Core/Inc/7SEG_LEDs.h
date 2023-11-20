/*
 * 7SEG_LEDS.h
 *
 *  Created on: Oct 21, 2023
 *      Author: thien
 */

#ifndef INC_7SEG_LEDS_H_
#define INC_7SEG_LEDS_H_

#include "main.h"
#include "global.h"

void update7SEG(int index);
void updateBufferForMode1();
void updateBufferForIncVal();
void fsmIncVal();

#endif /* INC_7SEG_LEDS_H_ */

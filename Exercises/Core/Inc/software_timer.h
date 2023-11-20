/*
 * software_timer.h
 *
 *  Created on: Sep 24, 2022
 *      Author: KAI
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"
#include "global.h"

int Current_Timer_Counter(int timer);
int IsTimerUp(int timer);
void setTimer(int timer, int duration);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */

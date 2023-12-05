/*
 * software_timer.h
 *
 *  Created on: Nov 20, 2023
 *      Author: Nguyen Quang Thien	- 2152994
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"
#include "global.h"

int Current_Timer_Counter(int timer);
int IsTimerUp(int timer);
void setTimer(int timer, int duration);
void timerRun(void);

void timerRun0(void);
void timerRun1(void);
void timerRun2(void);
void timerRun3(void);

#endif /* INC_SOFTWARE_TIMER_H_ */

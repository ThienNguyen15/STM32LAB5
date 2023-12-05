/*
 * software_timer.c
 *
 *  Created on: Nov 20, 2023
 *      Author: Le Van Phuc			- 2152241
 *      		Nguyen Quang Thien	- 2152994
 */

#include "software_timer.h"

int timer_counter[TIMER];
int timer_flag[TIMER];

int Current_Timer_Counter(int timer)
{
	return timer_counter[timer];
}

int IsTimerUp(int timer)
{
	return (timer_flag[timer] == 1);
}

void setTimer(int timer, int duration)
{
	timer_counter[timer] = duration;
	timer_flag[timer] = 0;
}

void timerRun(void)
{
	for (int timer = 0; timer < TIMER; timer++)
	{
		if(timer_counter[timer] > 0)
		{
			timer_counter[timer]--;
			if(timer_counter[timer] == 0)
				timer_flag[timer] = 1;
		}
	}
}

void timerRun0(void)
{
	if(timer_counter[0] > 0)
	{
		timer_counter[0]--;
		if(timer_counter[0] == 0)
			timer_flag[0] = 1;
	}
}

void timerRun1(void)
{
	if(timer_counter[1] > 0)
	{
		timer_counter[1]--;
		if(timer_counter[1] == 0)
			timer_flag[1] = 1;
	}
}

void timerRun2(void)
{
	if(timer_counter[2] > 0)
	{
		timer_counter[2]--;
		if(timer_counter[2] == 0)
			timer_flag[2] = 1;
	}
}

void timerRun3(void)
{
		if(timer_counter[3] > 0)
		{
			timer_counter[3]--;
			if(timer_counter[3] == 0)
				timer_flag[3] = 1;
		}
}

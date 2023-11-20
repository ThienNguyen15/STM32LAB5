/*
 * global.h
 *
 *  Created on: Oct 21, 2023
 *      Author: thien
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "button.h"
#include "fsm_mode.h"
#include "7SEG_LEDs.h"
#include "LEDs.h"

#define NORMAL_STATE	GPIO_PIN_SET
#define PRESSED_STATE 	GPIO_PIN_RESET
#define BUTTON_1	0
#define BUTTON_2	1
#define BUTTON_3	2
#define BUTTONS		3

#define TIMER		4

#define MODE_INIT	8
#define MODE_1		9
#define MODE_2		10
#define MODE_3		11
#define MODE_4		12

#define INC_RED		13
#define INC_AMBER	14
#define INC_GREEN	15

#define LED_ON		GPIO_PIN_SET
#define LED_OFF		GPIO_PIN_RESET

#define AUTO_INIT	16
#define AUTO_RED	17
#define AUTO_GREEN	18
#define AUTO_AMBER	19

#define SEG_ON		GPIO_PIN_RESET
#define SEG_OFF		GPIO_PIN_SET

// Global Variables
extern int mode;
extern int counterKeyPress;

extern int RED;
extern int AMBER;
extern int GREEN;

extern int RED_INIT;
extern int AMBER_INIT;
extern int GREEN_INIT;

extern int seg_index;

extern int SEG_Switch;
extern int LED_Blink;

extern int count_val;

#endif /* INC_GLOBAL_H_ */

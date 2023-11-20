/*
 * LEDs.c
 *
 *  Created on: Oct 21, 2023
 *      Author: thien
 */

#include "LEDs.h"

int Hori_Status = AUTO_INIT;
int Verti_Status = AUTO_INIT;
//GPIO_PinState Blink_Status = LED_ON;

void fsm_Hori_LEDs()
{
	switch(Hori_Status)
	{
		case AUTO_INIT:
			Hori_Status = AUTO_RED;
			setTimer(0, RED);
			break;

		case AUTO_RED:
			if (IsTimerUp(0))
			{
				Hori_Status = AUTO_GREEN;
				setTimer(0, GREEN);
			}
			break;

		case AUTO_GREEN:
			if (IsTimerUp(0))
			{
				Hori_Status = AUTO_AMBER;
				setTimer(0, AMBER);
			}
			break;

		case AUTO_AMBER:
			if (IsTimerUp(0))
			{
				Hori_Status = AUTO_RED;
				setTimer(0, RED);
			}
			break;

		default:
			break;
	}
}

void fsm_Verti_LEDs()
{
	switch (Verti_Status)
	{
		case AUTO_INIT:
			Verti_Status = AUTO_GREEN;
			setTimer(1, GREEN);
			break;

		case AUTO_GREEN:
			if (IsTimerUp(1))
			{
				Verti_Status = AUTO_AMBER;
				setTimer(1, AMBER);
			}
			break;

		case AUTO_AMBER:
			if (IsTimerUp(1))
			{
				Verti_Status = AUTO_RED;
				setTimer(1, RED);
			}
			break;

		case AUTO_RED:
			if (IsTimerUp(1))
			{
				Verti_Status = AUTO_GREEN;
				setTimer(1, GREEN);
			}
			break;

		default:
			break;
	}
}

void LEDsDisplay()
{
	fsm_Hori_LEDs();
	fsm_Verti_LEDs();

	switch (Hori_Status)
	{
		case AUTO_RED:
			HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, LED_ON);
			HAL_GPIO_WritePin(GPIOA, amber1_Pin | green1_Pin, LED_OFF);
			break;
		case AUTO_AMBER:
			HAL_GPIO_WritePin(amber1_GPIO_Port, amber1_Pin, LED_ON);
			HAL_GPIO_WritePin(GPIOA, red1_Pin | green1_Pin, LED_OFF);
			break;
		case AUTO_GREEN:
			HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin, LED_ON);
			HAL_GPIO_WritePin(GPIOA, red1_Pin | amber1_Pin, LED_OFF);
			break;
		default:
			break;
	}

	switch (Verti_Status)
	{
		case AUTO_RED:
			HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, LED_ON);
			HAL_GPIO_WritePin(GPIOA, amber2_Pin | green2_Pin, LED_OFF);
			break;
		case AUTO_AMBER:
			HAL_GPIO_WritePin(amber2_GPIO_Port, amber2_Pin, LED_ON);
			HAL_GPIO_WritePin(GPIOA, red2_Pin | green2_Pin, LED_OFF);
			break;
		case AUTO_GREEN:
			HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin, LED_ON);
			HAL_GPIO_WritePin(GPIOA, red2_Pin | amber2_Pin, LED_OFF);
			break;
		default:
			break;
	}
}

//void LEDsBlink()
//{
//	if (IsTimerUp(3))
//	{
//		Blink_Status = !Blink_Status;
//		setTimer(3, LED_Blink);
//	}
//	switch(mode)
//	{
//		case MODE_2:
//			HAL_GPIO_WritePin(GPIOA, red1_Pin | red2_Pin, Blink_Status);
//			HAL_GPIO_WritePin(GPIOA, amber1_Pin | amber2_Pin | green1_Pin | green2_Pin, LED_OFF);
//			break;
//		case MODE_3:
//			HAL_GPIO_WritePin(GPIOA, amber1_Pin | amber2_Pin, Blink_Status);
//			HAL_GPIO_WritePin(GPIOA, red1_Pin | red2_Pin | green1_Pin | green2_Pin, LED_OFF);
//			break;
//		case MODE_4:
//			HAL_GPIO_WritePin(GPIOA, green1_Pin | green2_Pin, Blink_Status);
//			HAL_GPIO_WritePin(GPIOA, red1_Pin | red2_Pin | amber1_Pin | amber2_Pin, LED_OFF);
//			break;
//	}
//}


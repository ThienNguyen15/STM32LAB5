/*
 * fsm_mode.c
 *
 *  Created on: Oct 21, 2023
 *      Author: thien
 */

#include "fsm_mode.h"
GPIO_PinState Blink_Status = LED_ON;

void fsm_mode()
{
	switch(mode)
	{
		case MODE_INIT:
			mode = MODE_1;
			break;

		case MODE_1:
			if (isButtonPressed(BUTTON_1))
				mode = MODE_2;

			LEDsDisplay();
			updateBufferForMode1();
			break;

		case MODE_2:
			if (isButtonPressed(BUTTON_1))
				mode = MODE_3;

			if (IsTimerUp(3))
			{
				Blink_Status = !Blink_Status;
				setTimer(3, LED_Blink);
			}

			HAL_GPIO_WritePin(GPIOA, red1_Pin | red2_Pin, Blink_Status);
			HAL_GPIO_WritePin(GPIOA, amber1_Pin | amber2_Pin | green1_Pin | green2_Pin, LED_OFF);

			count_val = RED / 100;
			updateBufferForIncVal();

			if (isButtonPressed(BUTTON_2))
			{
				mode = INC_RED;
				count_val++;
			}
			break;

		case MODE_3:
			if (isButtonPressed(BUTTON_1))
				mode = MODE_4;

			if (IsTimerUp(3))
			{
				Blink_Status = !Blink_Status;
				setTimer(3, LED_Blink);
			}

			HAL_GPIO_WritePin(GPIOA, amber1_Pin | amber2_Pin, Blink_Status);
			HAL_GPIO_WritePin(GPIOA, red1_Pin | red2_Pin | green1_Pin | green2_Pin, LED_OFF);

			count_val = AMBER / 100;
			updateBufferForIncVal();

			if (isButtonPressed(BUTTON_2))
			{
				mode = INC_AMBER;
				count_val++;
			}
			break;

		case MODE_4:
			if (isButtonPressed(BUTTON_1))
			{
				mode = MODE_1;
				setTimer(0, RED);
				setTimer(1, GREEN);
			}

			if (IsTimerUp(3))
			{
				Blink_Status = !Blink_Status;
				setTimer(3, LED_Blink);
			}

			HAL_GPIO_WritePin(GPIOA, green1_Pin | green2_Pin, Blink_Status);
			HAL_GPIO_WritePin(GPIOA, red1_Pin | red2_Pin | amber1_Pin | amber2_Pin, LED_OFF);

			count_val = GREEN / 100;
			updateBufferForIncVal();

			if (isButtonPressed(BUTTON_2))
			{
				mode = INC_GREEN;
				count_val++;
			}
			break;

		default:
			break;
	}
}

/*
 * fsm_mode.c
 *
 *  Created on: Oct 21, 2023
 *      Author: thien
 */

#include "fsm_mode.h"
GPIO_PinState Blink_Status = LED_ON;

void fsm_mode(void)
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

void seg_leds(void)
{
	  if(IsTimerUp(2))
	  {
		  HAL_GPIO_WritePin(GPIOA, 0xF00, SEG_OFF);
		  switch (seg_index)
		  {
		  	  case 0: // 1st 7SEG_LEDs
		  		  HAL_GPIO_WritePin(en0_GPIO_Port, en0_Pin, SEG_ON);
		  		  HAL_GPIO_WritePin(GPIOA, en1_Pin | en2_Pin | en3_Pin, SEG_OFF);
		  		  break;
		  	  case 1: // 2nd 7SEG_LEDs
		  		  HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, SEG_ON);
		  		  HAL_GPIO_WritePin(GPIOA, en0_Pin | en2_Pin | en3_Pin, SEG_OFF);
		  		  break;
		  	  case 2: // 3rd 7SEG_LEDs
		  		  HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, SEG_ON);
		  		  HAL_GPIO_WritePin(GPIOA, en0_Pin | en1_Pin | en3_Pin, SEG_OFF);
		  		  break;
		  	  case 3: // 4th 7SEG_LEDs
		  		  HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, SEG_ON);
		  		  HAL_GPIO_WritePin(GPIOA, en0_Pin | en1_Pin | en2_Pin, SEG_OFF);
		  		  break;
		  	  default:
		  		  break;
		  }
		  // Display 7SEG_LEDs
		  update7SEG(seg_index++);

		  // Set switching time
		  setTimer(2, SEG_Switch);
	  }
}

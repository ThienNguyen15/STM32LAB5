/*
 * 7SEG_LEDs.c
 *
 *  Created on: Oct 21, 2023
 *      Author: thien
 */

#include "7SEG_LEDs.h"

GPIO_TypeDef* seg_port[] = {a_GPIO_Port, b_GPIO_Port, c_GPIO_Port, d_GPIO_Port, e_GPIO_Port, f_GPIO_Port, g_GPIO_Port};
int seg_pin[] = {a_Pin, b_Pin, c_Pin, d_Pin, e_Pin, f_Pin, g_Pin};
int seg_config[10] = {0x01, 0x4F, 0x12, 0x06, 0x4C, 0x24, 0x20, 0x0F, 0x00, 0x04};
// Hexadecimal to Binary: 0x01->0x00000001, 0x4F->01001111, ...

void display7SEG(int num)
{
	GPIOB->ODR = seg_config[num];
}

const int MAX_LED = 4;
int led_buffer[4] = {1, 2, 3, 4};
void update7SEG(int index)
{
    switch (index)
    {
        case 0:
            //Display the first 7SEG with led_buffer[0]
    		display7SEG(led_buffer[index]);
            break;
        case 1:
            //Display the second 7SEG with led_buffer[1]
    		display7SEG(led_buffer[index]);
            break;
        case 2:
            //Display the third 7SEG with led_buffer[2]
    		display7SEG(led_buffer[index]);
            break;
        case 3:
            //Display the forth 7SEG with led_buffer[3]
    		display7SEG(led_buffer[index]);
            break;
        default:
            break;
    }
	if(seg_index >= 4) seg_index = 0;
}

void updateBufferForMode1()
{
	int Hori_Road = (Current_Timer_Counter(0)) / 100;
	int Verti_road = (Current_Timer_Counter(1)) / 100;

	led_buffer[0] = (Hori_Road + 1)/ 10;
	led_buffer[1] = (Hori_Road + 1) % 10;
	led_buffer[2] = (Verti_road + 1) / 10;
	led_buffer[3] = (Verti_road + 1) % 10;
}

void updateBufferForIncVal()
{
	led_buffer[2] = count_val / 10;
	led_buffer[3] = count_val % 10;

	led_buffer[0] = 0;
	switch(mode)
	{
		case MODE_2:
			led_buffer[1] = 2;
			break;
		case MODE_3:
			led_buffer[1] = 3;
			break;
		case MODE_4:
			led_buffer[1] = 4;
			break;
		default:
			break;
	}
}

void fsmIncVal()
{
	switch (mode)
	{
		case INC_RED:
			updateBufferForIncVal();

			if (isButtonPressed(BUTTON_1))
				mode = MODE_3;

			if (isButtonPressed(BUTTON_3))
			{
				mode = MODE_2;
				RED = count_val * 100;
			}

			if (isButtonPressed(BUTTON_2))
			{
				if (count_val > 99) count_val = 0;
				count_val++;
			}
			break;

		case INC_AMBER:
			updateBufferForIncVal();

			if (isButtonPressed(BUTTON_1))
				mode = MODE_4;

			if (isButtonPressed(BUTTON_3))
			{
				mode = MODE_3;
				AMBER = count_val * 100;
			}

			if (isButtonPressed(BUTTON_2))
			{
				if (count_val > 99) count_val = 0;
				count_val++;
			}
			break;

		case INC_GREEN:
			updateBufferForIncVal();

			if (isButtonPressed(BUTTON_1))
				mode = MODE_1;

			if (isButtonPressed(BUTTON_3))
			{
				mode = MODE_4;
				AMBER = count_val * 100;
			}

			if (isButtonPressed(BUTTON_2))
			{
				if (count_val > 99) count_val = 0;
				count_val++;
			}
			break;
		default:
			break;
	}

	if(RED > RED_INIT)
	{
		AMBER = AMBER * (RED / RED_INIT);
		GREEN = GREEN * (RED / RED_INIT);
	}
	else if(AMBER > AMBER_INIT)
	{
		RED = RED * (AMBER / AMBER_INIT);
		GREEN = GREEN * (AMBER / AMBER_INIT);
	}
	else if(GREEN > GREEN_INIT)
	{
		RED = RED * (GREEN / GREEN_INIT);
		AMBER = AMBER * (GREEN / GREEN_INIT);
	}
	else if(RED < RED_INIT)
	{
		AMBER = (RED / 5) * 2;
		GREEN = (RED / 5) * 3;
	}
	else if(AMBER < AMBER_INIT)
	{
		RED = (AMBER / 2) * 5;
		GREEN = (AMBER / 2) * 3;
	}
	else if(GREEN < GREEN_INIT)
	{
		RED = (GREEN / 3) * 5;
		AMBER = (GREEN / 3) * 2;
	}
	RED_INIT = RED;
	AMBER_INIT = AMBER;
	GREEN_INIT = GREEN;
}

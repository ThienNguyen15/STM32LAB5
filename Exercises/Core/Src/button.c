#include "button.h"

int button_flag[BUTTONS];
GPIO_PinState KeyReg[BUTTONS][4];
int TimeOutForKeyPress[BUTTONS];

int isButtonPressed(int button)
{
	if(button_flag[button] == 1)
	{
		button_flag[button] = 0;
		return 1;
	}
	return 0;
}

void getKeyInput(){
	for(int button = 0; button < BUTTONS; button++)
	{
		KeyReg[button][0] = KeyReg[button][1];
		KeyReg[button][1] = KeyReg[button][2];
		switch(button)
		{
			case BUTTON_1:
				KeyReg[button][2] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
				break;
			case BUTTON_2:
				KeyReg[button][2] = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
				break;
			case BUTTON_3:
				KeyReg[button][2] = HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin);
				break;
			default:
				break;
		}
		if((KeyReg[button][1] == KeyReg[button][0]) && (KeyReg[button][2] == KeyReg[button][1]))
		{
			if (KeyReg[button][3] != KeyReg[button][2])
			{
				KeyReg[button][3] = KeyReg[button][2];

				if (KeyReg[button][2] == PRESSED_STATE)
				{
					button_flag[button] = 1;
					TimeOutForKeyPress[button] = counterKeyPress;
				}
			}
			else
			{
				TimeOutForKeyPress[button]--;
				if (TimeOutForKeyPress[button] == 0)
					KeyReg[button][3] = NORMAL_STATE;
			}
		}
	}
}


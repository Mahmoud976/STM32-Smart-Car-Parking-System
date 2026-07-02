#include "Button.h"

Std_ReturnType Button_Init(const Button_Config_t * ButtonConfig)
{
	if(NULL == ButtonConfig)
	{
		return E_NOT_OK;
	}
	else
	{
		GPIO_Config_Pin_t Button;
		Button.PORTx = ButtonConfig->PORT;
		Button.Pin_Number = ButtonConfig->PIN_Number;
		Button.mode = GPIO_MODE_Input_FLO;

		GPIO_InitPin(&Button);
	}
	return E_OK;
}

Std_ReturnType Button_Read(const Button_Config_t * ButtonConfig, uint8_t * btn_Value)
{
	if((NULL == ButtonConfig) || (NULL == btn_Value))
	{
		return E_NOT_OK;
	}
	else
	{
		GPIO_ReadPin(ButtonConfig->PORT, ButtonConfig->PIN_Number, btn_Value);
	}
	return E_OK;
}

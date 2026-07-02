#ifndef Button_H
#define Button_H

#include "GPIO.h"




typedef struct{
	GPIO_TypeDef_t * PORT;
	uint16_t PIN_Number;
}Button_Config_t;

Std_ReturnType Button_Init(const Button_Config_t * ButtonConfig);
Std_ReturnType Button_Read(const Button_Config_t * ButtonConfig, uint8_t * btn_Value);


#endif //end Button_H

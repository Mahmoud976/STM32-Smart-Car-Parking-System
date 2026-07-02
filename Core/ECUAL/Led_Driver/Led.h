#ifndef Led_H
#define Led_H

#include "GPIO.h"



typedef enum
{
    LED_ACTIVE_HIGH = 0,
    LED_ACTIVE_LOW
}Led_Active_State_t;

typedef struct
{
	GPIO_TypeDef_t *  PORT;
    GPIO_Pin_t PIN_Number;
    Led_Active_State_t Active_State;
}Led_Config_t;

Std_ReturnType Led_Init(const Led_Config_t * LedConfig);
Std_ReturnType Led_ON(const Led_Config_t * LedConfig);
Std_ReturnType Led_OFF(const Led_Config_t * LedConfig);
Std_ReturnType Led_TOGGEL(const Led_Config_t * LedConfig);


#endif //end Led_H

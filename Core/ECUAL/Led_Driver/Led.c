#include"Led.h"



static uint8_t Led_Get_On_Value(const Led_Config_t * LedConfig)
{
    return (LedConfig->Active_State == LED_ACTIVE_HIGH) ? GPIO_HIGH : GPIO_LOW;
}

static uint8_t Led_Get_Off_Value(const Led_Config_t * LedConfig)
{
    return (LedConfig->Active_State == LED_ACTIVE_HIGH) ? GPIO_LOW : GPIO_HIGH;
}

Std_ReturnType Led_Init(const Led_Config_t * LedConfig)
{
    if(LedConfig == NULL  || NULL ==LedConfig->PORT )
    {
        return E_NOT_OK;
    }

    GPIO_Config_Pin_t LED;
    LED.PORTx = LedConfig->PORT;
    LED.Pin_Number = LedConfig->PIN_Number;
    LED.mode = (LedConfig->Active_State == LED_ACTIVE_HIGH) ? GPIO_MODE_Output_OD : GPIO_MODE_Output_PP;
    LED.Speed = GPIO_SPEED_10M;

    GPIO_InitPin(&LED);

    return E_OK;
}

Std_ReturnType Led_ON(const Led_Config_t * LedConfig)
{
    if(LedConfig == NULL)
    {
        return E_NOT_OK;
    }

    GPIO_WritePin(LedConfig->PORT,LedConfig->PIN_Number,Led_Get_On_Value(LedConfig));

    return E_OK;
}


Std_ReturnType Led_OFF(const Led_Config_t * LedConfig)
{
    if(LedConfig == NULL)
    {
        return E_NOT_OK;
    }

    GPIO_WritePin(LedConfig->PORT,
                  LedConfig->PIN_Number,
                  Led_Get_Off_Value(LedConfig));

    return E_OK;
}


Std_ReturnType Led_TOGGLE(const Led_Config_t * LedConfig)
{
    if(LedConfig == NULL)
    {
        return E_NOT_OK;
    }

    uint8_t current_state;

    GPIO_ReadPin(LedConfig->PORT,
                 LedConfig->PIN_Number,
                 &current_state);

    if(current_state == Led_Get_On_Value(LedConfig))
    {
        GPIO_WritePin(LedConfig->PORT,
                      LedConfig->PIN_Number,
                      Led_Get_Off_Value(LedConfig));
    }
    else
    {
        GPIO_WritePin(LedConfig->PORT,
                      LedConfig->PIN_Number,
                      Led_Get_On_Value(LedConfig));
    }

    return E_OK;
}

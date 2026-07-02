#include "KeyPad.h"

/* =================== LOCAL FUNCTIONS =================== */
static void KeyPad_SetAllRowsHigh(const KeyPad_ConfigType * ConfigPtr)
{
    for(uint8_t i = 0; i < ConfigPtr->Rows; i++)
    {
        GPIO_WritePin(ConfigPtr->RowPins[i].Port,
                      ConfigPtr->RowPins[i].Pin,
                      GPIO_HIGH);
    }
}

/* =================== API FUNCTIONS =================== */
Std_ReturnType KeyPad_Init(const KeyPad_ConfigType * ConfigPtr)
{
    if(ConfigPtr == NULL)
    {
        return E_NOT_OK;
    }

    GPIO_Config_Pin_t pin_cfg;

    /* Configure Rows as Output Push-Pull */
    pin_cfg.mode = GPIO_MODE_Output_PP;
    pin_cfg.Speed = GPIO_SPEED_10M;

    for(uint8_t i = 0; i < ConfigPtr->Rows; i++)
    {
        pin_cfg.PORTx = ConfigPtr->RowPins[i].Port;
        pin_cfg.Pin_Number = ConfigPtr->RowPins[i].Pin;
        GPIO_InitPin(&pin_cfg);
        GPIO_WritePin(ConfigPtr->RowPins[i].Port, ConfigPtr->RowPins[i].Pin, GPIO_HIGH);
    }

    /* Configure Columns as Input Pull-Up */
    pin_cfg.mode = GPIO_MODE_Input_PU;
    for(uint8_t i = 0; i < ConfigPtr->Cols; i++)
    {
        pin_cfg.PORTx = ConfigPtr->ColPins[i].Port;
        pin_cfg.Pin_Number = ConfigPtr->ColPins[i].Pin;
        GPIO_InitPin(&pin_cfg);
    }

    return E_OK;
}

Std_ReturnType KeyPad_GetKey(const KeyPad_ConfigType * ConfigPtr, uint8_t * KeyValue)
{
    if((ConfigPtr == NULL) || (KeyValue == NULL))
    {
        return E_NOT_OK;
    }

    uint8_t col_state;

    for(uint8_t row = 0; row < ConfigPtr->Rows; row++)
    {
        KeyPad_SetAllRowsHigh(ConfigPtr);
        GPIO_WritePin(ConfigPtr->RowPins[row].Port, ConfigPtr->RowPins[row].Pin, GPIO_LOW);

        for(uint8_t col = 0; col < ConfigPtr->Cols; col++)
        {
            GPIO_ReadPin(ConfigPtr->ColPins[col].Port, ConfigPtr->ColPins[col].Pin, &col_state);

            if(col_state == KEYPAD_PRESSED_STATE)
            {
                *KeyValue = ConfigPtr->KeyMap[row][col];

                /* Simple debounce */
                for(volatile uint32_t i = 0; i < KEYPAD_DEBOUNCE_DELAY; i++);

                /* Wait for release */
                do
                {
                    GPIO_ReadPin(ConfigPtr->ColPins[col].Port, ConfigPtr->ColPins[col].Pin, &col_state);
                } while(col_state == KEYPAD_PRESSED_STATE);

                return E_OK;
            }
        }
    }

    return E_NOT_OK;
}

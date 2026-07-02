#include "LCD.h"

/* Abstracted delay for portability */
static void Lcd_DelayMs(uint32_t ms)
{
    for(volatile uint32_t i = 0; i < (ms*1000); i++);
}

/* Write a single pin */
static void Lcd_WritePin(const Lcd_PinType * Pin, uint8_t value)
{
    GPIO_WritePin(Pin->Port, Pin->Pin, value);
}

/* Pulse Enable */
static void Lcd_PulseEnable(const Lcd_ConfigType * ConfigPtr)
{
    Lcd_WritePin(&ConfigPtr->EN, GPIO_HIGH);
    Lcd_DelayMs(1);
    Lcd_WritePin(&ConfigPtr->EN, GPIO_LOW);
    Lcd_DelayMs(1);
}

/* Write n bits (4 or 8) */
static void Lcd_WriteBits(const Lcd_ConfigType * ConfigPtr, uint8_t data, uint8_t bits)
{
    for(uint8_t i = 0; i < bits; i++)
    {
        Lcd_WritePin(&ConfigPtr->DataPins[i], (data >> i) & 0x01);
    }
    Lcd_PulseEnable(ConfigPtr);
}

/* Initialization */
Std_ReturnType Lcd_Init(const Lcd_ConfigType * ConfigPtr)
{
    if(ConfigPtr == NULL) return E_NOT_OK;

    GPIO_Config_Pin_t pin_cfg;
    pin_cfg.mode = GPIO_MODE_Output_PP;
    pin_cfg.Speed = GPIO_SPEED_10M;

    /* Control pins */
    pin_cfg.PORTx = ConfigPtr->RS.Port;
    pin_cfg.Pin_Number = ConfigPtr->RS.Pin;
    GPIO_InitPin(&pin_cfg);

    pin_cfg.PORTx = ConfigPtr->EN.Port;
    pin_cfg.Pin_Number = ConfigPtr->EN.Pin;
    GPIO_InitPin(&pin_cfg);

    if(ConfigPtr->RW_Used == LCD_RW_USED)
    {
        pin_cfg.PORTx = ConfigPtr->RW.Port;
        pin_cfg.Pin_Number = ConfigPtr->RW.Pin;
        GPIO_InitPin(&pin_cfg);
        Lcd_WritePin(&ConfigPtr->RW, GPIO_LOW);
    }

    /* Data pins */
    uint8_t data_pins = (ConfigPtr->Mode == LCD_8BIT_MODE) ? 8 : 4;
    for(uint8_t i = 0; i < data_pins; i++)
    {
        pin_cfg.PORTx = ConfigPtr->DataPins[i].Port;
        pin_cfg.Pin_Number = ConfigPtr->DataPins[i].Pin;
        GPIO_InitPin(&pin_cfg);
    }

    Lcd_DelayMs(40); /* Power-on delay */

    /* Init sequence */
    if(ConfigPtr->Mode == LCD_4BIT_MODE)
    {
        Lcd_WriteBits(ConfigPtr, 0x03, 4);
        Lcd_DelayMs(5);
        Lcd_WriteBits(ConfigPtr, 0x03, 4);
        Lcd_DelayMs(1);
        Lcd_WriteBits(ConfigPtr, 0x03, 4);
        Lcd_WriteBits(ConfigPtr, 0x02, 4); /* 4-bit mode */
    }
    else
    {
        Lcd_SendCommand(ConfigPtr, 0x30);
        Lcd_DelayMs(5);
        Lcd_SendCommand(ConfigPtr, 0x30);
        Lcd_DelayMs(1);
        Lcd_SendCommand(ConfigPtr, 0x30);
    }

    /* Function set, display on/off, entry mode */
    Lcd_SendCommand(ConfigPtr, (ConfigPtr->Mode == LCD_8BIT_MODE) ? 0x38 : 0x28);
    Lcd_SendCommand(ConfigPtr, 0x0C); /* Display ON, cursor OFF */
    Lcd_SendCommand(ConfigPtr, 0x06); /* Entry mode */
    Lcd_Clear(ConfigPtr);

    return E_OK;
}

/* Send command */
Std_ReturnType Lcd_SendCommand(const Lcd_ConfigType * ConfigPtr,uint8_t Command)
{
    if(ConfigPtr == NULL) return E_NOT_OK;

    Lcd_WritePin(&ConfigPtr->RS, GPIO_LOW);

    if(ConfigPtr->Mode == LCD_8BIT_MODE)
        Lcd_WriteBits(ConfigPtr, Command, 8);
    else
    {
        Lcd_WriteBits(ConfigPtr, Command >> 4, 4);
        Lcd_WriteBits(ConfigPtr, Command & 0x0F, 4);
    }

    Lcd_DelayMs(2);
    return E_OK;
}

/* Send char */
Std_ReturnType Lcd_SendChar(const Lcd_ConfigType * ConfigPtr,uint8_t Data)
{
    if(ConfigPtr == NULL) return E_NOT_OK;

    Lcd_WritePin(&ConfigPtr->RS, GPIO_HIGH);

    if(ConfigPtr->Mode == LCD_8BIT_MODE)
        Lcd_WriteBits(ConfigPtr, Data, 8);
    else
    {
        Lcd_WriteBits(ConfigPtr, Data >> 4, 4);
        Lcd_WriteBits(ConfigPtr, Data & 0x0F, 4);
    }

    Lcd_DelayMs(1);
    return E_OK;
}

/* Send string */
Std_ReturnType Lcd_SendString(const Lcd_ConfigType * ConfigPtr,const uint8_t * String)
{
    if((ConfigPtr == NULL) || (String == NULL)) return E_NOT_OK;

    while(*String)
        Lcd_SendChar(ConfigPtr, *String++);

    return E_OK;
}

/* Set cursor */
Std_ReturnType Lcd_SetCursor(const Lcd_ConfigType * ConfigPtr,uint8_t Row, uint8_t Col)
{
    if(ConfigPtr == NULL) return E_NOT_OK;

    uint8_t address;
    switch(Row)
    {
        case 0: address = 0x80 + Col; break;
        case 1: address = 0xC0 + Col; break;
        case 2: address = 0x94 + Col; break;
        case 3: address = 0xD4 + Col; break;
        default: return E_NOT_OK;
    }

    return Lcd_SendCommand(ConfigPtr, address);
}

/* Clear */
Std_ReturnType Lcd_Clear(const Lcd_ConfigType * ConfigPtr)
{
    return Lcd_SendCommand(ConfigPtr, 0x01);
}

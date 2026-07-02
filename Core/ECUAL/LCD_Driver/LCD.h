#ifndef LCD_H
#define LCD_H

#include "GPIO.h"

/* Modes */
#define LCD_4BIT_MODE  0U
#define LCD_8BIT_MODE  1U

/* Optional RW pin usage */
#define LCD_RW_NOT_USED 0
#define LCD_RW_USED     1

typedef struct
{
    GPIO_TypeDef_t * Port;
    GPIO_Pin_t      Pin;
} Lcd_PinType;

typedef struct
{
    uint8_t Mode;       /* LCD_4BIT_MODE or LCD_8BIT_MODE */
    uint8_t RW_Used;    /* LCD_RW_NOT_USED or LCD_RW_USED */

    Lcd_PinType RS;
    Lcd_PinType EN;
    Lcd_PinType RW;      /* Optional, only if RW_Used == LCD_RW_USED */

    Lcd_PinType DataPins[8]; /* D0-D7 (use first 4 if 4-bit mode) */

} Lcd_ConfigType;

/* APIs */
Std_ReturnType Lcd_Init(const Lcd_ConfigType * ConfigPtr);
Std_ReturnType Lcd_SendCommand(const Lcd_ConfigType * ConfigPtr,uint8_t Command);
Std_ReturnType Lcd_SendChar(const Lcd_ConfigType * ConfigPtr,uint8_t Data);
Std_ReturnType Lcd_SendString(const Lcd_ConfigType * ConfigPtr,const uint8_t * String);
Std_ReturnType Lcd_SetCursor(const Lcd_ConfigType * ConfigPtr,uint8_t Row, uint8_t Col);
Std_ReturnType Lcd_Clear(const Lcd_ConfigType * ConfigPtr);

#endif

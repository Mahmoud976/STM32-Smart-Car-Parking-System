#ifndef KEYPAD_H
#define KEYPAD_H

#include "GPIO.h"
/* =================== MACROS =================== */
#define KEYPAD_MAX_ROWS      4U
#define KEYPAD_MAX_COLS      4U
#define KEYPAD_PRESSED_STATE GPIO_LOW
#define KEYPAD_DEBOUNCE_DELAY 30000U  /* Busy-wait for debounce (can be replaced by timer) */

/* =================== TYPES =================== */
typedef uint8_t KeyPad_SizeType;

typedef struct
{
    GPIO_TypeDef_t * Port;
    GPIO_Pin_t Pin;
} KeyPad_PinType;

typedef struct
{
    KeyPad_SizeType Rows;
    KeyPad_SizeType Cols;

    KeyPad_PinType RowPins[KEYPAD_MAX_ROWS];
    KeyPad_PinType ColPins[KEYPAD_MAX_COLS];

    const uint8_t (*KeyMap)[KEYPAD_MAX_COLS];

} KeyPad_ConfigType;

/* =================== API FUNCTIONS =================== */
Std_ReturnType KeyPad_Init(const KeyPad_ConfigType * ConfigPtr);
Std_ReturnType KeyPad_GetKey(const KeyPad_ConfigType * ConfigPtr, uint8_t * KeyValue);

#endif /* KEYPAD_H */

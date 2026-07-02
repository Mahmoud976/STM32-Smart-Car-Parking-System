#ifndef GPIO_H
#define GPIO_H

/*************************************************************************************************************
 *                                               Include Section                                             *
**************************************************************************************************************/
#include "STM32F103C6.h"
#include "RCC.h"
/*************************************************************************************************************
 *                                               MACROS Section                                              *
**************************************************************************************************************/

/************* GPIO PIN STATE *************/
#define GPIO_LOW      0
#define GPIO_HIGH     1
/************* Peripherals Instance *************/
#define PORTA        ((GPIO_TypeDef_t*) GPIOA_BASE )
#define PORTB        ((GPIO_TypeDef_t*) GPIOB_BASE )
#define PORTC        ((GPIO_TypeDef_t*) GPIOC_BASE )
#define PORTD        ((GPIO_TypeDef_t*) GPIOD_BASE )
#define PORTE        ((GPIO_TypeDef_t*) GPIOE_BASE )

#define GPIO_PIN_MASK        0x0F
#define GPIO_BITS_PER_PIN    4U
#define GPIO_PINS_PER_REG    8U

#define GPIO_MODE_MASK       0x03
#define GPIO_CNF_MASK        0x03

#define GPIO_CRL_MAX_PIN     7U

#define IS_GPIO_PIN(PIN)   (((PIN) != 0U) && (((PIN) & ((PIN) - 1U)) == 0U))




#define IS_GPIO_PORT(PORT)   (((PORT) == PORTA) || \
                              ((PORT) == PORTB) || \
                              ((PORT) == PORTC) || \
                              ((PORT) == PORTD) || \
                              ((PORT) == PORTE))



#define IS_GPIO_OUTPUT_MODE(MODE)  ( \
    (MODE == GPIO_MODE_Output_PP)  || \
    (MODE == GPIO_MODE_Output_OD)  || \
    (MODE == GPIO_MODE_Output_AF_PP) || \
    (MODE == GPIO_MODE_Output_AF_OD) )



/*************************************************************************************************************
 *                                               USER TYPES Section                                          *
**************************************************************************************************************/
/************* GPIO PIN BIT MASKS *************/
typedef enum {
	 GPIO_PIN0  = ((uint16_t)(1U << 0)),   // 0x0001
	 GPIO_PIN1  = ((uint16_t)(1U << 1)),   // 0x0002
	 GPIO_PIN2  = ((uint16_t)(1U << 2)),   // 0x0004
	 GPIO_PIN3  = ((uint16_t)(1U << 3)),   // 0x0008
	 GPIO_PIN4  = ((uint16_t)(1U << 4)),   // 0x0010
	 GPIO_PIN5  = ((uint16_t)(1U << 5)),   // 0x0020
	 GPIO_PIN6  = ((uint16_t)(1U << 6)),   // 0x0040
	 GPIO_PIN7  = ((uint16_t)(1U << 7)),   // 0x0080
	 GPIO_PIN8  = ((uint16_t)(1U << 8)),   // 0x0100
	 GPIO_PIN9  = ((uint16_t)(1U << 9)),   // 0x0200
	 GPIO_PIN10 = ((uint16_t)(1U << 10)),  // 0x0400
	 GPIO_PIN11 = ((uint16_t)(1U << 11)),  // 0x0800
	 GPIO_PIN12 = ((uint16_t)(1U << 12)),  // 0x1000
	 GPIO_PIN13 = ((uint16_t)(1U << 13)),  // 0x2000
	 GPIO_PIN14 = ((uint16_t)(1U << 14)),  // 0x4000
	 GPIO_PIN15 = ((uint16_t)(1U << 15))   // 0x8000
}GPIO_Pin_t;

/*
In input mode (MODE[1:0]=00):
	0: Analog mode
	1: Floating input (reset state)
	2: Input with pull-up
	3: pull-down

In output mode (MODE[1:0]0>00):
	4: General purpose output push-pull
	5: General purpose output Open-drain
	6: Alternate function output Push-pull
	7: Alternate function output Open-drain
	8: Alternate function input

	1: Output mode, max speed 10 MHz.
	2: Output mode, max speed 2 MHz.
	3: Output mode, max speed 50 MHz.
*/
/************* GPIO SPEED *************/
typedef enum {
    GPIO_SPEED_10M = 1,
    GPIO_SPEED_2M  = 2,
    GPIO_SPEED_50M = 4
} GPIO_SPEED_t;


/************* GPIO MODE *************/
typedef enum {
    GPIO_MODE_Analog       = 0,
    GPIO_MODE_Input_FLO    = 1,
    GPIO_MODE_Input_PU     = 2,
    GPIO_MODE_Input_PD     = 3,
    GPIO_MODE_Output_PP    = 4,
    GPIO_MODE_Output_OD    = 5,
    GPIO_MODE_Output_AF_PP = 6,
    GPIO_MODE_Output_AF_OD = 7,
    GPIO_MODE_AF_Input     = 8
} GPIO_MODE_t;

//Peripherals Instance

typedef struct {
	volatile uint32_t CRL ;
	volatile uint32_t CRH ;
	volatile uint32_t IDR ;
	volatile uint32_t ODR ;
	volatile uint32_t BSRR;
	volatile uint32_t BRR ;
	volatile uint32_t LCKR;
}GPIO_TypeDef_t;



typedef struct{
	GPIO_TypeDef_t * PORTx;
	GPIO_Pin_t Pin_Number;
	GPIO_MODE_t mode;
	GPIO_SPEED_t Speed;
}GPIO_Config_Pin_t;



typedef enum {
	E_OK = 0,
	E_NOT_OK,
    INVALID_PIN,
    INVALID_PORT,
	INVALID_SPEED,
	INVALID_MODE,
	INVALID_TRIGGER,
	INVALID_IRQ_EN,
	INVALID_NVIC_EN,
} Std_ReturnType;
/*************************************************************************************************************
 *                                    API FUNCTION PROTOTYPES Section                                        *
**************************************************************************************************************/

/**
 * @brief        Initializes a GPIO pin according to the given configuration.
 *
 * @param[in]    PinConfigPtr   Pointer to GPIO configuration structure.
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Initialization successful.
 *               @retval E_NOT_OK       NULL pointer passed.
 *               @retval INVALID_PORT   Invalid GPIO port.
 *               @retval INVALID_PIN    Invalid GPIO pin.
 *               @retval INVALID_MODE   Invalid GPIO mode.
 *               @retval INVALID_SPEED  Invalid GPIO speed (for output modes).
 *
 * @pre          GPIO peripheral clock must be enabled before calling this function.
 * @post         The selected pin is configured and ready for use.
 *
 * @note         This function configures pin mode, speed, and pull-up/pull-down settings.
 *
 * @warning      Passing NULL pointer will result in E_NOT_OK.
 */
Std_ReturnType GPIO_InitPin(const GPIO_Config_Pin_t * PinConfig);

/**
 * @brief        De-initializes a specific GPIO pin, resetting it to default state.
 *
 * @param[in]    PORTx         Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Pin_Number    GPIO pin to reset (GPIO_PIN0 .. GPIO_PIN15).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Pin successfully de-initialized.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval INVALID_PIN    Invalid GPIO pin number.
 *
 * @pre          GPIO peripheral clock must be enabled before calling this function.
 * @post         The selected pin is reset: CRL/CRH cleared, output set LOW.
 *
 * @note         This function only affects the selected pin, not other pins in the port.
 * @warning      Using this on a pin currently in use may interrupt ongoing operations.
 */
Std_ReturnType GPIO_DeInitPin(GPIO_TypeDef_t * PORTx, GPIO_Pin_t Pin_Number);

/**
 * @brief        De-initializes an entire GPIO port, resetting all pins to default state.
 *
 * @param[in]    PORTx   Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Port successfully de-initialized.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *
 * @pre          GPIO peripheral clock must be enabled before calling this function.
 * @post         All pins in the port are reset: CRL/CRH cleared, outputs set LOW.
 *
 * @note         This function affects every pin in the selected port.
 * @warning      Using this on an active port may interrupt all ongoing operations.
 */
Std_ReturnType GPIO_DeInitPort(GPIO_TypeDef_t * PORTx);


/**
 * @brief        Reads the logic level of a specific GPIO pin.
 *
 * @param[in]    PORTx       Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Pin_Number  GPIO pin to read (GPIO_PIN0 .. GPIO_PIN15).
 * @param[out]   ptr_value   Pointer to variable where the pin state will be stored
 *                           (GPIO_LOW / GPIO_HIGH).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Pin successfully read.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval INVALID_PIN    Invalid GPIO pin number.
 *               @retval E_NOT_OK       NULL pointer passed for ptr_value.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         The state of the selected pin is returned in ptr_value.
 *
 * @note         Reading a pin configured as output returns the last written value.
 */
Std_ReturnType GPIO_ReadPin(GPIO_TypeDef_t * PORTx, GPIO_Pin_t Pin_Number, uint8_t * ptr_value);

/**
 * @brief        Reads the logic level of an entire GPIO port.
 *
 * @param[in]    PORTx       Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[out]   ptr_value   Pointer to variable where the 16-bit port state will be stored.
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Port successfully read.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval E_NOT_OK       NULL pointer passed for ptr_value.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         The current state of all pins in the port is returned in ptr_value.
 *
 * @note         Only the lower 16 bits of the IDR register are returned.
 */

Std_ReturnType GPIO_ReadPort(GPIO_TypeDef_t * PORTx,uint16_t * ptr_value);


/**
 * @brief        Writes a logic level to a specific GPIO pin.
 *
 * @param[in]    PORTx       Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Pin_Number  GPIO pin to write (GPIO_PIN0 .. GPIO_PIN15).
 * @param[in]    Value       Desired logic level (GPIO_LOW / GPIO_HIGH).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Pin successfully written.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval INVALID_PIN    Invalid GPIO pin number.
 *               @retval E_NOT_OK       Invalid value (not GPIO_LOW or GPIO_HIGH).
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         The selected pin output is updated according to Value.
 *
 * @note         Writing to an input pin has no effect.
 */
Std_ReturnType GPIO_WritePin(GPIO_TypeDef_t * PORTx, GPIO_Pin_t Pin_Number, uint8_t Value);

/**
 * @brief        Writes a 16-bit value to an entire GPIO port.
 *
 * @param[in]    PORTx   Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Value   16-bit value to write to the port.
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Port successfully written.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         All pins in the port are updated according to Value.
 *
 * @note         Only the lower 16 bits of Value are used. Writing to input pins has no effect.
 */
Std_ReturnType GPIO_WritePort(GPIO_TypeDef_t * PORTx, uint16_t Value);


/**
 * @brief        Toggles the logic level of a specific GPIO pin.
 *
 * @param[in]    PORTx       Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Pin_Number  GPIO pin to toggle (GPIO_PIN0 .. GPIO_PIN15).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Pin successfully toggled.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval INVALID_PIN    Invalid GPIO pin number.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         The selected pin logic level is inverted.
 *
 * @note         Toggling an input pin has no effect.
 */
Std_ReturnType GPIO_TogglePin(GPIO_TypeDef_t * PORTx, GPIO_Pin_t Pin_Number);

/**
 * @brief        Toggles the logic level of all pins in a GPIO port.
 *
 * @param[in]    PORTx   Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Port successfully toggled.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         All pins in the port have their logic levels inverted.
 *
 * @note         Only the lower 16 bits are toggled. Toggling input pins has no effect.
 */
Std_ReturnType GPIO_TogglePort(GPIO_TypeDef_t * PORTx);


/**
 * @brief        Locks the configuration of a specific GPIO pin.
 *
 * @param[in]    PORTx       Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Pin_Number  GPIO pin to lock (GPIO_PIN0 .. GPIO_PIN15).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Pin successfully locked.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval INVALID_PIN    Invalid GPIO pin number.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         The selected pin configuration is locked and cannot be modified until reset.
 *
 * @note         Lock sequence must be followed as per the reference manual.
 */
Std_ReturnType GPIO_LockPin(GPIO_TypeDef_t * PORTx, GPIO_Pin_t Pin_Number);

#endif //End GPIO_H

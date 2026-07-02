#ifndef EXTI_H
#define EXTI_H
#include "GPIO.h"





typedef struct {
	volatile uint32_t IMR ;
	volatile uint32_t EMR ;
	volatile uint32_t RTSR ;
	volatile uint32_t FTSR ;
	volatile uint32_t SWIER;
	volatile uint32_t PR ;
}EXTI_TypeDef_t;

#define EXTI        ((EXTI_TypeDef_t *)EXTI_BASE)

#define EXTI_Mapping_With_GPIO(x)     ( (x==PORTA)?0:\
										(x==PORTB)?1:\
										(x==PORTC)?2:\
										(x==PORTD)?3:4\
												)/*4  Not available in 48-pin */




typedef enum {
    EXTI_LINE_0 = 0,
    EXTI_LINE_1,
    EXTI_LINE_2,
    EXTI_LINE_3,
    EXTI_LINE_4,
    EXTI_LINE_5,
    EXTI_LINE_6,
    EXTI_LINE_7,
    EXTI_LINE_8,
    EXTI_LINE_9,
    EXTI_LINE_10,
    EXTI_LINE_11,
    EXTI_LINE_12,
    EXTI_LINE_13,
    EXTI_LINE_14,
    EXTI_LINE_15
} EXTI_Line_t;


typedef struct
{
	EXTI_Line_t EXTI_Input_Line_Number;
	GPIO_TypeDef_t*  GPIO_Port;
	GPIO_Pin_t     GPIO_PIN;
	uint8_t 	 IVT_IRQ_Number;



}EXTI_GPIO_Mapping_t;


typedef struct
{
	EXTI_GPIO_Mapping_t  EXTI_PIN;   	//Specifies the external interrupt GPIO Mapping.
										//this parameter must be set based on @ref EXTI_define

	uint8_t    Trigger_Case;        	//Specifies Rising or Falling Or both trigger.
										//this parameter must be set based on @ref EXTI_Trigger_define.

	uint8_t   IRQ_EN;       	       //enable or disable  the EXTI_IRQ  {that will enable the IRQ mask in EXTI and also on the NVIC }
								       //this parameter must be set based on @ref EXTI_IRQ_define.

	void (* P_IRQ_CallBack)(void);     // Set the C function () which will be called when IRQ happen
}EXTI_PinConfig_t;



//Reference Macros

//@ref EXTI_define

// EXTI0
#define EXTI0PA0                (EXTI_GPIO_Mapping_t){ EXTI_LINE_0,PORTA,GPIO_PIN0,EXTI0_IRQ}
#define EXTI0PB0                (EXTI_GPIO_Mapping_t){ EXTI_LINE_0,PORTB,GPIO_PIN0,EXTI0_IRQ}
#define EXTI0PC0                (EXTI_GPIO_Mapping_t){ EXTI_LINE_0,PORTC,GPIO_PIN0,EXTI0_IRQ}
#define EXTI0PD0                (EXTI_GPIO_Mapping_t){ EXTI_LINE_0,PORTD,GPIO_PIN0,EXTI0_IRQ}
// EXTI1
#define EXTI1PA1                (EXTI_GPIO_Mapping_t){ EXTI_LINE_1,PORTA,GPIO_PIN1,EXTI1_IRQ}
#define EXTI1PB1                (EXTI_GPIO_Mapping_t){ EXTI_LINE_1,PORTB,GPIO_PIN1,EXTI1_IRQ}
#define EXTI1PC1                (EXTI_GPIO_Mapping_t){ EXTI_LINE_1,PORTC,GPIO_PIN1,EXTI1_IRQ}
#define EXTI1PD1                (EXTI_GPIO_Mapping_t){ EXTI_LINE_1,PORTD,GPIO_PIN1,EXTI1_IRQ}
// EXTI2
#define EXTI2PA2                (EXTI_GPIO_Mapping_t){ EXTI_LINE_2,PORTA,GPIO_PIN2,EXTI2_IRQ}
#define EXTI2PB2                (EXTI_GPIO_Mapping_t){ EXTI_LINE_2,PORTB,GPIO_PIN2,EXTI2_IRQ}
#define EXTI2PC2                (EXTI_GPIO_Mapping_t){ EXTI_LINE_2,PORTC,GPIO_PIN2,EXTI2_IRQ}
#define EXTI2PD2                (EXTI_GPIO_Mapping_t){ EXTI_LINE_2,PORTD,GPIO_PIN2,EXTI2_IRQ}
// EXTI3
#define EXTI3PA3                (EXTI_GPIO_Mapping_t){ EXTI_LINE_3,PORTA,GPIO_PIN3,EXTI3_IRQ}
#define EXTI3PB3                (EXTI_GPIO_Mapping_t){ EXTI_LINE_3,PORTB,GPIO_PIN3,EXTI3_IRQ}
#define EXTI3PC3                (EXTI_GPIO_Mapping_t){ EXTI_LINE_3,PORTC,GPIO_PIN3,EXTI3_IRQ}
#define EXTI3PD3                (EXTI_GPIO_Mapping_t){ EXTI_LINE_3,PORTD,GPIO_PIN3,EXTI3_IRQ}
// EXTI4
#define EXTI4PA4                (EXTI_GPIO_Mapping_t){ EXTI_LINE_4,PORTA,GPIO_PIN4,EXTI4_IRQ}
#define EXTI4PB4                (EXTI_GPIO_Mapping_t){ EXTI_LINE_4,PORTB,GPIO_PIN4,EXTI4_IRQ}
#define EXTI4PC4                (EXTI_GPIO_Mapping_t){ EXTI_LINE_4,PORTC,GPIO_PIN4,EXTI4_IRQ}
#define EXTI4PD4                (EXTI_GPIO_Mapping_t){ EXTI_LINE_4,PORTD,GPIO_PIN4,EXTI4_IRQ}
// EXTI5
#define EXTI5PA5                (EXTI_GPIO_Mapping_t){ EXTI_LINE_5,PORTA,GPIO_PIN5,EXTI5_IRQ}
#define EXTI5PB5                (EXTI_GPIO_Mapping_t){ EXTI_LINE_5,PORTB,GPIO_PIN5,EXTI5_IRQ}
#define EXTI5PC5                (EXTI_GPIO_Mapping_t){ EXTI_LINE_5,PORTC,GPIO_PIN5,EXTI5_IRQ}
#define EXTI5PD5                (EXTI_GPIO_Mapping_t){ EXTI_LINE_5,PORTD,GPIO_PIN5,EXTI5_IRQ}
// EXTI6
#define EXTI6PA6                (EXTI_GPIO_Mapping_t){ EXTI_LINE_6,PORTA,GPIO_PIN6,EXTI6_IRQ}
#define EXTI6PB6                (EXTI_GPIO_Mapping_t){ EXTI_LINE_6,PORTB,GPIO_PIN6,EXTI6_IRQ}
#define EXTI6PC6                (EXTI_GPIO_Mapping_t){ EXTI_LINE_6,PORTC,GPIO_PIN6,EXTI6_IRQ}
#define EXTI6PD6                (EXTI_GPIO_Mapping_t){ EXTI_LINE_6,PORTD,GPIO_PIN6,EXTI6_IRQ}
// EXTI7
#define EXTI7PA7                (EXTI_GPIO_Mapping_t){ EXTI_LINE_7,PORTA,GPIO_PIN7,EXTI7_IRQ}
#define EXTI7PB7                (EXTI_GPIO_Mapping_t){ EXTI_LINE_7,PORTB,GPIO_PIN7,EXTI7_IRQ}
#define EXTI7PC7                (EXTI_GPIO_Mapping_t){ EXTI_LINE_7,PORTC,GPIO_PIN7,EXTI7_IRQ}
#define EXTI7PD7                (EXTI_GPIO_Mapping_t){ EXTI_LINE_7,PORTD,GPIO_PIN7,EXTI7_IRQ}
// EXTI8
#define EXTI8PA8                (EXTI_GPIO_Mapping_t){ EXTI_LINE_8,PORTA,GPIO_PIN8,EXTI8_IRQ}
#define EXTI8PB8                (EXTI_GPIO_Mapping_t){ EXTI_LINE_8,PORTB,GPIO_PIN8,EXTI8_IRQ}
#define EXTI8PC8                (EXTI_GPIO_Mapping_t){ EXTI_LINE_8,PORTC,GPIO_PIN8,EXTI8_IRQ}
#define EXTI8PD8                (EXTI_GPIO_Mapping_t){ EXTI_LINE_8,PORTD,GPIO_PIN8,EXTI8_IRQ}
// EXTI9
#define EXTI9PA9                (EXTI_GPIO_Mapping_t){ EXTI_LINE_9,PORTA,GPIO_PIN9,EXTI9_IRQ}
#define EXTI9PB9                (EXTI_GPIO_Mapping_t){ EXTI_LINE_9,PORTB,GPIO_PIN9,EXTI9_IRQ}
#define EXTI9PC9                (EXTI_GPIO_Mapping_t){ EXTI_LINE_9,PORTC,GPIO_PIN9,EXTI9_IRQ}
#define EXTI9PD9                (EXTI_GPIO_Mapping_t){ EXTI_LINE_9,PORTD,GPIO_PIN9,EXTI9_IRQ}
// EXTI10
#define EXTI10PA10              (EXTI_GPIO_Mapping_t){ EXTI_LINE_10,PORTA,GPIO_PIN10,EXTI10_IRQ}
#define EXTI10PB10              (EXTI_GPIO_Mapping_t){ EXTI_LINE_10,PORTB,GPIO_PIN10,EXTI10_IRQ}
#define EXTI10PC10              (EXTI_GPIO_Mapping_t){ EXTI_LINE_10,PORTC,GPIO_PIN10,EXTI10_IRQ}
#define EXTI10PD10              (EXTI_GPIO_Mapping_t){ EXTI_LINE_10,PORTD,GPIO_PIN10,EXTI10_IRQ}
// EXTI11
#define EXTI11PA11              (EXTI_GPIO_Mapping_t){ EXTI_LINE_11,PORTA,GPIO_PIN11,EXTI11_IRQ}
#define EXTI11PB11              (EXTI_GPIO_Mapping_t){ EXTI_LINE_11,PORTB,GPIO_PIN11,EXTI11_IRQ}
#define EXTI11PC11              (EXTI_GPIO_Mapping_t){ EXTI_LINE_11,PORTC,GPIO_PIN11,EXTI11_IRQ}
#define EXTI11PD11              (EXTI_GPIO_Mapping_t){ EXTI_LINE_11,PORTD,GPIO_PIN11,EXTI11_IRQ}
// EXTI12
#define EXTI12PA12              (EXTI_GPIO_Mapping_t){ EXTI_LINE_12,PORTA,GPIO_PIN12,EXTI12_IRQ}
#define EXTI12PB12              (EXTI_GPIO_Mapping_t){ EXTI_LINE_12,PORTB,GPIO_PIN12,EXTI12_IRQ}
#define EXTI12PC12              (EXTI_GPIO_Mapping_t){ EXTI_LINE_12,PORTC,GPIO_PIN12,EXTI12_IRQ}
#define EXTI12PD12              (EXTI_GPIO_Mapping_t){ EXTI_LINE_12,PORTD,GPIO_PIN12,EXTI12_IRQ}
// EXTI13
#define EXTI13PA13              (EXTI_GPIO_Mapping_t){ EXTI_LINE_13,PORTA,GPIO_PIN13,EXTI13_IRQ}
#define EXTI13PB13              (EXTI_GPIO_Mapping_t){ EXTI_LINE_13,PORTB,GPIO_PIN13,EXTI13_IRQ}
#define EXTI13PC13              (EXTI_GPIO_Mapping_t){ EXTI_LINE_13,PORTC,GPIO_PIN13,EXTI13_IRQ}
#define EXTI13PD13              (EXTI_GPIO_Mapping_t){ EXTI_LINE_13,PORTD,GPIO_PIN13,EXTI13_IRQ}
// EXTI14
#define EXTI14PA14              (EXTI_GPIO_Mapping_t){ EXTI_LINE_14,PORTA,GPIO_PIN14,EXTI14_IRQ}
#define EXTI14PB14              (EXTI_GPIO_Mapping_t){ EXTI_LINE_14,PORTB,GPIO_PIN14,EXTI14_IRQ}
#define EXTI14PC14              (EXTI_GPIO_Mapping_t){ EXTI_LINE_14,PORTC,GPIO_PIN14,EXTI14_IRQ}
#define EXTI14PD14              (EXTI_GPIO_Mapping_t){ EXTI_LINE_14,PORTD,GPIO_PIN14,EXTI14_IRQ}
// EXTI15
#define EXTI15PA15              (EXTI_GPIO_Mapping_t){ EXTI_LINE_15,PORTA,GPIO_PIN15,EXTI15_IRQ}
#define EXTI15PB15              (EXTI_GPIO_Mapping_t){ EXTI_LINE_15,PORTB,GPIO_PIN15,EXTI15_IRQ}
#define EXTI15PC15              (EXTI_GPIO_Mapping_t){ EXTI_LINE_15,PORTC,GPIO_PIN15,EXTI15_IRQ}
#define EXTI15PD15              (EXTI_GPIO_Mapping_t){ EXTI_LINE_15,PORTD,GPIO_PIN15,EXTI15_IRQ}


//@ref EXTI_Trigger_define
#define EXTI_Trigger_Rising              (1U << 0)
#define EXTI_Trigger_Falling             (1U << 1)
#define EXTI_Trigger_RisingAndFalling    (EXTI_Trigger_Rising | EXTI_Trigger_Falling )


//@ref EXTI_IRQ_define
#define EXTI_IRQ_Enable           1
#define EXTI_IRQ_Disable          0




/*function API*/

Std_ReturnType EXTI_GPIO_Init(const EXTI_PinConfig_t * EXTI_Config);
Std_ReturnType EXTI_GPIO_DeInit(void);
Std_ReturnType EXTI_GPIO_Update(const EXTI_PinConfig_t * EXTI_Config);






#endif /*End EXTI_H*/

#ifndef MCU_Config_H
#define MCU_Config_H


#include <stddef.h>
#include "RCC.h"

//******************MACROS**********************************
#define AFIO         ((AFIO_TypeDef*) AFIO_BASE )



//Alternative Function Peripherals Instance
typedef struct {
	volatile uint32_t EVCR ;
	volatile uint32_t MAPR ;
	volatile uint32_t EXTICR[4] ;
	volatile uint32_t RESERVED ;
	volatile uint32_t MAPR2 ;
}AFIO_TypeDef;

/* Macros*/
#define  EXTI0_IRQ           6
#define  EXTI1_IRQ           7
#define  EXTI2_IRQ           8
#define  EXTI3_IRQ           9
#define  EXTI4_IRQ           10
#define  EXTI5_IRQ           23
#define  EXTI6_IRQ           23
#define  EXTI7_IRQ           23
#define  EXTI8_IRQ           23
#define  EXTI9_IRQ           23
#define  EXTI10_IRQ          40
#define  EXTI11_IRQ          40
#define  EXTI12_IRQ          40
#define  EXTI13_IRQ          40
#define  EXTI14_IRQ          40
#define  EXTI15_IRQ          40






/* NVIC Enable Macros for EXTI lines */
#define NVIC_EXTI0_Enable   (NVIC_ISER0 |= 1 << 6)
#define NVIC_EXTI1_Enable   (NVIC_ISER0 |= 1 << 7)
#define NVIC_EXTI2_Enable   (NVIC_ISER0 |= 1 << 8)
#define NVIC_EXTI3_Enable   (NVIC_ISER0 |= 1 << 9)
#define NVIC_EXTI4_Enable   (NVIC_ISER0 |= 1 << 10)

#define NVIC_EXTI5_Enable   (NVIC_ISER0 |= 1 << 23)
#define NVIC_EXTI6_Enable   (NVIC_ISER0 |= 1 << 23)
#define NVIC_EXTI7_Enable   (NVIC_ISER0 |= 1 << 23)
#define NVIC_EXTI8_Enable   (NVIC_ISER0 |= 1 << 23)
#define NVIC_EXTI9_Enable   (NVIC_ISER0 |= 1 << 23)

#define NVIC_EXTI10_Enable  (NVIC_ISER1 |= 1 << (40-32))
#define NVIC_EXTI11_Enable  (NVIC_ISER1 |= 1 << (40-32))
#define NVIC_EXTI12_Enable  (NVIC_ISER1 |= 1 << (40-32))
#define NVIC_EXTI13_Enable  (NVIC_ISER1 |= 1 << (40-32))
#define NVIC_EXTI14_Enable  (NVIC_ISER1 |= 1 << (40-32))
#define NVIC_EXTI15_Enable  (NVIC_ISER1 |= 1 << (40-32))

#define NVIC_I2C1_EV_Enable  (NVIC_ISER0 |= 1 << (31))
#define NVIC_I2C1_ER_Enable  (NVIC_ISER1 |= 1 << (32-32))
#define NVIC_I2C2_EV_Enable  (NVIC_ISER1 |= 1 << (33-32))
#define NVIC_I2C2_ER_Enable  (NVIC_ISER1 |= 1 << (34-32))

#define NVIC_SPI1_Enable  (NVIC_ISER1 |= 1 << (35-32))
#define NVIC_SPI2_Enable  (NVIC_ISER1 |= 1 << (36-32))

#define NVIC_UART1_Enable  (NVIC_ISER1 |= 1 << (37-32))
#define NVIC_UART2_Enable  (NVIC_ISER1 |= 1 << (38-32))
#define NVIC_UART3_Enable  (NVIC_ISER1 |= 1 << (39-32))


/* NVIC Disable Macros for EXTI lines */
#define NVIC_EXTI0_Disable   (NVIC_ICER0 |= 1 << 6)
#define NVIC_EXTI1_Disable   (NVIC_ICER0 |= 1 << 7)
#define NVIC_EXTI2_Disable   (NVIC_ICER0 |= 1 << 8)
#define NVIC_EXTI3_Disable   (NVIC_ICER0 |= 1 << 9)
#define NVIC_EXTI4_Disable   (NVIC_ICER0 |= 1 << 10)

#define NVIC_EXTI5_Disable   (NVIC_ICER0 |= 1 << 23)
#define NVIC_EXTI6_Disable   (NVIC_ICER0 |= 1 << 23)
#define NVIC_EXTI7_Disable   (NVIC_ICER0 |= 1 << 23)
#define NVIC_EXTI8_Disable   (NVIC_ICER0 |= 1 << 23)
#define NVIC_EXTI9_Disable   (NVIC_ICER0 |= 1 << 23)

#define NVIC_EXTI10_Disable  (NVIC_ICER1 |= 1 << (40-32))
#define NVIC_EXTI11_Disable  (NVIC_ICER1 |= 1 << (40-32))
#define NVIC_EXTI12_Disable  (NVIC_ICER1 |= 1 << (40-32))
#define NVIC_EXTI13_Disable  (NVIC_ICER1 |= 1 << (40-32))
#define NVIC_EXTI14_Disable  (NVIC_ICER1 |= 1 << (40-32))
#define NVIC_EXTI15_Disable  (NVIC_ICER1 |= 1 << (40-32))


#define NVIC_I2C1_EV_Disable  (NVIC_ICER0 |= 1 << (31))
#define NVIC_I2C1_ER_Disable  (NVIC_ICER1 |= 1 << (32-32))
#define NVIC_I2C2_EV_Disable  (NVIC_ICER1 |= 1 << (33-32))
#define NVIC_I2C2_ER_Disable  (NVIC_ICER1 |= 1 << (34-32))

#define NVIC_SPI1_Disable    (NVIC_ICER1 |= 1 << (35-32))
#define NVIC_SPI2_Disable    (NVIC_ICER1 |= 1 << (36-32))

#define NVIC_UART1_Disable   (NVIC_ICER1 |= 1 << (37-32))
#define NVIC_UART2_Disable   (NVIC_ICER1 |= 1 << (38-32))
#define NVIC_UART3_Disable   (NVIC_ICER1 |= 1 << (39-32))


#endif //end MCU_Config_H

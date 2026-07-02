#ifndef STM32F103C_H
#define STM32F103C_H

/*************************************************************************************************************
 *                                              Include Section                                              *
**************************************************************************************************************/
#include <stdint.h>
#include "MCU_Config.h"
/*************************************************************************************************************
 *                                  Cortex M3 NVIC Offsets Section                                           *
**************************************************************************************************************/
/* NVIC Base Address */
#define NVIC_BASE              0xE000E100UL

/* Register Offsets */
#define NVIC_ISER_OFFSET           0x00UL
#define NVIC_ICER_OFFSET           0x80UL

/* Register Index Offsets */
#define NVIC_REG0_OFFSET           0x00UL
#define NVIC_REG1_OFFSET           0x04UL
#define NVIC_REG2_OFFSET           0x08UL
/*************************************************************************************************************
 *                                             Cortex M3 Core Peripherals Section                            *
*************************************************************************************************************/
/* ISER Registers */
#define NVIC_ISER0   *((volatile uint32_t*)(NVIC_BASE + NVIC_ISER_OFFSET + NVIC_REG0_OFFSET))
#define NVIC_ISER1   *((volatile uint32_t*)(NVIC_BASE + NVIC_ISER_OFFSET + NVIC_REG1_OFFSET))
#define NVIC_ISER2   *((volatile uint32_t*)(NVIC_BASE + NVIC_ISER_OFFSET + NVIC_REG2_OFFSET))

/* ICER Registers */
#define NVIC_ICER0   *((volatile uint32_t*)(NVIC_BASE + NVIC_ICER_OFFSET + NVIC_REG0_OFFSET))
#define NVIC_ICER1   *((volatile uint32_t*)(NVIC_BASE + NVIC_ICER_OFFSET + NVIC_REG1_OFFSET))
#define NVIC_ICER2   *((volatile uint32_t*)(NVIC_BASE + NVIC_ICER_OFFSET + NVIC_REG2_OFFSET))

/*************************************************************************************************************
 *                                          Memory Map Section                                               *
**************************************************************************************************************/
#define FLASH_BASE      			0x08000000UL
#define SRAM_BASE       			0x20000000UL
#define PERIPHERALS_BASE     		0x40000000UL

/*************************************************************************************************************
 *                                          Bus Base Section                                                 *
**************************************************************************************************************/
#define APB1_BASE       0x40000000
#define APB2_BASE       0x40010000
#define AHB_BASE        0x40018000


/*************************************************************************************************************
 *                                   AHB Peripheral Offsets Section                                          *
**************************************************************************************************************/
#define DMA1_OFFSET       0x0000
#define DMA2_OFFSET       0x0400   /* Not available in low-density devices / 48-pin */
#define RCC_OFFSET        0x9000
#define FLASH_REG_OFFSET  0xA000
#define CRC_OFFSET        0xB000

/*************************************************************************************************************
 *                                          AHB Peripherals Section                                          *
**************************************************************************************************************/
#define DMA1_BASE       (AHB_BASE + DMA1_OFFSET)       /* Fully available in 48-pin */
#define DMA2_BASE       (AHB_BASE + DMA2_OFFSET)       /* Not available in 48-pin */

#define RCC_BASE        (AHB_BASE + RCC_OFFSET)        /* Fully available in 48-pin */

#define FLASH_REG_BASE  (AHB_BASE + FLASH_REG_OFFSET)  /* Fully available in 48-pin */

#define CRC_BASE        (AHB_BASE + CRC_OFFSET)        /* Fully available in 48-pin */


/*************************************************************************************************************
 *                                   APB2 Peripheral Offsets Section                                         *
**************************************************************************************************************/
#define AFIO_OFFSET       0x0000
#define EXTI_OFFSET       0x0400
#define GPIOA_OFFSET      0x0800
#define GPIOB_OFFSET      0x0C00
#define GPIOC_OFFSET      0x1000
#define GPIOD_OFFSET      0x1400   /* Not available in 48-pin */
#define GPIOE_OFFSET      0x1800   /* Not available in 48-pin */
#define ADC1_OFFSET       0x2400
#define ADC2_OFFSET       0x2800
#define TIM1_OFFSET       0x2C00
#define SPI1_OFFSET       0x3000
#define USART1_OFFSET     0x3800

/*************************************************************************************************************
 *                                          APB2 Peripherals Section                                         *
**************************************************************************************************************/
#define AFIO_BASE       (APB2_BASE + AFIO_OFFSET)       /* Fully available in 48-pin */
#define EXTI_BASE       (APB2_BASE + EXTI_OFFSET)       /* Fully available in 48-pin */

#define GPIOA_BASE      (APB2_BASE + GPIOA_OFFSET)      /* Fully available in 48-pin */
#define GPIOB_BASE      (APB2_BASE + GPIOB_OFFSET)      /* Fully available in 48-pin */
#define GPIOC_BASE      (APB2_BASE + GPIOC_OFFSET)      /* Fully available in 48-pin */
#define GPIOD_BASE      (APB2_BASE + GPIOD_OFFSET)      /* Not available in 48-pin */
#define GPIOE_BASE      (APB2_BASE + GPIOE_OFFSET)      /* Not available in 48-pin */

#define ADC1_BASE       (APB2_BASE + ADC1_OFFSET)       /* Fully available in 48-pin */
#define ADC2_BASE       (APB2_BASE + ADC2_OFFSET)       /* Fully available in 48-pin */
#define TIM1_BASE       (APB2_BASE + TIM1_OFFSET)       /* Fully available in 48-pin */
#define SPI1_BASE       (APB2_BASE + SPI1_OFFSET)       /* Fully available in 48-pin */

#define USART1_BASE     (APB2_BASE + USART1_OFFSET)     /* Fully available in 48-pin */


/*************************************************************************************************************
 *                                   APB1 Peripheral Offsets Section                                         *
**************************************************************************************************************/
#define TIM2_OFFSET       0x0000
#define TIM3_OFFSET       0x0400
#define TIM4_OFFSET       0x0800
#define WWDG_OFFSET       0x2C00
#define IWDG_OFFSET       0x3000
#define SPI2_OFFSET       0x3800
#define USART2_OFFSET     0x4400
#define USART3_OFFSET     0x4800
#define I2C1_OFFSET       0x5400
#define I2C2_OFFSET       0x5800
#define USB_OFFSET        0x5C00
#define CAN_OFFSET        0x6400   /* Not available in 48-pin */
#define BKP_OFFSET        0x6C00
#define PWR_OFFSET        0x7000
#define DAC_OFFSET        0x7400   /* Not available in 48-pin */

/*************************************************************************************************************
 *                                          APB1 Peripherals Section                                         *
**************************************************************************************************************/
#define TIM2_BASE   (APB1_BASE + TIM2_OFFSET)       /* Fully available in 48-pin */
#define TIM3_BASE   (APB1_BASE + TIM3_OFFSET)       /* Fully available in 48-pin */
#define TIM4_BASE   (APB1_BASE + TIM4_OFFSET)       /* Fully available in 48-pin */

#define WWDG_BASE   (APB1_BASE + WWDG_OFFSET)      /* Fully available in 48-pin */
#define IWDG_BASE   (APB1_BASE + IWDG_OFFSET)      /* Fully available in 48-pin */
#define SPI2_BASE   (APB1_BASE + SPI2_OFFSET)      /* Fully available in 48-pin */

#define USART2_BASE (APB1_BASE + USART2_OFFSET)    /* Fully available in 48-pin */
#define USART3_BASE (APB1_BASE + USART3_OFFSET)    /* Fully available in 48-pin */

#define I2C1_BASE   (APB1_BASE + I2C1_OFFSET)      /* Fully available in 48-pin */
#define I2C2_BASE   (APB1_BASE + I2C2_OFFSET)      /* Fully available in 48-pin */

#define USB_BASE    (APB1_BASE + USB_OFFSET)       /* Available (depends on package) */
#define CAN_BASE    (APB1_BASE + CAN_OFFSET)       /* Not available in 48-pin */
#define BKP_BASE    (APB1_BASE + BKP_OFFSET)       /* Fully available in 48-pin */
#define PWR_BASE    (APB1_BASE + PWR_OFFSET)       /* Fully available in 48-pin */
#define DAC_BASE    (APB1_BASE + DAC_OFFSET)       /* Not available in 48-pin */



#endif //end STM32F103C_H

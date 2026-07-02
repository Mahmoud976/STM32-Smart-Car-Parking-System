#ifndef RCC_H
#define RCC_H

#include "GPIO.h"
#include "MCU_Config.h"






#define HSI_RC_CLCK      (uint32_t)16000000
#define HSE_Clock		 (uint32_t)8000000



//********************user define **************************
typedef struct{
	volatile uint32_t CR ;
	volatile uint32_t CFGR ;
	volatile uint32_t CIR ;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;

}RCC_TypeDef;


#define RCC          ((RCC_TypeDef*) RCC_BASE  )

//Enable peripheral

#define RCC_AFIO_CLK_EN()   (RCC->APB2ENR |=1<<0)

#define RCC_GPIOA_CLK_EN()   (RCC->APB2ENR |=1<<2)
#define RCC_GPIOB_CLK_EN()   (RCC->APB2ENR |=1<<3)

#define RCC_GPIOC_CLK_EN()   (RCC->APB2ENR |=1<<4)
#define RCC_GPIOD_CLK_EN()   (RCC->APB2ENR |=1<<5)

#define RCC_GPIOE_CLK_EN()   (RCC->APB2ENR |=1<<6)


#define RCC_UART1_CLK_EN()   (RCC->APB2ENR |=1<<14)
#define RCC_UART2_CLK_EN()   (RCC->APB1ENR |=1<<17)
#define RCC_UART3_CLK_EN()   (RCC->APB1ENR |=1<<18)



#define RCC_SPI1_CLK_EN()   (RCC->APB2ENR |=1<<12)
#define RCC_SPI2_CLK_EN()   (RCC->APB1ENR |=1<<14)


#define RCC_I2C1_CLK_EN()   (RCC->APB1ENR |=1<<21)
#define RCC_I2C2_CLK_EN()   (RCC->APB1ENR |=1<<22)

//Reset peripheral

#define RCC_UART1_CLK_Reset()   (RCC->APB2RSTR |=1<<14)
#define RCC_UART2_CLK_Reset()   (RCC->APB1RSTR |=1<<17)
#define RCC_UART3_CLK_Reset()   (RCC->APB1RSTR |=1<<18)

#define RCC_SPI1_CLK_Reset()   (RCC->APB2RSTR |=1<<12)
#define RCC_SPI2_CLK_Reset()   (RCC->APB1RSTR |=1<<14)

#define RCC_I2C1_CLK_Reset()   (RCC->APB1RSTR |=1<<21)
#define RCC_I2C2_CLK_Reset()   (RCC->APB1RSTR |=1<<22)

uint32_t RCC_GetSYS_CLCKFreq(void);
uint32_t RCC_Get_HCLCKFreq(void);
uint32_t RCC_Get_PCLK1Freq(void);
uint32_t RCC_Get_PCLK2Freq(void);


#endif /*End RCC_H*/

#ifndef UART_H
#define UART_H

#include "GPIO.h"
#include "RCC.h"
/////////////////////////////////////////////////////
//              UART Registers
/////////////////////////////////////////////////////

typedef struct {
	volatile uint32_t SR;     // Status register
	volatile uint32_t DR;     // Data register
	volatile uint32_t BRR;    // Baud rate register
	volatile uint32_t CR1;    // Control register 1
	volatile uint32_t CR2;    // Control register 2
	volatile uint32_t CR3;    // Control register 3
	volatile uint32_t GTPR;   // Guard time & prescaler register
} UART_TypeDef_t;

/////////////////////////////////////////////////////
//              UART Instances
/////////////////////////////////////////////////////

#define UART1     ((UART_TypeDef_t *)USART1_BASE)
#define UART2     ((UART_TypeDef_t *)USART2_BASE)
#define UART3     ((UART_TypeDef_t *)USART3_BASE)

/////////////////////////////////////////////////////
//              UART Config Structure
/////////////////////////////////////////////////////

typedef struct {

	UART_TypeDef_t *UART;         // UART instance (UART1, UART2, ...)

	uint32_t Mode;                // TX/RX enable configuration (@ref UART_MODE_Define)
	uint32_t BaudRate;            // Communication baud rate (@ref UART_BAUD_RATE_Define)

	uint32_t Payload_Length;      // Data frame length (8 or 9 bits)(@ref UART_Payload_Length_define)
	uint32_t Parity;              // Parity configuration (@ref UART_Parity_define)
	uint32_t StopBits;            // Stop bits configuration (@ref UART_STOP_BITS_Define)
	uint32_t HW_FlowCTL;          // Hardware flow control (@ref UART_HW_FlowCTL_Define)

	uint32_t IRQ_Enable;          // Interrupt enable configuration (@ref UART_IRQ_Enable_define)

	void (*p_IRQ_CallBack)(void); // Callback function for IRQ handling

} UART_ConfigPin_t;

/////////////////////////////////////////////////////
//              Return Type
/////////////////////////////////////////////////////

typedef enum {
	UART_OK,
	UART_BUSY,
	UART_ERROR,
	INVALID_PTR,
	INVALID_LENGTH,
} UART_Status_t;

/////////////////////////////////////////////////////
//              UART Modes
/////////////////////////////////////////////////////

#define UART_Mode_RX         (uint32_t)(1<<2)
#define UART_Mode_TX         (uint32_t)(1<<3)
#define UART_Mode_TX_RX      (UART_Mode_RX | UART_Mode_TX)

/////////////////////////////////////////////////////
//              Baud Rates
/////////////////////////////////////////////////////

#define UART_BaudRate_2400       2400
#define UART_BaudRate_9600       9600
#define UART_BaudRate_19200      19200
#define UART_BaudRate_57600      57600
#define UART_BaudRate_115200     115200
#define UART_BaudRate_230400     230400
#define UART_BaudRate_460800     460800
#define UART_BaudRate_921600     921600
#define UART_BaudRate_2250000    2250000
#define UART_BaudRate_4500000    4500000

/////////////////////////////////////////////////////
//              Payload Length
/////////////////////////////////////////////////////

#define UART_Payload_Length_8B    (uint32_t)(0)
#define UART_Payload_Length_9B    (uint32_t) (1<<12)

/////////////////////////////////////////////////////
//              Parity
/////////////////////////////////////////////////////

#define UART_Parity_NONE         (uint32_t)(0)
#define UART_Parity_EVEN         (uint32_t)((1<<10))
#define UART_Parity_ODD          (uint32_t)((1<<10) | (1<<9))

/////////////////////////////////////////////////////
//              Stop Bits
/////////////////////////////////////////////////////

#define UART_StopBits_1          (uint32_t)(0)
#define UART_StopBits_Half       (uint32_t)(1<<12)
#define UART_StopBits_2          (uint32_t)(2<<12)
#define UART_StopBits_1_Half     (uint32_t)(3<<12)

/////////////////////////////////////////////////////
//              Hardware Flow Control
/////////////////////////////////////////////////////

#define UART_HW_FlowCTL_NONE     (uint32_t)(0)
#define UART_HW_FlowCTL_RTS      (uint32_t)(1<<8)
#define UART_HW_FlowCTL_CTS      (uint32_t)(1<<9)
#define UART_HW_FlowCTL_RTS_CTS  (UART_HW_FlowCTL_RTS | UART_HW_FlowCTL_CTS)

/////////////////////////////////////////////////////
//              Interrupt Enable
/////////////////////////////////////////////////////

#define UART_IRQ_Enable_NONE     (uint32_t)(0)
#define UART_IRQ_Enable_TXE      (uint32_t)(1<<7)
#define UART_IRQ_Enable_TC       (uint32_t)(1<<6)
#define UART_IRQ_Enable_RXNE     (uint32_t)(1<<5)
#define UART_IRQ_Enable_PE       (uint32_t)(1<<8)



////////////////////////////////////////////////////
// helper Macros
/////////////////////////////////////////////////////
#define UARTDIV(_PCLK_,_BAUD_)              	       (uint32_t)(_PCLK_/(16*_BAUD_))
#define UARTDIV_MUL100(_PCLK_,_BAUD_)                  (uint32_t)((25*_PCLK_)/(4*_BAUD_))
#define Mantissa(_PCLK_,_BAUD_)               		   (uint32_t)(UARTDIV(_PCLK_,_BAUD_))
#define Mantissa_MUL100(_PCLK_,_BAUD_)                 (uint32_t)(UARTDIV(_PCLK_,_BAUD_)*100)
#define DIV_Fraction(_PCLK_,_BAUD_)              	   (uint32_t)(((UARTDIV_MUL100(_PCLK_,_BAUD_) - Mantissa_MUL100(_PCLK_,_BAUD_))*16)/100)
#define UART_BRR_Reg(_PCLK_,_BAUD_)              	   (Mantissa(_PCLK_,_BAUD_)<<4)|( DIV_Fraction(_PCLK_,_BAUD_) &0xF )





/////////////////////////////////////////////////////
//              APIs
/////////////////////////////////////////////////////

UART_Status_t UART_Init(UART_ConfigPin_t *UART_CFG);
UART_Status_t UART_DeInit(UART_ConfigPin_t *UART_CFG);

UART_Status_t UART_Send_Data(UART_ConfigPin_t *UART_CFG, uint16_t *Ptr_Data);
UART_Status_t UART_Receive_Data(UART_ConfigPin_t *UART_CFG, uint16_t *Ptr_Data);

UART_Status_t UART_Wait_TC(UART_ConfigPin_t *UART_CFG);

#endif // UART_H

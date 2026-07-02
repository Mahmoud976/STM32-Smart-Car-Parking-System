#include"UART.h"



void (* Gp_UART_CALLBACK[3])(void);


UART_Status_t UART_Init(UART_ConfigPin_t *UART_CFG)
{
	if(NULL== UART_CFG ||NULL== UART_CFG->UART)
	{
		return INVALID_PTR;
	}
	else
	{
		//
		uint32_t PCLK=0;
		GPIO_Config_Pin_t pin_cfg;
		//Enable the clock for given UART
		if(UART_CFG->IRQ_Enable != UART_IRQ_Enable_NONE)
		{
			UART_CFG->UART->CR1 |=UART_CFG->IRQ_Enable;
			if(UART_CFG->UART==UART1)
			{
				RCC_UART1_CLK_EN();
				NVIC_UART1_Enable;
				PCLK=RCC_Get_PCLK2Freq();
				Gp_UART_CALLBACK[0]=UART_CFG->p_IRQ_CallBack;
	//recommended GPIO pins for USART
/*
USART pinout      Configuration                            GPIO configuration
USARTx_TX(1)      Full duplex                              Alternate function push-pull
                  Half duplex synchronous mode             Alternate function push-pull
USARTx_RX         Full duplex                              Input floating / Input pull-up
                  Half duplex synchronous mode             Not used. Can be used as a general IO
USARTx_CK         Synchronous mode                         Alternate function push-pull
USARTx_RTS        Hardware flow control                    Alternate function push-pull
USARTx_CTS        Hardware flow control                    Input floating/ Input pull-up
*/
				//UART1 in blue pill  >> TX,RX,CTS,RTS >> PA9 ,PA10,PA11,PA12
				//	PA9 >>TX
				pin_cfg.PORTx=PORTA;
				pin_cfg.Pin_Number=GPIO_PIN9;
				pin_cfg.mode=GPIO_MODE_Output_AF_PP;
				pin_cfg.Speed=GPIO_SPEED_10M;
				GPIO_InitPin(&pin_cfg);
				//PA10 >>RX
				pin_cfg.Pin_Number=GPIO_PIN10;
				pin_cfg.mode=GPIO_MODE_Input_FLO;
				GPIO_InitPin(&pin_cfg);
				if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_CTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
				{
					//PA11 >> CTS
					pin_cfg.Pin_Number=GPIO_PIN11;
					pin_cfg.mode=GPIO_MODE_Input_FLO;
					GPIO_InitPin(&pin_cfg);

				}
				else if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
				{
					//PA12 >> RTS
					pin_cfg.Pin_Number=GPIO_PIN12;
					pin_cfg.mode=GPIO_MODE_Output_AF_PP;
					pin_cfg.Speed=GPIO_SPEED_10M;
					GPIO_InitPin(&pin_cfg);

				}
			}
			else if(UART_CFG->UART==UART2)
			{
				RCC_UART2_CLK_EN();
				NVIC_UART2_Enable;
				PCLK=RCC_Get_PCLK1Freq();
				Gp_UART_CALLBACK[1]=UART_CFG->p_IRQ_CallBack;

				//UART1 in blue pill  >> TX,RX,CTS,RTS >> PA2 ,PA3,PA0,PA1
				//	PA2 >>TX
				pin_cfg.PORTx=PORTA;
				pin_cfg.Pin_Number=GPIO_PIN2;
				pin_cfg.mode=GPIO_MODE_Output_AF_PP;
				pin_cfg.Speed=GPIO_SPEED_10M;
				GPIO_InitPin(&pin_cfg);
				//PA3 >>RX
				pin_cfg.Pin_Number=GPIO_PIN3;
				pin_cfg.mode=GPIO_MODE_Input_FLO;
				GPIO_InitPin(&pin_cfg);
				if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_CTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
				{
					//PA0 >> CTS
					pin_cfg.Pin_Number=GPIO_PIN0;
					pin_cfg.mode=GPIO_MODE_Input_FLO;
					GPIO_InitPin(&pin_cfg);

				}
				else if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
				{
					//PA1 >> RTS
					pin_cfg.Pin_Number=GPIO_PIN1;
					pin_cfg.mode=GPIO_MODE_Output_AF_PP;
					pin_cfg.Speed=GPIO_SPEED_10M;
					GPIO_InitPin(&pin_cfg);

				}
			}
			else if(UART_CFG->UART==UART3)
			{
				RCC_UART3_CLK_EN();
				NVIC_UART3_Enable;
				PCLK=RCC_Get_PCLK1Freq();
				Gp_UART_CALLBACK[2]=UART_CFG->p_IRQ_CallBack;
				//UART1 in blue pill  >> TX,RX,CTS,RTS >> PB10 ,PB11,PB13,PB14
				//	PA9 >>TX
				pin_cfg.PORTx=PORTB;
				pin_cfg.Pin_Number=GPIO_PIN10;
				pin_cfg.mode=GPIO_MODE_Output_AF_PP;
				pin_cfg.Speed=GPIO_SPEED_10M;
				GPIO_InitPin(&pin_cfg);
				//PA10 >>RX
				pin_cfg.Pin_Number=GPIO_PIN11;
				pin_cfg.mode=GPIO_MODE_Input_FLO;
				GPIO_InitPin(&pin_cfg);
				if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_CTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
				{
					//PA11 >> CTS
					pin_cfg.Pin_Number=GPIO_PIN13;
					pin_cfg.mode=GPIO_MODE_Input_FLO;
					GPIO_InitPin(&pin_cfg);

				}
				else if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
				{
					//PA12 >> RTS
					pin_cfg.Pin_Number=GPIO_PIN14;
					pin_cfg.mode=GPIO_MODE_Output_AF_PP;
					pin_cfg.Speed=GPIO_SPEED_10M;
					GPIO_InitPin(&pin_cfg);

				}
			}

			else
			{
				return UART_ERROR;
			}
		}
		else
		{
			if(UART_CFG->UART==UART1)
			{
				RCC_UART1_CLK_EN();
				PCLK=RCC_Get_PCLK2Freq();
//recommended GPIO pins for USART
/*
USART pinout      Configuration                            GPIO configuration
USARTx_TX(1)      Full duplex                              Alternate function push-pull
			  Half duplex synchronous mode             Alternate function push-pull
USARTx_RX         Full duplex                              Input floating / Input pull-up
			  Half duplex synchronous mode             Not used. Can be used as a general IO
USARTx_CK         Synchronous mode                         Alternate function push-pull
USARTx_RTS        Hardware flow control                    Alternate function push-pull
USARTx_CTS        Hardware flow control                    Input floating/ Input pull-up
*/
			//UART1 in blue pill  >> TX,RX,CTS,RTS >> PA9 ,PA10,PA11,PA12
			//	PA9 >>TX
			pin_cfg.PORTx=PORTA;
			pin_cfg.Pin_Number=GPIO_PIN9;
			pin_cfg.mode=GPIO_MODE_Output_AF_PP;
			pin_cfg.Speed=GPIO_SPEED_10M;
			GPIO_InitPin(&pin_cfg);
			//PA10 >>RX
			pin_cfg.Pin_Number=GPIO_PIN10;
			pin_cfg.mode=GPIO_MODE_Input_FLO;
			GPIO_InitPin(&pin_cfg);
			if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_CTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
			{
				//PA11 >> CTS
				pin_cfg.Pin_Number=GPIO_PIN11;
				pin_cfg.mode=GPIO_MODE_Input_FLO;
				GPIO_InitPin(&pin_cfg);

			}
			else if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
			{
				//PA12 >> RTS
				pin_cfg.Pin_Number=GPIO_PIN12;
				pin_cfg.mode=GPIO_MODE_Output_AF_PP;
				pin_cfg.Speed=GPIO_SPEED_10M;
				GPIO_InitPin(&pin_cfg);

			}

			}
			else if(UART_CFG->UART==UART2)
			{
				RCC_UART2_CLK_EN();
				PCLK=RCC_Get_PCLK1Freq();
				//UART1 in blue pill  >> TX,RX,CTS,RTS >> PA2 ,PA3,PA0,PA1
				//	PA2 >>TX
				pin_cfg.PORTx=PORTA;
				pin_cfg.Pin_Number=GPIO_PIN2;
				pin_cfg.mode=GPIO_MODE_Output_AF_PP;
				pin_cfg.Speed=GPIO_SPEED_10M;
				GPIO_InitPin(&pin_cfg);
				//PA3 >>RX
				pin_cfg.Pin_Number=GPIO_PIN3;
				pin_cfg.mode=GPIO_MODE_Input_FLO;
				GPIO_InitPin(&pin_cfg);
				if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_CTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
				{
					//PA0 >> CTS
					pin_cfg.Pin_Number=GPIO_PIN0;
					pin_cfg.mode=GPIO_MODE_Input_FLO;
					GPIO_InitPin(&pin_cfg);

				}
				else if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
				{
					//PA1 >> RTS
					pin_cfg.Pin_Number=GPIO_PIN1;
					pin_cfg.mode=GPIO_MODE_Output_AF_PP;
					pin_cfg.Speed=GPIO_SPEED_10M;
					GPIO_InitPin(&pin_cfg);

				}
			}
			else if(UART_CFG->UART==UART3)
			{
				RCC_UART3_CLK_EN();
				PCLK=RCC_Get_PCLK1Freq();
				//UART3 in blue pill  >> TX,RX,CTS,RTS >> PB10 ,PB11,PB13,PB14
				//	PB10 >>TX
				pin_cfg.PORTx=PORTB;
				pin_cfg.Pin_Number=GPIO_PIN10;
				pin_cfg.mode=GPIO_MODE_Output_AF_PP;
				pin_cfg.Speed=GPIO_SPEED_10M;
				GPIO_InitPin(&pin_cfg);
				//PB11 >>RX
				pin_cfg.Pin_Number=GPIO_PIN11;
				pin_cfg.mode=GPIO_MODE_Input_FLO;
				GPIO_InitPin(&pin_cfg);
				if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_CTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
				{
					//PB13 >> CTS
					pin_cfg.Pin_Number=GPIO_PIN13;
					pin_cfg.mode=GPIO_MODE_Input_FLO;
					GPIO_InitPin(&pin_cfg);

				}
				else if(UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS || UART_CFG->HW_FlowCTL== UART_HW_FlowCTL_RTS_CTS)
				{
					//PB14 >> RTS
					pin_cfg.Pin_Number=GPIO_PIN14;
					pin_cfg.mode=GPIO_MODE_Output_AF_PP;
					pin_cfg.Speed=GPIO_SPEED_10M;
					GPIO_InitPin(&pin_cfg);

				}
			}

			else
			{
				return UART_ERROR;
			}

		}

		/*Bit 3 TE: Transmitter enable
		This bit enables the transmitter. It is set and cleared by software.
		0: Transmitter is disabled
		1: Transmitter is enabled
		Note: 1: During transmission, a “0” pulse on the TE bit (“0” followed by “1”) sends a preamble
		(idle line) after the current word, except in Smartcard mode.
		2: When TE is set there is a 1 bit-time delay before the transmission starts.
		Bit 2 RE: Receiver enable
		This bit enables the receiver. It is set and cleared by software.
		0: Receiver is disabled
		1: Receiver is enabled and begins searching for a start bit*/
		UART_CFG->UART->CR1 |=UART_CFG->Mode;
		/*Bit 12 M: Word length
		This bit determines the word length. It is set or cleared by software.
		0: 1 Start bit, 8 Data bits, n Stop bit
		1: 1 Start bit, 9 Data bits, n Stop bit
		Note: The M bit must not be modified during a data transfer (both transmission and reception)*/
		UART_CFG->UART->CR1 |=UART_CFG->Payload_Length;
		/*Bit 10 PCE: Parity control enable
		This bit selects the hardware parity control (generation and detection). When the parity
		control is enabled, the computed parity is inserted at the MSB position (9th bit if M=1; 8th bit
		if M=0) and parity is checked on the received data. This bit is set and cleared by software.
		Once it is set, PCE is active after the current byte (in reception and in transmission).
		0: Parity control disabled
		1: Parity control enabled
		Bit 9 PS: Parity selection
		This bit selects the odd or even parity when the parity generation/detection is enabled (PCE
		bit set). It is set and cleared by software. The parity will be selected after the current byte.
		0: Even parity
		1: Odd parity*/
		UART_CFG->UART->CR1 |= UART_CFG->Parity;
		/*Bits 13:12 STOP: STOP bits
		These bits are used for programming the stop bits.
		00: 1 Stop bit
		01: 0.5 Stop bit
		10: 2 Stop bits
		11: 1.5 Stop bit
		The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5.*/
		UART_CFG->UART->CR2 |= UART_CFG->StopBits;
		/*Bit 9 CTSE: CTS enable
		0: CTS hardware flow control disabled
		1: CTS mode enabled, data is only transmitted when the CTS input is asserted (tied to 0). If
		the CTS input is deasserted while a data is being transmitted, then the transmission is
		completed before stopping. If a data is written into the data register while CTS is deasserted,
		the transmission is postponed until CTS is asserted.
		This bit is not available for UART4 & UART5.*/
		UART_CFG->UART->CR3 |= UART_CFG->HW_FlowCTL;
		/*Bits 31:16 Reserved, forced by hardware to 0.
		Bits 15:4 DIV_Mantissa[11:0]: mantissa of USARTDIV
		These 12 bits define the mantissa of the USART Divider (USARTDIV)
		Bits 3:0 DIV_Fraction[3:0]: fraction of USARTDIV
		These 4 bits define the fraction of the USART Divider (USARTDIV) */
		UART_CFG->UART->BRR = UART_BRR_Reg(PCLK,UART_CFG->BaudRate);
		/*Enable Interrupt
		The USART interrupt events are connected to the same interrupt vector (see Figure 302).
		 During transmission: Transmission Complete, Clear to Send or Transmit Data register
		empty interrupt.
		 While receiving: Idle Line detection, Overrun error, Receive Data register not empty,
		Parity error, LIN break detection, Noise Flag (only in multi buffer communication) and
		Framing Error (only in multi buffer communication).
		These events generate an interrupt if the corresponding Enable Control Bit is set. */

		/*make it on line 20*/


		/*Bit 13 UE: USART enable
		When this bit is cleared the USART prescalers and outputs are stopped and the end of the
		current
		byte transfer in order to reduce power consumption. This bit is set and cleared by software.
		0: USART prescaler and outputs disabled
		1: USART enabled*/
		UART_CFG->UART->CR1 |=(1<<13);






	}
	return UART_OK;
}
UART_Status_t UART_DeInit(UART_ConfigPin_t *UART_CFG)
{
	if(NULL==UART_CFG || NULL ==UART_CFG->UART)
	{
		return INVALID_PTR;
	}
	else
	{
		if(UART_CFG->UART==UART1)
		{
			RCC_UART1_CLK_Reset();
			NVIC_UART1_Disable;

		}
		else if(UART_CFG->UART==UART2)
		{
			RCC_UART2_CLK_Reset();
			NVIC_UART2_Disable;
		}
		else if(UART_CFG->UART==UART3)
		{
			RCC_UART3_CLK_Reset();
			NVIC_UART3_Disable;
		}

		else
		{
			return UART_ERROR;
		}



	}
	return UART_OK;

}



UART_Status_t UART_Send_Data(UART_ConfigPin_t *UART_CFG, uint16_t *Ptr_Data)
{
	if(NULL==UART_CFG || NULL ==UART_CFG->UART)
	{
		return INVALID_PTR;
	}
	else
	{
		if(UART_CFG->IRQ_Enable ==UART_IRQ_Enable_NONE)
		{
			while(!(UART_CFG->UART->SR & 1<<7) );
		}
		/*
			Parity control (generation of parity bit in transmission and parity checking in reception) can
			be enabled by setting the PCE bit in the USART_CR1 register. Depending on the frame
			length defined by the M bit, the possible USART frame formats are as listed in Table 195.
			In case of wake up by an address mark, the MSB bit of the data is taken into account and
			not the parity bit
			Even parity: the parity bit is calculated to obtain an even number of “1s” inside the frame
			made of the 7 or 8 LSB bits (depending on whether M is equal to 0 or 1) and the parity bit.
			Ex: data=00110101; 4 bits set => parity bit will be 0 if even parity is selected (PS bit in
			USART_CR1 = 0).
			Odd parity: the parity bit is calculated to obtain an odd number of “1s” inside the frame
			made of the 7 or 8 LSB bits (depending on whether M is equal to 0 or 1) and the parity bit.
			Ex: data=00110101; 4 bits set => parity bit will be 1 if odd parity is selected (PS bit in
			USART_CR1 = 1).
			Transmission mode: If the PCE bit is set in USART_CR1, then the MSB bit of the data
			written in the data register is transmitted but is changed by the parity bit (even number of
			“1s” if even parity is selected (PS=0) or an odd number of “1s” if odd parity is selected
			(PS=1)). If the parity check fails, the PE flag is set in the USART_SR register and an
			interrupt is generated if PEIE is set in the USART_CR1 register
		 */
			if(UART_CFG->Payload_Length ==UART_Payload_Length_8B)
			{
				UART_CFG->UART->DR=	(*Ptr_Data & (uint8_t)0xFF );
			}
			else if (UART_CFG->Payload_Length ==UART_Payload_Length_9B)
			{
				UART_CFG->UART->DR=	(*Ptr_Data & (uint16_t)0x01FF );

			}
			else
			{
				return INVALID_LENGTH;
			}

		}


	return UART_OK;
}

UART_Status_t UART_Receive_Data(UART_ConfigPin_t *UART_CFG, uint16_t *Ptr_Data)
{
	if(NULL==UART_CFG || NULL ==UART_CFG->UART)
	{
		return INVALID_PTR;
	}
	else
	{
		if(UART_CFG->IRQ_Enable ==UART_IRQ_Enable_NONE)
		{
			while(!(UART_CFG->UART->SR & 1<<5) );
		}
		/*
			Parity control (generation of parity bit in transmission and parity checking in reception) can
			be enabled by setting the PCE bit in the USART_CR1 register. Depending on the frame
			length defined by the M bit, the possible USART frame formats are as listed in Table 195.
			In case of wake up by an address mark, the MSB bit of the data is taken into account and
			not the parity bit
			Even parity: the parity bit is calculated to obtain an even number of “1s” inside the frame
			made of the 7 or 8 LSB bits (depending on whether M is equal to 0 or 1) and the parity bit.
			Ex: data=00110101; 4 bits set => parity bit will be 0 if even parity is selected (PS bit in
			USART_CR1 = 0).
			Odd parity: the parity bit is calculated to obtain an odd number of “1s” inside the frame
			made of the 7 or 8 LSB bits (depending on whether M is equal to 0 or 1) and the parity bit.
			Ex: data=00110101; 4 bits set => parity bit will be 1 if odd parity is selected (PS bit in
			USART_CR1 = 1).
			Transmission mode: If the PCE bit is set in USART_CR1, then the MSB bit of the data
			written in the data register is transmitted but is changed by the parity bit (even number of
			“1s” if even parity is selected (PS=0) or an odd number of “1s” if odd parity is selected
			(PS=1)). If the parity check fails, the PE flag is set in the USART_SR register and an
			interrupt is generated if PEIE is set in the USART_CR1 register
		 */

			if(UART_CFG->Parity!=UART_Parity_NONE)
			{
				if(UART_CFG->Payload_Length ==UART_Payload_Length_8B)
				{
					*Ptr_Data = (UART_CFG->UART->DR & (uint8_t)0xFF);

				}
				else if (UART_CFG->Payload_Length ==UART_Payload_Length_9B)
				{
					*Ptr_Data =(uint16_t)(UART_CFG->UART->DR);

				}
				else
				{
					return INVALID_LENGTH;
				}
			}
			else
			{
				if(UART_CFG->Payload_Length ==UART_Payload_Length_8B)
				{
					*Ptr_Data = (UART_CFG->UART->DR & (uint8_t)0x7F);

				}
				else if (UART_CFG->Payload_Length ==UART_Payload_Length_9B)
				{
					*Ptr_Data =((UART_CFG->UART->DR)&(uint8_t)0xFF);

				}
				else
				{
					return INVALID_LENGTH;
				}

			}
		}

	return UART_OK;

}

UART_Status_t UART_Wait_TC(UART_ConfigPin_t *UART_CFG)
{

	while(!(UART_CFG->UART->SR & 1<<6) );
	return UART_OK;

}




void USART1_IRQHandler ()
{

	Gp_UART_CALLBACK[0]();
}

void USART2_IRQHandler ()
{
	Gp_UART_CALLBACK[1]();


}

void USART3_IRQHandler ()
{

	Gp_UART_CALLBACK[2]();

}


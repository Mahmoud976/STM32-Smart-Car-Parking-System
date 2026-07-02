#include "EXTI.h"


void (* GP_IRQ_CallBack[16])(void);

static void enable_NVIC(x)
{
	switch(x)
	{
	case 0:
		NVIC_EXTI0_Enable;
		break;
	case 1:
			NVIC_EXTI1_Enable;
			break;
	case 2:
			NVIC_EXTI2_Enable;
			break;
	case 3:
			NVIC_EXTI3_Enable;
			break;
	case 4:
			NVIC_EXTI4_Enable;
			break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
			NVIC_EXTI9_Enable;
			break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
			NVIC_EXTI10_Enable;
			break;
	}

}
static void disable_NVIC(x)
{
	switch(x)
	{
	case 0:
		NVIC_EXTI0_Disable;
		break;
	case 1:
			NVIC_EXTI1_Disable;
			break;
	case 2:
			NVIC_EXTI2_Disable;
			break;
	case 3:
			NVIC_EXTI3_Disable;
			break;
	case 4:
			NVIC_EXTI4_Disable;
			break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
			NVIC_EXTI9_Disable;
			break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
			NVIC_EXTI10_Disable;
			break;


	}

}
Std_ReturnType EXTI_GPIO_Init(const EXTI_PinConfig_t * EXTI_Config)
{
	if(NULL== EXTI_Config || NULL== EXTI_Config->P_IRQ_CallBack || NULL == EXTI_Config->EXTI_PIN.GPIO_Port)return E_NOT_OK;
	else
	{
		//Enable RCC for AFIO
		RCC_AFIO_CLK_EN();

		// configure GPIO pin to be FI (FLOTING_INPUT)
		GPIO_Config_Pin_t Pin_CFG;
		Pin_CFG.PORTx=EXTI_Config->EXTI_PIN.GPIO_Port;
		Pin_CFG.Pin_Number=EXTI_Config->EXTI_PIN.GPIO_PIN;
		Pin_CFG.mode=GPIO_MODE_Input_FLO;
		GPIO_InitPin(&Pin_CFG);
		//******************************************
		// Update AFIO Route between EXTI line With PORT A,B,C,D
		uint8_t AFOI_EXTICR_Index=EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number/4;
		uint8_t AFOI_EXTICR_Position=(EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number%4)*4;
		//clear four bit
		AFIO->EXTICR[AFOI_EXTICR_Index] &=~(0x0F<<AFOI_EXTICR_Position);
		AFIO->EXTICR[AFOI_EXTICR_Index] |=((EXTI_Mapping_With_GPIO(EXTI_Config->EXTI_PIN.GPIO_Port) & 0x0F) << AFOI_EXTICR_Position);
		//************************************************
		//Update rising or falling or both
		EXTI->RTSR &=~(1<<EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number);
		EXTI->FTSR &=~(1<<EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number);
		if(EXTI_Config->Trigger_Case==EXTI_Trigger_Rising)
		{
			EXTI->RTSR |=(1<<EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number);
		}
		else if(EXTI_Config->Trigger_Case==EXTI_Trigger_Falling)
		{
			EXTI->FTSR |=(1<<EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number);
		}
		else if (EXTI_Config->Trigger_Case==EXTI_Trigger_RisingAndFalling)
		{
			EXTI->RTSR |=(1<<EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number);
			EXTI->FTSR |=(1<<EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number);
		}
		else
		{
			return INVALID_TRIGGER;
			/*Nothing*/
		}
		//****************************************************************************
		//Call The CallBack Function
		GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number]=EXTI_Config->P_IRQ_CallBack;
		//*******************************************************************************************
		// enable EXTI
		if(EXTI_Config->IRQ_EN==EXTI_IRQ_Enable)
		{
			EXTI->IMR |=(1<<EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number);
		}
		else if(EXTI_Config->IRQ_EN== EXTI_IRQ_Disable)
		{
			EXTI->IMR &=~(1<<EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number);
		}
		else
		{
			return INVALID_IRQ_EN;
			/*Nothing*/
		}
		///********************************************************************************************
		//Enable NVIC
		if(EXTI_Config->IRQ_EN==EXTI_IRQ_Enable)
		{
			enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number);
		}
		else if(EXTI_Config->IRQ_EN== EXTI_IRQ_Disable)
		{
			disable_NVIC(EXTI_Config->EXTI_PIN.EXTI_Input_Line_Number);
		}
		else
		{
			return INVALID_NVIC_EN;
			/*Nothing*/
		}

	}
}
Std_ReturnType EXTI_GPIO_DeInit(void)
{

	EXTI->EMR=0x00000000;
	EXTI->IMR=0x00000000;
	EXTI->FTSR=0x00000000;
	EXTI->RTSR=0x00000000;
	EXTI->SWIER=0x00000000;
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR=0xFFFFFFFF;


	//disable NVIC
	 NVIC_EXTI0_Disable;
	 NVIC_EXTI1_Disable;
	 NVIC_EXTI2_Disable;
	 NVIC_EXTI3_Disable;
	 NVIC_EXTI4_Disable;
	 NVIC_EXTI5_Disable;
	 NVIC_EXTI3_Disable;
}
Std_ReturnType EXTI_GPIO_Update(const EXTI_PinConfig_t * EXTI_Config)
{
	EXTI_GPIO_Init(EXTI_Config);
}


void EXTI0_IRQHandler(void)
{
	//clear i=IRQ
	EXTI->PR=(1<<0);
	// call the CallBack Fun
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler(void)
{
	//clear i=IRQ
	EXTI->PR |=(1<<1);
	// call the CallBack Fun
	GP_IRQ_CallBack[1]();

}
void EXTI2_IRQHandler(void)
{
	//clear i=IRQ
	EXTI->PR |=(1<<2);
	// call the CallBack Fun
	GP_IRQ_CallBack[2]();
}
void EXTI3_IRQHandler(void)
{
	//clear i=IRQ
	EXTI->PR |=(1<<3);
	// call the CallBack Fun
	GP_IRQ_CallBack[3]();
}
void EXTI4_IRQHandler(void)
{
	//clear i=IRQ
	EXTI->PR |=(1<<4);
	// call the CallBack Fun
	GP_IRQ_CallBack[4]();
}
void EXTI9_5_IRQHandler (void)
{
	if(EXTI->PR &(1<<5)){EXTI->PR |=(1<<5);GP_IRQ_CallBack[5]();}
	if(EXTI->PR &(1<<6)){EXTI->PR |=(1<<6);GP_IRQ_CallBack[6]();}
	if(EXTI->PR &(1<<7)){EXTI->PR |=(1<<7);GP_IRQ_CallBack[7]();}
	if(EXTI->PR &(1<<8)){EXTI->PR |=(1<<8);GP_IRQ_CallBack[8]();}
	if(EXTI->PR &(1<<9)){EXTI->PR |=(1<<9);GP_IRQ_CallBack[9]();}
}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR &(1<<10)){EXTI->PR |=(1<<10);GP_IRQ_CallBack[10]();}
	if(EXTI->PR &(1<<11)){EXTI->PR |=(1<<11);GP_IRQ_CallBack[11]();}
	if(EXTI->PR &(1<<12)){EXTI->PR |=(1<<12);GP_IRQ_CallBack[12]();}
	if(EXTI->PR &(1<<13)){EXTI->PR |=(1<<13);GP_IRQ_CallBack[13]();}
	if(EXTI->PR &(1<<14)){EXTI->PR |=(1<<14);GP_IRQ_CallBack[14]();}
	if(EXTI->PR &(1<<15)){EXTI->PR |=(1<<15);GP_IRQ_CallBack[15]();}

}

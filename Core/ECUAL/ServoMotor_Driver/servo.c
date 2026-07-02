#include "servo.h"

//Direction of motion
#define UP   1
#define Down 2


//B8 SERVO1
void Servo1_Entry_Gate_Init(void)
{
	/*SERVO MOTOR 1*/
	GPIO_Config_Pin_t PinCinfg;
	PinCinfg.PORTx=PORTB;
	PinCinfg.Pin_Number=GPIO_PIN8;
	PinCinfg.mode = GPIO_MODE_Output_PP;
	PinCinfg.Speed =GPIO_SPEED_10M;
	GPIO_InitPin(&PinCinfg);
}

//Direction Up or Down
void Servo1_Entry_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo1 Enter gate up +90
		GPIO_WritePin(PORTB, GPIO_PIN8, 1);
		dus(500);
		GPIO_WritePin(PORTB, GPIO_PIN8, 0);
	}
	if(Direction==Down)
	{
		//servo1 Enter gate down -90
		GPIO_WritePin(PORTB, GPIO_PIN8, 1);
		dus(1488);
		GPIO_WritePin(PORTB, GPIO_PIN8, 0);
	}


}

//B9 SERVO2
void Servo2_Exit_Gate_Init(void)
{
	/*SERVO MOTOR 2*/
	GPIO_Config_Pin_t PinCinfg;
	PinCinfg.PORTx=PORTB;
	PinCinfg.Pin_Number=GPIO_PIN9;
	PinCinfg.mode = GPIO_MODE_Output_PP;
	PinCinfg.Speed =GPIO_SPEED_10M;
	GPIO_InitPin(&PinCinfg);
}

//Direction Up or Down
void Servo2_Exit_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo2 Exit gate up +90
		GPIO_Config_Pin_t PinCinfg;
		GPIO_WritePin(PORTB, GPIO_PIN9, 1);
		dus(500);
		GPIO_WritePin(PORTB, GPIO_PIN9, 0);
	}

	if(Direction == Down)
	{
		//servo2 Exit gate down -90
		GPIO_WritePin(PORTB, GPIO_PIN9, 1);
		dus(1488);
		GPIO_WritePin(PORTB, GPIO_PIN9, 0);
	}

}


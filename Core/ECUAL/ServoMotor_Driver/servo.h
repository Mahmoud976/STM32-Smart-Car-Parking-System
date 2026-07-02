#ifndef SERVO_H
#define SERVO_H


#include "GPIO.h"
#include "timer.h"

//Direction of motion
#define UP   1
#define Down 2

void Servo1_Entry_Gate_Init(void);
void Servo1_Entry_Gate(uint8_t Direction);

void Servo2_Exit_Gate_Init(void);
void Servo2_Exit_Gate(uint8_t Direction);





















#endif /*End SERVO_H*/

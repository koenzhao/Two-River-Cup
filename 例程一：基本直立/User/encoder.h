#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"

void TIM_Init(void);

void TIM4_Mode_Config(void);
void  TIM2_Mode_Config(void);
s16 Get_Speed_L(void);
s16 Get_Speed_R(void);
#endif 

#ifndef _USART_H_
#define _USART_H_
#include "stm32f10x.h"
void Usart_Configuration(void);			//配置Usart1 Tx->PA9 Rx->PA10
void USART1_Putc(uint8_t data);			//利用Usart1发送一个8位数据
void USART1_Puts(uint8_t * buffer);			//利用Uart4发送一个字符串
void NVIC_Configuration(void);
void USART1_Send_Enter(void);//利用串口1发送一换行符

extern int temp_data[3];
extern int temp_data11;
#endif

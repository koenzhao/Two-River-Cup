		
#ifndef __DELAY_H
#define __DELAY_H  
#include"stm32f10x.h"     
//使用SysTick的普通计数模式对延迟进行管理
//包括delay_us,delay_ms  
//正点原子@SCUT
//2008/12/13  
static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数
//初始化延迟函数
void delay_init(u8 SYSCLK); 
//延时Nms
//注意Nms的范围
//Nms<=0xffffff*8/SYSCLK
//对72M条件下,Nms<=1864 
void delay_ms(u16 nms);
//延时us           
void delay_us(u32 Nus);


#endif


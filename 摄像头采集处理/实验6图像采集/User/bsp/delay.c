#include"includes.h"
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;//选择内部时钟 HCLK/8
	fac_us=SYSCLK/8;      
	fac_ms=(u16)fac_us*1000;
}            
//延时Nms
//注意Nms的范围
//Nms<=0xffffff*8/SYSCLK
//对72M条件下,Nms<=1864 
void delay_ms(u16 nms)
{    
	SysTick->LOAD=(u32)nms*fac_ms; //时间加载  
	SysTick->CTRL|=0x01;               //开始倒数    
	while(!(SysTick->CTRL&(1<<16)));   //等待时间到达 
	SysTick->CTRL&=0XFFFFFFFE;         //关闭计数器
	SysTick->VAL=0X00000000;           //清空计数器     
}   
//延时us           
void delay_us(u32 Nus)
{ 
	SysTick->LOAD=Nus*fac_us;       //时间加载      
	SysTick->CTRL|=0x01;            //开始倒数    
	while(!(SysTick->CTRL&(1<<16)));//等待时间到达 
	SysTick->CTRL=0X00000000;       //关闭计数器
	SysTick->VAL=0X00000000;        //清空计数器     
}  

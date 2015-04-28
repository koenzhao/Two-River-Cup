#include "sys.h"
#include "System_init.h"
/**********************************************************
** 函数名:MYRCC_DeInit
** 功能描述: 把所有时钟寄存器复位	 
** 输入参数: 无
** 输出参数: 无
** 说明：不能在这里执行所有外设复位!否则至少引起串口不工作.
***********************************************************/   
void MYRCC_DeInit(void)
{										  					   
	RCC->APB1RSTR = 0x00000000;//复位结束			 
	RCC->APB2RSTR = 0x00000000; 
	  
  	RCC->AHBENR = 0x00000014;  //睡眠模式闪存和SRAM时钟使能.其他关闭.	  
  	RCC->APB2ENR = 0x00000000; //外设时钟关闭.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //使能内部高速时钟HSION	 															 
	RCC->CFGR &= 0xF8FF0000;   //复位SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //复位HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //复位HSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //复位PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR = 0x00000000;     //关闭所有中断
	/*配置向量表				  
#ifdef  VECT_TAB_RAM
	MY_NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else   
	MY_NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif*/
}
//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI
__asm void WFI_SET(void)
{
	WFI;    
}
/**********************************************************
** 函数名:Sys_Standby
** 功能描述: 进入待机模式	 
** 输入参数: 无
** 输出参数: 无
***********************************************************/    
void Sys_Standby(void)
{
	SCB->SCR|=1<<2;//使能SLEEPDEEP位 (SYS->CTRL)	   
  	RCC->APB1ENR|=1<<28;     //使能电源时钟	    
 	PWR->CSR|=1<<8;          //设置WKUP用于唤醒
	PWR->CR|=1<<2;           //清除Wake-up 标志
	PWR->CR|=1<<1;           //PDDS置位		  
	WFI_SET();				 //执行WFI指令		 
}	  
/**********************************************************
** 函数名: Sys_Soft_Reset
** 功能描述: 系统软件复位，要使用软件复位时调用此函数
** 输入参数: 无
** 输出参数: 无
***********************************************************/    
void Sys_Soft_Reset(void)
{   
	SCB->AIRCR =0X05FA0000|(u32)0x04;	  
} 
/**********************************************************
** 函数名: JTAG_Set
** 功能描述: JTAG模式设置,用于设置JTAG的模式
** 输入参数: mode
** 输出参数: 无
** 说明：mode:jtag,swd模式设置;00,全使能;01,使能SWD;10,全关闭;
		 要把JTAG口引脚作为普通GPIO口使用时，必须关闭JTAG
	注意：当关闭JTAG后将不能用JLINK下载程序，但可以用串口下载
		 用JTAG下载程序前，必须使能JTAG	
***********************************************************/
void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //开启辅助时钟	   
	AFIO->MAPR&=0XF8FFFFFF; //清除MAPR的[26:24]
	AFIO->MAPR|=temp;       //设置jtag模式
} 
/**********************************************************
** 函数名: Stm32_Clock_Init
** 功能描述: 系统时钟初始化函数
** 输入参数: PLL 系统时钟倍频数
** 输出参数: 无
** 说明：pll:选择的倍频数，从2开始，最大值为16	
***********************************************************/
void Stm32_Clock_Init(u8 PLL)
{
	unsigned char temp=0;   
	MYRCC_DeInit();		  //复位并配置向量表
	RCC->CR|=0x00010000;  //外部高速时钟使能HSEON
	while(!(RCC->CR>>17));//等待外部时钟就绪
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;//抵消2个单位
	RCC->CFGR|=PLL<<18;   //设置PLL值 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	FLASH->ACR|=0x32;	  //FLASH 2个延时周期

	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//等待PLL锁定
	RCC->CFGR|=0x00000002;//PLL作为系统时钟	 
	while(temp!=0x02)     //等待PLL作为系统时钟设置成功
	{   
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}    
}		    

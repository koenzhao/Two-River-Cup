#include"includes.h"

//外部中断配置
void EXTI_Config(uint8_t flag)	
{
	
	NVIC_InitTypeDef NVIC_InitStructure;/*声明嵌套中断结构体*/ 	
  	EXTI_InitTypeDef EXTI_InitStructure;/*声明中断配置结构体*/		
	GPIO_InitTypeDef GPIO_InitStructure;/*声明通用IO口配置结构体*/ 
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);/*开启GPIO与AFIO时钟*/
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	/*选择中断优先级第1组*/    
	/*外部中断0 */	
 	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;					
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	/*抢占优先级 1*/    
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	/*子优先级0*/ 		  
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	/*使能*/				 
  	NVIC_Init(&NVIC_InitStructure);	
	/*PA0*/
   	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	      
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	/*中断模式*/
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;/*下降沿触发*/	
	if(flag==EN)
	{
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;	
	} 
	else
	{
		EXTI_InitStructure.EXTI_LineCmd = DISABLE;	
	}
  	 

	EXTI_InitStructure.EXTI_Line = EXTI_Line0;//PA0 					  
  	EXTI_Init(&EXTI_InitStructure);


  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_4;	         	 	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   	 		//内部上拉输入
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


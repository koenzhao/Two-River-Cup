#include"includes.h"
/*
*******************************************************************************
*
*
*
*
*
*******************************************************************************
*/
//输入配置 函数,两个参数 GPIO 和GPIO_Pin
void IO_Input_Config(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	/*通用GPIO结构体声明*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
	/*开启时钟*/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);		
	GPIO_Init(GPIOx,&GPIO_InitStructure);

}
//输出配置 函数,两个参数 GPIO 和GPIO_Pin
void IO_Output_Config(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	/*通用GPIO结构体声明*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
	/*开启时钟*/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);		
	GPIO_Init(GPIOx,&GPIO_InitStructure);

}

#include"includes.h"
/*
************************************************************************
*  函数名称：
*  函数功能：
*  输入形参：  	
*  返回值：	
*
************************************************************************
*/
void LED_Init(void)
{
	/*通用GPIO结构体声明*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED_1_Clock,ENABLE);
	RCC_APB2PeriphClockCmd(LED_2_Clock,ENABLE);
	/*推挽输出*/	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	/*配置速度*/ 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	/*LED_1控制管脚号设置*/
	GPIO_InitStructure.GPIO_Pin=LED_1_Pin;
	/*根据设置初始化管脚分组*/	
	GPIO_Init(LED_1_Port,&GPIO_InitStructure);
	/*LED_2控制管脚号设置*/
	GPIO_InitStructure.GPIO_Pin=LED_2_Pin;
	/*根据设置初始化管脚分组*/	
	GPIO_Init(LED_2_Port,&GPIO_InitStructure);
	LED_1(OFF);
	LED_2(OFF);

}












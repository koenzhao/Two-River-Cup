#include"includes.h"
//按键初始化函数
void KEY_Init(void)
{
	/*通用GPIO结构体声明*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启KEY时钟*/
	RCC_APB2PeriphClockCmd(KEY_1_Clock,ENABLE);
	RCC_APB2PeriphClockCmd(KEY_2_Clock,ENABLE);
	/*浮空输入如果没有外部上拉电阻的话就必须将此项配制成上啦输入的形式 */	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	/*KEY_1控制管脚号设置*/
	GPIO_InitStructure.GPIO_Pin=KEY_1_Pin;
	/*根据设置初始化管脚分组*/	
	GPIO_Init(KEY_1_Port,&GPIO_InitStructure);
	/*KEY_2控制管脚号设置*/
	GPIO_InitStructure.GPIO_Pin=KEY_2_Pin;
	/*根据设置初始化管脚分组*/	
	GPIO_Init(KEY_2_Port,&GPIO_InitStructure);

}


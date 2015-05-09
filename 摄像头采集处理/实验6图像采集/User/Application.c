#include"includes.h"

	extern uint8_t PIC[R][C];
/*
------------------------------------------------------------------------
*  函数名称：void Application(void)
*  函数功能：当有图像数据可读时读取数据
*  输入形参：无 	
*  返回值：无	
*
------------------------------------------------------------------------
*/
void Application(void)
{
	while(1)/*在循环里开服务*/
	{ 		
		if(OV_State==Read)// 如果摄像头传感器可以度数据
		{
			//关闭中断
			EXTI_Config(DIS);
			//读取图片信息
			Read_Pic();
			
			//Send_Pic();

			//V_control(PIC);
			PIC_Process();
			//PIC_Process_2();

			//通过串口发送图片信息
			//Send_Pic();
			//Send_MidLine();
			USART_SendData(USART1,Curve_Value);
			
			//状态转移
			OV_State=Wait_Vsync1;
			//开启中断
			EXTI_Config(EN);
		}
	}
}
/*
-----------------------------------------------------------------------------
*  函数名称：void Board_Init(void)
*  函数功能：调用各个模块初始化接口函数
*  输入形参：无  	
*  返回值：无	
*
-----------------------------------------------------------------------------
*/
void Board_Init(void)
{
	/*选择外部8M晶振作为时钟源*/
	SystemInit();
	/*延时初始化*/
	delay_init(72);
	/*LED初始化*/
	LED_Init();
	/*串口初始化*/
	USART_Config();
	NVIC_Config();
	/*OV7670模块初始化*/	 	
	OV7670_Init();
}

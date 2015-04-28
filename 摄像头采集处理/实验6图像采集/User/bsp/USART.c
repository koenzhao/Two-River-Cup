#include"includes.h"
/*

*/
/*重新定义printf函数*/
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
PUTCHAR_PROTOTYPE
{
	USART_SendData(USART1, (uint8_t) ch);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//等待发送完成
  	return ch;
}
void USART_Config(void)
{
	/*数据类型声明*/
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* 第1步：打开GPIO和USART部件的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* 第2步：将USART Tx的GPIO配置为推挽复用模式 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 第3步：将USART Rx的GPIO配置为浮空输入模式
		由于CPU复位后，GPIO缺省都是浮空输入模式，因此下面这个步骤不是必须的
		但是，我还是建议加上便于阅读，并且防止其它地方修改了这个口线的设置参数
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 第4步：配置USART参数
	    - 波特率   = 115200 baud
	    - 数据长度 = 8 Bits
	    - 1个停止位
	    - 无校验
	    - 禁止硬件流控(即禁止RTS和CTS)
	    - 使能接收和发送
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 
	/* 第5步：使能 USART， 配置完毕 */
	USART_Cmd(USART1, ENABLE);
	/* 
		CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题：
	 	清发送完成标志，Transmission Complete flag 
	*/
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能中断

	USART_ClearFlag(USART1, USART_FLAG_TC); 	
	//printf("串口通信正常");

}
/*
**************************************************************************************
*函数名称：
*函数功能：
*输入形参：
*返回值:
**************************************************************************************
*/
void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
   	#ifdef VECT_TAB_RAM  
   	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
   	#else  
   	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
   	#endif 
   	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
   	NVIC_InitStructure.NVIC_IRQChannel= USART1_IRQn; //串口1中断配置   
   	/*抢占优先级*/
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	/*子优先级*/	     
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			 
	/*使能*/ 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 //使能
  	NVIC_Init(&NVIC_InitStructure);	 
}

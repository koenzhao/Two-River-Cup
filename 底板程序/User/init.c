#include "init.h"
#include "System_init.h"


u8 flag =0;

void system_init(void)
{
  	 Stm32_Clock_Init(9);			//系统时钟设置为外部晶振，9倍频
	 delay_init(72);				//系统SysTick初始化
	 Usart_Configuration();    		//串口初始化
	 TIM1_Configuration();			//定时器一初始化
	 GPIO_Configuration();		    //gpio初始化
	 Timer3_configuration();		//定时器三初始化
	 NVIC_Configuration();			//中断向量使能初始化
	 I2C_Congiguration();			//IIC初始化
	 MPU6050_Init();				//陀螺仪 加速度  初始化
	 TIM_Init();					//定时器编码器捕捉初始化
	 //对PWM初始化赋值
	 TIM3->CCR2 = 3600;	//电机设置这个寄存器 TIM3->CCR2 = 40;	//电机设置这个寄存器
     TIM3->CCR1 = 3600;	//电机设置这个寄存器 TIM3->CCR2 = 40;	//电机设置这个寄存器
     TIM3->CCR3 = 3600;
	 TIM3->CCR4 = 3600;
	 	
}

void TIM2_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     //定义一个定时器结构体变量

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定时器2
  
  TIM_TimeBaseStructure.TIM_Period = (10000 - 1);	  //计数100次，因为从0开始，所以减1
  TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);	  //时钟72分频，因为0不分频，所以减1
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;	      // 使用的采样频率之间的分频比例
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);	  //初始化定时器2

  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		  //清除定时器2中断标志位
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		  //打开定时器2中断

  TIM_Cmd(TIM2, ENABLE);                              //计数器使能，开始计数
}


void NVIC_Configuration(void)
{ 
   NVIC_InitTypeDef NVIC_InitStructure;
  
   NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

/********************注册定时器2中断处理函数***********************/
 
   NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
   NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;

   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

/******************注册串口1中断服务函数************************/
   NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//配置串口中断
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//占先式优先级设置为0
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //副优先级设置为0
   //NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;//中断禁止
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断开启
   NVIC_Init(&NVIC_InitStructure);//中断初始化
}

//保持原有配置								        
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;   
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
                        |RCC_APB2Periph_GPIOB
						|RCC_APB2Periph_GPIOC
						|RCC_APB2Periph_GPIOD,
						ENABLE);
 //****** TIM3 CH1  ch2 (PA6   PA7) ******************************
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;	
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;       //复用推完输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //****** TIM3 CH3,4  
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;	
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;       //复用推完输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8| GPIO_Pin_9;	
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;       //复用推完输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);


  //*******************寻线设置GPIO	 PC0
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; 	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  //*******************寻线设置GPIO  PC0
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1|GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; 	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  //拨码开关 PD2
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;//上拉输入模式 	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; 	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void Timer3_configuration(void)
{
  	//TIM_DeInit(TIM1);
  	TIM_TimeBaseInitTypeDef TIM1_TimeBaseStructure;
  	TIM_OCInitTypeDef TIM_OCInitStructure;
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
 
  	TIM1_TimeBaseStructure.TIM_Period = 7200-1;                              // 0xFFFF; 计数初值        
  	TIM1_TimeBaseStructure.TIM_Prescaler = 200;                          //0xF;   分频
  	TIM1_TimeBaseStructure.TIM_ClockDivision = 0x0;
  	TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        
  	TIM_TimeBaseInit(TIM3, &TIM1_TimeBaseStructure);                      // 高速总线时钟频率36MHz,周期=36M/(36000-1+1)/1000
  
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_Pulse = 3600;                                    //这里设置504   504/7119=7%,是舵机中间位置
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  	//初始化通道1-PA6
  	TIM_OC1Init(TIM3,&TIM_OCInitStructure);                     
  	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
 	//初始化通道2-PA7
  	TIM_OC2Init(TIM3,&TIM_OCInitStructure);                     
  	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  	//初始化通道3-PB0
  	TIM_OC3Init(TIM3,&TIM_OCInitStructure);                     
  	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
  	//初始化通道4-PB1
  	TIM_OC4Init(TIM3,&TIM_OCInitStructure);                     
  	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
  	TIM_ARRPreloadConfig(TIM3, ENABLE);                                        
  	//使能定时器3
  	TIM_Cmd(TIM3,ENABLE);
  
  	TIM_ARRPreloadConfig(TIM3, ENABLE);                                       
  	TIM_Cmd(TIM3,ENABLE);

}

void TIM1_Configuration(void)
{
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//定义一个定时器结构体变量
  	//TIM_TimeBaseInitTypeDef  TIM_BaseInitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  
  	TIM_TimeBaseStructure.TIM_Period = (10000 - 1);	//计数100次，因为从0开始，所以减1
  	TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);	//时钟72分频，因为0不分频，所以减1
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// 使用的采样频率之间的分频比例
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
  	//TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
  	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);	//初始化定时器1  
  	//清中断，以免一启用中断后立即产生中断
  	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  	//使能TIM1中断源
  	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  	//TIM1总开关：开启
 	TIM_Cmd(TIM1, ENABLE);
}

//定时器1中断
void TIM1_UP_IRQHandler(void)
{
 	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
 	{
   		TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update); //清中断

  		if ( 0==flag )
		{ 
	 		flag=1;  
		}  
 	}
}



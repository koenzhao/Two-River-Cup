#include"includes.h"

uint8_t PIC[R][C];
int Mid_Line[R]={0};
uint8_t PIC_Smooth[R][C]={0};
uint8_t PIC_Outline[R][C]={0};
uint8_t PIC_erzhihua[C];
//当前的状态
//下一步的状态
OV7670_State OV_State=Wait_Vsync1;
u16 TrueLine;
u8 datareadyflag=0;
int left,right,data_last,data;
int left_flag,right_flag;
int Threshold = 100;
uint8_t y[R]={80};
uint8_t Curve_Value = 0;


/*
	摄像头模块初始化

*/
void Data_Bus_Config(void)
{					  
	
	/*通用GPIO结构体声明*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	
	/*开启时钟*/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	GPIO_InitStructure.GPIO_Pin=D0_Pin;		
	GPIO_Init(D0_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D1_Pin;		
	GPIO_Init(D1_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D2_Pin;		
	GPIO_Init(D2_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D3_Pin;		
	GPIO_Init(D3_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D4_Pin;		
	GPIO_Init(D4_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D5_Pin;		
	GPIO_Init(D5_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D6_Pin;		
	GPIO_Init(D6_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D7_Pin;		
	GPIO_Init(D7_Port,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	//PWDN
	GPIO_InitStructure.GPIO_Pin=PWDN_Pin;
	GPIO_Init(PWDN_Port,&GPIO_InitStructure);
	//RESET
	GPIO_InitStructure.GPIO_Pin=RESET_Pin;
	GPIO_Init(RESET_Port,&GPIO_InitStructure);
	//FIFO_RCK
	GPIO_InitStructure.GPIO_Pin=FIFO_RCK_Pin;
	GPIO_Init(FIFO_RCK_Port,&GPIO_InitStructure);
	//FIFO_EO
	GPIO_InitStructure.GPIO_Pin=FIFO_OE_Pin;
	GPIO_Init(FIFO_OE_Port,&GPIO_InitStructure);
	//FIFO_RRST
	GPIO_InitStructure.GPIO_Pin=FIFO_RRST_Pin;
	GPIO_Init(FIFO_RRST_Port,&GPIO_InitStructure);
	//FIFO_WR
	GPIO_InitStructure.GPIO_Pin=FIFO_WR_Pin;
	GPIO_Init(FIFO_WR_Port,&GPIO_InitStructure);
	//FIFO_WRST
	GPIO_InitStructure.GPIO_Pin=FIFO_WRST_Pin;
	GPIO_Init(FIFO_WRST_Port,&GPIO_InitStructure);
	//STORBE
	GPIO_InitStructure.GPIO_Pin=STORBE_Pin;
	GPIO_Init(STORBE_Port,&GPIO_InitStructure);
}
void OV7670_Init(void)
{
	/*I2C控制引脚初始化*/
	I2C_Configuration();
	/*数据总线与控制总线初始化*/
	Data_Bus_Config();
	OV7670_Register_Init();
	/*以上初始化结束之后才可以初始化下面的*/
	EXTI_ClearITPendingBit(EXTI_Line0);
	EXTI_Config(EN);

	
}
void OV7670_Register_Init(void)
{
	PWDN_L;/*电源工作方式*/
	RESET_L;//寄存器复位
	delay_ms(20);
	RESET_H;

	//YUV格式
	I2C_WriteByte(0x12,0x80);
	I2C_WriteByte(0x3a, 0x04);
	I2C_WriteByte(0x40, 0xd0);
	I2C_WriteByte(0x12, 0x14);
	I2C_WriteByte(0x32, 0x80);
	I2C_WriteByte(0x17, 0x16);
	I2C_WriteByte(0x18, 0x04);
	I2C_WriteByte(0x19, 0x02);
	I2C_WriteByte(0x1a, 0x7b);
	I2C_WriteByte(0x03, 0x06);
	I2C_WriteByte(0x0c, 0x00);
	I2C_WriteByte(0x3e, 0x00);
	I2C_WriteByte(0x70, 0x3a);
	I2C_WriteByte(0x71, 0x35);
	I2C_WriteByte(0x72, 0x11);
	I2C_WriteByte(0x73, 0x00);
	I2C_WriteByte(0xa2, 0x02);
	I2C_WriteByte(0x11, 0x81); 	
	I2C_WriteByte(0x7a, 0x20);
	I2C_WriteByte(0x7b, 0x1c);
	I2C_WriteByte(0x7c, 0x28);
	I2C_WriteByte(0x7d, 0x3c);
	I2C_WriteByte(0x7e, 0x55);
	I2C_WriteByte(0x7f, 0x68);
	I2C_WriteByte(0x80, 0x76);
	I2C_WriteByte(0x81, 0x80);
	I2C_WriteByte(0x82, 0x88);
	I2C_WriteByte(0x83, 0x8f);
	I2C_WriteByte(0x84, 0x96);
	I2C_WriteByte(0x85, 0xa3);
	I2C_WriteByte(0x86, 0xaf);
	I2C_WriteByte(0x87, 0xc4);
	I2C_WriteByte(0x88, 0xd7);
	I2C_WriteByte(0x89, 0xe8);	
	I2C_WriteByte(0x13, 0xe0);
	I2C_WriteByte(0x00, 0x00); 	
	I2C_WriteByte(0x10, 0x00);
	I2C_WriteByte(0x0d, 0x00);
	I2C_WriteByte(0x14, 0x28);
	I2C_WriteByte(0xa5, 0x05);
	I2C_WriteByte(0xab, 0x07);
	I2C_WriteByte(0x24, 0x75);
	I2C_WriteByte(0x25, 0x63);
	I2C_WriteByte(0x26, 0xA5);
	I2C_WriteByte(0x9f, 0x78);
	I2C_WriteByte(0xa0, 0x68);
	I2C_WriteByte(0xa1, 0x03);
	I2C_WriteByte(0xa6, 0xdf);
	I2C_WriteByte(0xa7, 0xdf);
	I2C_WriteByte(0xa8, 0xf0);
	I2C_WriteByte(0xa9, 0x90);
	I2C_WriteByte(0xaa, 0x94);
	I2C_WriteByte(0x13, 0xe5);
	I2C_WriteByte(0x0e, 0x61);
	I2C_WriteByte(0x0f, 0x4b);
	I2C_WriteByte(0x16, 0x02);
	I2C_WriteByte(0x1e, 0x37);
	I2C_WriteByte(0x21, 0x02);
	I2C_WriteByte(0x22, 0x91);
	I2C_WriteByte(0x29, 0x07);
	I2C_WriteByte(0x33, 0x0b);
	I2C_WriteByte(0x35, 0x0b);
	I2C_WriteByte(0x37, 0x1d);
	I2C_WriteByte(0x38, 0x71);
	I2C_WriteByte(0x39, 0x2a);
	I2C_WriteByte(0x3c, 0x78);
	I2C_WriteByte(0x4d, 0x40);
	I2C_WriteByte(0x4e, 0x20);
	I2C_WriteByte(0x69, 0x00);
	I2C_WriteByte(0x6b, 0x60);
	I2C_WriteByte(0x74, 0x19);
	I2C_WriteByte(0x8d, 0x4f);
	I2C_WriteByte(0x8e, 0x00);
	I2C_WriteByte(0x8f, 0x00);
	I2C_WriteByte(0x90, 0x00);
	I2C_WriteByte(0x91, 0x00);
	I2C_WriteByte(0x92, 0x00);
	I2C_WriteByte(0x96, 0x00);
	I2C_WriteByte(0x9a, 0x80);
	I2C_WriteByte(0xb0, 0x84);
	I2C_WriteByte(0xb1, 0x0c);
	I2C_WriteByte(0xb2, 0x0e);
	I2C_WriteByte(0xb3, 0x82);
	I2C_WriteByte(0xb8, 0x0a); 
	I2C_WriteByte(0x43, 0x14);
	I2C_WriteByte(0x44, 0xf0);
	I2C_WriteByte(0x45, 0x34);
	I2C_WriteByte(0x46, 0x58);
	I2C_WriteByte(0x47, 0x28);
	I2C_WriteByte(0x48, 0x3a);
	I2C_WriteByte(0x59, 0x88);
	I2C_WriteByte(0x5a, 0x88);
	I2C_WriteByte(0x5b, 0x44);
	I2C_WriteByte(0x5c, 0x67);
	I2C_WriteByte(0x5d, 0x49);
	I2C_WriteByte(0x5e, 0x0e);
	I2C_WriteByte(0x64, 0x04);
	I2C_WriteByte(0x65, 0x20);
	I2C_WriteByte(0x66, 0x05);
	I2C_WriteByte(0x94, 0x04);
	I2C_WriteByte(0x95, 0x08);
	I2C_WriteByte(0x6c, 0x0a);
	I2C_WriteByte(0x6d, 0x55);
	I2C_WriteByte(0x6e, 0x11);
	I2C_WriteByte(0x6f, 0x9f);
	I2C_WriteByte(0x6a, 0x40);
	I2C_WriteByte(0x01, 0x40);
	I2C_WriteByte(0x02, 0x40);
	I2C_WriteByte(0x13, 0xe7);
	I2C_WriteByte(0x15, 0x00);  	
	I2C_WriteByte(0x4f, 0x80);
	I2C_WriteByte(0x50, 0x80);
	I2C_WriteByte(0x51, 0x00);
	I2C_WriteByte(0x52, 0x22);
	I2C_WriteByte(0x53, 0x5e);
	I2C_WriteByte(0x54, 0x80);
	I2C_WriteByte(0x58, 0x9e); 	
	I2C_WriteByte(0x41, 0x08);
	I2C_WriteByte(0x3f, 0x00);
	I2C_WriteByte(0x75, 0x05);
	I2C_WriteByte(0x76, 0xe1);
	I2C_WriteByte(0x4c, 0x00);
	I2C_WriteByte(0x77, 0x01);
	I2C_WriteByte(0x3d, 0xc2);	
	I2C_WriteByte(0x4b, 0x09);
	I2C_WriteByte(0xc9, 0x60);
	I2C_WriteByte(0x41, 0x38);
	I2C_WriteByte(0x56, 0x40);	
	I2C_WriteByte(0x34, 0x11);
	I2C_WriteByte(0x3b, 0x02); 								
	I2C_WriteByte(0xa4, 0x89);
	I2C_WriteByte(0x96, 0x00);
	I2C_WriteByte(0x97, 0x30);
	I2C_WriteByte(0x98, 0x20);
	I2C_WriteByte(0x99, 0x30);
	I2C_WriteByte(0x9a, 0x84);
	I2C_WriteByte(0x9b, 0x29);
	I2C_WriteByte(0x9c, 0x03);
	I2C_WriteByte(0x9d, 0x4c);
	I2C_WriteByte(0x9e, 0x3f);
	I2C_WriteByte(0x78, 0x04);	
	I2C_WriteByte(0x79, 0x01);
	I2C_WriteByte(0xc8, 0xf0);
	I2C_WriteByte(0x79, 0x0f);
	I2C_WriteByte(0xc8, 0x00);
	I2C_WriteByte(0x79, 0x10);
	I2C_WriteByte(0xc8, 0x7e);
	I2C_WriteByte(0x79, 0x0a);
	I2C_WriteByte(0xc8, 0x80);
	I2C_WriteByte(0x79, 0x0b);
	I2C_WriteByte(0xc8, 0x01);
	I2C_WriteByte(0x79, 0x0c);
	I2C_WriteByte(0xc8, 0x0f);
	I2C_WriteByte(0x79, 0x0d);
	I2C_WriteByte(0xc8, 0x20);
	I2C_WriteByte(0x79, 0x09);
	I2C_WriteByte(0xc8, 0x80);
	I2C_WriteByte(0x79, 0x02);
	I2C_WriteByte(0xc8, 0xc0);
	I2C_WriteByte(0x79, 0x03);
	I2C_WriteByte(0xc8, 0x40);
	I2C_WriteByte(0x79, 0x05);
	I2C_WriteByte(0xc8, 0x30);
	I2C_WriteByte(0x79, 0x26); 
	I2C_WriteByte(0x09, 0x00);	



	/*
	

//        {0x3a, 0x04},//RGB
        {0x12, 0x10},//QVGA  YUV
        {0x3a, 0x14},//使用固定UV输出
        {0x3d, 0x80},//使用固定UV输出
                                                        //0         0       :      Y U Y V （3a:14 3d:80）
                                                        //0         1       :      Y V Y U  (3a:14 3d:81)
                                                        //1         0       :      U Y V Y (3a:18 3d:80)
                                                        //1         1       :      V Y U Y (3a:18 3d:81)
        {0x67, 0x11},//固定U值，0x11，方便测试
        {0x68, 0xFF},//固定V值，0xFF，方便测试
//        {0x40, 0x10},//RGB565
        {0x40, 0xC0},//初始配置，YUV模式，这个寄存器必须设置，否则不好使
//        {0x12, 0x14},//QVGA  RGB，


	   I2C_WriteByte(0x12, 0x10);
	   I2C_WriteByte (0x3a, 0x14);
	   I2C_WriteByte (0x3d, 0x80);
	   I2C_WriteByte(0x67, 0x11);
	   I2C_WriteByte(0x68, 0xFF);
	   I2C_WriteByte(0x40, 0xC0);
	 

	*/
	   I2C_WriteByte(0x12, 0x10);
	   I2C_WriteByte(0x3a, 0x14);
	   I2C_WriteByte(0x3d, 0x80);
	   I2C_WriteByte(0x67, 0x11);
	   I2C_WriteByte(0x68, 0xFF);
	   I2C_WriteByte(0x40, 0xC0);

	   LED_1(ON);
	   LED_2(ON);
}

void Read_Pic(void)
{
	u16 i,j;
	u16 t1,t2;
	//以下代码完成，图像的采集，并显示在tft上				 							
	for(i = 0; i < 240; i ++)	 
	{	
		 if(i%6==1)
		{
			for(j = 0; j < 320; j ++)
			{
				if (j<160)
				{
				    //获得一个Y分量的过程										
					FIFO_RCK_L;					
					FIFO_RCK_H;		 				
					t1=(0x00ff&GPIOC->IDR);	 				
					FIFO_RCK_L;						
					FIFO_RCK_H;						
					t2=(0x00ff&GPIOC->IDR);
	
					//跳过一个点，隔开取点
				    FIFO_RCK_L;					
					FIFO_RCK_H;		 				
					t2=(0x00ff&GPIOC->IDR);	 				
					FIFO_RCK_L;						
					FIFO_RCK_H;						
					t2=(0x00ff&GPIOC->IDR);
					PIC[TrueLine][j]=t1; 
					}
	    	}
		  TrueLine++;
		}
		else
		{	  //否则跳过这些像素点
	      	for(j = 0; j < 320; j ++)
			{
				FIFO_RCK_L;					
				FIFO_RCK_H;		 				
				t2=(0x00ff&GPIOC->IDR);	 				
				FIFO_RCK_L;						
				FIFO_RCK_H;						
				t2=(0x00ff&GPIOC->IDR);
			}
		}
	}
	FIFO_OE_H;		 	  //禁止FIFO输出
}
/*************************************************************
函数名：void Send_Pic(void)
功能：通过串口发送图片
输入：无
输出：无
*************************************************************/
void Send_Pic(void)
{
	u8 i;
	u8 j;
	USART_ClearFlag(USART1, USART_FLAG_TC); 
	USART_SendData(USART1,0x00);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	USART_SendData(USART1,0xff);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	USART_SendData(USART1,0x01);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	USART_SendData(USART1,0x00);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	
	for(i=0;i<40;i++)
	{
		for(j=0;j<160;j++)
		{
			USART_ClearFlag(USART1, USART_FLAG_TC); 
		  	USART_SendData(USART1,PIC[i][j]);
			//USART_SendData(USART1,PIC_Smooth[i][j]);
			//USART_SendData(USART1,PIC_Outline[i][j]);
  			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		}
	}
}

/*********************************************************************
*图像处理函数 
*从第40行向上处理，因为识别双线，中间向两边查找黑白跳变沿找到黑
*白跳变沿进行两边的记录。这时候有四种情况，1）两条线都找到。2）
*只有左边线。3）只有右边线。4）两边线都没有。
*********************************************************************/
/*void V_control(uint8_t (*p)[160])
{
	int hang,lie;
  	for(hang=39;hang>0;hang--)
  	{
    	if(hang == 39)
		{
    		for(lie=0;lie<160;lie++)
			{
	  			if(*(*(p+hang)+lie)<100)
	  			{
	    			PIC_erzhihua[lie]=0x01; 
	  			}
	  			else
	  			{	
	    			PIC_erzhihua[lie]=0x00;
	  			}
			} 
    		for(lie=0;lie<159;lie++)
			{
				if((PIC_erzhihua[lie]>PIC_erzhihua[lie-1])&&(PIC_erzhihua[lie]>PIC_erzhihua[lie-2])
	     			&&(PIC_erzhihua[lie+1]>PIC_erzhihua[lie-1])&&(PIC_erzhihua[lie+1]>PIC_erzhihua[lie-2]))
				{
					left = lie;
		   			left_flag = 1;
		   			break;		    
		 		}
	    		left_flag = 0; 
			}
			for(lie=159;lie>0;lie--)
			{
	  	 		if((PIC_erzhihua[lie]>PIC_erzhihua[lie+1])&&(PIC_erzhihua[lie]>PIC_erzhihua[lie+2])
	     			&&(PIC_erzhihua[lie-1]>PIC_erzhihua[lie+1])&&(PIC_erzhihua[lie-1]>PIC_erzhihua[lie+2]))
		 		{
		   			right = lie;
		   			right_flag = 1;
		  			break;		    
		 		}
	    		right_flag = 0; 
			}
			//两条线全部找到 计算两条线的中间值
			if(( right_flag == 1 )&&( left_flag == 1 ))
			{
	 			data = (left+right)/2;
	  			data_last =  data;
	  			right_flag = 0;
	  			left_flag = 0;
			}
			//
			else 
			{
	 			data = data_last; 
			}
			left = 0;
			right = 0;
    		for(lie=0;lie<160;lie++)
			{
	  			PIC_erzhihua[lie]=0x00;
			} 
			USART_SendData(USART1,data);
  			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	 
		}
	}    
}*/

/****************************************************************************
函数名：PIC_Process()
功能：二值化，滤波
备注：2015年4月26日赵冬阳添加
****************************************************************************/

void PIC_Process()
{
	int end = R-5;
	int start = end-7;
	TwoValue_Process();
	Get_MidLine();
	SmoothMid();
   	for (;start>=4;start -= 6, end -= 6)
	{
		Least_Squares(start, end);
	}
	Curve_Value = Curve();
	Display_MidLine();
}

/****************************************************************************
函数名：void TwoValue_Process(void)
功能：二值化，滤波
备注：2015年4月26日添加
****************************************************************************/
void TwoValue_Process(void)
{
	int row=0;
	int col=0;
	Threshold = Get_GrayValue(); //获得计算后的灰度阈值
	for (row = R-1; row>=0; row--)//处理第row行
	{
		for (col = 0; col<C; col++)//二值化
		{
			if(PIC[row][col] >= Threshold)
			{
				PIC[row][col] = white;
			}
			else 
			{
				PIC[row][col] = black;
			}
		}
		for(col=1; col<C-1; col++)//滤波
		{
			if( PIC[row][col-1]==white && PIC[row][col]==black && PIC[row][col+1]==white )
			{
				PIC[row][col]=white;
			}
			else if( PIC[row][col-1]==black && PIC[row][col]==white && PIC[row][col+1]==black )
			{
				PIC[row][col]=black;
			}
		}
	}
}

/*********************************************************************
函数名：显示中线黑线
功能：在PIC图像中显示中线黑线
输入：无
输出：无
备注：2015年4月28日赵冬阳添加
*********************************************************************/
void Display_MidLine()
{
	int row;
	for (row=R-1;row>=0;row--)
	{
		PIC[row][Mid_Line[row]]=black;
	}
}



/*********************************************************************
函数名：void Get_MidLine()
功能：获取图像中心线
输出：无
输出：无
备注：2015年4月28日赵冬阳添加
*********************************************************************/
void Get_MidLine()
{
	int row = 0;
	int col = 0;
	int Left_Border = 0;
	int Right_Border = 0;
	short int Left_Find = 0;
	short int Right_Find = 0;

	for(row=R-1;row>=0;row--)
	{
		if(row>=30)//前10行处理
		{
			for(col=39;col>=0;col--)
			{
				if((PIC[row][col]==black) && !Left_Find)
				{
					Left_Border = col;
					if(PIC[row][col-1]==black)
					{
						Left_Find = 1;
					}
				}
				if(PIC[row][C-1-col]==black && !Right_Find)
				{
					Right_Border = (C-1-col);
					if(PIC[row][C-2-col]==black)
					{
							Right_Find = 1;
					}
				}
				if(Left_Find && Right_Find)
					break;
			}
			if(Left_Find == 0)
				Left_Border = 0;
			if(Right_Find == 0)
				Right_Border = 160;
		}
		else	//后30行处理
		{
			for(col=79;col>=0;col--)
			{
				if((PIC[row][col]==black) && !Left_Find)
				{
					Left_Border = col;
					if(PIC[row][col-1]==black)
					{
						Left_Find = 1;
					}
				}
				if(PIC[row][C-1-col]==black && !Right_Find)
				{
					Right_Border = (C-1-col);
					if(PIC[row][C-1-col-1]==black)
					{
						 Right_Find = 1;
					}
				}
				if(Left_Find && Right_Find)
					break;
			}
			if(Left_Find == 0)
				Left_Border = 0;
			if(Right_Find == 0)
				Right_Border = 160;
		}
		Mid_Line[row]=(Left_Border+Right_Border)/2;
		Left_Find = 0;
		Right_Find = 0;
	}
}



/**********************************************************************
函数名：void PIC_Process_2(void)
输入：无
输出：无
功能：处理图像，包括图像平滑，锐化，二值化
备注：2015年4月27日赵冬阳添加
**********************************************************************/
/*void PIC_Process_2(void)
{
	  int i = 0;
	  int j = 0;
	  int row = 0;
	  int col = 0;
	  long int sum = 0;
	  
	  int templates[3][3]={
	  						{1,1,1},
	  						{1,1,1},
	  						{1,1,1}
	  };

	  for(row=1;row<=R-2;row++)
	  {
	  	for(col=1;col<=C-2;col++)
		{
			for(i=-1;i<2;i++)
			{
				for (j=-1;j<2;j++)
				{
					 //图像平滑
					 sum += PIC[row+i][col+j]*templates[i+1][j+1];
				}
			}
			sum = sum/9;
			if(sum>255)
				sum = 255;
			if(sum<0)
				sum = 0;
			PIC_Smooth[row][col] = sum;//获取平滑后的图像
			//PIC[row][col] = sum;
			
			sum = 0;
		}
	  }
	  //图像锐化算法
	  for(row=0;row<R;row++)
	  {
	  	for(col=0;col<C;col++)
		{
			//PIC_Outline[row][col] = PIC[row][col] + (PIC[row][col]-PIC_Smooth[row][col]); //锐化图=原图 +（原图-平滑图）
			PIC[row][col] = PIC[row][col] + (PIC[row][col]-PIC_Smooth[row][col]);
		}
	  }
	  for (row=0;row<R;row++)
	  {
	  	for(col=0;col<C;col++)
		{
			if(PIC[row][col]<=Threshold)
			{
				PIC[row][col]=black;
			}
			else
			{
				PIC[row][col]=white;
			}
		}
	  }
}  */


/***************************************************
函数名：int8_t Abs8(int8_t a)
功能：求8位数据的绝对值
输入：a
输出：temp
备注：2015年5月3日添加
***************************************************/
int8_t Abs8(int8_t a)
{
	int8_t temp;
	temp=a;
	if (temp<=0)
	{
		temp = -temp;
	}
  	return temp;
}


/**********************************************************************
函数名：SmoothMid(void)
功能：平滑曲线
输入：无
输出：无
备注：2015年5月3日添加
**********************************************************************/
void SmoothMid(void)
{
	uint8_t  i;
	uint8_t temp=0;
	uint8_t temp1=0;
 	for (i=R-1;i>3;i--) 
	{
		if(Mid_Line[i] != Mid_Line[i-1])
		{
			temp = Abs8(Mid_Line[i-1]-Mid_Line[i]);
		}
		

		if(Mid_Line[i] != Mid_Line[i+1])
		{
		 	temp1 = Abs8(Mid_Line[i+1]-Mid_Line[i]);
		}
		
		if (((temp>5)&&(temp1>5)) || ((Mid_Line[i-1]<Mid_Line[i])&&(Mid_Line[i+1]<Mid_Line[i])) || ((Mid_Line[i-1]>Mid_Line[i])&&(Mid_Line[i+1]>Mid_Line[i])))	 
		{
			Mid_Line[i]=(Mid_Line[i-1]+Mid_Line[i+1])*0.5;
		}
	}
}


/****************************************************************************
函数名：Least_Squares(int start, int end)
功能：通过最小二乘法平滑中心线
输入：start,end
输出：无
备注：2015年5月3日添加
*****************************************************************************/
void Least_Squares(int start, int end)
{
	uint8_t i=0;
	double A=0, B=0, D=0, F=0, Delta;
	
	double a,b;
	int t;

	for (i=end;i>=start;i--)
	{
		//BlackLineData[i]=y[i];
		y[i]=Mid_Line[i];
	}

	
	for (i=start;i<=end;i++)
	{
		A += i*i; //pow(i,2)
		B += i;
 		D += i*y[i];
		F += y[i];
	}
	
	t = end-start+1;
	Delta = A*t-B*B;
	a = (D*t-B*F)/Delta;
	b = (A*F-D*B)/Delta;
	
	
	for (i=start;i<=end;i++)
	{
		Mid_Line[i]=(a*i+b);
	}
	
	A=0;
	B=0;
	D=0;
	F=0;
	
	//y[]={0};
}
/*****************************************************************
函数名：Curve(void)
功能：计算曲率半径
输入：无
输出：无
备注：s8 Curve(void)
*****************************************************************/
uint8_t Curve(void)
{
	int8_t i;
	uint8_t sum_MidLine=0;
	uint8_t average_MidLine=0;
	uint8_t curve_MidLine=0;
	uint8_t differ_MidLine=0;
	for(i=25, sum_MidLine=0; i>=10; i--)
	{
		sum_MidLine+=Mid_Line[i];
	}
	average_MidLine = sum_MidLine / 16;
	for(i=25, curve_MidLine=0;i>=10;i--)
	{
		differ_MidLine = Abs8(Mid_Line[i]-average_MidLine);
		curve_MidLine += differ_MidLine;
	}
	return curve_MidLine;
}

/*******************************************************
函数名：int Get_GrayValue()
输入：无；
输出：灰度阈值
说明：最优阈值灰度分割算法
备注：2015年4月27日赵冬阳添加
*******************************************************/
int Get_GrayValue()
{
	 int row,col;
	 int Obj_Count=0;//目标阈值个数计数
	 int Bla_Count=0;//背景阈值个数计数
	 uint32_t Obj_GrayValue=0;//目标灰度总和 
	 uint32_t Bla_GrayValue=0;//背景灰度总和
	 int Min_GrayValue = 127;//最小阈值
	 int Max_GrayValue = 127;//最大阈值
	 int Init_GrayValue = 0;//最初灰度阈值
	 int Init_GrayValue_Last = 0;//记录上一次计算的最初灰度阈值
	 int Mean_GrayValue_1 = 0;//目标灰度平均阈值
	 int Mean_GrayValue_2 = 0;//背景灰度平均阈值
	 
	 /*扫描整个图片，记录最小灰度阈值和最大灰度阈值*/
	 for(row=0;row<R;row++)
	 {
	 	for(col=0;col<C;col++)
		{
			if(Min_GrayValue>PIC[row][col])
				Min_GrayValue = PIC[row][col];//更新最小灰度阈值
			if(Max_GrayValue<PIC[row][col])
				Max_GrayValue = PIC[row][col];//更新最大灰度阈值
		}
	 }
	 Init_GrayValue = (Min_GrayValue+Max_GrayValue)/2;//得到最初的灰度阈值
	 
	 /*计算灰度阈值，直到循环计算出的灰度阈值与上一次计算的灰度阈值相等*/
	 do
	 {
	 	Init_GrayValue_Last = Init_GrayValue;
		Obj_Count=0;
		Bla_Count=0;
		Obj_GrayValue=0;
		Bla_GrayValue=0;
	 	for(row=0;row<R;row++)
	 	{
	 		for(col=0;col<C;col++)
			{
				if((Min_GrayValue<PIC[row][col])&&(PIC[row][col]<Init_GrayValue))//从最小灰度阈值到最初灰度阈值
				{
					Obj_GrayValue += PIC[row][col];//此范围内灰度求和
					Obj_Count++;//计数	
				}
				if((Init_GrayValue<PIC[row][col])&&(PIC[row][col]<Max_GrayValue))//从最初灰度阈值到最大灰度阈值
				{
					Bla_GrayValue += PIC[row][col];//此范围内灰度求和
					Bla_Count++;//计数
				}	
			}	
	 	}
	 	Mean_GrayValue_1 = Obj_GrayValue/Obj_Count;//计算目标灰度平均阈值
	 	Mean_GrayValue_2 = Bla_GrayValue/Bla_Count;//计数背景灰度平均阈值
	 	Init_GrayValue = (Mean_GrayValue_1+Mean_GrayValue_2)/2;//计算平均灰度阈值
	 }while(Init_GrayValue_Last!=Init_GrayValue);//直到上一次平均灰度阈值和最新计算出来的平均灰度阈值相等为止
	 
	 /*返回灰度阈值*/
	 return Init_GrayValue;
}

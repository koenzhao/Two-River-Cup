#include"includes.h"

/*
**************************************************************************************
*	函数名称：void I2C_Configuration(void)
*	函数功能：I2C接口配置函数
*	输入形参：无
*	返回值： 无
*	函数说明：
**************************************************************************************
*/	
void I2C_Configuration(void)
{
	GPIO_InitTypeDef I2C;
	/*开漏输出，速度50MHZ*/	
	I2C.GPIO_Speed=GPIO_Speed_50MHz;
	/*必须设置成开漏模式*/
	I2C.GPIO_Mode=GPIO_Mode_Out_OD;
	//I2C SDA 
	RCC_APB2PeriphClockCmd(SDA_Clock,ENABLE);
	I2C.GPIO_Pin=SDA_Pin;
	GPIO_Init(SDA_Port,&I2C);
	//I2C SCL
	RCC_APB2PeriphClockCmd(SCL_Clock,ENABLE);
	I2C.GPIO_Pin=SCL_Pin;
	GPIO_Init(SCL_Port,&I2C);
	SCL_H;
	SDA_H;
}
/*
*********************************************************************************************************
*	函数名称：I2C_Start()
*	函数功能：I2C开始序列
*	输入形参：
*	返回值：
*	函数说明：当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号
*********************************************************************************************************
*/ 

void I2C_Start(void)
{
   	SDA_H;
	delay_us(100);
	SCL_H;//延时5us 等待电平稳定
	delay_us(100);
	SDA_L;
	delay_us(100);
	SCL_L;	
	delay_us(100);
	
}

/*
*********************************************************************************************************
*	函数名称：I2C_Stop(void)
*	函数功能：发送I2C总线停止信号
*	输入形参：无
*	返回值：  无
*	函数说明：当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号
*********************************************************************************************************
*/ 

void I2C_Stop(void)
{
	SDA_L;
	delay_us(100);
	SCL_H;
	delay_us(100);
	SDA_H; 
	delay_us(100);

}

/*
*********************************************************************************************************
*	函 数 名: i2c_SendByte
*	功能说明: CPU向I2C总线设备发送8bit数据
*	形    参：_ucByte ： 等待发送的字节
*	返 回 值: 无
*********************************************************************************************************
*/

void I2C_SendByte(uint8_t _ucByte)
{
	uint8_t i;
	SCL_L;//发送之前先拉低 
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			SDA_H;
		}
		else
		{
			SDA_L;
		}
		_ucByte <<= 1;	/* 左移一个bit */
		delay_us(100);
		SCL_H;//高电平采集数据
		delay_us(100);
		SCL_L;
		delay_us(100);
		if (i == 7)
		{
			 SDA_H; // 释放总线
		}	
	}
}

/*
*********************************************************************************************************
*	函 数 名: i2c_ReadByte
*	功能说明: CPU从I2C总线设备读取8bit数据
*	形    参：无
*	返 回 值: 读到的数据
*********************************************************************************************************
*/

uint8_t I2C_ReadByte(void)
{
	uint8_t i;
	uint8_t value;
	/* 读到第1个bit为数据的bit7 */
	value = 0;
	SCL_L;

	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		SCL_H;
		delay_us(100);
		if (I2C_SDA_READ())
		{
			value++;
		}
		else
		{
		
		}
		SCL_L;
		delay_us(100);
	}
	return value;
}

/*
*********************************************************************************************************
*	函 数 名: i2c_WaitAck
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参：无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
*********************************************************************************************************
*/

uint8_t I2C_WaitAck(void)
{
	uint8_t re=0;
	SCL_L;
	SDA_H;	/* CPU释放SDA总线 */	
	SCL_H;	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	delay_us(100);
	if(I2C_SDA_READ())
	{
	 	re=1;	 	
	}
	else
	{
		re=0;
	}  
	SCL_L;
	delay_us(100);
	return re;
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

void I2C_Ack(void)
{
	/* CPU驱动SDA = 0 */
	SCL_L;
	delay_us(10);
	SDA_L;
	delay_us(10);	
	/* CPU产生1个时钟 */
	SCL_H;
	delay_us(10);	
	SCL_L;
	delay_us(10);
}

/*
*********************************************************************************************************
*	函 数 名: i2c_NAck
*	功能说明: CPU产生1个NACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void I2C_NAck(void)
{
	/* CPU驱动SDA = 1 */
	SDA_H;
	delay_us(100);	
	/* CPU产生1个时钟 */
	SCL_H;
	delay_us(100);	
	SCL_L;
	delay_us(100);
	SDA_H;
	delay_us(100);

}
/*******************************************************************************
* Function Name  : I2C_WriteByte
* Description    : 写一字节数据
* Input          : - WriteAddress: 待写入地址
*           	   - SendByte: 待写入数据
*                  - DeviceAddress: 器件类型
* Output         : None
* Return         : 返回为:=1成功写入,=0失败
* Attention		 : None
*******************************************************************************/ 
int I2C_WriteByte( uint16_t WriteAddress , uint8_t SendByte )
{
	I2C_Start();
	delay_us(100);
	//发送器件地址
	I2C_SendByte(ADDR_OV7670);
	//如果器件没有应答，那么就发送停止信号
	if(I2C_WaitAck()==1)
	{
		I2C_Stop();
		printf("器件没有应答\n"); //调试使用
		return 0;
	}
	delay_us(5);
    I2C_SendByte((uint8_t)(WriteAddress & 0x00FF));   /* 设置低起始地址 */  
	//如果器件没有应答，那么就发送停止信号
	if(I2C_WaitAck()==1)
	{
		I2C_Stop();
		printf("写寄存器地址失败\n"); //调试使用
		return 0;
	}
	I2C_SendByte(SendByte);   /* 设置低起始地址写寄存器数据 */  
	//如果器件没有应答，那么就发送停止信号
	if(I2C_WaitAck()==1)
	{
		I2C_Stop();
		printf("写寄存器内容失败\n"); //调试使用
		return 0;
	}
	I2C_Stop();
	return 1;

}
//读书菊
uint8_t I2C_ReadOneByte(uint8_t Address)
{
	uint8_t  temp;
	I2C_Start();
	delay_us(100);
	//	写器件地址
	I2C_SendByte(ADDR_OV7670);
	//如果器件没有应答，那么就发送停止信号
	if(I2C_WaitAck()==1)
	{
		I2C_Stop();
		printf("器件没有应答\n"); //调试使用
		return 0;
	}
	delay_us(5);
	I2C_SendByte(Address);
	//如果器件没有应答，那么就发送停止信号
	if(I2C_WaitAck()==1)
	{
		I2C_Stop();
		printf("写寄存器地址失败\n"); //调试使用
		return 0;
	}
	I2C_Stop();
	delay_us(500);
	//开始读
	I2C_Start();
	//发送读命令
	I2C_SendByte(ADDR_OV7670|0x01);
	if(I2C_WaitAck()==1)
	{
		I2C_Stop();
		printf("读失败\n"); //调试使用
		return 0;
	}
	delay_us(100);
	temp=I2C_ReadByte();
   	I2C_NAck();
	I2C_Stop();
	return temp;
}





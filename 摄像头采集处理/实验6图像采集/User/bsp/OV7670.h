#ifndef __OV7670_H__
#define __OV7670_H__
// 行场 中断输出接口

#define VSYNC_Port		GPIOA
#define VSYNC_Pin		GPIO_Pin_0 
#define HREF_Port		GPIOA
#define HREF_Pin		GPIO_Pin_4
//I2C接口	  
#define SCL_Port	GPIOB
#define SCL_Pin     GPIO_Pin_10	
#define SCL_Clock	RCC_APB2Periph_GPIOB  
#define SDA_Port	GPIOB
#define SDA_Pin     GPIO_Pin_11
#define SDA_Clock	RCC_APB2Periph_GPIOB 
#define SCL_H       GPIO_SetBits(SCL_Port, SCL_Pin)
#define SCL_L       GPIO_ResetBits(SCL_Port, SCL_Pin)
#define SDA_H       GPIO_SetBits(SDA_Port, SDA_Pin)
#define SDA_L       GPIO_ResetBits(SDA_Port, SDA_Pin)
#define I2C_SDA_READ()		GPIO_ReadInputDataBit(SDA_Port,SDA_Pin)

 //D0-D7	 需要配置成输入方式	 
#define D0_Port		GPIOC
#define D0_Pin		GPIO_Pin_0 
#define D1_Port		GPIOC
#define D1_Pin		GPIO_Pin_1 	
#define D2_Port		GPIOC
#define D2_Pin		GPIO_Pin_2 
#define D3_Port		GPIOC
#define D3_Pin		GPIO_Pin_3 
#define D4_Port		GPIOC
#define D4_Pin		GPIO_Pin_4 
#define D5_Port		GPIOC
#define D5_Pin		GPIO_Pin_5 
#define D6_Port		GPIOC
#define D6_Pin		GPIO_Pin_6	
#define D7_Port		GPIOC
#define D7_Pin		GPIO_Pin_7 
#define Read_Data_Bus	(uint8_t)(GPIO_ReadInputData(GPIOC)) 
//控制接口	   输出方式
#define PWDN_Port		GPIOA
#define PWDN_Pin		GPIO_Pin_12	 //PA12

#define RESET_Port		GPIOB
#define RESET_Pin		GPIO_Pin_12	 //PB12

#define FIFO_RCK_Port	GPIOB
#define FIFO_RCK_Pin	GPIO_Pin_13	  //PB13
	
#define FIFO_OE_Port	GPIOB
#define FIFO_OE_Pin		GPIO_Pin_15	  	 //PB15
 
#define FIFO_RRST_Port	GPIOC
#define FIFO_RRST_Pin	GPIO_Pin_9       //pc9 

#define FIFO_WR_Port	GPIOB
#define FIFO_WR_Pin	GPIO_Pin_14         //pb14	 

#define FIFO_WRST_Port	GPIOC
#define FIFO_WRST_Pin	GPIO_Pin_8 
   
#define STORBE_Port		GPIOC
#define STORBE_Pin		GPIO_Pin_12

#define PWDN_H			GPIO_SetBits(PWDN_Port,PWDN_Pin)
#define PWDN_L			GPIO_ResetBits(PWDN_Port,PWDN_Pin)

#define RESET_H			GPIO_SetBits(RESET_Port,RESET_Pin)
#define RESET_L			GPIO_ResetBits(RESET_Port,RESET_Pin)

#define FIFO_RCK_H		GPIO_SetBits(FIFO_RCK_Port,FIFO_RCK_Pin)
#define FIFO_RCK_L		GPIO_ResetBits(FIFO_RCK_Port,FIFO_RCK_Pin)

#define FIFO_OE_H		GPIO_SetBits(FIFO_OE_Port,FIFO_OE_Pin)
#define FIFO_OE_L		GPIO_ResetBits(FIFO_OE_Port,FIFO_OE_Pin)

#define FIFO_RRST_H		GPIO_SetBits(FIFO_RRST_Port,FIFO_RRST_Pin)
#define FIFO_RRST_L		GPIO_ResetBits(FIFO_RRST_Port,FIFO_RRST_Pin)

#define FIFO_WR_H		GPIO_SetBits(FIFO_WR_Port,FIFO_WR_Pin)
#define FIFO_WR_L		GPIO_ResetBits(FIFO_WR_Port,FIFO_WR_Pin) 

#define FIFO_WRST_H		GPIO_SetBits(FIFO_WRST_Port,FIFO_WRST_Pin)
#define FIFO_WRST_L		GPIO_ResetBits(FIFO_WRST_Port,FIFO_WRST_Pin)

#define STORBE_H		GPIO_SetBits(STORBE_Port,STORBE_Pin)
#define STORBE_L		GPIO_ResetBits(STORBE_Port,STORBE_Pin) 

#define R	40
#define C	160	  
#define Threshold  100
#define white 254
#define black 0
void OV7670_Init(void);
void OV7670_Register_Init(void);  
void Send_Pic(void);
void Read_Pic(void);
void data_erzhihua(void);
extern void PIC_Process(void);
extern void PIC_Process_2(void);
void V_control(uint8_t (*p)[160]);
extern int Get_GrayValue(void);


#define ADDR_OV7670   0x42	 
extern uint8_t PIC[R][C];
extern uint8_t PIC_Smooth[R][C];
extern uint8_t PIC_Outline[R][C];

typedef enum{
Wait_Vsync1,
Wait_Vsync2,
Read
} OV7670_State;

extern OV7670_State OV_State;
const extern u16 SlampeLine[R];
extern u16 TrueLine;
extern u8 datareadyflag;



#endif

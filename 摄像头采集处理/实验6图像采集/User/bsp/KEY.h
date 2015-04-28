#ifndef __KEY_H__	   
#define __KEY_H__
//端口宏定义   便于移植
#define KEY_1_Port		GPIOC
#define KEY_1_Pin		GPIO_Pin_10
#define KEY_1_Clock		RCC_APB2Periph_GPIOC
#define READ_KEY_1		GPIO_ReadInputDataBit(KEY_1_Port,KEY_1_Pin)

#define KEY_2_Port		GPIOC
#define KEY_2_Pin		GPIO_Pin_11
#define KEY_2_Clock		RCC_APB2Periph_GPIOC
#define READ_KEY_2		GPIO_ReadInputDataBit(KEY_2_Port,KEY_2_Pin)
//按键初始化函数声明
void KEY_Init(void);
#endif

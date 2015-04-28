#ifndef __LED_H__
#define __LED_H__

#define ON		1
#define OFF		0
		 
/*LED_1相关*/

#define LED_1_Port		GPIOB
#define LED_1_Pin		GPIO_Pin_8
#define LED_1_Clock		RCC_APB2Periph_GPIOB
#define LED_1(a)		a>0?GPIO_ResetBits(LED_1_Port,LED_1_Pin):GPIO_SetBits(LED_1_Port,LED_1_Pin)   

/*LED_2相关*/

#define LED_2_Port		GPIOB
#define LED_2_Pin		GPIO_Pin_9
#define LED_2_Clock		RCC_APB2Periph_GPIOB
#define LED_2(a)		a>0?GPIO_ResetBits(LED_2_Port,LED_2_Pin):GPIO_SetBits(LED_2_Port,LED_2_Pin)  
/*初始化函数*/
void LED_Init(void);
#endif	  

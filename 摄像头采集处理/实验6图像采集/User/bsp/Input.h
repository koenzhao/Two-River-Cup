#ifndef __INPUT_H__
#define __INPUT_H__
//输入配置 函数,两个参数 GPIO 和GPIO_Pin
void IO_Input_Config(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
//输出配置 函数,两个参数 GPIO 和GPIO_Pin
void IO_Output_Config(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);

#endif

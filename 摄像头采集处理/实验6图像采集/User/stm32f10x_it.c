/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include"includes.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

//外部中断
void EXTI15_10_IRQHandler(void)
{
	 //判别是否有下降沿 产生
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)				  
  	{
			LED_1(ON);
			LED_2(ON);
			//清除中断请求标志
			printf("按键 1 中断\n");
    		EXTI_ClearITPendingBit(EXTI_Line10);
							  
  	}
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)				  
  	{
			LED_1(OFF);
			LED_2(OFF);
			//清除中断请求标志
			printf("按键 2 中断\n");
    		EXTI_ClearITPendingBit(EXTI_Line11);
							  
  	}

}
//中断之后
void EXTI0_IRQHandler(void)
{
	 //判别是否有下降沿 产生
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)				  
  	{
	
		switch(OV_State)
		{
			case Wait_Vsync1://启动图片的存储	第一次中断
			{	
				//关闭行信号中断 这一步非常重要，在操作执行玩之后在开启中断
				EXTI_Config(DIS);			
				FIFO_WRST_H;
				FIFO_WRST_L;   			
				FIFO_WRST_H;//写指针复位
				FIFO_WR_H;//写使能 
				OV_State=Wait_Vsync2; //状态转移
				//开启中断
				EXTI_Config(EN);				
			} break;

			case Wait_Vsync2://禁止图片存储并启动读图片部分	 第二次中断
			{
				//关闭行信号中断 这一步非常重要，在操作执行玩之后在开启中断
				EXTI_Config(DIS);
				FIFO_WR_L;//写FIFO禁止 	
				FIFO_RRST_L;//读指针复位 
      			FIFO_RCK_L;//给时钟   
      			FIFO_RCK_H;	       		
      			FIFO_RCK_L;      
     			FIFO_RCK_H;
				FIFO_RRST_H;
				delay_ms(1);
				FIFO_OE_L;//允许FIFO输出 
				OV_State=Read; 	
				TrueLine=0;	
				//开启中断
				EXTI_Config(EN);	
			}break;

		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
//外部中断
void EXTI4_IRQHandler(void)
{
	 //判别是否有下降沿 产生
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)				  
  	{
			
			//printf("HERF\n");
    		EXTI_ClearITPendingBit(EXTI_Line4);
							  
  	}
}
//串口1中断函数入口，此函数入口在start_up_stm32f10x_md.s文件中有声明，必须一致
void USART1_IRQHandler(void)
{
	u8 temp;
 	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
 	{
     	temp=USART_ReceiveData(USART1);
		printf("接收到上位机数据 %c\n",temp);

	}	
}

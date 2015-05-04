#include "System_init.h"

int PWM_kongzhi;
int zhuanwan_pwm;

/***************À¶ÑÀÐ­Òé*************/
void speed_control(int *p)
{
 if((*p == 'y')&&((*(p+2)) == 'z'))

 {
	if((*(p+1))>100)
	{
	  *(p+1)=100;
	}
	if((*(p+1))<0)
	{
	  *(p+1)=0;
	}
	if(*(p+3)>100)
	{
	  *(p+3)=100; 
	}
	if(*(p+3)<0)
	{
	  *(p+3)=0; 
	}

    PWM_kongzhi = ((*(p+1)-50)*20);
	zhuanwan_pwm = ((*(p+3)-50)*20); 
 } 
}

/***************Ñ­¼£¿ØÖÆ*************
void read_data_control(void)
{
	temp_left = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0);
	temp_right = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7); 
	
    if( 10 == time_flag )
	{
	  time_flag = 0;
	  jiance_flag = 0;
	}
	if( 1==jiance_flag )
	{
	  zhuanwan_pwm =  zhuanwan_pwm_last;
	  time_flag += 1;	  
	}
	else
	{
	if((0x00 == temp_left)&&(0x01 == temp_right))
	{
	  jiance_flag = 1;		   
	  zhuanwan_pwm = 800;
	  PWM_kongzhi=0;
	}
	else if(( 0x01 == temp_left)&&( 0x00 == temp_right))
	{
	  jiance_flag = 1; 
	  zhuanwan_pwm = -800; 
	  PWM_kongzhi =0;	  
	}
	else
	{
	zhuanwan_pwm = 0;
	PWM_kongzhi = 100;	
	}
	}
	zhuanwan_pwm_last = zhuanwan_pwm;
}	*/

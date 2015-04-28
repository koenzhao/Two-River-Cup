#include "System_init.h"

int PWM_kongzhi;
int zhuanwan_pwm;

/***************¿∂—¿–≠“È*************/
void speed_control(int ip, int V_control, int S_control)
{

 //if((*p == 'z')&&((*(p+2)) == 'w'))
// {
	zhuanwan_pwm = ((ip-80)*10); 
 //}
    PWM_kongzhi = -1200; 
}

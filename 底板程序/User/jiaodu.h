#ifndef _jiaodu_H_
#define _jiaodu_H_
#include "stm32f10x.h"

void Kalman_Filter(float Angle_Kal,float Gyro_Kal);
extern float g_fAngle;                   // 滤波之后的角度   
extern float g_fAngle_Dot;                 // 滤波之后的角速度
void PWM_out(void);
void Angle_Calculate(void);
void pid_sudu(float p,float i,float d);
void upright_Adjust(float p,float i,float d);
void SpeedL(int SpeedL);
void SpeedR(int SpeedR);
#endif

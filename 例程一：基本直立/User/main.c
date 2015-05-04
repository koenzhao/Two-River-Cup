#include "System_init.h"

/*特别主意：此变量不可删除.否则无法直立*/
extern u8 flag;


/**********主函数**********/										   
int main(void)
{
	system_init();	 //整体系统初始化
	for(;;)
	{
	  if(1 == flag)
	  {
	   /*函数说明：
	   upright_Adjust函数;
	   参数：3个;
	   1）为P参数
	   2）为I参数
	   3）为D参数
	   如果仅要求直立直接调用其此函数即可。	   
	   */	     
	   upright_Adjust(185.0,0.0,14.0);
	   /*重要说明  flag 变量不可更改位置和数值*/
	   flag = 0;							   
	  }
	}
}




//实例19：用if语句控制P0口8位LED的流水方向
#include<reg51.h>  //包含单片机寄存器的头文件
sbit K5=P1^4;     //将S1位定义为P1.4
sbit K6=P1^5;     //将S2位定义为P1.5
/*****************************
函数功能：主函数
*****************************/
void main(void)
{  
   while(1)
	 {
	  if(K5==0)   //如果按键S1按下
	    P0=0x0f;  //P0口高四位LED点亮
	  if(K6==0)   //如果按键S2按下
	    P0=0xf0;  //P0口低四位LED点亮
	  }      
}
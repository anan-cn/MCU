//无软件消抖的独立式键盘输入实验
#include<reg52.h>    //  包含51单片机寄存器定义的头文件
sbit S1=P1^4;        //将S1位定义为P1.4引脚
sbit LED0=P0^0;       //将LED0位定义为P3.0引脚
void main(void)  //主函数
{
   LED0=0;       //P3.0引脚输出低电平
while(1)
   {
	    if(S1==0)   //P1.4引脚输出低电平，按键S1被按下
	    LED0=~LED0;  //P3.0引脚取反
		
	}
}

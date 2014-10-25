//实例7：通过对P0口地址的操作流水点亮8位LED
#include<reg51.h>   //包含单片机寄存器的头文件
//sfr x=0x80;   //P0口在存储器中的地址是80H， 通过sfr可定义8051内核单片机
          //的所有内部8位特殊功能寄存器,对地址x的操作也就是对P0口的操作
sfr x=0x90;   //P1口在存储器中的地址是90H， 通过sfr可定义8051内核单片机
          //的所有内部8位特殊功能寄存器,对地址x的操作也就是对P1口的操作
/****************************************
函数功能：延时一段时间
*****************************************/
void delay(void)
   {
	  unsigned char i,j;
	   for(i=0;i<250;i++)
		 for(j=0;j<250;j++)		 
		   ;   //利用循环等待若干机器周期，从而延时一段时间
	  }
/*****************************************
函数功能：主函数 
******************************************/
void main(void)
{
    while(1)
	  {
		    x=0xfe;   //第一个灯亮
		 	delay();  //调用延时函数
		 	 x=0xfd;  //第二个灯亮
		 	delay();  //调用延时函数
			 x=0xfb;  //第三个灯亮
		 	delay();  //调用延时函数
			 x=0xf7;  //第四个灯亮
		 	delay();  //调用延时函数
			x=0xef;   //第五个灯亮
	   	delay();  //调用延时函数
			x=0xdf;   //第六个灯亮
	 	   delay();  //调用延时函数
			x=0xbf;   //第七个灯亮
	   	delay();  //调用延时函数
			x=0x7f;   //第八个灯亮
	   	delay();  //调用延时函数    
	}

 }

	     





//实例24：用字符型数组控制P0口8位LED流水点亮
#include<reg51.h>  //包含单片机寄存器的头文件
/****************************************
函数功能：延时约60ms (3*100*200=60000μs)
****************************************/
void delay60ms(void)
{
 unsigned char m,n;
 for(m=0;m<100;m++)
   for(n=0;n<200;n++)
        ;
}
/****************************************
函数功能：主函数
****************************************/
void main(void)
{  
  unsigned char i;
  unsigned char code Tab[ ]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; //定义无符号字符型数组  
  while(1)
  {
	 for(i=0;i<8;i++)
      {
        P0=Tab[i];//依次引用数组元素，并将其送P0口显示
        delay60ms();//调用延时函数
	   }
	}
}

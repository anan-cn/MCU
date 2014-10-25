//用LED数码显示器循环显示数字0~9
#include<reg52.h>    //  包含51单片机寄存器定义的头文件
/**************************************************
函数功能：延时函数，延时一段时间
***************************************************/
 void delay(void)    
{
   unsigned char i,j;
   for(i=0;i<255;i++)
    for(j=0;j<255;j++)
	       ;
}
/**************************************************
函数功能：主函数
***************************************************/
void main(void)
{
  unsigned char i;
  unsigned char code Tab[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};  
              //数码管显示0～9的段码表，程序运行中当数组值不发生变化时，
			     //前面加关键字code ，可以大大节约单片机的存储空间                    
  P2=0x7f;   //P2.7引脚输出低电平，数码显示器第7位接通电源工作
  while(1)   //无限循环
   {
     for(i=0;i<10;i++)
      {
         P0=Tab[i];  //让P0口输出数字的段码92H
         delay();   //调用延时函数
       }
    } 
}


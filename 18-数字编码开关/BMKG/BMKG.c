#include <reg52.h>
sbit     BMA    = P1^4;//编码开关A引脚
sbit     BMB    = P1^5;//编码开关B引脚
sbit     BMC    = P1^6;//编码开关 下按引脚

unsigned char  display[3];
unsigned char  code  LEDData[ ] = { 
   0xC0,0xF9,0xA4,0xB0,0x99,0x92,
   0x82,0xF8,0x80,0x90,0xff
}; 
unsigned char  counter = 0;     //编码器脉冲计数 
unsigned char  n,shift;

/**********************************************************

ms延时子函数

**********************************************************/
void delayms(unsigned int ms)
{
  unsigned char k;

  while (ms--)
  {
    for (k = 0; k < 114; k++)
      ;
  }
}

/**********************************************************

扫描编码器子函数

在编码器引脚A为低电平期间：

编码器引脚B从0到1为正转，编码器引脚B从1到0为反转。

**********************************************************/
void scan_encoder(void) 
{ 
   static  bit  Curr_b;  //定义一个变量来储存当前B信号 
   static  bit  Last_b;  //定义一个变量来储存上次B脚信号 
   static  bit  update= 0;

   if( BMA && BMB)           //编码器无转动退出
   {
     update = 0; 
     return;
   }

   Last_b = BMB;       //记录B信号

   while(!BMA)                //等待A由低变高
   { 
     Curr_b = BMB;     //记录等待期间的B信号(指当前B信号)
     update = 1;
   
   	if(!BMC)                //当按下旋钮时
     {
       counter = 0;            //计数单元清零(归位)
       delayms(10);
     }
   
   
   } 

   if(update)
   {
   update = 0 ;
     if( (Last_b == 0)&&(Curr_b== 1) ) //B从0到1为正转
     { 
   if(counter == 255)
       return;
       counter++;          //正转计数加
     } 
     else if( (Last_b == 1)&&(Curr_b == 0) ) //B从1到0为反转
     { 
       if(counter == 0)
       return;
       counter--;         //反转计数减
     } 
   }
}

/**********************************************************

主函数

**********************************************************/
void  main(void)
{
   P0 = 0xff;
   P1 = 0xff;
   P2 = 0xff;

   T2CON = 0x00;               //设置T2CON寄存器         
   TH2 = 0xfc;                 //1ms定时
   TL2 = 0x66;
   ET2 = 1;                    //启用Timer2中断
   EA = 1;                     //总中断允许
   TR2 = 1;                    //启动定时器2
   counter = 0;                //计数单元清零

   while(1)
   {

   scan_encoder();
    if(!BMC)                //当按下旋钮时
     {
       counter = 0;            //计数单元清零(归位)
       delayms(10);
     } 
   }
}

/*********************************************************

Timer2中断函数

**********************************************************/
void  timer2() interrupt 5 
{ 
   TR2 = 0;
   TF2 = 0;                         //手工清中断标志  
   TH2 = 0xfc;                      //1ms定时常数
   TL2 = 0x66;

   if(n >= 3)                       //3位数码管显示
   {
     n = 0;
     shift = 0x7f;                  //送位码初值
     P2 = 0xff;                     //关闭显示
   }
   else
   {
     display[0] = counter%10;       //个位数据
     display[1] = (counter%100)/10; //十位数据
     display[2] = counter/100;      //百位数据
     
     if(display[2] == 0)
     {
       display[2] = 0x0a;           //百位为0,不显示
       if(display[1] == 0)
       display[1]  =0x0a;           //十位为0,不显示
}

     P0 = LEDData[display[n++]];    //送段码
     P2 = shift;                    //送位码
     shift = (shift>>1)|0x80;       //调整位码
   }
   TR2 = 1;
}

/*********************************************************/
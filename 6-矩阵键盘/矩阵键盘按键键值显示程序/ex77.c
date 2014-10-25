//矩阵式键盘按键值的数码管显示实验
#include<reg52.h>   //包含51单片机寄存器定义的头文件
sbit P14=P1^4;      //将P14位定义为P1.4引脚
sbit P15=P1^5;      //将P15位定义为P1.5引脚
sbit P16=P1^6;      //将P16位定义为P1.6引脚
sbit P17=P1^7;      //将P17位定义为P1.7引脚
unsigned char code Tab[ ]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};    //数字0~9的段码
unsigned char keyval;    //定义变量储存按键值
/**************************************************************
函数功能：数码管动态扫描延时
**************************************************************/
void led_delay(void)     
 {
   unsigned char j;
	for(j=0;j<200;j++)
	 ;
  }
/**************************************************************
函数功能：按键值的数码管显示子程序
**************************************************************/
 void display(unsigned char k)
{
   P2=0xbf;            //点亮数码管DS6
   P0=Tab[k/10];       //显示十位 
   led_delay();        //动态扫描延时 
    led_delay();        //动态扫描延时
	 led_delay();        //动态扫描延时  
   P0=0xff;
   P2=0x7f;            //点亮数码管DS7
   P0=Tab[k%10];       //显示个位 
	led_delay();       //动态扫描延时 
	 led_delay();        //动态扫描延时 
	  led_delay();        //动态扫描延时 
	P0=0xff;  
 }
/**************************************************************
函数功能：软件延时子程序
**************************************************************/
 void delay20ms(void)   
{
   unsigned char i,j;
	for(i=0;i<100;i++)
	 for(j=0;j<60;j++)
           ;
 }
/**************************************************************
函数功能：主函数
**************************************************************/ 
 void main(void)
 {
   EA=1;                  //开总中断
	ET0=1;                 //定时器T0中断允许         
	TMOD=0x01;            //使用定时器T0的模式1
	TH0=(65536-500)/256;  //定时器T0的高8位赋初值
	TL0=(65536-500)%256;  //定时器T0的高8位赋初值
	TR0=1;                //启动定时器T0
	keyval=0x00;          //按键值初始化为0
	   
	while(1)                //无限循环
		{
		  display(keyval);   //调用按键值的数码管显示子程序
		   led_delay();        //动态扫描延时 
		}

}
/**************************************************************
函数功能：定时器0的中断服务子程序，进行键盘扫描，判断键位
**************************************************************/ 
  void time0_interserve(void) interrupt 1 using 1    //定时器T0的中断编号为1，使用第一组寄存器
  {
     TR0=0;                  //关闭定时器T0
     P1=0xf0;                 //所有行线置为低电平“0”，所有列线置为高电平“1”
	  if((P1&0xf0)!=0xf0)      //列线中有一位为低电平“0”，说明有键按下
	     delay20ms();           //延时一段时间、软件消抖
	  if((P1&0xf0)!=0xf0)      //确实有键按下
	    {
	       P1=0xfe;             //第一行置为低电平“0”（P1.0输出低电平“0”）
	       if(P14==0)           //如果检测到接P1.4引脚的列线为低电平“0”
             keyval=1;            //可判断是S1键被按下
           if(P15==0)             //如果检测到接P1.5引脚的列线为低电平“0”
             keyval=2;            //可判断是S2键被按下
           if(P16==0)             //如果检测到接P1.6引脚的列线为低电平“0”
             keyval=3;            //可判断是S3键被按下
           if(P17==0)            //如果检测到接P1.7引脚的列线为低电平“0”
             keyval=4;           //可判断是S4键被按下

           P1=0xfd;             //第二行置为低电平“0”（P1.1输出低电平“0”）
	      if(P14==0)           //如果检测到接P1.4引脚的列线为低电平“0”
             keyval=5;            //可判断是S5键被按下
           if(P15==0)             //如果检测到接P1.5引脚的列线为低电平“0”
             keyval=6;            //可判断是S6键被按下
           if(P16==0)             //如果检测到接P1.6引脚的列线为低电平“0”
             keyval=7;            //可判断是S7键被按下
           if(P17==0)            //如果检测到接P1.7引脚的列线为低电平“0”
             keyval=8;           //可判断是S8键被按下
		
           P1=0xfb;             //第三行置为低电平“0”（P1.2输出低电平“0”）
	    if(P14==0)          //如果检测到接P1.4引脚的列线为低电平“0”
             keyval=9;          //可判断是S9键被按下
           if(P15==0)           //如果检测到接P1.5引脚的列线为低电平“0”
             keyval=10;         //可判断是S10键被按下
           if(P16==0)          //如果检测到接P1.6引脚的列线为低电平“0”
             keyval=11;        //可判断是S11键被按下
           if(P17==0)          //如果检测到接P1.7引脚的列线为低电平“0”
             keyval=12;        //可判断是S12键被按下

           P1=0xf7;             //第四行置为低电平“0”（P1.3输出低电平“0”）
	    if(P14==0)          //如果检测到接P1.4引脚的列线为低电平“0”
             keyval=13;          //可判断是S13键被按下
           if(P15==0)           //如果检测到接P1.5引脚的列线为低电平“0”
             keyval=14;         //可判断是S14键被按下
           if(P16==0)          //如果检测到接P1.6引脚的列线为低电平“0”
             keyval=15;        //可判断是S15键被按下
           if(P17==0)          //如果检测到接P1.7引脚的列线为低电平“0”
             keyval=16;        //可判断是S16键被按下
       }
     TR0=1;                    //开启定时器T0
     TH0=(65536-500)/256;  //定时器T0的高8位赋初值
	  TL0=(65536-500)%256;  //定时器T0的高8位赋初值		 
 }


#include<reg52.h>

sbit  PINA   = P1^4;
sbit  PINB   = P1^5;
sbit  PIND   = P1^6;

sbit  BEEP   = P3^6 ;        //蜂鸣器

unsigned char direction;
unsigned char PWM = 0x7f ;   //赋初值

/*********************************************************

延时子程序

*********************************************************/
void delayms(unsigned char ms) 
{
   unsigned char i ;
   while(ms--)
   {
     for(i=0 ; i<114 ; i++);
   }
}

/*********************************************************

延时子程序

*********************************************************/
void delay(unsigned char t)
{ 
   while(t--) ;
}

/*********************************************************

蜂鸣器子程序

*********************************************************/
void Beep()     
{
   unsigned char i  ;
   for (i=0  ;i<100  ;i++)
   {
     delay(100);
     BEEP = !BEEP;                 //Beep取反
   } 
   BEEP = 1;                       //关闭蜂鸣器
   delayms(100);
} 

/**********************************************************

扫描编码器子函数

在编码器引脚A为低电平期间：

编码器引脚B从0到1为正转，编码器引脚B从1到0为反转。

**********************************************************/
void scan_encoder(void) 
{ 
   static  bit  Curr_encoder_b;  //定义一个变量来储存当前B信号 
   static  bit  Last_encoder_b;  //定义一个变量来储存上次B脚信号 
   static  bit  updata= 0;

   if( PINA && PINB)           //编码器无转动退出
   {
     updata = 0; 
     return;
   }

   Last_encoder_b = PINB;       //记录B信号

   while(!PINA)                //等待A由低变高
   { 
     Curr_encoder_b = PINB;     //记录等待期间的B信号(指当前B信号)
     updata = 1;
	 if(! PIND)              //当按下旋钮时
     {
       PWM = 0x7f ;          //恢复初始值
     }
   } 

   if(updata)
   {
   updata = 0;
     if( (Last_encoder_b == 0)&&(Curr_encoder_b== 1) ) //B从0到1为正转
     { 
       direction = 1;
     }
     else if( (Last_encoder_b == 1)&&(Curr_encoder_b == 0) ) //B从1到0为反转
     { 
       direction = 2;
     }
   }
}

/**********************************************************

主程序

**********************************************************/
void main(void)
{   
   P1 = 0xff;
   TMOD = 0x21;
   TH0 = 0xfe;               //1ms延时常数
   TL0 = 0x66;               //频率调节

   TH1 = PWM;                //脉宽调节
   TL1 = 0;
   EA = 1;
   ET0 = 1;
   ET1 = 1;
   TR0 = 1;

   while(1)
   {
     scan_encoder();

     if(direction == 1)      //顺时针旋转
     {
       if(PWM!=0x02)
        PWM--; 
       else 
        Beep() ; 
       direction = 0;
     }

     if(direction == 2)      //逆时针旋转
     {
       if(PWM!=0xff)
        PWM++ ;
       else 
        Beep() ; 
       direction = 0;
     }

     if(! PIND)              //当按下旋钮时
     {
       PWM = 0x7f ;          //恢复初始值
     }
   }
}

/*********************************************************

定时器0中断服务程序  （频率）

*********************************************************/
void timer0() interrupt 1 
{  
    TR1 = 0;
    TH0 = 0xfe;      //1ms延时常数
    TL0 = 0x66;      //频率调节
    TH1 = PWM;
    TR1 = 1;
    P0 = 0x00;      //启动输出
}

/*********************************************************

定时器1中断服务程序 （脉宽）

*********************************************************/
void timer1() interrupt 3 
{ 
    TR1 = 0;
    P0 = 0xff;     //结束输出
}

/*********************************************************/
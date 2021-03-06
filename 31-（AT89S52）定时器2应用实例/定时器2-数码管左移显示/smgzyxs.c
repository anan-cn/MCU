#include <reg52.h>       //51芯片管脚定义头文件

typedef   unsigned char  uchar; 
typedef   unsigned int   uint;

uchar code ledcode[11] =
    {
      0xC0,0xF9,0xA4,0xB0,0x99,
      0x92,0x82,0xF8,0x80,0x90,0xff 
    };
                       
uchar data display[8];

uchar  shift,n,num ;

/**********************************************************

延时函数

**********************************************************/
void delayms(uint ms) 
{
   uchar t;
   while(ms--)
   { 
     for(t = 0; t < 114; t++);
   }
}

/**********************************************************

显存单元初始化子函数

**********************************************************/
void  init_data(void)
{
   uchar  i;

   for(i=0; i<8; i++)
   display[i] = 0x0a;        //写入熄灭代码
}

/**********************************************************

数据交换子函数 1  (向左移动)

**********************************************************/
void  exchange1()
{
   uchar  i;

   for(i=7; i>0; i--) 
   display[i] = display[i-1]; //低位单元向高位单元传输数据
   
   display[0] = num+1;        //写入数据“1-8”
}

/**********************************************************

数据交换子函数 2  (向左移动)

**********************************************************/
void  exchange2()
{
   uchar  i;

   for(i=7; i>0; i--) 
   display[i] = display[i-1]; //低位单元向高位单元传输数据

   display[0] = 0x0a;         //写入熄灭代码
}

/**********************************************************

主函数

**********************************************************/
void  main(void)
{
   P0=0xff;
   P2=0xff;
   n=0;
   num = 0;
   shift=0x7f;           //位码初值

   T2CON = 0x00;         //设置T2CON寄存器
   TH2 = 0xfc;           //1ms定时
   TL2 = 0x66;
   ET2 = 1;              //启用Timer2中断
   EA = 1;               //总中断允许
   TR2 = 1;              //启动定时器2

   while(1)
   { 
     init_data();

     while(num<8)
     {
       exchange1();      //数据交换
       delayms(500);    //调整移动速度
       num++;            //计数值加1
     }
     
     num = 0;            //清计数单元
     delayms(1000);      //调整停留速度
     
     while(num<8)
     {
       exchange2();      //数据交换
       delayms(500);    //调整移动速度
       num++;            //计数值加1
     }
     num = 0;            //清计数单元
   }
}

/**********************************************************

中断服务子函数

**********************************************************/ 
void  timer2() interrupt 5
{
   TF2 = 0;                  //手工清中断标志  
   TH2 = 0xfc;               //1ms定时常数
   TL2 = 0x66;

   if(n >= 8)                //8位数码管显示
   {
     n=0;
     shift=0x7f;             //位码初值
     P2 = 0xff;              //关闭显示
   }
   else
   {
     P0=ledcode[display[n]]; //送段码
     P2=shift;               //送位码
     shift=shift>>1|0x80;    //修改位码
     n++;
   }
}

/*********************************************************/

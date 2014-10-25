#include <reg52.h>

unsigned char code ledcode[11] =
{ 
   0xC0,0xF9,0xA4,0xB0,0x99,
   0x92,0x82,0xF8,0x80,0x90,0xff
};

unsigned char  shift,n = 0;

char code reserve [3] _at_ 0x3b;  //保留0x3b开始的3个字节

/**********************************************************

  主函数

**********************************************************/
main()
{
   T2CON = 0x00;           //设置T2CON寄存器       
   TH2 = 0xfc;             //1ms定时常数
   TL2 = 0x66;

   ET2 = 1;                //允许Timer2中断
   EA = 1;                 //总中断允许
   TR2 = 1;                //启动定时器2
   shift = 0xfe;           //送位码初值
   while(1);
}

/**********************************************************

  Timer2中断服务子函数

**********************************************************/
void  timer2(void) interrupt 5 
{ 
   TF2 = 0;                  //手工清中断标志  
   TH2 = 0xfc;               //1ms定时常数
   TL2 = 0x66;
  
   if(n >= 8)
   {
     n = 0;
     shift = 0xfe;           //送位码初值
     P2 = 0xff;              //关闭数码管显示 
   }
   else
   {
     P0 = ledcode[n+1];        //送段码
     P2 = shift;             //送位码
     shift = shift<<1|0x01;  //修改位码
     n++;
   }
}

/*********************************************************/
//数码时钟设计
#include<reg52.h>    //  包含51单片机寄存器定义的头文件
unsigned char Tab[ ]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};  //control  shape
unsigned char port[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
unsigned char int_time ; //中断次数计数变量
unsigned char second;    //秒计数变量
unsigned char minute;    //分钟计数变量
unsigned char hour;     //小时计数变量

/////////////////////////////////////////////////////

 void delay(void)      //延时函数，延时约0.6ms
 {
   unsigned char j;
	for(j=0;j<180;j++)
	 ;
  }

/******************************************************************
函数功能：显示秒的子程序
入口参数：s
********************************************************************/
 void DisplaySecond(unsigned char s)
{
   P2=0xbf;        //P2.6引脚输出低电平， DS6点亮 
   P0=Tab[s/10];          //显示十位
   delay();
  delay();
   delay();
  
   P2=0x7f;       //P2.7引脚输出低电平， DS7点亮 
   P0=Tab[s%10];         //显示个位
 delay();
  delay();
   delay();
  
	P2=0xff;     //关闭所有数码管
   	P0=0xff;
	 delay();
  delay();
   delay();
 
 }
 
/******************************************************************
函数功能：显示分钟的子程序
入口参数：m
********************************************************************/
void DisplayMinute(unsigned char m)
{
     P2=0xf7;   // P2.3引脚输出低电平， DS3点亮 
     P0=Tab[m/10];//显示个位
	   delay();
  delay();
   delay();
  delay();
	  P2=0xef;   // P2.4引脚输出低电平， DS4点亮 
	  P0=Tab[m%10];
	  delay();
  delay();
   delay();
  
	  P2=0xdf;   //P2.5引脚输出低电平， DS5点亮 
	  P0=0xbf;   //分隔符“-”的段码
	  delay();
  delay();
   delay();
  
	  P2=0xff;   //关闭所有数码管
	  P0=0xff;
	   delay();
  delay();
   delay();
  

 }
/******************************************************************
函数功能：显示小时的子程序
入口参数：h
********************************************************************/
void DisplayHour(unsigned char h)
{
   
   P2=0xfe;        //P2.0引脚输出低电平， DS0点亮 
   P0=Tab[h/10];          //显示十位 
   delay();
  delay();
   delay();
 
   P2=0xfd;       //P2.1引脚输出低电平， DS1点亮 
   P0=Tab[h%10];    //显示个位
 delay();
  delay(); 
   delay();
   
	P2=0xfb;     //P2.2引脚输出低电平， DS2点亮 
	P0=0xbf;     //分隔符“-”的段码
 delay();
  delay();
   delay();
  
   P2=0xff;     //关闭所有数码管
   P0=0xff;
    delay();
  delay();
   delay();
   
 }
 /******************************************************************
函数功能：主函数
********************************************************************/

 void main(void)
   {
	    	
			TMOD=0x01;             //使用定时器T0		
			EA=1;                  //开中断总允许
			ET0=1;                 //允许T0中断
			TH0=(65536-46083)/256;  //定时器高八位赋初值
			TL0=(65536-46083)%256;  //定时器低八位赋初值
			TR0=1;
			int_time=0;    //中断计数变量初始化
			second=0;      //秒计数变量初始化
			minute=0;     //分钟计数变量初始化
			hour=0;       //小时计数变量初始化
        
         while(1)
			{	      
	 				 DisplaySecond(second);    //调用秒显示子程序
					 delay();
					 DisplayMinute(minute);   //调用分钟显示子程序
					 delay();
				 	 DisplayHour(hour);     
					 delay();       							  
		   }
  }

/******************************************************************
函数功能：定时器T0的中断服务子程序
********************************************************************/
  void interserve(void ) interrupt 1 using 1  //using Time0
  {
       int_time++;
		 if(int_time==20)
		   {
              int_time=0;    //中断计数变量清0
		        second++;      //秒计数变量加1
			}
			  if(second==60)
				 {
					  second=0;    //如果秒计满60，将秒计数变量清0
					  minute++;    //分钟计数变量加1
				 }
					 if(minute==60)
					   {
						   minute=0;    //如果分钟计满60，将分钟计数变量清0
						   hour++;      //小时计数变量加1
						}
						  if(hour==24)
						    {
							   hour=0;    //如果小时计满24，将小时计数变量清0
							 }

		   TH0=(65536-46083)/256;   //定时器重新赋初值
			TL0=(65536-46083)%256;
				   		   
		
  }  

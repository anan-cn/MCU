//简易电子琴
#include<reg52.h>   //包含51单片机寄存器定义的头文件

sbit P14=P1^4;      //将P14位定义为P1.4引脚
sbit P15=P1^5;      //将P15位定义为P1.5引脚
sbit P16=P1^6;      //将P16位定义为P1.6引脚
sbit P17=P1^7;      //将P17位定义为P1.7引脚
unsigned char keyval;    //定义变量储存按键值

sbit sound=P3^6;    //将sound位定义为P3.7
unsigned int C;     //全局变量，储存定时器的定时常数
unsigned int f;     //全局变量，储存音阶的频率

//以下是C调低音的音频宏定义
#define l_dao 262   //将“l_dao”宏定义为低音“1”的频率262Hz
#define l_re 286    //将“l_re”宏定义为低音“2”的频率286Hz
#define l_mi 311    //将“l_mi”宏定义为低音“3”的频率311Hz
#define l_fa 349    //将“l_fa”宏定义为低音“4”的频率349Hz
#define l_sao 392   //将“l_sao”宏定义为低音“5”的频率392Hz
#define l_la 440    //将“l_a”宏定义为低音“6”的频率440Hz
#define l_xi 494    //将“l_xi”宏定义为低音“7”的频率494Hz
       
     //以下是C调中音的音频宏定义
#define dao 523     //将“dao”宏定义为中音“1”的频率523Hz
#define re 587      //将“re”宏定义为中音“2”的频率587Hz
#define mi 659      //将“mi”宏定义为中音“3”的频率659Hz
#define fa 698      //将“fa”宏定义为中音“4”的频率698Hz
#define sao 784     //将“sao”宏定义为中音“5”的频率784Hz
#define la 880      //将“la”宏定义为中音“6”的频率880Hz
#define xi 987      //将“xi”宏定义为中音“7”的频率53
      
//以下是C调高音的音频宏定义
#define h_dao 1046     //将“h_dao”宏定义为高音“1”的频率1046Hz
#define h_re 1174      //将“h_re”宏定义为高音“2”的频率1174Hz
#define h_mi 1318      //将“h_mi”宏定义为高音“3”的频率1318Hz
#define h_fa 1396     //将“h_fa”宏定义为高音“4”的频率1396Hz
#define h_sao 1567    //将“h_sao”宏定义为高音“5”的频率1567Hz
#define h_la 1760     //将“h_la”宏定义为高音“6”的频率1760Hz
#define h_xi 1975     //将“h_xi”宏定义为高音“7”的频率1975Hz
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


/*******************************************
函数功能：节拍的延时的基本单位，延时200ms
******************************************/
void delay()               
   {
     unsigned char i,j;
	  for(i=0;i<250;i++)
	    for(j=0;j<250;j++)
           	 ;
   }
/*******************************************
函数功能：输出音频
入口参数：F
******************************************/
void Output_Sound(void)
{
  C=(46083/f)*10;	   //计算定时常数
  TH0=(8192-C)/32;     //可证明这是13位计数器TH0高8位的赋初值方法
  TL0=(8192-C)%32;     //可证明这是13位计数器TL0低5位的赋初值方法
  TR0=1;               //开定时T0
  delay();             //延时200ms，播放音频
  TR0=0;               //关闭定时器
  sound=1;        //关闭蜂鸣器
  keyval=0xff;	    //播放按键音频后，将按键值更改，停止播放
}
/*******************************************
函数功能：主函数
******************************************/	
void main(void)
  {  
  	   EA=1;         //开总中断
	   ET0=1;         //定时器T0中断允许
		ET1=1;        //定时器T1中断允许
		TR1=1;        //定时器T1启动，开始键盘扫描
      TMOD=0x10;    //分别使用定时器T1的模式1，T0的模式0
     TH1=(65536-500)/256;  //定时器T1的高8位赋初值
	  TL1=(65536-500)%256;  //定时器T1的高8位赋初值	 							   
			
				 while(1)            //无限循环
				   {
				    switch(keyval)
					    {
						    case 1:f=dao;            //如果第1个键按下，将中音1的频率赋给f
							    Output_Sound();    //转去计算定时常数 
								 break;
							 case 2:f=l_xi;           //如果第2个键按下，将低音7的频率赋给f
							    Output_Sound();    //转去计算定时常数 
								 break;
                      case 3:f=l_la;           //如果第3个键按下，将低音6的频率赋给f
							    Output_Sound();    //转去计算定时常数 
								 break;
						    case 4:f=l_sao;          //如果第4个键按下，将低音5的频率赋给f
							      Output_Sound();    //转去计算定时常数 
								 break;
							 case 5:f=sao;             //如果第5个键按下，将中音5的频率赋给f
							        Output_Sound();    //转去计算定时常数 
								 break;
							 case 6:f=fa;              //如果第6个键按下，将中音4的频率赋给f
							     Output_Sound();    //转去计算定时常数 
								 break;
                      case 7:f=mi;             //如果第7个键按下，将中音3的频率赋给f
							    Output_Sound();    //转去计算定时常数 
								 break; 
						    case 8:f=re;              //如果第8个键按下，将中音2的频率赋给f
							    Output_Sound();    //转去计算定时常数 
								 break;
							 case 9:f=h_re;           //如果第9个键按下，将高音2的频率赋给f
							     Output_Sound();    //转去计算定时常数 
								 break;
							 case 10:f=h_dao;           //如果第10个键按下，将高音1的频率赋给f
							    Output_Sound();    //转去计算定时常数 
								 break;
                      case 11:f=xi;            //如果第11个键按下，将中音7的频率赋给f
							   Output_Sound();    //转去计算定时常数 
								 break;
						    case 12:f=la;            //如果第12个键按下，将中音6的频率赋给f
							    Output_Sound();    //转去计算定时常数 
								 break; 
							 case 13:f=h_la;          //如果第13个键按下，将高音6的频率赋给f
							    Output_Sound();    //转去计算定时常数 
								 break;
							 case 14:f=h_sao;          //如果第14个键按下，将高音5的频率赋给f
							    Output_Sound();    //转去计算定时常数 
								 break;
                      case 15:f=h_fa;          //如果第15个键按下，将高音4的频率赋给f
							    Output_Sound();    //转去计算定时常数 
								 break;
						    case 16:f=h_mi;           //如果第16个键按下，将高音3的频率赋给f
							    Output_Sound();    //转去计算定时常数 
								 break;  
		           } 
		  	}	
	} 
/**************************************************************
函数功能：定时器T0的中断服务子程序，使P3.7引脚输出音频方波
**************************************************************/ 

  void Time0_serve(void ) interrupt 1 using 1  
  {
         
        TH0=(8192-C)/32;     //可证明这是13位计数器TH0高8位的赋初值方法
        TL0=(8192-C)%32;     //可证明这是13位计数器TL0低5位的赋初值方法 
	     sound=!sound;        //将P3.7引脚取反，输出音频方波
  }
		
/**************************************************************
函数功能：定时器T1的中断服务子程序，进行键盘扫描，判断键位
**************************************************************/ 
  void time1_serve(void) interrupt 3 using 2    //定时器T1的中断编号为3，使用第2组寄存器
  {
     TR1=0;                  //关闭定时器T0
     P1=0xf0;                 //所有行线置为低电平“0”，所有列线置为高电平“1”
	  if((P1&0xf0)!=0xf0)      //列线中有一位为低电平“0”，说明有键按下
	   {
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
		}
     TR1=1;                    //开启定时器T1
     TH1=(65536-500)/256;  //定时器T1的高8位赋初值
	  TL1=(65536-500)%256;  //定时器T1的高8位赋初值		 
 }

		


#include "MusInstru.h"

/* 键消抖延时函数 */
void delay(void)
{
	uchar i;
	for (i=300;i>0;i--);
}

/* 键扫描函数 */
uchar getkey(void)
{
	uchar scancode,tmpcode;

	if ((P1&0xf0)==0xf0)			
		return(0);

	scancode = 0xfe;
	while((scancode&0x10)!=0)		// 逐行扫描
	{
		P1 = scancode;				// 输出行扫描码
		if ((P1&0xf0)!=0xf0)		// 本行有键按下
		{
			tmpcode = (P1&0xf0)|0x0f;

			/* 返回特征字节码，为1的位即对应于行和列 */
			return((~scancode)+(~tmpcode));
		}
		else scancode = (scancode<<1)|0x01;		// 行扫描码左移一位
	}
}

/* 定时器0中断服务子程序 */
void time0_int(void) interrupt 1 using 0
{
	/* 设置计数初值 */
  	TH0 = STH0;
  	TL0 = STL0; 
   	P36=~P36; 							// 反相，产生输出脉冲
}

/* 主程序 */
void main()
{
	uchar key,k;

	TMOD = 0x01;							// T0，工作方式1

	ET0 = 1;
	EA = 1;

 	while(1)
    {
		P1 = 0xf0;			 					// 发全0行扫描码
		if ((P1&0xf0)!=0xf0)					// 若有键按下
		{
			delay();							// 延时去抖动
			if ((P1&0xf0)!=0xf0)				// 延时后再判断一次，去除抖动影响
			{
				key = getkey();					// 调用键盘扫描函数

				// 根据获取的按键位置得到k值
				switch(key)
   				{
      				case 0x11:						// 1行1列
						k = 0;
						break;
					case 0x21:						// 1行2列
						k = 1;
						break;			
					case 0x41:						// 1行3列
						k = 2;
						break;
     				case 0x81:						// 1行4列
						k = 3;
						break;
					case 0x12:						// 2行1列
						k = 4;
						break;
					case 0x22:						// 2行2列
						k = 5;
						break;
					case 0x42:						// 2行3列
						k = 6;
						break;
					case 0x82:						// 2行4列
						k = 7;
						break;
					case 0x14:						// 3行1列
						k = 8;
						break;
					case 0x24:						// 3行2列
						k = 9;
						break;
					case 0x44:						// 3行3列
						k = 10;
						break;
					case 0x84:						// 3行4列
						k = 11;
						break;
					case 0x18:						// 3行4列
						k = 12;
						break;
					case 0x28:						// 3行4列
						k = 13;
						break;
					case 0x48:						// 3行4列
						k = 14;
						break;
					case 0x88:						// 3行4列
						k = 15;
						break;
					default:	
						break;
				}	

				P36 = ~P36; 						// 反相
		
				/* 根据所得的k值设定计数器1的计数初值 */
      		    STH0 = tab[k]/256;
       		    STL0 = tab[k]%256; 

      		  	TR0 = 1;							// 开始计数 

				P1 = 0xf0;			 				// 发全0行扫描码
				while ((P1&0xf0)!=0xf0)				// 若没有松开按键
				{
					P1 = 0xf0;	
				}

				TR1 = 0;							// 若按键松开，则停止计数，不产生脉冲输出
			}
		}
	}    
}

  


  





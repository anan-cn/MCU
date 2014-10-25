#include<reg52.h>
#include"mouse.h"
#include"LCD1602_4.h"

sbit beep=P3^6;

void main()
{

	LCM1602_Init();//初始化液晶1602
	Init_mouse();
	mouse_send_data(0xf4);//向鼠标发送0xF4命令发其开始工作 
	EX1=0;//关掉外部中断以避开鼠标发回的应答
	delayms(100);
	EX1=1;//重开外部中断
	while(1)
	{		
		CLEARSCREEN;//清屏
		LCM1602_write_string(0,0,"x:");
		num(0,2,move_x);//x坐标值
		LCM1602_write_string(0,8,"y:");
		num(0,10,move_y);//y坐标值
		if(mouse_data[0]&0x01)//如果点下左键
		{
			beep=0;
			LCM1602_write_string(1,0,"left");
		}
		else if(mouse_data[0]&0x02)//如果点下右键
		{
			beep=0;
			LCM1602_write_string(1,0,"right");
		}
		else if(mouse_data[0]&0x04)//如果点下中键
		{
			beep=0;
			LCM1602_write_string(1,0,"middle");
		}
		else
		{
			beep=1;
			LCM1602_write_string(1,0,"nothing");
		} 
		delayms(50);
	}
}
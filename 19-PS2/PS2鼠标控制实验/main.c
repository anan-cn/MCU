#include<reg52.h>
#include"mouse.h"
#include"LCD1602_4.h"

sbit beep=P3^6;

void main()
{

	LCM1602_Init();//��ʼ��Һ��1602
	Init_mouse();
	mouse_send_data(0xf4);//����귢��0xF4����俪ʼ���� 
	EX1=0;//�ص��ⲿ�ж��Աܿ���귢�ص�Ӧ��
	delayms(100);
	EX1=1;//�ؿ��ⲿ�ж�
	while(1)
	{		
		CLEARSCREEN;//����
		LCM1602_write_string(0,0,"x:");
		num(0,2,move_x);//x����ֵ
		LCM1602_write_string(0,8,"y:");
		num(0,10,move_y);//y����ֵ
		if(mouse_data[0]&0x01)//����������
		{
			beep=0;
			LCM1602_write_string(1,0,"left");
		}
		else if(mouse_data[0]&0x02)//��������Ҽ�
		{
			beep=0;
			LCM1602_write_string(1,0,"right");
		}
		else if(mouse_data[0]&0x04)//��������м�
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
#include"delay52.h"
#ifndef MOUSE_H
#define MOUSE_H

sbit mouse_SDA=P3^2;//������P3_2
sbit mouse_CLK=P3^3;//ʱ����P3_3

sbit led1=P1^3;
                            
unsigned char bdata mouse_byte; //�����ֽ�
sbit mouse_byte_bit0=mouse_byte^0;//mouse_byte��0λ
sbit mouse_byte_bit1=mouse_byte^1;//mouse_byte��1λ
sbit mouse_byte_bit2=mouse_byte^2;//mouse_byte��2λ
sbit mouse_byte_bit3=mouse_byte^3;//mouse_byte��3λ
sbit mouse_byte_bit4=mouse_byte^4;//mouse_byte��4λ
sbit mouse_byte_bit5=mouse_byte^5;//mouse_byte��5λ
sbit mouse_byte_bit6=mouse_byte^6;//mouse_byte��6λ
sbit mouse_byte_bit7=mouse_byte^7;//mouse_byte��7λ

unsigned char bdata mouse_fuction;//������Ϣ�ֽ� 
                      
unsigned char mouse_buffer[11];//����λ���ݻ�����
unsigned char mouse_buffer_bit=0;//mouse_buffer[mouse_buffer_bit]
unsigned char mouse_data[3];//����������ݻ�����,�ֱ���:������Ϣ�ֽ�,xλ����,yλ����
unsigned char mouse_data_bit=0;//mouse_data[mouse_data_bit]

unsigned int move_x=10000;//��ź�����
unsigned int move_y=10000;//���������

void Init_mouse(void)
{
     TCON=0x00;
     EA=1;
     EX1=1;//�����ⲿ�ж�1
     ET0=0x01;//����ȫ���жϣ�����ʱ��/������0����ж�
     PX1=1;//�����ж����ȼ�
}


/***********************************************************************
		��������
************************************************************************/
 void mouse_send_data(unsigned char dat)
{
	unsigned char i;
	EX1=0;                              /*�ر��ⲿ�ж�1*/
	ACC=dat;                            /*��Ҫ���͵����ݷ���A�Ĵ���*/
	mouse_CLK=0;                       /*����ʱ����*/
	delay10us(200);                      /*��ʱ100us����*/
	mouse_SDA=0;                        /*����������*/
	delay10us(40);
	mouse_CLK=1;                       /*�ͷ�ʱ����*/
	for(i=0;i<=7;i++)             /*��λ��ǰ��һ�η���8������λ*/
	{
		while(mouse_CLK==1);           /*�ȴ��豸����ʱ����*/
		mouse_SDA=(dat>>i)&0x01;      /*��������λ*/
		while(mouse_CLK==0);           /*�ȴ��豸�ͷ�ʱ����*/
	}
	while(mouse_CLK==1);
	mouse_SDA=~P;                       /*����У��λ����У��*/
	while(mouse_CLK==0);
	while(mouse_CLK==1);
	mouse_SDA=1;                        /*����ֹͣλ*/
	while(mouse_CLK==0);							  
	while(mouse_CLK==1);				/*Ӧ��λ*/
	while(mouse_CLK==0);	
	EX1=1;                              /*���ⲿ�ж�1*/
}

/*********************************************
		 	��У��
**********************************************/
unsigned char Checkout(void)			
{
	ACC=mouse_byte;
	if(~P==mouse_buffer[9])
		return 1;
	else
		return 0;
} 

/*********************************************************
		   ���ݷ���������
**********************************************************/
void data_analyse(void)
{
	//���յ���11λ�ź��н�ȡ8λ���ݷŽ�mouse_byte
	mouse_byte_bit0=mouse_buffer[1];
	mouse_byte_bit1=mouse_buffer[2];
	mouse_byte_bit2=mouse_buffer[3];
	mouse_byte_bit3=mouse_buffer[4];
	mouse_byte_bit4=mouse_buffer[5];
	mouse_byte_bit5=mouse_buffer[6];
	mouse_byte_bit6=mouse_buffer[7];
	mouse_byte_bit7=mouse_buffer[8];	
	if(Checkout())//���У����ȷ
	{
		if(mouse_data_bit<3)         
			mouse_data[mouse_data_bit++]=mouse_byte; 
		if(mouse_data_bit==3)
		{
			mouse_data_bit=0;
			if(mouse_data[0]&0x10)//���"X sign bit"Ϊ1,��ʾ���������
			{
				move_x-=(256-mouse_data[1]);//x�����
			}
			else
			{
				move_x+=mouse_data[1];//x�����
			}
			if(mouse_data[0]&0x20)
			{
				move_y-=(256-mouse_data[2]);//y�����
			}
			else
			{
				move_y+=mouse_data[2];//y�����
			}
		}
	}
}

/**************************************************
	   			�ⲿ�ж�1
***************************************************/
void ReceiveData(void)  interrupt 2
{
	if(mouse_buffer_bit<=10)
	{	                               	 
		while(mouse_CLK==0);//�ȴ��豸����ʱ����
		mouse_buffer[mouse_buffer_bit++]=mouse_SDA;//��������
	}	
	if(mouse_buffer_bit==10)
	{
		data_analyse();//���ݷ���������
		mouse_buffer_bit=0;
	}			 	 					
}

#endif


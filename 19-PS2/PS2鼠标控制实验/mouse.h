#include"delay52.h"
#ifndef MOUSE_H
#define MOUSE_H

sbit mouse_SDA=P3^2;//数据线P3_2
sbit mouse_CLK=P3^3;//时钟线P3_3

sbit led1=P1^3;
                            
unsigned char bdata mouse_byte; //接收字节
sbit mouse_byte_bit0=mouse_byte^0;//mouse_byte第0位
sbit mouse_byte_bit1=mouse_byte^1;//mouse_byte第1位
sbit mouse_byte_bit2=mouse_byte^2;//mouse_byte第2位
sbit mouse_byte_bit3=mouse_byte^3;//mouse_byte第3位
sbit mouse_byte_bit4=mouse_byte^4;//mouse_byte第4位
sbit mouse_byte_bit5=mouse_byte^5;//mouse_byte第5位
sbit mouse_byte_bit6=mouse_byte^6;//mouse_byte第6位
sbit mouse_byte_bit7=mouse_byte^7;//mouse_byte第7位

unsigned char bdata mouse_fuction;//功能信息字节 
                      
unsigned char mouse_buffer[11];//接收位数据缓冲区
unsigned char mouse_buffer_bit=0;//mouse_buffer[mouse_buffer_bit]
unsigned char mouse_data[3];//接收鼠标数据缓冲区,分别存放:功能信息字节,x位移量,y位移量
unsigned char mouse_data_bit=0;//mouse_data[mouse_data_bit]

unsigned int move_x=10000;//存放横坐标
unsigned int move_y=10000;//存放纵坐标

void Init_mouse(void)
{
     TCON=0x00;
     EA=1;
     EX1=1;//允许外部中断1
     ET0=0x01;//允许全局中断，允许定时器/计数器0溢出中断
     PX1=1;//设置中断优先级
}


/***********************************************************************
		发送数据
************************************************************************/
 void mouse_send_data(unsigned char dat)
{
	unsigned char i;
	EX1=0;                              /*关闭外部中断1*/
	ACC=dat;                            /*将要发送的数据放入A寄存器*/
	mouse_CLK=0;                       /*拉低时钟线*/
	delay10us(200);                      /*延时100us以上*/
	mouse_SDA=0;                        /*拉低数据线*/
	delay10us(40);
	mouse_CLK=1;                       /*释放时钟线*/
	for(i=0;i<=7;i++)             /*低位在前，一次发送8个数据位*/
	{
		while(mouse_CLK==1);           /*等待设备拉低时钟线*/
		mouse_SDA=(dat>>i)&0x01;      /*发送数据位*/
		while(mouse_CLK==0);           /*等待设备释放时钟线*/
	}
	while(mouse_CLK==1);
	mouse_SDA=~P;                       /*发送校验位，奇校验*/
	while(mouse_CLK==0);
	while(mouse_CLK==1);
	mouse_SDA=1;                        /*发送停止位*/
	while(mouse_CLK==0);							  
	while(mouse_CLK==1);				/*应答位*/
	while(mouse_CLK==0);	
	EX1=1;                              /*打开外部中断1*/
}

/*********************************************
		 	奇校检
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
		   数据分析及处理
**********************************************************/
void data_analyse(void)
{
	//将收到的11位信号中截取8位数据放进mouse_byte
	mouse_byte_bit0=mouse_buffer[1];
	mouse_byte_bit1=mouse_buffer[2];
	mouse_byte_bit2=mouse_buffer[3];
	mouse_byte_bit3=mouse_buffer[4];
	mouse_byte_bit4=mouse_buffer[5];
	mouse_byte_bit5=mouse_buffer[6];
	mouse_byte_bit6=mouse_buffer[7];
	mouse_byte_bit7=mouse_buffer[8];	
	if(Checkout())//如果校验正确
	{
		if(mouse_data_bit<3)         
			mouse_data[mouse_data_bit++]=mouse_byte; 
		if(mouse_data_bit==3)
		{
			mouse_data_bit=0;
			if(mouse_data[0]&0x10)//如果"X sign bit"为1,表示鼠标向左移
			{
				move_x-=(256-mouse_data[1]);//x坐标减
			}
			else
			{
				move_x+=mouse_data[1];//x坐标加
			}
			if(mouse_data[0]&0x20)
			{
				move_y-=(256-mouse_data[2]);//y坐标减
			}
			else
			{
				move_y+=mouse_data[2];//y坐标加
			}
		}
	}
}

/**************************************************
	   			外部中断1
***************************************************/
void ReceiveData(void)  interrupt 2
{
	if(mouse_buffer_bit<=10)
	{	                               	 
		while(mouse_CLK==0);//等待设备拉高时钟线
		mouse_buffer[mouse_buffer_bit++]=mouse_SDA;//接收数据
	}	
	if(mouse_buffer_bit==10)
	{
		data_analyse();//数据分析及处理
		mouse_buffer_bit=0;
	}			 	 					
}

#endif


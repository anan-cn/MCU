#ifndef	LCD1602_4_H
#define LCD1602_4_H
#include <intrins.h>

#define  LCM1602_DATA P0
#define CLEARSCREEN LCM1602_write_cmd(0x01)

sbit LCD1602_RS=P2^0;
sbit LCD1602_RW=P2^1; 
sbit LCD1602_EN=P2^2;

//**********************************************************************
void LCM1602_Init(void);													//液晶初始化
void LCM1602_write_cmd(unsigned char command);								//写命令
void LCM1602_write_data(unsigned char temp);								//写数据
void LCM1602_set_xy(unsigned char x, unsigned char y);						//设置坐标
void LCM1602_write_char(unsigned x,unsigned char y,unsigned char dat);		//写一个字符到第x行y列
void LCM1602_write_string(unsigned char x,unsigned char y,unsigned char *s);//写字符串到第x行y列
void LCM1602_Read_BF(void);													//读忙信号
void num(unsigned char x,unsigned char y,unsigned int n);					//在第x行,第y列显示整型数字n
//**********************************************************************

void LCM1602_Init(void)
{ 
	LCM1602_write_cmd(0x28);
	LCM1602_write_cmd(0x28);
	LCM1602_write_cmd(0x28);//设置4位数据传输模式
	LCM1602_write_cmd(0x0C);
	LCM1602_write_cmd(0x80);
    CLEARSCREEN;
}


void LCM1602_Read_BF(void)
{
	LCD1602_RW=1;		//RW 1
	LCD1602_RS=0;			//RS 0
	LCD1602_EN=1;		//EN 1	Read BF
 	LCM1602_DATA=LCM1602_DATA&0x0F|0xf0;
	while(LCM1602_DATA&0x80);
	LCD1602_EN=0;		
}
void LCD_en_write(void)        //EN端产生一个高电平脉冲，写LCD
  {
    LCD1602_EN=1;
	_nop_();
    LCD1602_EN=0;	
  }

//*************************************
void LCM1602_write_cmd(unsigned char command)
{
	LCM1602_Read_BF();
	LCD1602_RS=0;   	//RS 0 
	LCD1602_RW=0;		//RW 0 
	
	LCM1602_DATA&=0x0F;
	LCM1602_DATA=command&0xf0 | LCM1602_DATA&0x0f;
	LCD_en_write();
	command=command<<4; 
	LCM1602_DATA&=0x0F;
	LCM1602_DATA=command&0xf0 | LCM1602_DATA&0x0f;
	LCD_en_write();
}
//*********************************
void LCM1602_write_data(unsigned char dat)
{
	LCM1602_Read_BF();
	LCD1602_RS=1;	 //RS 1 
	LCD1602_RW=0;	 //RW 0 
	LCM1602_DATA &=0x0F;
	LCM1602_DATA=dat&0xf0 | LCM1602_DATA&0x0f;
	LCD_en_write();
	dat=dat<<4;
	LCM1602_DATA &=0x0F;
	LCM1602_DATA=dat&0xf0 | LCM1602_DATA&0x0f;
	LCD_en_write();
}
//**********************************************
void LCM1602_set_xy(unsigned char x,unsigned char y)
{
	unsigned char address;
	y&=0x0f;
	if(!x)	
		address=0x80+y;
	else 			
		address=0xc0+y;
	LCM1602_write_cmd(address); 
}
//****************************************************************
void LCM1602_write_char(unsigned x,unsigned char y,unsigned char dat)
{
	LCM1602_set_xy(x,y); 
	LCM1602_write_data(dat);
}
//*********************************************************************
void LCM1602_write_string(unsigned char x,unsigned char y,const unsigned char *s)
{
	LCM1602_set_xy(x,y); 
	while(*s)  
	{
		LCM1602_write_data(*s);   
		s++;
	}
}

void num(unsigned char x,unsigned char y,unsigned int n)
{
	unsigned char i,length,a[6]={0,0,0,0,0,0};
	unsigned int nx=n;
	if(n==0){LCM1602_write_char(x,y,'0');return;}
	for(i=0;i<6;i++)
	{
		if(nx>=1)length++;
		nx/=10;
	}
	nx=n;
	for(;length>0;length--)
	{
		a[length-1]=nx%10+48;
		nx/=10;
	}
	LCM1602_write_string(x,y,a);
}

#endif

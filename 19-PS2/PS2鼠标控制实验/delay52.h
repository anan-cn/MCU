//����11.0592M
#ifndef DELAY52_H
#define DELAY52_H
#define uchar unsigned char
#define uint unsigned int
#include<intrins.h>

//��ʼֵdelayus(1)=27us,���9.9us
void delay10us(unsigned int t)
{
	while(t--);
}

void delayms(unsigned int t)
{
	unsigned int i;
	unsigned char j;
	for(i=0;i<t;i++)
		for(j=0;j<125;j++);
}

#endif
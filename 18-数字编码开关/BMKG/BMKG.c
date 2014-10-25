#include <reg52.h>
sbit     BMA    = P1^4;//���뿪��A����
sbit     BMB    = P1^5;//���뿪��B����
sbit     BMC    = P1^6;//���뿪�� �°�����

unsigned char  display[3];
unsigned char  code  LEDData[ ] = { 
   0xC0,0xF9,0xA4,0xB0,0x99,0x92,
   0x82,0xF8,0x80,0x90,0xff
}; 
unsigned char  counter = 0;     //������������� 
unsigned char  n,shift;

/**********************************************************

ms��ʱ�Ӻ���

**********************************************************/
void delayms(unsigned int ms)
{
  unsigned char k;

  while (ms--)
  {
    for (k = 0; k < 114; k++)
      ;
  }
}

/**********************************************************

ɨ��������Ӻ���

�ڱ���������AΪ�͵�ƽ�ڼ䣺

����������B��0��1Ϊ��ת������������B��1��0Ϊ��ת��

**********************************************************/
void scan_encoder(void) 
{ 
   static  bit  Curr_b;  //����һ�����������浱ǰB�ź� 
   static  bit  Last_b;  //����һ�������������ϴ�B���ź� 
   static  bit  update= 0;

   if( BMA && BMB)           //��������ת���˳�
   {
     update = 0; 
     return;
   }

   Last_b = BMB;       //��¼B�ź�

   while(!BMA)                //�ȴ�A�ɵͱ��
   { 
     Curr_b = BMB;     //��¼�ȴ��ڼ��B�ź�(ָ��ǰB�ź�)
     update = 1;
   
   	if(!BMC)                //��������ťʱ
     {
       counter = 0;            //������Ԫ����(��λ)
       delayms(10);
     }
   
   
   } 

   if(update)
   {
   update = 0 ;
     if( (Last_b == 0)&&(Curr_b== 1) ) //B��0��1Ϊ��ת
     { 
   if(counter == 255)
       return;
       counter++;          //��ת������
     } 
     else if( (Last_b == 1)&&(Curr_b == 0) ) //B��1��0Ϊ��ת
     { 
       if(counter == 0)
       return;
       counter--;         //��ת������
     } 
   }
}

/**********************************************************

������

**********************************************************/
void  main(void)
{
   P0 = 0xff;
   P1 = 0xff;
   P2 = 0xff;

   T2CON = 0x00;               //����T2CON�Ĵ���         
   TH2 = 0xfc;                 //1ms��ʱ
   TL2 = 0x66;
   ET2 = 1;                    //����Timer2�ж�
   EA = 1;                     //���ж�����
   TR2 = 1;                    //������ʱ��2
   counter = 0;                //������Ԫ����

   while(1)
   {

   scan_encoder();
    if(!BMC)                //��������ťʱ
     {
       counter = 0;            //������Ԫ����(��λ)
       delayms(10);
     } 
   }
}

/*********************************************************

Timer2�жϺ���

**********************************************************/
void  timer2() interrupt 5 
{ 
   TR2 = 0;
   TF2 = 0;                         //�ֹ����жϱ�־  
   TH2 = 0xfc;                      //1ms��ʱ����
   TL2 = 0x66;

   if(n >= 3)                       //3λ�������ʾ
   {
     n = 0;
     shift = 0x7f;                  //��λ���ֵ
     P2 = 0xff;                     //�ر���ʾ
   }
   else
   {
     display[0] = counter%10;       //��λ����
     display[1] = (counter%100)/10; //ʮλ����
     display[2] = counter/100;      //��λ����
     
     if(display[2] == 0)
     {
       display[2] = 0x0a;           //��λΪ0,����ʾ
       if(display[1] == 0)
       display[1]  =0x0a;           //ʮλΪ0,����ʾ
}

     P0 = LEDData[display[n++]];    //�Ͷ���
     P2 = shift;                    //��λ��
     shift = (shift>>1)|0x80;       //����λ��
   }
   TR2 = 1;
}

/*********************************************************/
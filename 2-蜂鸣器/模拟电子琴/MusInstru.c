
#include "MusInstru.h"

/* ��������ʱ���� */
void delay(void)
{
	uchar i;
	for (i=300;i>0;i--);
}

/* ��ɨ�躯�� */
uchar getkey(void)
{
	uchar scancode,tmpcode;

	if ((P1&0xf0)==0xf0)			
		return(0);

	scancode = 0xfe;
	while((scancode&0x10)!=0)		// ����ɨ��
	{
		P1 = scancode;				// �����ɨ����
		if ((P1&0xf0)!=0xf0)		// �����м�����
		{
			tmpcode = (P1&0xf0)|0x0f;

			/* ���������ֽ��룬Ϊ1��λ����Ӧ���к��� */
			return((~scancode)+(~tmpcode));
		}
		else scancode = (scancode<<1)|0x01;		// ��ɨ��������һλ
	}
}

/* ��ʱ��0�жϷ����ӳ��� */
void time0_int(void) interrupt 1 using 0
{
	/* ���ü�����ֵ */
  	TH0 = STH0;
  	TL0 = STL0; 
   	P36=~P36; 							// ���࣬�����������
}

/* ������ */
void main()
{
	uchar key,k;

	TMOD = 0x01;							// T0��������ʽ1

	ET0 = 1;
	EA = 1;

 	while(1)
    {
		P1 = 0xf0;			 					// ��ȫ0��ɨ����
		if ((P1&0xf0)!=0xf0)					// ���м�����
		{
			delay();							// ��ʱȥ����
			if ((P1&0xf0)!=0xf0)				// ��ʱ�����ж�һ�Σ�ȥ������Ӱ��
			{
				key = getkey();					// ���ü���ɨ�躯��

				// ���ݻ�ȡ�İ���λ�õõ�kֵ
				switch(key)
   				{
      				case 0x11:						// 1��1��
						k = 0;
						break;
					case 0x21:						// 1��2��
						k = 1;
						break;			
					case 0x41:						// 1��3��
						k = 2;
						break;
     				case 0x81:						// 1��4��
						k = 3;
						break;
					case 0x12:						// 2��1��
						k = 4;
						break;
					case 0x22:						// 2��2��
						k = 5;
						break;
					case 0x42:						// 2��3��
						k = 6;
						break;
					case 0x82:						// 2��4��
						k = 7;
						break;
					case 0x14:						// 3��1��
						k = 8;
						break;
					case 0x24:						// 3��2��
						k = 9;
						break;
					case 0x44:						// 3��3��
						k = 10;
						break;
					case 0x84:						// 3��4��
						k = 11;
						break;
					case 0x18:						// 3��4��
						k = 12;
						break;
					case 0x28:						// 3��4��
						k = 13;
						break;
					case 0x48:						// 3��4��
						k = 14;
						break;
					case 0x88:						// 3��4��
						k = 15;
						break;
					default:	
						break;
				}	

				P36 = ~P36; 						// ����
		
				/* �������õ�kֵ�趨������1�ļ�����ֵ */
      		    STH0 = tab[k]/256;
       		    STL0 = tab[k]%256; 

      		  	TR0 = 1;							// ��ʼ���� 

				P1 = 0xf0;			 				// ��ȫ0��ɨ����
				while ((P1&0xf0)!=0xf0)				// ��û���ɿ�����
				{
					P1 = 0xf0;	
				}

				TR1 = 0;							// �������ɿ�����ֹͣ�������������������
			}
		}
	}    
}

  


  





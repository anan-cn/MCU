//ʵ��20����swtich���Ŀ���P0��8λLED�ĵ���״̬
#include<reg51.h>  //������Ƭ���Ĵ�����ͷ�ļ�
sbit K5=P1^4;     //��K5λ����ΪP1.4
/*****************************
�������ܣ���ʱһ��ʱ��
*****************************/
void delay(void)
{
 unsigned int n;
 for(n=0;n<20000;n++)
        ;
}
/*****************************
�������ܣ�������
*****************************/
void main(void)
{  
   unsigned char i;
	i=0;    //��i��ʼ��Ϊ0
	while(1)
	 {
		  if(K5==0)     //���S1������
		   {
			  delay();  //��ʱһ��ʱ�� ��������
			  if(K5==0) //����ٴμ�⵽S1������
			    i++;    //i����1
			  if(i==9)  //���i=9�����½�����Ϊ1
			    i=1;
				
		   }
		 switch(i)   //ʹ�ö��֧ѡ�����
				 {
				   case 1: P0=0xfe;  //��һ��LED��
							break;
					case 2: P0=0xfd;  //�ڶ���LED��
					      break;
					case 3:P0=0xfb;   //������LED��
					      break;
					case 4:P0=0xf7;   //���ĸ�LED��
					      break;
					case 5:P0=0xef;   //�����LED��
					      break;
					case 6:P0=0xdf;   //������LED��
					      break;
					case 7:P0=0xbf;   //���߸�LED��
				         break;
					case 8:P0=0x7f;   //�ڰ˸�LED��
					      break;
					default:   //ȱʡֵ���ر�����LED
					      P0=0xff;
				 }
		 }	  
}
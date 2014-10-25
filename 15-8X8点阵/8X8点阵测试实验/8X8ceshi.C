#include <AT89X52.H>  
#include "74HC595.H"
unsigned char code taba[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; 
unsigned char code tabb[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; 
void delay1(void) 
{ 
  unsigned char i,j,k; 
  for(k=10;k>0;k--) 
  for(i=20;i>0;i--) 
  for(j=248;j>0;j--); 
} 

void main(void) 
{ 
  unsigned char i,j; 
  while(1) 
    { 
     for(j=0;j<3;j++)//从左到右3次
        { 

          for(i=0;i<8;i++) 
            { 

		Ser_IN(taba[i]);//8X8点阵列扫描
	          Ser_IN(0xff);//8X8点阵行送扫描数据
	          Par_OUT();//74HC595输出显示
              delay1(); 
            } 

        } 

      for(j=0;j<3;j++)//from right to left 3 time 
        { 
          for(i=0;i<8;i++) 
            { 
			    Ser_IN(taba[7-i]);//8X8点阵列扫描
	          Ser_IN(0xff);//8X8点阵行送扫描数据
	          Par_OUT();//74HC595输出显示
              delay1(); 

            } 

        } 

 for(j=0;j<3;j++)//从上到下 3次 

        { 

for(i=0;i<8;i++) 

            { 


			  Ser_IN(0x00);//8X8点阵列扫描
	          Ser_IN(tabb[i]);//8X8点阵行送扫描数据
	          Par_OUT();//74HC595输出显示

          

              delay1(); 

            } 

        } 
      for(j=0;j<3;j++)//从下到上3次 

        { 

          for(i=0;i<8;i++) 

            { 

             Ser_IN(0x00);//8X8点阵列扫描
	          Ser_IN(tabb[7-i]);//8X8点阵行送扫描数据
	          Par_OUT();//74HC595输出显示

              delay1(); 

            } 

        } 

    } 

} 
 


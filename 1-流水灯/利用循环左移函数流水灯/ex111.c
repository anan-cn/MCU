

#include<reg51.h>
#include <intrins.h>


void delayms(unsigned char ms)	
// 延时子程序
{						
	unsigned char i;
	while(ms--)
	{
		for(i = 0; i < 120; i++);
	}
}

main()
{
	unsigned char LED;
LED = 0xfe;
	P0 = LED;
	
	while(1)
	{
		delayms(250);			
		LED = _crol_(LED,1);		//循环左移1位，点亮下一个LED
		P0 = LED;
	}
}
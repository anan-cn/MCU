//将数据"0x0f"写入AT24C08再读出送P0口显示
#include <reg52.h>        //  包含51单片机寄存器定义的头文件
#include <intrins.h>      //包含_nop_()函数定义的头文件
#define	OP_READ	0xa1		// 器件地址以及读取操作,0xa1即为1010 0001B
#define	OP_WRITE 0xa0		// 器件地址以及写入操作,0xa1即为1010 0000B
sbit SDA=P3^5;          //将串行数据总线SDA位定义在为P3.5引脚
sbit SCL=P3^4;         //将串行时钟总线SDA位定义在为P3.4引脚

/*****************************************************
函数功能：延时1ms
(3j+2)*i=(3×33+2)×10=1010(微秒)，可以认为是1毫秒
***************************************************/
void delay1ms()
{
   unsigned char i,j;	
	 for(i=0;i<10;i++)
	  for(j=0;j<33;j++)
	   ;		 
 }

/*****************************************************
函数功能：延时若干毫秒
入口参数：n
***************************************************/
 void delaynms(unsigned char n)
 {
   unsigned char i;
	for(i=0;i<n;i++)
	   delay1ms();
 }
/***************************************************
函数功能：开始数据传送
***************************************************/
void start()
// 开始位
{
	SDA = 1;    //SDA初始化为高电平“1”
   SCL = 1;    //开始数据传送时，要求SCL为高电平“1”
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	SDA = 0;    //SDA的下降沿被认为是开始信号
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	SCL = 0;    //SCL为低电平时，SDA上数据才允许变化(即允许以后的数据传递）  
}
/***************************************************
函数功能：结束数据传送
***************************************************/
void stop()
// 停止位
{
	SDA = 0;     //SDA初始化为低电平“0”	_n
	SCL = 1;     //结束数据传送时，要求SCL为高电平“1”
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	SDA = 1;    //SDA的上升沿被认为是结束信号
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	SDA=0;
	SCL=0;
}
/***************************************************
函数功能：从AT24Cxx读取数据
出口参数：x
***************************************************/
unsigned char ReadData()
// 从AT24Cxx移入数据到MCU
{
	unsigned char i;
	unsigned char x;   //储存从AT24Cxx中读出的数据
	for(i = 0; i < 8; i++)
	{
		SCL = 1;                //SCL置为高电平
		x<<=1;                  //将x中的各二进位向左移一位
		x|=(unsigned char)SDA;  //将SDA上的数据通过按位“或“运算存入x中
		SCL = 0;                        //在SCL的下降沿读出数据
	}
	return(x);                //将读取的数据返回
}
/***************************************************
函数功能：向AT24Cxx的当前地址写入数据
入口参数：y (储存待写入的数据）
***************************************************/
//在调用此数据写入函数前需首先调用开始函数start(),所以SCL=0
bit WriteCurrent(unsigned char y)
{
	unsigned char i;
	bit ack_bit;               //储存应答位
	for(i = 0; i < 8; i++)		// 循环移入8个位
	{
    	SDA = (bit)(y&0x80);   //通过按位“与”运算将最高位数据送到S
		                                  //因为传送时高位在前，低位在后
		_nop_();            //等待一个机器周期   
	   SCL = 1;            //在SCL的上升沿将数据写入AT24Cxx      
   	_nop_();            //等待一个机器周期 
	  _nop_();             //等待一个机器周期       
		
	  	SCL = 0;            //将SCL重新置为低电平，以在SCＬ线形成传送数据所需的８个脉冲
		y <<= 1;           //将y中的各二进位向左移一位
	}
	SDA = 1;			  // 发送设备（主机）应在时钟脉冲的高电平期间(SCL=1)释放SDA线，
	                //以让SDA线转由接收设备(AT24Cxx)控制
	_nop_();        //等待一个机器周期 
	_nop_();        //等待一个机器周期 
	SCL = 1;       //根据上述规定，SCL应为高电平
	_nop_();       //等待一个机器周期 
	_nop_();       //等待一个机器周期 
	_nop_();       //等待一个机器周期 
	_nop_();       //等待一个机器周期 
	ack_bit = SDA; //接受设备（AT24Cxx)向SDA送低电平，表示已经接收到一个字节
	               //若送高电平，表示没有接收到，传送异常
	SCL = 0;       //SCL为低电平时，SDA上数据才允许变化(即允许以后的数据传递）
	return  ack_bit;			// 返回AT24Cxx应答位
}
/***************************************************
函数功能：向AT24Cxx中的指定地址写入数据
入口参数：add (储存指定的地址）；dat(储存待写入的数据）
***************************************************/
void WriteSet(unsigned char add, unsigned char dat)
// 在指定地址addr处写入数据WriteCurrent
{
	start();               //开始数据传递
	WriteCurrent(OP_WRITE);  //选择要操作的AT24Cxx芯片，并告知要对其写入数据
	WriteCurrent(add);       //写入指定地址
	WriteCurrent(dat);       //向当前地址（上面指定的地址）写入数据
	stop();                //停止数据传递
	delaynms(4);	       //1个字节的写入周期为1ms, 最好延时1ms以上
}
/***************************************************
函数功能：从AT24Cxx中的当前地址读取数据
出口参数：x (储存读出的数据） 
***************************************************/
unsigned char ReadCurrent()
{
	unsigned char x;
	start();               //开始数据传递
	WriteCurrent(OP_READ);   //选择要操作的AT24Cxx芯片，并告知要读其数据
	x=ReadData();         //将读取的数据存入x
	stop();                //停止数据传递
	return x;              //返回读取的数据
}
/***************************************************
函数功能：从AT24Cxx中的指定地址读取数据
入口参数：set_addr
出口参数：x 
***************************************************/
unsigned char ReadSet(unsigned char set_addr)
// 在指定地址读取
{
	start();                      //开始数据传递
	WriteCurrent(OP_WRITE);       //选择要操作的AT24Cxx芯片，并告知要对其写入数据
	WriteCurrent(set_addr);       //写入指定地址
	return(ReadCurrent());        //从指定地址读出数据并返回
}
/***************************************************
函数功能：主函数
***************************************************/
main(void)
{
   SDA = 1;           // SDA=1,SCL=1,使主从设备处于空闲状态
	SCL = 1;  	       
   WriteSet(0x36,0x0f);   //在指定地址“0x36”中写入数据“0x0f”
	P0=ReadSet(0x36);      //从指定地址“0x36中读取数据并送P1口显示

}


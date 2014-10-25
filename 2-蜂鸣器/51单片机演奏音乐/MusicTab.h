/*  定义音符表  */
//  音频变量名 定时器初值     音频率值  音名 
#define	A	  0xEFA3     //  110.000Hz  A
#define	 As   0xF08E     //  116.541Hz   A#
#define	B	  0xF16C     //  123.471Hz  B
#define	c	  0xF23D     //  130.813Hz  c
#define	 cs   0xF303     //  138.591Hz   c#
#define	d	  0xF3BE     //  146.832Hz  d
#define	 ds   0xF46E     //  155.563Hz   d#
#define	e	  0xF514     //  164.814Hz  e
#define	f	  0xF5B1     //  174.614Hz  
#define	 fs   0xF645     //  184.997Hz   f#
#define	g	  0xF6D1     //  195.998Hz  g
#define	 gs   0xF755     //  207.652Hz   g#
#define	a	  0xF7D1     //  220.000Hz  a
#define	 as   0xF847     //  233.082Hz   a#
#define	b	  0xF8B6     //  246.942Hz  b
#define	c1	  0xF91F     //  261.626Hz  c1 (中央C)
#define	 c1s  0xF982     //  277.183Hz   c1#
#define	d1	  0xF9DF     //  293.665Hz  d1
#define	 d1s  0xFA37     //  311.127Hz   d1#
#define	e1	  0xFA8A     //  329.628Hz  e1
#define	f1	  0xFAD9     //  349.228Hz  f1
#define	 f1s  0xFB23     //  369.994Hz   f1#
#define	g1	  0xFB68     //  391.995Hz  g1
#define	 g1s  0xFBAA     //  415.305Hz   g1#
#define	a1	  0xFBE9     //  440.000Hz  a1(标准音)
#define	 a1s  0xFC24     //  466.164Hz   a1#
#define	b1	  0xFC5B     //  493.883Hz  b1
#define	c2	  0xFC8F     //  523.251Hz  c2
#define	 c2s  0xFCC1     //  554.365Hz   c2#
#define	d2	  0xFCEF     //  587.330Hz  d2
#define	 d2s  0xFD1B     //  622.254Hz   d2#
#define	e2	  0xFD45     //  659.255Hz  e2
#define	f2	  0xFD6C     //  698.456Hz  f2
#define	 f2s  0xFD91     //  739.989Hz   f2#
#define	g2	  0xFDB4     //  783.991Hz  g2
#define	 g2s  0xFDD5     //  830.609Hz   g2#
#define	a2	  0xFDF4     //  880.000Hz  a2
#define	 a2s  0xFE12     //  932.328Hz   a2#
#define	b2	  0xFE2D     //  987.767Hz  b2
#define	c3	  0xFE48     // 1046.500Hz  c3
#define	 c3s  0xFE60     // 1108.730Hz   c3#
#define	d3	  0xFE78     // 1174.660Hz  d3
#define	 d3s  0xFE8E     // 1244.510Hz   d3# 
#define	e3	  0xFEA3     // 1318.510Hz  e3
#define	f3	  0xFEB6     // 1396.910Hz  f3
#define	 f3s  0xFEC9     // 1479.980Hz   f3#
#define	g3	  0xFEDA     // 1567.980Hz  g3
#define	 g3s  0xFEEB     // 1661.220Hz    g3#
#define	a3	  0xFEFA     // 1760.000Hz  a3
#define	 a3s  0xFF09     // 1864.660Hz   a3# 
#define	b3	  0xFF17     // 1975.530Hz  b3

//定义发声时值
//T*4全音符，T*2二分音符，T四分音符，T/2八分音符，T/4十六分音符
#define T	1000

//《兰花花》
code CNote MusicTab[] =
{  //	{音名,时值}
	{d2,T/2},{e2,T/2},{d2,T/2},{d2,T/4},{c2,T/4},{d2,T/2},{e2,T/2},{d2,T},
{c2,T/2},{d2,T/2},{a1,T/2},{g1,T/4},{g1,T/4},{f1,T/2},{d1,T+T/2},
{g1,T/2},{a1,T/2},{c2,T/2},{c2,T/2},{a1,T/2},{d2,T/2},{c2,T/2},{a1,T/2},
{g1,T/4},{a1,T/4},{g1,T/4},{f1,T/4},{d1,T/2},{c1,T/2},{d1,T*2},
{0,T},	{0,T},
	{0,0}		//结束标志
};

//《在那遥远的地方》
code CNote MusicTab1[] ={  //	{音名,时值}
{c2s,T/2},{e2,T/2},{f2s,T/2},{e2,T/4},{c2s,T/2},{c2s,T/2},{e2,T/2},
{f2s,T+T/2},{e2,T/4},{c2s,T/4},{c2s,T/2},{e2,T/2},{e2,T/2},{d2s,T/2},{c2s,T*2},
{c2s,T/2},{e2,T/2},{f2s,T/2},{e2,T/4},{c2s,T/4},{b1,T/2},{c2s,T/4},{b1,T/4},
{a1,T/2},{b1,T/2},{c2s,T/2},{e2,T/2},{a1,T/2},{b1,T/2},
{c2s,T/2},{b1,T/4},{a1,T/4},{g1s,T},{f1s,T*2+T},	
	{0,0}		//结束标志
};



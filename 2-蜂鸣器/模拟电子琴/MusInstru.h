/*****************************************/
/* Copyright (c) 2005, 通信工程学院      */
/* All rights reserved.                  */
/* 作    者：戴 佳						 */
/*****************************************/

#ifndef	_MUSINSTRU_H 		// 防止MusInstru.h被重复引用

#define	_MUSINSTRU_H

#include <reg52.h>
#include <absacc.h>
#include <stdio.h>	
#include <math.h>

#define uchar unsigned char
#define uint unsigned int

/* 音符与计数值对应表 */
uint code tab[]={64021,64103,64260,64400, 
                 64524,64580,64684,64777, 
                 64820,64898,64968,65030, 
                 65058,65110,65157,65178}; 

sbit P36 = P3^6;		// 此引脚输出脉冲

uchar STH0; 
uchar STL0; 

#endif

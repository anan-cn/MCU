/*****************************************/
/* Copyright (c) 2005, ͨ�Ź���ѧԺ      */
/* All rights reserved.                  */
/* ��    �ߣ��� ��						 */
/*****************************************/

#ifndef	_MUSINSTRU_H 		// ��ֹMusInstru.h���ظ�����

#define	_MUSINSTRU_H

#include <reg52.h>
#include <absacc.h>
#include <stdio.h>	
#include <math.h>

#define uchar unsigned char
#define uint unsigned int

/* ���������ֵ��Ӧ�� */
uint code tab[]={64021,64103,64260,64400, 
                 64524,64580,64684,64777, 
                 64820,64898,64968,65030, 
                 65058,65110,65157,65178}; 

sbit P36 = P3^6;		// �������������

uchar STH0; 
uchar STL0; 

#endif

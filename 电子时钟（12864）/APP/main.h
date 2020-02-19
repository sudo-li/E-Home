#ifndef _MAIN_H
#define _MAIN_H

#include "reg52.h"
#include "intrins.h"

#define uchar unsigned char
#define uint unsigned int 	
#define ulong unsigned long
	
sbit beep = P1^5;
	
#define ds1302init 0   //ds1302初始化时间标志

void Delay10ms(unsigned int c);


#endif



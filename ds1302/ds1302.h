#ifndef _DS1302_H
#define _DS1302_H

#include "main.h"

sbit DS_SCLK = P2^0;
sbit DS_IO = P2^1;
sbit DS_CE = P2^2;

extern uchar time[7];

void Init_ds1302(void);
void Read_ds1302time(void);//获取时间
void Write_ds1302(uchar addr, uchar dat);//写入时间
#endif


#ifndef _KEY_H
#define _KEY_H

#include "main.h"

sbit ADD = P3^2;  		//加
sbit RED = P3^3;		//减		
sbit ALARM = P3^4;		//闹钟
sbit SET = P3^5;		//设置

#define ADD_1	1		//加返回值
#define RED_2	2		//减返回值
#define ALARM_3	3		//闹钟返回值
#define SET_4	4		//设置返回值

extern uchar clock[3];			//clock[0]接收小时数据  clock[1]接收分钟数据 clock[2]是进入闹钟标志
extern uchar Alarm_clock[2];	//闹钟的时，分

uchar Key_Read(void);			//读取按键值的函数
void Key_Function(uchar temp);	//根据按键值实现功能的函数


#endif


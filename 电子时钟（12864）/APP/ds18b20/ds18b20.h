#ifndef _DS18B20_H
#define _DS18B20_H

#include "main.h"

sbit DSPORT = P1^6;
void Delay1ms(uint y);
int Ds18b20ReadTemp(void);//¶ÁÈ¡ÎÂ¶Èº¯Êý

#endif


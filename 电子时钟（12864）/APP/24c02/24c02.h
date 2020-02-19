#ifndef _24C02_H
#define _24C02_H

#include "main.h"

sbit I2C_SCL = P3^7;
sbit I2C_SDA = P3^6;

void At24c02Write(uchar addr,uchar dat);
uchar At24c02Read(uchar addr);


#endif


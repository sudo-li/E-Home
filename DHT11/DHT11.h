#ifndef _DHT11_H
#define _DHT11_H

#include "main.h"

sbit DHT11_PORT = P2^4;

uchar DHT11_Init(void);
uchar DHT11_Read_Data(uchar *zhumi);


#endif


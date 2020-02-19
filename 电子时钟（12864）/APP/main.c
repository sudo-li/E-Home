#include "main.h"
#include "lcd.h"			//显示头文件
#include "ds1302.h"			//温度传感器
#include "24c02.h"			//存储
#include "ds18b20.h"		//时钟
//#include "DHT11.h"
#include "key.h"			//按键

void Delay10ms(unsigned int c)
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

void main(void)
{	 
	uchar b = 50,n=10;
	TMOD|=0X01;					//选择为定时器0模式，工作方式1，仅用TR0打开启动。
	TH0 = 0xff;
	TL0 = 0x9c;
	ET0 = 1;
	EA = 1;	//使用定时器0中断
	Init_lcd();
	#if ds1302init 				//是否初始化时间
		Init_ds1302();
	#endif
	clear_all();
	display_graphic_8x16(1,1,&num[2][0]);
	display_graphic_8x16(1,8,&num[0][0]);
	display_graphic_8x16(3,8*12,O);
	display_graphic_8x16(3,8*13,F);
	display_graphic_8x16(3,8*14,F);
	while(1)
	{
		At24c02Write(1,0x00);
		if(At24c02Read(1) == 0x00)
			display_graphic_16x16(3,8*14,ri);
		Key_Function(Key_Read()); 		//按键读取函数并实现相应功能
		if(n == 10) 		//延时控制
		{
			time_display();   //时间显示函数
			n=0;
		}
		if(b == 50) 		//延时控制
		{
			Ds18b20_display(Ds18b20ReadTemp());     //温度显示函数
			//DHT11_display();      //湿度显示函数
			b=0;
		}
		if(clock[2] == 0x01) 		//判断闹钟标志
		{
			if(Alarm_clock[0] == time[2])    //检查闹钟是否到时
			{
				if(Alarm_clock[1] == time[1])
				{
					TR0 = 1;  //开启定时器0
					clear_8x16(3,8*13);
					display_graphic_8x16(3,8*13,F);
					display_graphic_8x16(3,8*14,F);
					clear_8x16(5,8*3);
					clear_8x16(5,8*4);
					clear_8x16(5,8*5);
					clear_8x16(5,8*6);
					clear_8x16(5,8*7);
					clock[2] = 0x00;
					clock[0] = 0x00;
					clock[1] = 0x00;
				}
			}
		}
		Delay10ms(1);
		b++;
		n++;
	}
}

void Timer0() interrupt 1
{
	static uint i;
	TH0=0xff;	
	TL0=0x9c;
	beep = ~beep;			//蜂鸣器
	i++;
	if(i==15000)   //可调整想多长时间
	{
		i=0;
		TR0 = 0;
	}	
}


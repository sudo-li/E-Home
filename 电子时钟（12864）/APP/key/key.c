#include "key.h"
#include "lcd.h"
#include "ds1302.h"
#include "24c02.h"

uchar clock[3];  		//clock[0]接收小时数据  clock[1]接收分钟数据 clock[2]是进入闹钟标志
uchar Alarm_clock[2]; 	//闹钟的时，分

uchar Key_Read()
{
	if((ADD == 0) || (RED == 0) || (ALARM == 0) || (SET) == 0)
	{
		Delay10ms(1); 	//延时去抖动
		if(ADD == 0)
		{
			while(!ADD);
			return ADD_1;
		}
		else if(RED == 0)
		{
			while(!RED);
			return RED_2;
		}
		else if(ALARM == 0)
		{
			while(!ALARM);
			return ALARM_3;
		}
		else if(SET == 0)
		{
			while(!SET);
			return SET_4;
		}
	}
	return 0;  //如果无则返回0
}

/********************************************************
数值加一函数
参数一用于按键检查 如果检查不对直接退出函数
参数二用于修改那个时间比如 i=1 则修改年，i=2 则修改月 以此类推
time全局外部数组 在ds1303.c中定义，顺序是 秒，分，时，日，月，星期，年
无返回值
*************************************************************/
void  Add_one(uchar temp,uchar i) 
{
	if(temp == ADD_1)//加一
	{
		Write_ds1302(0x8e,0x00);	//关闭写保护
		
		
		if(i == 1)
		{
			if((time[6] & 0x0f) == 0x09)  //判断是否需要进位 比如19到20  以下均是
			{
				time[6] >>= 4;  
				time[6] ++;
				time[6] <<= 4;
			}
			else
				time[6]++;
			Write_ds1302(0x8c,time[6]);
		}
		
		
		if(i == 2)
		{
			if((time[4] & 0x0f) == 0x09)
			{
				time[4] >>= 4;
				time[4] ++;
				time[4] <<= 4;
			}
			else
				time[4]++;
			if(time[4] == 0x13)
				time[4] = 0x01;
			Write_ds1302(0x88,time[4]);
		}
		
		
		if(i == 3)
		{
			if((time[3] & 0x0f) == 0x09)
			{
				time[3] >>= 4;
				time[3] ++;
				time[3] <<= 4;
			}
			else
				time[3]++;
			if(time[3] == 0x32)
				time[3] = 0x01;
			Write_ds1302(0x86,time[3]);
		}
		
		
		if(i == 4)
		{
			time[5]++;
			if(time[5] == 0x08)
				time[5] = 0x01;
			Write_ds1302(0x8a,time[5]);
		}
		
		
		if(i == 5)
		{
			if((time[2] & 0x0f) == 0x09)
			{
				time[2] >>= 4;
				time[2] ++;
				time[2] <<= 4;
			}
			else
				time[2]++;
			if(time[2] == 0x24)
				time[2] = 0x00;
			Write_ds1302(0x84,time[2]);
		}
		
		if(i == 6)
		{
			if((time[1] & 0x0f) == 0x09)
			{
				time[1] >>= 4;
				time[1] ++;
				time[1] <<= 4;
			}
			else
				time[1]++;
			if(time[1] == 0x60)
				time[1] = 0x00;
			Write_ds1302(0x82,time[1]);
		}
		
		if(i == 7)
		{
			if((time[0] & 0x0f) == 0x09)
			{
				time[0] >>= 4;
				time[0] ++;
				time[0] <<= 4;
			}
			else
				time[0]++;
			if(time[0] == 0x60)
				time[0] = 0x00;
			Write_ds1302(0x80,time[0]);
		}
		
		Write_ds1302(0x8e,0x80);  //打开写保护
	}
}

/********************************************************
数值减一函数
参数一用于按键检查 如果检查不对直接退出函数
参数二用于修改那个时间比如 i=1 则修改年，i=2 则修改月 以此类推
无返回值
*************************************************************/
void Red_one(uchar temp,uchar i)
{		
	if(temp == RED_2)
	{
		Write_ds1302(0x8e,0x00);//关闭写保护
		
		
		if(i == 1)
		{
			if((time[6] & 0x0f) == 0x00)
			{
				time[6] >>= 4;
				time[6] --;
				time[6] <<= 4;
				time[6] |= 0x09;
			}
			else
				time[6]--;
			Write_ds1302(0x8c,time[6]);
		}
		
		
		if(i == 2)
		{
			if((time[4] & 0x0f) == 0x00)
			{
				time[4] >>= 4;
				time[4] --;
				time[4] <<= 4;
				time[4] |= 0x09;
			}
			else
				time[4]--;
			if(time[4] == 0x00)
				time[4] = 0x12;
			Write_ds1302(0x88,time[4]);
		}
		
		
		if(i == 3)
		{
			if((time[3] & 0x0f) == 0x00)
			{
				time[3] >>= 4;
				time[3] --;
				time[3] <<= 4;
				time[3] |= 0x09;
			}
			else
				time[3]--;
			if(time[3] == 0x00)
				time[3] = 0x31;
			Write_ds1302(0x86,time[3]);
		}
		
		if(i == 4)
		{
			time[5]--;
			if(time[5] == 0x00)
				time[5] = 0x07;
			Write_ds1302(0x8a,time[5]);
		}
		
		
		if(i == 5)
		{
			if((time[2] & 0x0f) == 0x00)
			{
				time[2] >>= 4;
				time[2] --;
				time[2] <<= 4;
				time[2] |= 0x09;
			}
			else
				time[2]--;
			Write_ds1302(0x84,time[2]);
		}
		
		if(i == 6)
		{
			if((time[1] & 0x0f) == 0x00)
			{
				time[1] >>= 4;
				time[1] --;
				time[1] <<= 4;
				time[1] |= 0x09;
			}
			else
				time[1]--;
			Write_ds1302(0x82,time[1]);
		}
		
		if(i == 7)
		{
			if((time[0] & 0x0f) == 0x00)
			{
				time[0] >>= 4;
				time[0] --;
				time[0] <<= 4;
				time[0] |= 0x09;
			}
			else
				time[0]--;
			Write_ds1302(0x80,time[0]);
		}
		
		Write_ds1302(0x8e,0x80);  //打开写保护
	}
}

/********************************************************
按键功能实现函数（调整时间，闹钟）
参数一用于检查是哪个功能
无返回值
*************************************************************/
void Key_Function(uchar temp)
{
	static uchar i = 0,k = 0,filg = 1,filg1 = 1,j = 0,s = 0;
	if(((k == 1) || (temp == SET_4)) && (filg == 1))//进入设置时间模式
	{
		filg1 = 0;
		if(temp == SET_4)  //实现调整时间闪烁提示
			i++;
		k = 1;
		switch(i)
		{
			case 1:clear_8x16(1,8*2); clear_8x16(1,8*3); break;
			case 2:clear_8x16(1,8*6); clear_8x16(1,8*7); break;
			case 3:clear_8x16(1,8*10); clear_8x16(1,8*11); break;
			case 4:clear_8x16(1,8*15); break;
			case 5:clear_8x16(3,8*3); clear_8x16(3,8*4); break;
			case 6:clear_8x16(3,8*6); clear_8x16(3,8*7); break;
			case 7:clear_8x16(3,8*9); clear_8x16(3,8*10); break;
			case 8:i = 0; k = 0; filg1 = 1;
		}
		Add_one(temp,i);
		Red_one(temp,i);
	}
	if(((s == 1) || (temp == ALARM_3)) && (filg1 == 1))//设置闹钟时间
	{
		s = 1;
		clock[2] = 0x01; //进入闹钟标志置一
		if(k == 0)
		{
			
			clock[0] = time[2];
			clock[1] = time[1];
			clear_8x16(3,8*13);  //清除OFF 的前两个字母
			clear_8x16(3,8*14);
		}
		filg = 0;
		k = 1;
		display_graphic_8x16(3,8*13,N); //显示ON
		display_graphic_8x16(5,8*3,&num[(clock[0] / 16)][0]);
		display_graphic_8x16(5,8*4,&num[(clock[0] & 0x0f)][0]);
		display_graphic_8x16(5,8*5,mao_hao);
		display_graphic_8x16(5,8*6,&num[(clock[1] / 16)][0]);
		display_graphic_8x16(5,8*7,&num[(clock[1] & 0x0f)][0]);
		if(temp == SET_4)  //计数按了几次
			j++;
		switch(j)
		{
			case 1:clear_8x16(5,8*3);clear_8x16(5,8*4);break;
			case 2:clear_8x16(5,8*6);clear_8x16(5,8*7);break;
			case 3:filg = 1; s = 0;
		}
		if(j == 1)
		{
			if(temp == ADD_1)
			{
				if((clock[0] & 0x0f) == 0x09) //判断是否需要进位 比如19到20
				{
					clock[0] >>= 4;
					clock[0] ++;
					clock[0] <<= 4;
				}
				else
					clock[0]++;
			}			
			if(temp == RED_2)
			{
				if((clock[0] & 0x0f) == 0x00)
				{
					clock[0] >>= 4;
					clock[0] --;
					clock[0] <<= 4;
					clock[0] |= 0x09;
				}
				else
					clock[0]--;
			}
		}
		if(j == 2)
		{
			if(temp == ADD_1)
			{
				if((clock[1] & 0x0f) == 0x09)
				{
					clock[1] >>= 4;
					clock[1] ++;
					clock[1] <<= 4;
				}
				else
					clock[1]++;
			}
			
			if(temp == RED_2)
			{
				if((clock[1] & 0x0f) == 0x00)
				{
					clock[1] >>= 4;
					clock[1] --;
					clock[1] <<= 4;
					clock[1] |= 0x09;
				}
				else
					clock[1]--;
			}
		}
		if(j == 3) //表示设置闹钟完成 设置值存入全局数组
		{
			Alarm_clock[1] = clock[1];
			Alarm_clock[0] = clock[0];
			j = 0;
		}
	}
}





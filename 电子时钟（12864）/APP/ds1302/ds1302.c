#include "ds1302.h"
#include "lcd.h"

uchar code read_addr[]={0x81, 0x83, 0x85, 0x87, 0x89,0x8b,0x8d};//地址
uchar code write_addr[]={0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
uchar code set[]={0x00,0x21,0x17,0x18,0x12,0x03,0x19};//写入的顺序是 秒，分，时，日，月，星期，年
uchar time[7] = 0;//获取到的时间数组

void Write_ds1302(uchar addr, uchar dat)
{
	uchar n;
	DS_CE = 0;
	_nop_();

	DS_SCLK = 0;//先将SCLK置低电平。
	_nop_();
	DS_CE = 1; //然后将RST(CE)置高电平。
	_nop_();

	for (n=0; n<8; n++)//开始传送八位地址命令
	{
		DS_IO = addr & 0x01;//数据从低位开始传送
		addr >>= 1;
		DS_SCLK = 1;//数据在上升沿时，DS1302读取数据
		_nop_();
		DS_SCLK = 0;
		_nop_();
	}
	for (n=0; n<8; n++)//写入8位数据
	{
		DS_IO = dat & 0x01;
		dat >>= 1;
		DS_SCLK = 1;//数据在上升沿时，DS1302读取数据
		_nop_();
		DS_SCLK = 0;
		_nop_();	
	}	
		 
	DS_CE = 0;//传送数据结束
	_nop_();
}

uchar Read_ds1302(uchar addr)
{
	uchar n,dat,dat1;
	DS_CE = 0;
	_nop_();

	DS_SCLK = 0;//先将SCLK置低电平。
	_nop_();
	DS_CE = 1;//然后将RST(CE)置高电平。
	_nop_();

	for(n=0; n<8; n++)//开始传送八位地址命令
	{
		DS_IO = addr & 0x01;//数据从低位开始传送
		addr >>= 1;
		DS_SCLK = 1;//数据在上升沿时，DS1302读取数据
		_nop_();
		DS_SCLK = 0;//DS1302下降沿时，放置数据
		_nop_();
	}

	_nop_();
	for(n=0; n<8; n++)//读取8位数据
	{
		dat1 = DS_IO;//从最低位开始接收
		dat = (dat>>1) | (dat1<<7);
		DS_SCLK = 1;
		_nop_();
		DS_SCLK = 0;//DS1302下降沿时，放置数据
		_nop_();
	}

	DS_CE = 0;
	_nop_();	//以下为DS1302复位的稳定时间,必须的。
	DS_SCLK = 1;
	_nop_();
	DS_IO = 0;
	_nop_();
	DS_IO = 1;
	_nop_();
	return dat;	
}
void Init_ds1302()
{
	uchar i;
	Write_ds1302(0x8e,0x00);//关闭写保护
	for(i=0;i<7;i++)
	{
		Write_ds1302(write_addr[i],set[i]);
	}
	Write_ds1302(0x8e,0x80);
}


void Read_ds1302time()//获取时间
{
	uchar i;
	for(i=0;i<7;i++)
	{
		time[i]=Read_ds1302(read_addr[i]);
	}
}


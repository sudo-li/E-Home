#include "ds1302.h"
#include "lcd.h"

uchar code read_addr[]={0x81, 0x83, 0x85, 0x87, 0x89,0x8b,0x8d};//��ַ
uchar code write_addr[]={0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
uchar code set[]={0x00,0x21,0x17,0x18,0x12,0x03,0x19};//д���˳���� �룬�֣�ʱ���գ��£����ڣ���
uchar time[7] = 0;//��ȡ����ʱ������

void Write_ds1302(uchar addr, uchar dat)
{
	uchar n;
	DS_CE = 0;
	_nop_();

	DS_SCLK = 0;//�Ƚ�SCLK�õ͵�ƽ��
	_nop_();
	DS_CE = 1; //Ȼ��RST(CE)�øߵ�ƽ��
	_nop_();

	for (n=0; n<8; n++)//��ʼ���Ͱ�λ��ַ����
	{
		DS_IO = addr & 0x01;//���ݴӵ�λ��ʼ����
		addr >>= 1;
		DS_SCLK = 1;//������������ʱ��DS1302��ȡ����
		_nop_();
		DS_SCLK = 0;
		_nop_();
	}
	for (n=0; n<8; n++)//д��8λ����
	{
		DS_IO = dat & 0x01;
		dat >>= 1;
		DS_SCLK = 1;//������������ʱ��DS1302��ȡ����
		_nop_();
		DS_SCLK = 0;
		_nop_();	
	}	
		 
	DS_CE = 0;//�������ݽ���
	_nop_();
}

uchar Read_ds1302(uchar addr)
{
	uchar n,dat,dat1;
	DS_CE = 0;
	_nop_();

	DS_SCLK = 0;//�Ƚ�SCLK�õ͵�ƽ��
	_nop_();
	DS_CE = 1;//Ȼ��RST(CE)�øߵ�ƽ��
	_nop_();

	for(n=0; n<8; n++)//��ʼ���Ͱ�λ��ַ����
	{
		DS_IO = addr & 0x01;//���ݴӵ�λ��ʼ����
		addr >>= 1;
		DS_SCLK = 1;//������������ʱ��DS1302��ȡ����
		_nop_();
		DS_SCLK = 0;//DS1302�½���ʱ����������
		_nop_();
	}

	_nop_();
	for(n=0; n<8; n++)//��ȡ8λ����
	{
		dat1 = DS_IO;//�����λ��ʼ����
		dat = (dat>>1) | (dat1<<7);
		DS_SCLK = 1;
		_nop_();
		DS_SCLK = 0;//DS1302�½���ʱ����������
		_nop_();
	}

	DS_CE = 0;
	_nop_();	//����ΪDS1302��λ���ȶ�ʱ��,����ġ�
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
	Write_ds1302(0x8e,0x00);//�ر�д����
	for(i=0;i<7;i++)
	{
		Write_ds1302(write_addr[i],set[i]);
	}
	Write_ds1302(0x8e,0x80);
}


void Read_ds1302time()//��ȡʱ��
{
	uchar i;
	for(i=0;i<7;i++)
	{
		time[i]=Read_ds1302(read_addr[i]);
	}
}


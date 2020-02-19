#include "main.h"
#include "lcd.h"			//��ʾͷ�ļ�
#include "ds1302.h"			//�¶ȴ�����
#include "24c02.h"			//�洢
#include "ds18b20.h"		//ʱ��
//#include "DHT11.h"
#include "key.h"			//����

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
	TMOD|=0X01;					//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1������TR0��������
	TH0 = 0xff;
	TL0 = 0x9c;
	ET0 = 1;
	EA = 1;	//ʹ�ö�ʱ��0�ж�
	Init_lcd();
	#if ds1302init 				//�Ƿ��ʼ��ʱ��
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
		Key_Function(Key_Read()); 		//������ȡ������ʵ����Ӧ����
		if(n == 10) 		//��ʱ����
		{
			time_display();   //ʱ����ʾ����
			n=0;
		}
		if(b == 50) 		//��ʱ����
		{
			Ds18b20_display(Ds18b20ReadTemp());     //�¶���ʾ����
			//DHT11_display();      //ʪ����ʾ����
			b=0;
		}
		if(clock[2] == 0x01) 		//�ж����ӱ�־
		{
			if(Alarm_clock[0] == time[2])    //��������Ƿ�ʱ
			{
				if(Alarm_clock[1] == time[1])
				{
					TR0 = 1;  //������ʱ��0
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
	beep = ~beep;			//������
	i++;
	if(i==15000)   //�ɵ�����೤ʱ��
	{
		i=0;
		TR0 = 0;
	}	
}


#ifndef _LCD_H
#define _LCD_H

#include "main.h"

sbit L_SCLK = P1^0;
sbit L_SDA = P1^1;
sbit L_RS = P1^2;
sbit L_CS = P1^3;
sbit L_RESET = P1^4;

extern char code nian[];
extern char code yue[];
extern char code ri[];
extern char code mao_hao[];
extern char code jia_hao[];
extern char code jian_hao[];
extern char code dian[];
extern char code wendu[];
extern char code baifen_hao[];
extern char code O[];
extern char code N[];
extern char code F[];
//extern char code num0[];
//extern char code num1[];
//extern char code num2[];
//extern char code num3[];
//extern char code num4[];
//extern char code num5[];
//extern char code num6[];
//extern char code num7[];
//extern char code num8[];
//extern char code num9[];

extern char code num[10][16];
extern uchar time[7];

void Init_lcd(void);//��ʼ��
void clear_all(void);//ȫ������
//void full_display(void);//ȫ����ʾ
void clear_8x16(uchar page, uchar column);//�������
void display_graphic_16x16(uchar page, uchar column, uchar *dp);//��ʾ16*16����
void display_graphic_8x16(uchar page, uchar column, uchar *dp);//��ʾ8*16���ֻ��ַ�

void time_display(void);//��ʾʱ��
void Ds18b20_display(int temp);//��ʾ�¶�
//void DHT11_display(void);

#endif


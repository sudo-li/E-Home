#ifndef _KEY_H
#define _KEY_H

#include "main.h"

sbit ADD = P3^2;  		//��
sbit RED = P3^3;		//��		
sbit ALARM = P3^4;		//����
sbit SET = P3^5;		//����

#define ADD_1	1		//�ӷ���ֵ
#define RED_2	2		//������ֵ
#define ALARM_3	3		//���ӷ���ֵ
#define SET_4	4		//���÷���ֵ

extern uchar clock[3];			//clock[0]����Сʱ����  clock[1]���շ������� clock[2]�ǽ������ӱ�־
extern uchar Alarm_clock[2];	//���ӵ�ʱ����

uchar Key_Read(void);			//��ȡ����ֵ�ĺ���
void Key_Function(uchar temp);	//���ݰ���ֵʵ�ֹ��ܵĺ���


#endif


#include "DHT11.h"
#include "ds18b20.h"

void Delay10us(uchar b)
{
	uchar a;
	for(; b>0; b--)
	{
		for(a=2; a>0; a--);
	}
}

void DHT11_Rst()//��λDHT11
{
	DHT11_PORT = 0;
	Delay1ms(20);
	DHT11_PORT = 1;
	Delay10us(3);
}
//�ȴ�DHT11�Ļ�Ӧ
//����1:δ��⵽DHT11�Ĵ���
//����0:����
uchar DHT11_Check()
{
	uchar retry = 0;
	while(DHT11_PORT && retry<10)
	{
		retry++;
		Delay10us(1);
	}
	if(retry >= 10) return 1;
	else retry = 0;
	while(!DHT11_PORT && retry<10)
	{
		retry++;
		Delay10us(1);
	}	
	if(retry >= 10) return 1;
	else return 0;
}
//��DHT11��ȡһ��λ
//����ֵ��1/0
uchar DHT11_Read_Bit(void) 			 
{
 	uchar retry=0;
	while(DHT11_PORT && retry<10)//�ȴ���Ϊ�͵�ƽ
	{
		retry++;
		Delay10us(1);
	}
	retry=0;
	while(!DHT11_PORT&&retry<100)//�ȴ���ߵ�ƽ
	{
		retry++;
		Delay10us(1);
	}
	Delay10us(4);//�ȴ�40us
	if(DHT11_PORT)return 1;
	else return 0;		   
}

//��DHT11��ȡһ���ֽ�
//����ֵ������������
uchar DHT11_Read_Byte(void)    
{        
    uchar i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}

//��DHT11��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
uchar DHT11_Read_Data(uchar *zhumi)    
{        
 	uchar buf[5];
	uchar i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*zhumi=buf[0];
			//*xhumi=buf[1];
		}
	}else return 1;
	return 0;	    
}

uchar DHT11_Init()
{
	DHT11_Rst();  //��λDHT11
	return DHT11_Check();//�ȴ�DHT11�Ļ�Ӧ
}





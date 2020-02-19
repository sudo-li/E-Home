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

void DHT11_Rst()//复位DHT11
{
	DHT11_PORT = 0;
	Delay1ms(20);
	DHT11_PORT = 1;
	Delay10us(3);
}
//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
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
//从DHT11读取一个位
//返回值：1/0
uchar DHT11_Read_Bit(void) 			 
{
 	uchar retry=0;
	while(DHT11_PORT && retry<10)//等待变为低电平
	{
		retry++;
		Delay10us(1);
	}
	retry=0;
	while(!DHT11_PORT&&retry<100)//等待变高电平
	{
		retry++;
		Delay10us(1);
	}
	Delay10us(4);//等待40us
	if(DHT11_PORT)return 1;
	else return 0;		   
}

//从DHT11读取一个字节
//返回值：读到的数据
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

//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
uchar DHT11_Read_Data(uchar *zhumi)    
{        
 	uchar buf[5];
	uchar i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
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
	DHT11_Rst();  //复位DHT11
	return DHT11_Check();//等待DHT11的回应
}





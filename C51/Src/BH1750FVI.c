#include"BH1750FVI.h"
#include"uart.h"
#include<reg52.h>
#include <intrins.h>
#include"time.h"
#include"delay.h"
 
sbit SDA=P2^0;
sbit SCL=P2^1;
 
typedef   unsigned char BYTE;
BYTE BUF[8];
 
unsigned char num;
unsigned char a,b,sec,count;
unsigned char ge,shi,bai,qian,wan;            //显示变量
 
int dis_data,dis_data1;                       //变量
 
//初始化
void BH1750_init()
{
		Single_Write_BH1750(0x01);
}
 

//IIC发送起始信号
void BH1750_Start()
{
		SDA=1;
		NOP();
		SCL=1;
		NOP();
		SDA=0;
		NOP();
		SCL=0;
		NOP();
}
 
//IIC发送停止信号
void BH1750_Stop()
{
		SDA=0;
		NOP();
		SCL=1;
		NOP();
		SDA=1;
		NOP();
}
 
//写入一个字节
void BH1750_Write_Byte(unsigned char dat)
{
		unsigned char i,temp;
		temp=dat;
		for(i=0;i<8;i++)
		{
			temp=temp<<1;
			SDA=CY;
			NOP();
			SCL=1;
			NOP();
			SCL=0;
			NOP();
		}
		SDA=0;  //注意：以下6句不可少，否则读到的数据是不正常的，如00212等
		NOP();
		SCL=1;
		NOP();
		SCL=0;  
		NOP();
}
 
//IIC读取一个字节
unsigned char BH1750_Read_Byte()
{
		unsigned char i,x=0;
		SDA=1;
		NOP();
		for(i=0;i<8;i++)
		{
		x=x<<1;
		SCL=1;
		NOP();
		x=x|SDA;
		SCL=0;
		NOP();
		}
		return x;
}
 
//响应
void Responds()
{
    SDA=0;
    NOP();
    SCL=1;
    NOP();
    SCL=0;
    NOP();
}

//无响应
void No_Responds()
{
    SDA=1;
    NOP();
    SCL=1;
    NOP();
    SCL=0;
    NOP();
}
 
void Single_Write_BH1750(unsigned char reg_address)
{
		BH1750_Start();
		BH1750_Write_Byte(0x46);
		BH1750_Write_Byte(reg_address);
		BH1750_Stop();
}
 
void Multiple_Read_BH1750(void)
{
		unsigned char i;
		BH1750_Start();
		BH1750_Write_Byte(0x47);
		for(i=0;i<2;i++)                      //连续读取2个地址数据，存储中BUF
				{
						BUF[i]=BH1750_Read_Byte();    //BUF[0]存储0x32地址中的数据
						if (i == 1)
					 {
						 No_Responds();               //最后一个数据需要回NOACK
						}
					 else
					 { 
						 Responds();                	//回应ACK
					 }
			 }
				BH1750_Stop();                          //停止信号
				Delay(5);
}
 
//获得传感器的数据
float Get_BH1750_Data()
{
		 float temp;
		 EA=0;
		 BH1750_init();
		 Single_Write_BH1750(0x01);
		 Single_Write_BH1750(0x10);
		 Delay(180);
		 Multiple_Read_BH1750();
		 dis_data=BUF[0];
		 dis_data=(dis_data<<8)+BUF[1];					//合成数据，即光照数据
		 temp=(float)dis_data/1.2;
		 EA=1;
	   return temp; 
}
 



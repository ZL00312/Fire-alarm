#include"ADC0809.h"
#include<reg52.h>
#include"delay.h"
#include"uart.h"

sbit ADDA=P1^0;			   // 地址A
sbit ADDB=P1^1;			   //	地址B
sbit ADDC=P1^2;			   //	地址C
sbit START_ALE=P1^4;	 //	地址装载，转换启动脚
sbit OE=P1^5;			     //	输出使能
sbit EOC=P1^6;			   //	转换标志位

//ADC初始化
void ADC_Init()
{
   ADDA=0;
   ADDB=0;
   ADDC=0;
   START_ALE=0;
}


//ADC转换开始函数
void ADC_START()		  
{
	START_ALE=0;
	delay_us(2);
	START_ALE=1;				  //一个正脉冲
	delay_us(20);
	START_ALE=0;
	while(EOC==0);
	OE=1;
}

//获得模数转换后的数据
float Get_AdcData()
{
	unsigned int ADC_Data;
	 float temp;
   ADC_START();
   ADC_Data=P0;	
	 OE=0;
	 temp = (float)ADC_Data/51*1.0;
	 return temp;	 
}
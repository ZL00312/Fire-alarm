#include<stdio.h>
#include<reg52.h>
#include<intrins.h>
#include<uart.h>
#include"DS18B20.h"
#include"delay.h"
#include"ADC0809.h"
#include"time.h"
#include"BH1750FVI.h"

#define uint unsigned int
#define uchar unsigned char

//三个float存储数据
float temperature;
float smoke;
float light;

void main()
{
	uart_init();			//串口初始化
	Time_Init();			//定时器初始化
	ADC_Init();				//ADC初始化
	DS18B20_init();		//DS18B20初始化
	while(1)
	{		
		temperature=temper_change();		//获得转后的温度数据
		light = Get_BH1750_Data();			//获得光强数据
		smoke=Get_AdcData();						//获得ADC模数转化后的数据，即烟雾电压
		printf("temperature = %6.2f,light = %6.2f,smoke = %6.2f\r\n",temperature,light,smoke);		//串口发送
		delay_us(1000);									//延时
	}
}